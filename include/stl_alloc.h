#ifndef TTSTL_STL_ALLOC_H
#define TTSTL_STL_ALLOC_H

#include <cstdlib>

#  if !defined(_THROW_BAD_ALLOC)
#    include <iostream>
#    define _THROW_BAD_ALLOC std::cerr << "Out of memory" << std::endl; exit(1)
#  endif

namespace tt {

    class _malloc_alloc_template {
    private:
        /* oom: Out of memory */
        static void * oom_malloc(size_t sz);
        static void * oom_realloc(void *p, size_t new_size);
        static void (*_malloc_alloc_oom_handler)();

    public:
        static void * allocate (size_t sz) {
            void *mem = malloc(sz);
            if (mem == 0)
                return oom_malloc(sz);
            return mem;
        }

        static void deallocate(void *p, size_t /* sz */) {
            free(p);
        }

        static void * 
        reallcate(void *p, size_t /* old_size */, size_t new_size) {
            void *mem = realloc(p, new_size);
            if (mem == 0)
                return oom_realloc(p, new_size);
            return mem;
        }

        static void (*set_malloc_handler(void (*fun)()))() {
            void (*old_handler)() = _malloc_alloc_oom_handler;
            _malloc_alloc_oom_handler = fun;
            return old_handler;
        }
    };

    void (*_malloc_alloc_template::_malloc_alloc_oom_handler)() = 0;

    void * _malloc_alloc_template::oom_malloc(size_t sz) {
        while (true) {
            if (_malloc_alloc_oom_handler == 0) {
                _THROW_BAD_ALLOC;
            }
            _malloc_alloc_oom_handler();
            void *mem = malloc(sz);
            if (mem) return mem;
        }
    }

    void * _malloc_alloc_template::oom_realloc(void *p, size_t new_size) {
        while (true) {
            if (_malloc_alloc_oom_handler == 0) {
                _THROW_BAD_ALLOC;
            }
            _malloc_alloc_oom_handler();
            void *mem = realloc(p, new_size);
            if (mem) return mem;
        }
    }

    typedef _malloc_alloc_template malloc_alloc;

    /* ================= _default_alloc_template ================= */
    class _default_alloc_template {
    private:
        union obj {
            union obj * free_list_link;
            char client_data[1];
        };
        enum { _ALIGN = 8 };
        enum { _MAX_BYTES = 128 };
        enum { _NFREELIST = _MAX_BYTES / _ALIGN };

        static obj * volatile free_list[_NFREELIST];
        static char *start_free;
        static char *end_free;
        static size_t heap_size;

        /**
         * \return Minimum number(`N`) that satisfies: `N * _ALIGN >= n`
         */
        static size_t ROUND_UP(size_t n) { return (n + _ALIGN - 1) / _ALIGN; }

        /**
         * \return Mininum index of free_list that can hold `bytes` bytes.
         * \warning Make sure that `bytes` is larger than 0, 0 will cause error.
         */
        static size_t FREELIST_INDEX(size_t bytes) {
            return (bytes + _ALIGN - 1) / _ALIGN - 1;
        }

        /**
         * Get a `obj` can hold `n` bytes. Probably allocate new blocks to free_list.
         * \return First address of getted `obj`
         */
        static void * refill(size_t n);

        /**
         * Allocate memory of `nobjs * sz` bytes.
         * If `nobjs * sz` is too large to allocate, value of `nobjs` will be changed.
         * \return First address of getted memory.
         */
        static char * chunk_alloc(size_t sz, int &nobjs);

    public:
        static void * allocate(size_t sz);
        static void deallocate(void *p, size_t sz);
        static void * reallocate(void *p, size_t old_size, size_t new_size);
    };

    _default_alloc_template::obj * volatile 
        _default_alloc_template::free_list[_NFREELIST] = { 0 }; // TODO 考虑这里初始化会不会出问题
    char * _default_alloc_template::start_free = 0;
    char * _default_alloc_template::end_free   = 0;
    size_t _default_alloc_template::heap_size  = 0;

    void * _default_alloc_template::allocate(size_t sz) {
        if (sz == 0) return nullptr;

        if (sz > _MAX_BYTES) {
            return malloc_alloc::allocate(sz);
        }

        obj * volatile * my_free_list = free_list + FREELIST_INDEX(sz);
        if (*my_free_list == 0) {
            return refill(sz);
        }
        obj * result = *my_free_list;
        *my_free_list = result->free_list_link;
        return reinterpret_cast<void *>(result);
    }

    void _default_alloc_template::deallocate(void *p, size_t sz) {
        if (sz > _MAX_BYTES) {
            malloc_alloc::deallocate(p, sz);
            return;
        }

        obj * volatile * my_free_list = free_list + FREELIST_INDEX(sz);
        obj *node = reinterpret_cast<obj *>(p);
        node->free_list_link = *my_free_list;
        *my_free_list = node;
    }

    void * _default_alloc_template::reallocate(void *p, size_t old_size, 
                                               size_t new_size) {
        if (old_size > _MAX_BYTES && new_size > _MAX_BYTES) {
            return malloc_alloc::reallcate(p, old_size, new_size);
        } else {
            void *result = allocate(new_size);
            char *old_mem = reinterpret_cast<char *>(p);
            char *new_mem = reinterpret_cast<char *>(result);
            size_t sz = old_size < new_size ? old_size : new_size;
            for (int i = 0; i < sz; ++i) {
                *(new_mem + i) = *(old_mem + i);
            }
            malloc_alloc::deallocate(p, old_size);
            return result;
        }
    }

    void * _default_alloc_template::refill(size_t n) {
        int nobjs = 20;
        void *result = chunk_alloc(n, nobjs);
        if (nobjs == 1) {
            return result;
        }

        obj * volatile * my_free_list = free_list + FREELIST_INDEX(n);
        obj * next_obj = (obj *)((char *)(result) + n);
        *my_free_list = next_obj;
        obj * current_obj;
        for (int i = 1; i < nobjs - 1; ++i) {
            current_obj = next_obj;
            next_obj = reinterpret_cast<obj *>((char *)current_obj + n); // TODO 当n不是8的倍数的时候出问题
            current_obj->free_list_link = next_obj;
        }
        next_obj->free_list_link = 0;

        return result;
    }

    char * _default_alloc_template::chunk_alloc(size_t sz, int &nobjs) {
        size_t bytes_need = sz * nobjs;
        size_t bytes_left = end_free - start_free;
        char * result;

        if (bytes_left >= bytes_need) {
            result = start_free;
            start_free += bytes_need;
            return result;
        }
        if (bytes_left >= sz) {
            nobjs = bytes_left / sz;
            result = start_free;
            start_free += sz * nobjs;
            return result;
        }
        obj * volatile * my_free_list;
        if (bytes_left > 0) {
            /* TODO 这里bytes_left有没有可能不是_ALIGN的倍数，如果有可能的话，就不能这样算 */
            my_free_list = free_list + FREELIST_INDEX(bytes_left);
            obj * left_obj = reinterpret_cast<obj *>(start_free);
            left_obj->free_list_link = *my_free_list;
            *my_free_list = left_obj;
        }
        size_t bytes_to_get = bytes_need * 2 + (heap_size >> 4);
        char * mem = (char *)malloc(bytes_to_get);
        start_free = mem;
        if (mem == 0) {
            for (size_t t_sz = sz; t_sz < _MAX_BYTES; t_sz += _ALIGN) {
                my_free_list = free_list + FREELIST_INDEX(t_sz);
                if (*my_free_list != 0) {
                    start_free = reinterpret_cast<char *>(*my_free_list);
                    *my_free_list = (*my_free_list)->free_list_link;
                    end_free = start_free + FREELIST_INDEX(t_sz) * _ALIGN;
                    return chunk_alloc(sz, nobjs);
                }
            }
            end_free = 0;
            start_free = 
                reinterpret_cast<char *>(malloc_alloc::allocate(bytes_to_get));
        }
        heap_size += bytes_to_get;
        end_free = start_free + bytes_to_get;
        return chunk_alloc(sz, nobjs);
    }

    // TODO 发现_default_alloc_template最终没有释放内存池中的内存，所以先改用_malloc_alloc_template
    // typedef _default_alloc_template alloc;
    typedef _malloc_alloc_template alloc;

    template <typename T, typename Alloc = alloc>
    class simple_alloc {
    public:
        static T * allocate(size_t n) {
            return reinterpret_cast<T*>(Alloc::allocate(n * sizeof(T)));
        }

        static T * allocate() {
            return reinterpret_cast<T*>(Alloc::allocate(sizeof(T)));
        }

        static void deallocate(T *p, size_t n) {
            Alloc::deallocate(reinterpret_cast<void *>(p), n * sizeof(T));
        }

        static void deallocate(T *p) {
            Alloc::deallocate(reinterpret_cast<void *>(p), sizeof(T));
        }
    };
}

#endif /* TTSTL_STL_ALLOC_H */