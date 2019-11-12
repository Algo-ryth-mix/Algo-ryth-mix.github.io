template <class T, std::size_t A_N, std::size_t B_N, std::size_t C_N>
mat<T, A_N, B_N> operator*(const mat<T, A_N, C_N>& lhs, const mat<T, C_N, B_N>& rhs)
{
  #ifdef PIXL_HAS_SSESIMPLE
  #ifndef __linux__
  if constexpr(A_N == 4 && B_N == 4 && C_N == 4 && std::is_same<T,float>::value){
    if(InstructionSet::SSE()){
      return fast_mul4by4(lhs,rhs);
    }
  }
  else if constexpr (A_N == 2 && B_N == 2 && C_N == 2 && std::is_same<T,float>::value){
    if(InstructionSet::SSE()){
    return fast_mul2by2(lhs,rhs);
    }
  }
  #endif
  #endif

  mat<T, A_N, B_N> m;

  for (std::size_t i = 0; i < B_N; ++i) {
    for (std::size_t j = 0; j < A_N; ++j) {
      for (std::size_t k = 0; k < C_N; ++k)
      {
        m.data_md[i][j] += lhs.data_md[i][k] * rhs.data_md[k][j];
      }
    }
  }
  return m;
}
