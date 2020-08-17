/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * nullAssignment.c
 *
 * Code generation for function 'nullAssignment'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "mexBetweenessCentrality.h"
#include "nullAssignment.h"
#include "mexBetweenessCentrality_emxutil.h"
#include "eml_int_forloop_overflow_check.h"
#include "mexBetweenessCentrality_data.h"

/* Variable Definitions */
static emlrtRSInfo kb_emlrtRSI = { 12, /* lineNo */
  "nullAssignment",                    /* fcnName */
  "A:\\MatlabR2017A\\toolbox\\eml\\eml\\+coder\\+internal\\nullAssignment.m"/* pathName */
};

static emlrtRSInfo lb_emlrtRSI = { 16, /* lineNo */
  "nullAssignment",                    /* fcnName */
  "A:\\MatlabR2017A\\toolbox\\eml\\eml\\+coder\\+internal\\nullAssignment.m"/* pathName */
};

static emlrtRSInfo mb_emlrtRSI = { 165,/* lineNo */
  "nullAssignment",                    /* fcnName */
  "A:\\MatlabR2017A\\toolbox\\eml\\eml\\+coder\\+internal\\nullAssignment.m"/* pathName */
};

static emlrtRSInfo nb_emlrtRSI = { 167,/* lineNo */
  "nullAssignment",                    /* fcnName */
  "A:\\MatlabR2017A\\toolbox\\eml\\eml\\+coder\\+internal\\nullAssignment.m"/* pathName */
};

static emlrtRSInfo ob_emlrtRSI = { 170,/* lineNo */
  "nullAssignment",                    /* fcnName */
  "A:\\MatlabR2017A\\toolbox\\eml\\eml\\+coder\\+internal\\nullAssignment.m"/* pathName */
};

static emlrtRSInfo pb_emlrtRSI = { 257,/* lineNo */
  "nullAssignment",                    /* fcnName */
  "A:\\MatlabR2017A\\toolbox\\eml\\eml\\+coder\\+internal\\nullAssignment.m"/* pathName */
};

static emlrtRSInfo qb_emlrtRSI = { 130,/* lineNo */
  "nullAssignment",                    /* fcnName */
  "A:\\MatlabR2017A\\toolbox\\eml\\eml\\+coder\\+internal\\nullAssignment.m"/* pathName */
};

static emlrtRTEInfo q_emlrtRTEI = { 1, /* lineNo */
  14,                                  /* colNo */
  "nullAssignment",                    /* fName */
  "A:\\MatlabR2017A\\toolbox\\eml\\eml\\+coder\\+internal\\nullAssignment.m"/* pName */
};

static emlrtRTEInfo s_emlrtRTEI = { 163,/* lineNo */
  9,                                   /* colNo */
  "nullAssignment",                    /* fName */
  "A:\\MatlabR2017A\\toolbox\\eml\\eml\\+coder\\+internal\\nullAssignment.m"/* pName */
};

static emlrtRTEInfo bb_emlrtRTEI = { 179,/* lineNo */
  9,                                   /* colNo */
  "nullAssignment",                    /* fName */
  "A:\\MatlabR2017A\\toolbox\\eml\\eml\\+coder\\+internal\\nullAssignment.m"/* pName */
};

static emlrtRTEInfo cb_emlrtRTEI = { 83,/* lineNo */
  27,                                  /* colNo */
  "nullAssignment",                    /* fName */
  "A:\\MatlabR2017A\\toolbox\\eml\\eml\\+coder\\+internal\\nullAssignment.m"/* pName */
};

/* Function Definitions */
void nullAssignment(const emlrtStack *sp, emxArray_real_T *x, const
                    emxArray_int32_T *idx)
{
  boolean_T overflow;
  int32_T k;
  boolean_T exitg1;
  emxArray_boolean_T *b;
  int32_T nxin;
  int32_T nrowx;
  int32_T k0;
  int32_T nxout;
  emxArray_real_T *b_x;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b(sp);
  st.site = &kb_emlrtRSI;
  overflow = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= idx->size[1] - 1)) {
    if ((idx->data[k] < 1) || (idx->data[k] > x->size[0])) {
      overflow = false;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (!overflow) {
    emlrtErrorWithMessageIdR2012b(&st, &cb_emlrtRTEI,
      "MATLAB:subsdeldimmismatch", 0);
  }

  emxInit_boolean_T1(&st, &b, 2, &s_emlrtRTEI, true);
  st.site = &lb_emlrtRSI;
  nxin = x->size[0];
  nrowx = x->size[0];
  b_st.site = &mb_emlrtRSI;
  k0 = b->size[0] * b->size[1];
  b->size[0] = 1;
  b->size[1] = x->size[0];
  emxEnsureCapacity(&b_st, (emxArray__common *)b, k0, sizeof(boolean_T),
                    &q_emlrtRTEI);
  nxout = x->size[0];
  for (k0 = 0; k0 < nxout; k0++) {
    b->data[k0] = false;
  }

  c_st.site = &pb_emlrtRSI;
  overflow = ((!(1 > idx->size[1])) && (idx->size[1] > 2147483646));
  if (overflow) {
    d_st.site = &y_emlrtRSI;
    check_forloop_overflow_error(&d_st);
  }

  for (k = 1; k <= idx->size[1]; k++) {
    b->data[idx->data[k - 1] - 1] = true;
  }

  b_st.site = &nb_emlrtRSI;
  k0 = 0;
  c_st.site = &qb_emlrtRSI;
  overflow = ((!(1 > b->size[1])) && (b->size[1] > 2147483646));
  if (overflow) {
    d_st.site = &y_emlrtRSI;
    check_forloop_overflow_error(&d_st);
  }

  for (k = 1; k <= b->size[1]; k++) {
    k0 += b->data[k - 1];
  }

  nxout = x->size[0] - k0;
  k0 = -1;
  b_st.site = &ob_emlrtRSI;
  overflow = ((!(1 > x->size[0])) && (x->size[0] > 2147483646));
  if (overflow) {
    c_st.site = &y_emlrtRSI;
    check_forloop_overflow_error(&c_st);
  }

  for (k = 1; k <= nxin; k++) {
    if ((k > b->size[1]) || (!b->data[k - 1])) {
      k0++;
      x->data[k0] = x->data[k - 1];
    }
  }

  emxFree_boolean_T(&b);
  if (!(nxout <= nrowx)) {
    emlrtErrorWithMessageIdR2012b(&st, &bb_emlrtRTEI,
      "Coder:builtins:AssertionFailed", 0);
  }

  if (1 > nxout) {
    nxout = 0;
  }

  emxInit_real_T(&st, &b_x, 1, &q_emlrtRTEI, true);
  k0 = b_x->size[0];
  b_x->size[0] = nxout;
  emxEnsureCapacity(&st, (emxArray__common *)b_x, k0, sizeof(real_T),
                    &q_emlrtRTEI);
  for (k0 = 0; k0 < nxout; k0++) {
    b_x->data[k0] = x->data[k0];
  }

  k0 = x->size[0];
  x->size[0] = b_x->size[0];
  emxEnsureCapacity(&st, (emxArray__common *)x, k0, sizeof(real_T), &q_emlrtRTEI);
  nxout = b_x->size[0];
  for (k0 = 0; k0 < nxout; k0++) {
    x->data[k0] = b_x->data[k0];
  }

  emxFree_real_T(&b_x);
  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

/* End of code generation (nullAssignment.c) */
