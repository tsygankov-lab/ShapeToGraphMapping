/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_mexBetweenessCentrality_api.c
 *
 * Code generation for function '_coder_mexBetweenessCentrality_api'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "mexBetweenessCentrality.h"
#include "_coder_mexBetweenessCentrality_api.h"
#include "mexBetweenessCentrality_emxutil.h"
#include "mexBetweenessCentrality_data.h"

/* Variable Definitions */
static emlrtRTEInfo r_emlrtRTEI = { 1, /* lineNo */
  1,                                   /* colNo */
  "_coder_mexBetweenessCentrality_api",/* fName */
  ""                                   /* pName */
};

/* Function Declarations */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, struct0_T *y);
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y);
static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y);
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y);
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *V, const
  char_T *identifier, struct0_T *y);
static const mxArray *emlrt_marshallOut(const emxArray_real_T *u);
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y);
static real_T g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *E, const
  char_T *identifier, struct1_T *y);
static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, struct1_T *y);
static real_T j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *color,
  const char_T *identifier);
static void k_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *vertFilterList, const char_T *identifier, emxArray_boolean_T *y);
static void l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_boolean_T *y);
static void m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *r2sV, const
  char_T *identifier, emxArray_real_T *y);
static void n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y);
static void o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret);
static void p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret);
static void q_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret);
static void r_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret);
static real_T s_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static void t_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_boolean_T *ret);
static void u_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret);

/* Function Definitions */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, struct0_T *y)
{
  emlrtMsgIdentifier thisId;
  static const char * fieldNames[10] = { "pos", "rad", "borderRegions",
    "vertexCoorID", "locationType", "degree", "edgeIDList", "color", "infinite",
    "length" };

  static const int32_T dims = 0;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(sp, parentId, u, 10, fieldNames, 0U, &dims);
  thisId.fIdentifier = "pos";
  c_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "pos")),
                     &thisId, y->pos);
  thisId.fIdentifier = "rad";
  d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "rad")),
                     &thisId, y->rad);
  thisId.fIdentifier = "borderRegions";
  c_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0,
    "borderRegions")), &thisId, y->borderRegions);
  thisId.fIdentifier = "vertexCoorID";
  d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "vertexCoorID")),
                     &thisId, y->vertexCoorID);
  thisId.fIdentifier = "locationType";
  d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "locationType")),
                     &thisId, y->locationType);
  thisId.fIdentifier = "degree";
  d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "degree")),
                     &thisId, y->degree);
  thisId.fIdentifier = "edgeIDList";
  e_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "edgeIDList")),
                     &thisId, y->edgeIDList);
  thisId.fIdentifier = "color";
  f_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "color")),
                     &thisId, y->color);
  thisId.fIdentifier = "infinite";
  d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "infinite")),
                     &thisId, y->infinite);
  thisId.fIdentifier = "length";
  y->length = g_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0,
    "length")), &thisId);
  emlrtDestroyArray(&u);
}

static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y)
{
  o_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y)
{
  p_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y)
{
  q_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *V, const
  char_T *identifier, struct0_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(sp, emlrtAlias(V), &thisId, y);
  emlrtDestroyArray(&V);
}

static const mxArray *emlrt_marshallOut(const emxArray_real_T *u)
{
  const mxArray *y;
  const mxArray *m1;
  static const int32_T iv2[1] = { 0 };

  y = NULL;
  m1 = emlrtCreateNumericArray(1, iv2, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m1, (void *)&u->data[0]);
  emlrtSetDimensions((mxArray *)m1, u->size, 1);
  emlrtAssign(&y, m1);
  return y;
}

static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y)
{
  r_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static real_T g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = s_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *E, const
  char_T *identifier, struct1_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  i_emlrt_marshallIn(sp, emlrtAlias(E), &thisId, y);
  emlrtDestroyArray(&E);
}

static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, struct1_T *y)
{
  emlrtMsgIdentifier thisId;
  static const char * fieldNames[10] = { "twinID", "edgeType", "origin", "dist",
    "dir", "obj", "color", "controlPoint", "faceID", "length" };

  static const int32_T dims = 0;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(sp, parentId, u, 10, fieldNames, 0U, &dims);
  thisId.fIdentifier = "twinID";
  d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "twinID")),
                     &thisId, y->twinID);
  thisId.fIdentifier = "edgeType";
  d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "edgeType")),
                     &thisId, y->edgeType);
  thisId.fIdentifier = "origin";
  c_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "origin")),
                     &thisId, y->origin);
  thisId.fIdentifier = "dist";
  d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "dist")),
                     &thisId, y->dist);
  thisId.fIdentifier = "dir";
  c_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "dir")),
                     &thisId, y->dir);
  thisId.fIdentifier = "obj";
  d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "obj")),
                     &thisId, y->obj);
  thisId.fIdentifier = "color";
  d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "color")),
                     &thisId, y->color);
  thisId.fIdentifier = "controlPoint";
  c_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "controlPoint")),
                     &thisId, y->controlPoint);
  thisId.fIdentifier = "faceID";
  d_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0, "faceID")),
                     &thisId, y->faceID);
  thisId.fIdentifier = "length";
  y->length = g_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2013a(sp, u, 0,
    "length")), &thisId);
  emlrtDestroyArray(&u);
}

static real_T j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *color,
  const char_T *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = g_emlrt_marshallIn(sp, emlrtAlias(color), &thisId);
  emlrtDestroyArray(&color);
  return y;
}

static void k_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *vertFilterList, const char_T *identifier, emxArray_boolean_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  l_emlrt_marshallIn(sp, emlrtAlias(vertFilterList), &thisId, y);
  emlrtDestroyArray(&vertFilterList);
}

static void l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_boolean_T *y)
{
  t_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *r2sV, const
  char_T *identifier, emxArray_real_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  n_emlrt_marshallIn(sp, emlrtAlias(r2sV), &thisId, y);
  emlrtDestroyArray(&r2sV);
}

static void n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y)
{
  u_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret)
{
  static const int32_T dims[2] = { -1, 2 };

  const boolean_T bv0[2] = { true, false };

  int32_T iv3[2];
  int32_T i1;
  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims, &bv0[0],
    iv3);
  i1 = ret->size[0] * ret->size[1];
  ret->size[0] = iv3[0];
  ret->size[1] = iv3[1];
  emxEnsureCapacity(sp, (emxArray__common *)ret, i1, sizeof(real_T),
                    (emlrtRTEInfo *)NULL);
  emlrtImportArrayR2015b(sp, src, ret->data, 8, false);
  emlrtDestroyArray(&src);
}

static void p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret)
{
  static const int32_T dims[1] = { -1 };

  const boolean_T bv1[1] = { true };

  int32_T iv4[1];
  int32_T i2;
  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 1U, dims, &bv1[0],
    iv4);
  i2 = ret->size[0];
  ret->size[0] = iv4[0];
  emxEnsureCapacity(sp, (emxArray__common *)ret, i2, sizeof(real_T),
                    (emlrtRTEInfo *)NULL);
  emlrtImportArrayR2015b(sp, src, ret->data, 8, false);
  emlrtDestroyArray(&src);
}

static void q_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret)
{
  static const int32_T dims[2] = { -1, 4 };

  const boolean_T bv2[2] = { true, false };

  int32_T iv5[2];
  int32_T i3;
  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims, &bv2[0],
    iv5);
  i3 = ret->size[0] * ret->size[1];
  ret->size[0] = iv5[0];
  ret->size[1] = iv5[1];
  emxEnsureCapacity(sp, (emxArray__common *)ret, i3, sizeof(real_T),
                    (emlrtRTEInfo *)NULL);
  emlrtImportArrayR2015b(sp, src, ret->data, 8, false);
  emlrtDestroyArray(&src);
}

static void r_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret)
{
  static const int32_T dims[2] = { -1, 3 };

  const boolean_T bv3[2] = { true, false };

  int32_T iv6[2];
  int32_T i4;
  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims, &bv3[0],
    iv6);
  i4 = ret->size[0] * ret->size[1];
  ret->size[0] = iv6[0];
  ret->size[1] = iv6[1];
  emxEnsureCapacity(sp, (emxArray__common *)ret, i4, sizeof(real_T),
                    (emlrtRTEInfo *)NULL);
  emlrtImportArrayR2015b(sp, src, ret->data, 8, false);
  emlrtDestroyArray(&src);
}

static real_T s_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, &dims);
  ret = *(real_T *)mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static void t_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_boolean_T *ret)
{
  static const int32_T dims[1] = { -1 };

  const boolean_T bv4[1] = { true };

  int32_T iv7[1];
  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "logical", false, 1U, dims, &bv4[0],
    iv7);
  ret->size[0] = iv7[0];
  ret->allocatedSize = ret->size[0];
  ret->data = (boolean_T *)mxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

static void u_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret)
{
  static const int32_T dims[1] = { -1 };

  const boolean_T bv5[1] = { true };

  int32_T iv8[1];
  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 1U, dims, &bv5[0],
    iv8);
  ret->size[0] = iv8[0];
  ret->allocatedSize = ret->size[0];
  ret->data = (real_T *)mxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

void mexBetweenessCentrality_api(const mxArray * const prhs[8], const mxArray
  *plhs[1])
{
  struct0_T V;
  struct1_T E;
  emxArray_boolean_T *vertFilterList;
  emxArray_real_T *r2sV;
  emxArray_real_T *s2rV;
  emxArray_boolean_T *nonLeafVerts;
  emxArray_real_T *betweenness;
  real_T color;
  real_T location;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInitStruct_struct0_T(&st, &V, &r_emlrtRTEI, true);
  emxInitStruct_struct1_T(&st, &E, &r_emlrtRTEI, true);
  emxInit_boolean_T(&st, &vertFilterList, 1, &r_emlrtRTEI, true);
  emxInit_real_T(&st, &r2sV, 1, &r_emlrtRTEI, true);
  emxInit_real_T(&st, &s2rV, 1, &r_emlrtRTEI, true);
  emxInit_boolean_T(&st, &nonLeafVerts, 1, &r_emlrtRTEI, true);
  emxInit_real_T(&st, &betweenness, 1, &r_emlrtRTEI, true);

  /* Marshall function inputs */
  emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "V", &V);
  h_emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "E", &E);
  color = j_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "color");
  k_emlrt_marshallIn(&st, emlrtAlias(prhs[3]), "vertFilterList", vertFilterList);
  location = j_emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "location");
  m_emlrt_marshallIn(&st, emlrtAlias(prhs[5]), "r2sV", r2sV);
  m_emlrt_marshallIn(&st, emlrtAlias(prhs[6]), "s2rV", s2rV);
  k_emlrt_marshallIn(&st, emlrtAlias(prhs[7]), "nonLeafVerts", nonLeafVerts);

  /* Invoke the target function */
  mexBetweenessCentrality(&st, &V, &E, color, vertFilterList, location, r2sV,
    s2rV, nonLeafVerts, betweenness);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(betweenness);
  betweenness->canFreeData = false;
  emxFree_real_T(&betweenness);
  nonLeafVerts->canFreeData = false;
  emxFree_boolean_T(&nonLeafVerts);
  s2rV->canFreeData = false;
  emxFree_real_T(&s2rV);
  r2sV->canFreeData = false;
  emxFree_real_T(&r2sV);
  vertFilterList->canFreeData = false;
  emxFree_boolean_T(&vertFilterList);
  emxFreeStruct_struct1_T(&E);
  emxFreeStruct_struct0_T(&V);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/* End of code generation (_coder_mexBetweenessCentrality_api.c) */
