#ifndef STL_ALGOBASE_H
#define STL_ALGOBASE_H

namespace tt {
template<typename InputIterator, typename OutputIterator>
OutputIterator copy(InputIterator first,
                    InputIterator last,
                    OutputIterator result) {

}

template<typename ForwardIterator, typename T>
void fill(ForwardIterator first, ForwardIterator last, const T &x) {

}

template<typename OutputIterator, typename Size, typename T>
OutputIterator fill_n(OutputIterator first, Size n, const T &x) {

}

template<typename InputIterator, typename Size, typename OutputIterator>
OutputIterator copy_n(InputIterator first, Size n, OutputIterator result) {

}
} // namespace tt

#endif // STL_ALGOBASE_H