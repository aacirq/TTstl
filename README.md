# TTstl

看《STL源码剖析》和部分g++源码，自己尝试模仿实现。g++版本为：g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0

文件及内容：

- stl_iterator_base_types.h

定义了5种iterator category，`iterator_traits`，及迭代器定义模板`iterator`。


- stl_iterator_base_funcs.h

定义了4个对迭代器操作的函数`distance(first, last)`, `advance(itr, n)`, `next(itr, n=1)`, `prev(itr, n=1)`。

