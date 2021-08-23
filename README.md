# TTstl

看《STL源码剖析》和部分g++源码，自己尝试模仿实现。g++版本为：g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0

文件及内容：

- stl_iterator_base_types.h

    定义了5种迭代器类型(`iterator_category`)，`iterator_traits`，及迭代器定义模板`iterator`。


- stl_iterator_base_funcs.h

    定义了4个对迭代器操作的函数`distance(first, last)`, `advance(itr, n)`, `next(itr, n=1)`, `prev(itr, n=1)`。


- type_traits.h

    定义了type_traits，包括4个判定类型

    1. `has_trivial_default_constructor`
    2. `has_trivial_copy_constructor`
    3. `has_trivial_assignment_operator`
    4. `has_trivial_destructor`
    5. `is_POD_type`

    用来帮助代码提速。


- stl_uninitialized.h

    定义了内存构造的函数，包括：

    1. `ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)`
    2. `void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T &x)`
    3. `ForwardIterator uninitialized_copy_n(InputIterator first, Size count, ForwardIterator result)`
    4. `ForwardIterator uninitialized_fill_n(ForwardIterator first, Size count, const T &x)`


- stl_algobase.h

