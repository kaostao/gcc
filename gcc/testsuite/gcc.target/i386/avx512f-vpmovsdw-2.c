/* { dg-do run } */
/* { dg-options "-O2 -mavx512f" } */
/* { dg-require-effective-target avx512f } */

#define AVX512F

#include "avx512f-helper.h"

#define SIZE (AVX512F_LEN / 32)
#include "avx512f-mask-type.h"
#define SIZE_HALF (AVX512F_LEN_HALF / 16)
#include <limits.h>

CALC (short *r, int *s)
{
  int i;
  for (i = 0; i < SIZE_HALF; i++)
    {
      if (s[i] < SHRT_MIN)
	r[i] = SHRT_MIN;
      else if (s[i] > SHRT_MAX)
	r[i] = SHRT_MAX;
      else
	r[i] = s[i];
      r[i] = (i < SIZE) ? r[i] : 0;
    }
}

void static
TEST (void)
{
  int i, sign;
  UNION_TYPE (AVX512F_LEN_HALF, i_w) res1, res2, res3;
  UNION_TYPE (AVX512F_LEN, i_d) src;
  MASK_TYPE mask = MASK_VALUE;
  short res_ref[SIZE_HALF];

  sign = -1;
  for (i = 0; i < SIZE; i++)
    {
      src.a[i] = 1 + 34 * i * sign;
      sign = sign * -1;
      res2.a[i] = DEFAULT_VALUE;
    }

  res1.x = INTRINSIC (_cvtsepi32_epi16) (src.x);
  res2.x = INTRINSIC (_mask_cvtsepi32_epi16) (res2.x, mask, src.x);
  res3.x = INTRINSIC (_maskz_cvtsepi32_epi16) (mask, src.x);

  CALC (res_ref, src.a);

  if (UNION_CHECK (AVX512F_LEN_HALF, i_w) (res1, res_ref))
    abort ();

  MASK_MERGE (i_w) (res_ref, mask, SIZE);
  if (UNION_CHECK (AVX512F_LEN_HALF, i_w) (res2, res_ref))
    abort ();

  MASK_ZERO (i_w) (res_ref, mask, SIZE);
  if (UNION_CHECK (AVX512F_LEN_HALF, i_w) (res3, res_ref))
    abort ();
}
