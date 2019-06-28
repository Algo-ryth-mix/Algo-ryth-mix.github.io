/**@brief this constructor takes exactly as many values as the matrix needs to be fully defined via nested initializer lists. e.g.:
 * @code
 * mat2f m0=
 * {
 *	{ 2.0f,1.0f },
 *	{ 3.0f,2.0f }
 * };
 * @endcode
 */
template <typename Indices = std::make_index_sequence<dimensions_.first>>
mat(std::initializer_list<std::array<T, dimensions_.second>>&& list) : mat(std::forward<std::initializer_list<std::array<T, dimensions_.second>>>(list), Indices{})
{}

/// support constructors for @code mat(std::initializer_list<std::array<T, dimensions_.second>>&& list) @endcode
private:
template<std::size_t... I>
mat(std::initializer_list<std::array<T, dimensions_.second>>&& list, std::index_sequence<I...>) :
  mat(
    std::forward<std::initializer_list<std::array<T, dimensions_.second>>>(list),
    std::forward<typename std::initializer_list<std::array<T, dimensions_.second>>::const_iterator>(list.begin() + I)...
  )
{}

template<typename... Values>
mat(std::initializer_list<std::array<T, dimensions_.second>>&& list, Values... values) :
  data_md{ list.size() == dimensions_.first ? *values : throw std::logic_error("LINT_ASM:ERR_ cannot create matrix from too little arguments! "s + __FILE__ + std::to_string(__LINE__))... }
{}
