#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>

#include <new>

namespace {

template <typename T>
class allocator {
 public:
  typedef T value_type;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef T &reference;
  typedef const T &const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  template <typename T1>
  struct rebind {
    typedef allocator<T1> other;
  };

  allocator() {}
  allocator(const allocator &) {}
  template <typename U>
  allocator(const allocator<U> &) {}

  ~allocator() {}

  pointer address(reference x) const noexcept {
    return reinterpret_cast<pointer>(&x);
  }

  const_pointer address(const_pointer x) const noexcept {
    return reinterpret_cast<const_pointer>(&x);
  }

  pointer allocate(size_type n, const void *p = static_cast<const void *>(0)) {
    return static_cast<pointer>(::operator new(n * sizeof(T)));
  }

  void deallocate(pointer p, size_type n) { ::operator delete(p); }

  size_type max_size() const noexcept {
    return static_cast<size_t>(-1) / sizeof(T);
  }

  void construct(pointer p, const T &x) { new (p) T(x); }

  template <typename U>
  void destroy(U *p) {
    p->~U();
  }
};  // class allocator

}  // namespace

#endif  // ALLOCATOR_H
