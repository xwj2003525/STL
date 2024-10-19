#pragma once

#include <cstddef>
#include <cstdlib>

template <int inst> class __malloc_alloc_template {
private:
  // oom : out of memmory
  static void *oom_malloc(size_t);
  static void *oom_realloc(void *, size_t);
  static void (*__malloc_alloc_oom_hander)();

  // 变量__malloc_alloc_oom_hander = void (*)()
  // (*) 表示函数指针

public:
  static void *allocate(size_t n) {
    void *ret = malloc(n);

    // 内存不足处理
    if (0 == ret)
      ret = oom_malloc(n);
    return ret;
  }

  static void deallocate(void *p, size_t) { free(p); }

  static void *reallocate(void *p, size_t, size_t new_s) {
    void *ret = realloc(p, new_s);
    if (0 == ret)
      ret = oom_realloc(p, new_s);
    return ret;
  }

  // 模拟c++ ：：opeartor new的hander
  // 一个名为set_malloc_hander的函数，返回为 void () 函数指针，参数为(void
  // (*f)()),接受一个函数指针 为void ()类型
  static void (*set_malloc_hander(void (*f)()))() {
    void (*old)() = __malloc_alloc_oom_hander;
    __malloc_alloc_oom_hander = f;
    return (old);
  }
};

//不设置默认的oom处理函数
template <int inst>
void (*__malloc_alloc_template<inst>::__malloc_alloc_oom_hander)() = 0;

template <int inst> void *__malloc_alloc_template<inst>::oom_malloc(size_t n) {
  void (*oom)();
  void *ret;

  while (1) {
    oom = __malloc_alloc_oom_hander;
    //没有oom处理函数
    if (0 == oom) {
      //__THROW_BAD_ALLOC;
      exit(1);
    }
    //运行oom处理函数, 进行某些不必要内存释放，然后重新分配
    (*oom)();
    ret = malloc(n);
    if (ret)
      return (ret);
  }
}

template <int inst>
void *__malloc_alloc_template<inst>::oom_realloc(void *p, size_t n) {
  void (*oom)();
  void *ret;

  while (1) {
    oom = __malloc_alloc_oom_hander;
    //没有oom处理函数
    if (0 == oom) {
      //__THROW_BAD_ALLOC;
      exit(1);
    }
    //运行oom处理函数, 进行某些不必要内存释放，然后重新分配
    (*oom)();
    ret = realloc(p, n);
    if (ret)
      return (ret);
  }
}

typedef __malloc_alloc_template<0> malloc_alloc;

// 当内存分配超过128B，使用malloc_alloc;
// 小于128B，使用下面
//
//
//

enum { __ALIGN = 8 };
enum { __MAX_BYTES = 128 };
enum { __FREELISTS = __MAX_BYTES / __ALIGN };

template <int inst> class __default_alloc_template {
private:
  // 向上分配一个最近的大小 如6->8 11->16 20->24
  static size_t ROUND_UP(size_t bytes) {
    if (bytes == 0)
      return 8;
    return (bytes % 8 == 0) ? (bytes) : ((bytes / 8) + 1) * 8;
  }

  union obj {
    union obj *free_list_link;
    char clinet_data[1];
  };

  // volatile表示多线程环境下的变量
  static obj *volatile free_list[__FREELISTS];

  //从1开始算，1-16块free_list
  static size_t FREELIST_INDEX(size_t bytes) { return ROUND_UP(bytes) / 8 - 1; }

  static void *refill(size_t n);

  static char *chunk_alloc(size_t size, int &nobjs);

  static char *start_free;
  static char *end_free;
  static size_t heap_size;

public:
  static void *allocate(size_t n) {

    // free_list数组里面每个元素是一个指针，用二维数组
    obj *volatile *fl;
    obj *ret;

    // 超过128B，使用malloc_alloc分配
    if (n > (size_t)__MAX_BYTES) {
      return (malloc_alloc::allocate(n));
    }

    //寻找适合的一组链表
    fl = free_list + FREELIST_INDEX(n);
    ret = *fl;

    // 没有挂载链表，创建一个
    if (0 == ret) {
      void *r = refill(ROUND_UP(n));
      return r;
    }

    // 返回合适的链表
    *fl = ret->free_list_link;
    return (ret);
  }

  static void deallocate(void *p, size_t n) {
    if (!p)
      return;

    obj *q = (obj *)p;
    obj *volatile *fl;

    if (n > (size_t)__MAX_BYTES) {
      malloc_alloc::deallocate(p, n);
      return;
    }

    fl = free_list + FREELIST_INDEX(n);

    // 头插法，入链表
    q->free_list_link = *fl;
    *fl = q;
  }

  static void *reallocate(void *p, size_t old, size_t new_sz);
};

template <int inst> char *__default_alloc_template<inst>::start_free = 0;

template <int inst> char *__default_alloc_template<inst>::end_free = 0;

template <int inst> size_t __default_alloc_template<inst>::heap_size = 0;

template <int inst>
typename __default_alloc_template<inst>::obj
    *volatile __default_alloc_template<inst>::free_list[__FREELISTS] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// 没有空闲了，通过内存池调用,期望分配20个n大小的连续内存
template <int inst> void *__default_alloc_template<inst>::refill(size_t n) {
  int nojs = 20;
  char *chunk = chunk_alloc(n, nojs);
  obj *volatile *fl;
  obj *ret;
  obj *current_obj, *next_obj;
  int i;

  // chunk不给力，只分配一个，直接给用户，而不是添加到链表中
  if (1 == nojs) {
    return (chunk);
  }

  fl = free_list + FREELIST_INDEX(n);

  // 第一块直接返回给用户,不入链表
  ret = (obj *)chunk;

  // 从第二块开始入链表
  *fl = next_obj = (obj *)(chunk + n);

  // 把剩余分配的连续内存连成链表
  for (i = 1; i < nojs; i++) {
    current_obj = next_obj;

    // 移动n个B，char总是表示n个B
    next_obj = (obj *)((char *)next_obj + n);

    // 到末尾了
    if (nojs - 1 == i) {
      current_obj->free_list_link = 0;
      break;
    } else {
      current_obj->free_list_link = next_obj;
    }
  }

  return (ret);
}

// 内存池，chunck分配给第二分配器

template <int inst>
char *__default_alloc_template<inst>::chunk_alloc(size_t size, int &n) {
  char *ret;
  size_t B_require_n = size * n;
  size_t B_require_one = size;
  size_t B_left = end_free - start_free;

  if (B_left >= B_require_n) {
    ret = start_free;
    start_free += B_require_n;
    return (ret);
  } else if (B_left >= B_require_one) {
    n = B_left / B_require_one;
    ret = start_free;
    start_free += n * B_require_one;
    return (ret);
  } else {
    //?
    size_t B_alloc = 2 * B_require_n + ROUND_UP(heap_size >> 4);
    if (B_left > 0) {
      obj *volatile *fl = free_list + FREELIST_INDEX(B_left);
      ((obj *)start_free)->free_list_link = *fl;
      *fl = (obj *)start_free;
    }

    start_free = (char *)malloc(B_alloc);
    if (0 == start_free) {
      int i;
      obj *volatile *fl, *p;
      for (i = size; i <= __MAX_BYTES; i += __ALIGN) {
        fl = free_list + FREELIST_INDEX(i);
        p = *fl;
        if (!p) {
          *fl = p->free_list_link;
          start_free = (char *)p;
          end_free = start_free + i;
          return (chunk_alloc(size, n));
        }
      }

      end_free = 0;
      start_free = (char *)malloc_alloc::allocate(B_alloc);
    }

    heap_size += B_alloc;
    end_free = start_free + B_alloc;
    return (chunk_alloc(size, n));
  }
}

typedef __default_alloc_template<0> default_alloc;
