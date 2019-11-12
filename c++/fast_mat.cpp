PIXL_NODISCARD PIXL_ALWAYS_INLINE static mat<float, 4, 4> fast_mul4by4(const mat<float, 4, 4>& lhs, const mat<float, 4, 4>& rhs)
{
  //load the rhs mat into 4 components
  const __m128 BCx = _mm_load_ps(rhs.data);
  const __m128 BCy = _mm_load_ps(rhs.data + 0x4);
  const __m128 BCz = _mm_load_ps(rhs.data + 0x8);
  const __m128 BCw = _mm_load_ps(rhs.data + 0xC);


  mat<float, 4, 4> res;

  //prepare some iterators
  const float* lhs_row_ptr = lhs.data;
  float * res_row_ptr = res.data;

  for (size_t i = 0; i < 4; ++i, lhs_row_ptr += 4, res_row_ptr += 4) {

    //extract single row elements
    __m128 ARx = _mm_set1_ps(lhs_row_ptr[0]);
    __m128 ARy = _mm_set1_ps(lhs_row_ptr[1]);
    __m128 ARz = _mm_set1_ps(lhs_row_ptr[2]);
    __m128 ARw = _mm_set1_ps(lhs_row_ptr[3]);

    //multiply whole rows
    __m128 X = ARx * BCx;
    __m128 Y = ARy * BCy;
    __m128 Z = ARz * BCz;
    __m128 W = ARw * BCw;

    //add all
    __m128 R = X + Y + Z + W;

    //store in result pointer
    _mm_store_ps(res_row_ptr,R);
  }
  return res;
}

//vs

//generic mat multiplication
template <class T, std::size_t A_N, std::size_t B_N, std::size_t C_N>
mat<T, A_N, B_N> unoptimized_mul(const mat<T, A_N, C_N>& lhs, const mat<T, C_N, B_N>& rhs)
{
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
