/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mexBetweenessCentrality.h
 *
 * Code generation for function 'mexBetweenessCentrality'
 *
 */

#ifndef MEXBETWEENESSCENTRALITY_H
#define MEXBETWEENESSCENTRALITY_H

/* Include files */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mwmathutil.h"
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include "rtwtypes.h"
#include "mexBetweenessCentrality_types.h"

/* Function Declarations */
extern void mexBetweenessCentrality(const emlrtStack *sp, const struct0_T *V,
  const struct1_T *E, real_T color, const emxArray_boolean_T *vertFilterList,
  real_T location, const emxArray_real_T *r2sV, const emxArray_real_T *s2rV,
  const emxArray_boolean_T *nonLeafVerts, emxArray_real_T *betweenness);

#endif

/* End of code generation (mexBetweenessCentrality.h) */
