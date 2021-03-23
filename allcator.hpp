//
// Created by aacirq.
//

#include <cstddef>

#ifndef TTSTL_ALLCATOR_HPP
#define TTSTL_ALLCATOR_HPP
namespace tt {
    template<typename T>
    inline T *_allocate(ptrdiff_t n, T *) {
        std::set_new_handler(0);
        T *mem = (T *) (::operator new(n * sizeof(T)));
        if (mem == 0) {
            std::cerr << "Out of memory." << std::endl;
            exit(1);
        }

        return mem;
    }

    template<typename T>
    inline void _deallocate(T *mem) {
        ::operator delete(mem);
    }

    template<typename T1, typename T2>
    inline void _construct(T1 *mem, const T2 &value) {
        new(mem) T1(value);
    }

    template<typename T>
    inline void _destroy(T *mem) {
        mem->~T();
    }

    template<class T>
    class allocator {
    public:
        typedef T          value_type;
        typedef T *        pointer;
        typedef const T *  const_pointer;
        typedef T &        reference;
        typedef const T &  const_reference;
        typedef size_t     size_type;
        typedef ptrdiff_t  difference_type;

        T *allocate(size_type size, const void *hint = 0) {
            return _allocate((difference_type) size, (pointer) 0);
        }

        void deallocate(pointer mem, size_type n) {
            // size_type形参是为了满足STL对allocator类的调用标准
            _deallocate(mem);
        }

        void construct(pointer mem, const_reference value) {
            _construct(mem, value);
        }

        void destroy(pointer mem) {
            _destroy(mem);
        }

        pointer address(reference value) {
            return (pointer) &value;
        }

        const_pointer const_address(const_reference value) {
            return (const_pointer) &value;
        }

        size_type max_size() {
            return (size_type) (UINT32_MAX / sizeof(value_type));
        }
    };
}

#endif //TTSTL_ALLCATOR_HPP
