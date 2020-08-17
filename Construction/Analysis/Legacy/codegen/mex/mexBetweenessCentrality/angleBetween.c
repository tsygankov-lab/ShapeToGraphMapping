/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * angleBetween.c
 *
 * Code generation for function 'angleBetween'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "mexBetweenessCentrality.h"
#include "angleBetween.h"
#include "norm.h"

/* Function Definitions */
real_T angleBetween(real_T dir1[2], real_T dir2[2])
{
  real_T approx;
  real_T mag1;
  real_T mag2;
  int32_T i0;

  /* <2 - approaxing antiparallel */
  /* 1 - 90 degree angle */
  /* 0 - Parallel */
  /* -1 - 270 degree angle */
  /* -2 - antiparallel */
  /* assumes vectors are normalized already */
  mag1 = norm(dir1);
  mag2 = norm(dir2);
  if (mag2 < 2.2204460492503131E-14) {
    /* change to dynamic */
    approx = 0.0;
  } else {
    for (i0 = 0; i0 < 2; i0++) {
      dir1[i0] /= mag1;
      dir2[i0] /= mag2;
    }

    mag1 = dir1[0] * dir2[1] - dir1[1] * dir2[0];

    /* Orientation calculation */
    mag2 = dir1[0] * dir2[0] + dir1[1] * dir2[1];

    /* Dot product */
    /* This calculates tan(theta) and pushes it closer to the extreme if the */
    /* angle is lower than 90 or above 270.  If you are not comfortable with */
    /* this, you may use the commented out version instead. */
    if (mag1 == 0.0) {
      approx = 0.0 - (real_T)(mag2 < 2.2204460492503131E-16) * 2.0;
    } else {
      approx = mag1 + (real_T)(mag2 < 2.2204460492503131E-16) * (2.0 * (1.0 -
        muDoubleScalarAbs(mag1)) * muDoubleScalarSign(mag1));
    }
  }

  /*  approx = atan2d(dir1(1)*dir2(2) - dir1(2)*dir2(1),dir1(1)*dir2(1) + dir1(2)*dir2(2)); */
  return approx;
}

/* End of code generation (angleBetween.c) */
