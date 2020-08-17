/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mexBetweenessCentrality.c
 *
 * Code generation for function 'mexBetweenessCentrality'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "mexBetweenessCentrality.h"
#include "mpower.h"
#include "mexBetweenessCentrality_emxutil.h"
#include "eml_int_forloop_overflow_check.h"
#include "sqrt.h"
#include "toLogicalCheck.h"
#include "sum.h"
#include "nullAssignment.h"
#include "eps.h"
#include "angleBetween.h"
#include "indexShapeCheck.h"
#include "mexBetweenessCentrality_data.h"

/* Variable Definitions */
static emlrtRSInfo emlrtRSI = { 18,    /* lineNo */
  "mexBetweenessCentrality",           /* fcnName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pathName */
};

static emlrtRSInfo b_emlrtRSI = { 23,  /* lineNo */
  "mexBetweenessCentrality",           /* fcnName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pathName */
};

static emlrtRSInfo c_emlrtRSI = { 24,  /* lineNo */
  "mexBetweenessCentrality",           /* fcnName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pathName */
};

static emlrtRSInfo d_emlrtRSI = { 30,  /* lineNo */
  "mexBetweenessCentrality",           /* fcnName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pathName */
};

static emlrtRSInfo e_emlrtRSI = { 52,  /* lineNo */
  "mexBetweenessCentrality",           /* fcnName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pathName */
};

static emlrtRSInfo f_emlrtRSI = { 64,  /* lineNo */
  "mexBetweenessCentrality",           /* fcnName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pathName */
};

static emlrtRSInfo g_emlrtRSI = { 66,  /* lineNo */
  "mexBetweenessCentrality",           /* fcnName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pathName */
};

static emlrtRSInfo h_emlrtRSI = { 68,  /* lineNo */
  "mexBetweenessCentrality",           /* fcnName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pathName */
};

static emlrtRSInfo i_emlrtRSI = { 103, /* lineNo */
  "mexBetweenessCentrality",           /* fcnName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pathName */
};

static emlrtRSInfo j_emlrtRSI = { 108, /* lineNo */
  "mexBetweenessCentrality",           /* fcnName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pathName */
};

static emlrtRSInfo k_emlrtRSI = { 110, /* lineNo */
  "mexBetweenessCentrality",           /* fcnName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pathName */
};

static emlrtRSInfo l_emlrtRSI = { 112, /* lineNo */
  "mexBetweenessCentrality",           /* fcnName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pathName */
};

static emlrtRSInfo m_emlrtRSI = { 121, /* lineNo */
  "mexBetweenessCentrality",           /* fcnName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pathName */
};

static emlrtRSInfo n_emlrtRSI = { 136, /* lineNo */
  "mexBetweenessCentrality",           /* fcnName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pathName */
};

static emlrtRSInfo o_emlrtRSI = { 165, /* lineNo */
  "mexBetweenessCentrality",           /* fcnName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pathName */
};

static emlrtRSInfo p_emlrtRSI = { 199, /* lineNo */
  "mexBetweenessCentrality",           /* fcnName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pathName */
};

static emlrtRSInfo q_emlrtRSI = { 238, /* lineNo */
  "mexBetweenessCentrality",           /* fcnName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pathName */
};

static emlrtRSInfo r_emlrtRSI = { 258, /* lineNo */
  "mexBetweenessCentrality",           /* fcnName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pathName */
};

static emlrtRSInfo s_emlrtRSI = { 277, /* lineNo */
  "mexBetweenessCentrality",           /* fcnName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pathName */
};

static emlrtRSInfo t_emlrtRSI = { 280, /* lineNo */
  "mexBetweenessCentrality",           /* fcnName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pathName */
};

static emlrtRSInfo u_emlrtRSI = { 284, /* lineNo */
  "mexBetweenessCentrality",           /* fcnName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pathName */
};

static emlrtRSInfo v_emlrtRSI = { 44,  /* lineNo */
  "find",                              /* fcnName */
  "A:\\MatlabR2017A\\toolbox\\eml\\lib\\matlab\\elmat\\find.m"/* pathName */
};

static emlrtRSInfo w_emlrtRSI = { 234, /* lineNo */
  "find",                              /* fcnName */
  "A:\\MatlabR2017A\\toolbox\\eml\\lib\\matlab\\elmat\\find.m"/* pathName */
};

static emlrtRSInfo x_emlrtRSI = { 253, /* lineNo */
  "find",                              /* fcnName */
  "A:\\MatlabR2017A\\toolbox\\eml\\lib\\matlab\\elmat\\find.m"/* pathName */
};

static emlrtRSInfo ib_emlrtRSI = { 15, /* lineNo */
  "min",                               /* fcnName */
  "A:\\MatlabR2017A\\toolbox\\eml\\lib\\matlab\\datafun\\min.m"/* pathName */
};

static emlrtRSInfo jb_emlrtRSI = { 16, /* lineNo */
  "minOrMax",                          /* fcnName */
  "A:\\MatlabR2017A\\toolbox\\eml\\eml\\+coder\\+internal\\minOrMax.m"/* pathName */
};

static emlrtMCInfo emlrtMCI = { 281,   /* lineNo */
  13,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pName */
};

static emlrtRTEInfo emlrtRTEI = { 2,   /* lineNo */
  24,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pName */
};

static emlrtRTEInfo b_emlrtRTEI = { 253,/* lineNo */
  13,                                  /* colNo */
  "find",                              /* fName */
  "A:\\MatlabR2017A\\toolbox\\eml\\lib\\matlab\\elmat\\find.m"/* pName */
};

static emlrtRTEInfo c_emlrtRTEI = { 8, /* lineNo */
  1,                                   /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pName */
};

static emlrtRTEInfo d_emlrtRTEI = { 18,/* lineNo */
  1,                                   /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pName */
};

static emlrtRTEInfo e_emlrtRTEI = { 23,/* lineNo */
  5,                                   /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pName */
};

static emlrtRTEInfo f_emlrtRTEI = { 24,/* lineNo */
  5,                                   /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pName */
};

static emlrtRTEInfo g_emlrtRTEI = { 26,/* lineNo */
  5,                                   /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pName */
};

static emlrtRTEInfo h_emlrtRTEI = { 27,/* lineNo */
  5,                                   /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pName */
};

static emlrtRTEInfo i_emlrtRTEI = { 29,/* lineNo */
  5,                                   /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pName */
};

static emlrtRTEInfo j_emlrtRTEI = { 31,/* lineNo */
  5,                                   /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pName */
};

static emlrtRTEInfo k_emlrtRTEI = { 32,/* lineNo */
  5,                                   /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pName */
};

static emlrtRTEInfo l_emlrtRTEI = { 33,/* lineNo */
  5,                                   /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pName */
};

static emlrtRTEInfo m_emlrtRTEI = { 34,/* lineNo */
  5,                                   /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pName */
};

static emlrtRTEInfo n_emlrtRTEI = { 35,/* lineNo */
  5,                                   /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pName */
};

static emlrtRTEInfo o_emlrtRTEI = { 36,/* lineNo */
  5,                                   /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pName */
};

static emlrtRTEInfo p_emlrtRTEI = { 36,/* lineNo */
  6,                                   /* colNo */
  "find",                              /* fName */
  "A:\\MatlabR2017A\\toolbox\\eml\\lib\\matlab\\elmat\\find.m"/* pName */
};

static emlrtRTEInfo t_emlrtRTEI = { 121,/* lineNo */
  27,                                  /* colNo */
  "minOrMax",                          /* fName */
  "A:\\MatlabR2017A\\toolbox\\eml\\eml\\+coder\\+internal\\minOrMax.m"/* pName */
};

static emlrtRTEInfo u_emlrtRTEI = { 39,/* lineNo */
  27,                                  /* colNo */
  "minOrMax",                          /* fName */
  "A:\\MatlabR2017A\\toolbox\\eml\\eml\\+coder\\+internal\\minOrMax.m"/* pName */
};

static emlrtRTEInfo v_emlrtRTEI = { 243,/* lineNo */
  9,                                   /* colNo */
  "find",                              /* fName */
  "A:\\MatlabR2017A\\toolbox\\eml\\lib\\matlab\\elmat\\find.m"/* pName */
};

static emlrtBCInfo emlrtBCI = { -1,    /* iFirst */
  -1,                                  /* iLast */
  110,                                 /* lineNo */
  102,                                 /* colNo */
  "zeroedgeIndexMatrixFiltConnected",  /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo b_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  64,                                  /* lineNo */
  74,                                  /* colNo */
  "edgeIndexMatrixFiltConnected",      /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo c_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  236,                                 /* lineNo */
  28,                                  /* colNo */
  "boundaryVertexCoor",                /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo d_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  41,                                  /* lineNo */
  16,                                  /* colNo */
  "distMatrix",                        /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo e_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  40,                                  /* lineNo */
  15,                                  /* colNo */
  "radMatrix",                         /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo f_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  266,                                 /* lineNo */
  48,                                  /* colNo */
  "parentEdge",                        /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo emlrtDCI = { 266,   /* lineNo */
  48,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo g_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  255,                                 /* lineNo */
  40,                                  /* colNo */
  "parentEdge",                        /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo b_emlrtDCI = { 255, /* lineNo */
  40,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo h_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  254,                                 /* lineNo */
  48,                                  /* colNo */
  "vertexTerminal_circList",           /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo i_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  246,                                 /* lineNo */
  44,                                  /* colNo */
  "parentEdge",                        /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo c_emlrtDCI = { 246, /* lineNo */
  44,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo j_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  236,                                 /* lineNo */
  41,                                  /* colNo */
  "V.pos",                             /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo d_emlrtDCI = { 236, /* lineNo */
  41,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtDCInfo e_emlrtDCI = { 226, /* lineNo */
  24,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtDCInfo f_emlrtDCI = { 226, /* lineNo */
  24,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  4                                    /* checkKind */
};

static emlrtBCInfo k_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  168,                                 /* lineNo */
  32,                                  /* colNo */
  "dirMat",                            /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo l_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  168,                                 /* lineNo */
  49,                                  /* colNo */
  "E.dir",                             /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo g_emlrtDCI = { 168, /* lineNo */
  49,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo m_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  166,                                 /* lineNo */
  32,                                  /* colNo */
  "dirMat",                            /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo n_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  166,                                 /* lineNo */
  49,                                  /* colNo */
  "dirMat",                            /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo o_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  165,                                 /* lineNo */
  59,                                  /* colNo */
  "V.pos",                             /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo h_emlrtDCI = { 165, /* lineNo */
  59,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo p_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  152,                                 /* lineNo */
  43,                                  /* colNo */
  "r2sV",                              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo i_emlrtDCI = { 152, /* lineNo */
  43,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo q_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  151,                                 /* lineNo */
  43,                                  /* colNo */
  "r2sV",                              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo j_emlrtDCI = { 151, /* lineNo */
  43,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo r_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  137,                                 /* lineNo */
  52,                                  /* colNo */
  "edgeIndexMatrixFinal",              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo s_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  133,                                 /* lineNo */
  77,                                  /* colNo */
  "E.dir",                             /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo t_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  133,                                 /* lineNo */
  63,                                  /* colNo */
  "dirMat",                            /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo u_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  123,                                 /* lineNo */
  93,                                  /* colNo */
  "E.dir",                             /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo v_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  123,                                 /* lineNo */
  79,                                  /* colNo */
  "dirMat",                            /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo w_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  39,                                  /* lineNo */
  12,                                  /* colNo */
  "dirMat",                            /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo x_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  121,                                 /* lineNo */
  114,                                 /* colNo */
  "V.pos",                             /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo k_emlrtDCI = { 121, /* lineNo */
  114,                                 /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo y_emlrtBCI = { -1,  /* iFirst */
  -1,                                  /* iLast */
  120,                                 /* lineNo */
  77,                                  /* colNo */
  "zeroedgeIndexMatrixFinal",          /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo ab_emlrtBCI = { 1,  /* iFirst */
  4,                                   /* iLast */
  109,                                 /* lineNo */
  93,                                  /* colNo */
  "V.edgeIDList",                      /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo l_emlrtDCI = { 109, /* lineNo */
  93,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo bb_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  109,                                 /* lineNo */
  102,                                 /* colNo */
  "V.degree",                          /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo m_emlrtDCI = { 109, /* lineNo */
  102,                                 /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo cb_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  109,                                 /* lineNo */
  82,                                  /* colNo */
  "V.edgeIDList",                      /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo db_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  101,                                 /* lineNo */
  53,                                  /* colNo */
  "edgeIndexMatrixFinal",              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo eb_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  97,                                  /* lineNo */
  52,                                  /* colNo */
  "edgeIndexMatrixFinal",              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo fb_emlrtBCI = { 1,  /* iFirst */
  4,                                   /* iLast */
  63,                                  /* lineNo */
  68,                                  /* colNo */
  "V.edgeIDList",                      /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo n_emlrtDCI = { 63,  /* lineNo */
  68,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo gb_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  63,                                  /* lineNo */
  77,                                  /* colNo */
  "V.degree",                          /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo o_emlrtDCI = { 63,  /* lineNo */
  77,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo hb_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  63,                                  /* lineNo */
  58,                                  /* colNo */
  "V.edgeIDList",                      /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo ib_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  50,                                  /* lineNo */
  46,                                  /* colNo */
  "vertexCollectionList",              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo jb_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  42,                                  /* lineNo */
  26,                                  /* colNo */
  "vertexCollectionList",              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo kb_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  40,                                  /* lineNo */
  26,                                  /* colNo */
  "V.rad",                             /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo lb_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  38,                                  /* lineNo */
  25,                                  /* colNo */
  "r2sV",                              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo mb_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  37,                                  /* lineNo */
  35,                                  /* colNo */
  "validStartPoints",                  /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtECInfo emlrtECI = { -1,    /* nDims */
  18,                                  /* lineNo */
  25,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pName */
};

static emlrtECInfo b_emlrtECI = { -1,  /* nDims */
  8,                                   /* lineNo */
  24,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pName */
};

static emlrtBCInfo nb_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  8,                                   /* lineNo */
  62,                                  /* colNo */
  "V.borderRegions",                   /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo p_emlrtDCI = { 8,   /* lineNo */
  62,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtDCInfo q_emlrtDCI = { 23,  /* lineNo */
  34,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtDCInfo r_emlrtDCI = { 24,  /* lineNo */
  34,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo ob_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  28,                                  /* lineNo */
  46,                                  /* colNo */
  "V.vertexCoorID",                    /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo pb_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  43,                                  /* lineNo */
  17,                                  /* colNo */
  "parentEdge",                        /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo s_emlrtDCI = { 43,  /* lineNo */
  17,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo qb_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  56,                                  /* lineNo */
  40,                                  /* colNo */
  "vertexCollectionList",              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo rb_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  57,                                  /* lineNo */
  28,                                  /* colNo */
  "vertexTerminal",                    /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo t_emlrtDCI = { 57,  /* lineNo */
  28,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo sb_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  57,                                  /* lineNo */
  49,                                  /* colNo */
  "vertexCollectionList",              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo tb_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  176,                                 /* lineNo */
  45,                                  /* colNo */
  "vertexTerminal_SubGraph_Proc",      /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo u_emlrtDCI = { 176, /* lineNo */
  45,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo ub_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  176,                                 /* lineNo */
  50,                                  /* colNo */
  "r2sV",                              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo v_emlrtDCI = { 176, /* lineNo */
  50,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo vb_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  176,                                 /* lineNo */
  71,                                  /* colNo */
  "vertexCollectionList",              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo wb_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  177,                                 /* lineNo */
  46,                                  /* colNo */
  "vertexTerminal_SubGraph_Proc",      /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo w_emlrtDCI = { 177, /* lineNo */
  46,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo xb_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  177,                                 /* lineNo */
  51,                                  /* colNo */
  "r2sV",                              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo x_emlrtDCI = { 177, /* lineNo */
  51,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo yb_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  177,                                 /* lineNo */
  72,                                  /* colNo */
  "vertexCollectionList",              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo ac_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  179,                                 /* lineNo */
  59,                                  /* colNo */
  "r2sV",                              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo y_emlrtDCI = { 179, /* lineNo */
  59,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo bc_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  179,                                 /* lineNo */
  80,                                  /* colNo */
  "vertexCollectionList",              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo cc_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  179,                                 /* lineNo */
  41,                                  /* colNo */
  "vertexTerminal_circList",           /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo dc_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  58,                                  /* lineNo */
  27,                                  /* colNo */
  "parentEdge",                        /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo ab_emlrtDCI = { 58, /* lineNo */
  27,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo ec_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  58,                                  /* lineNo */
  32,                                  /* colNo */
  "r2sV",                              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo bb_emlrtDCI = { 58, /* lineNo */
  32,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo fc_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  58,                                  /* lineNo */
  53,                                  /* colNo */
  "vertexCollectionList",              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo gc_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  61,                                  /* lineNo */
  38,                                  /* colNo */
  "parentEdge",                        /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo cb_emlrtDCI = { 61, /* lineNo */
  38,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo hc_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  61,                                  /* lineNo */
  43,                                  /* colNo */
  "r2sV",                              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo db_emlrtDCI = { 61, /* lineNo */
  43,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo ic_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  61,                                  /* lineNo */
  64,                                  /* colNo */
  "vertexCollectionList",              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo jc_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  59,                                  /* lineNo */
  38,                                  /* colNo */
  "parentEdge",                        /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo eb_emlrtDCI = { 59, /* lineNo */
  38,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo kc_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  59,                                  /* lineNo */
  43,                                  /* colNo */
  "r2sV",                              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo fb_emlrtDCI = { 59, /* lineNo */
  43,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo lc_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  59,                                  /* lineNo */
  64,                                  /* colNo */
  "vertexCollectionList",              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo gb_emlrtDCI = { 64, /* lineNo */
  89,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo mc_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  64,                                  /* lineNo */
  89,                                  /* colNo */
  "edgeFilterList",                    /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo nc_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  65,                                  /* lineNo */
  75,                                  /* colNo */
  "edgeIndexMatrixFiltInSubGraph",     /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo oc_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  66,                                  /* lineNo */
  89,                                  /* colNo */
  "edgeProcessed",                     /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo pc_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  66,                                  /* lineNo */
  74,                                  /* colNo */
  "edgeIndexMatrixFiltNoReverse",      /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo qc_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  68,                                  /* lineNo */
  70,                                  /* colNo */
  "vertexCollectionList",              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo rc_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  102,                                 /* lineNo */
  45,                                  /* colNo */
  "E.twinID",                          /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo sc_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  103,                                 /* lineNo */
  39,                                  /* colNo */
  "E.dir",                             /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo tc_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  103,                                 /* lineNo */
  57,                                  /* colNo */
  "E.dir",                             /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo uc_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  133,                                 /* lineNo */
  38,                                  /* colNo */
  "angleMat",                          /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo vc_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  106,                                 /* lineNo */
  50,                                  /* colNo */
  "E.twinID",                          /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo wc_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  107,                                 /* lineNo */
  49,                                  /* colNo */
  "E.origin",                          /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo hb_emlrtDCI = { 110,/* lineNo */
  117,                                 /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo xc_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  110,                                 /* lineNo */
  117,                                 /* colNo */
  "edgeFilterList",                    /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo yc_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  111,                                 /* lineNo */
  103,                                 /* colNo */
  "zeroedgeIndexMatrixFiltInSubGraph", /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo ad_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  112,                                 /* lineNo */
  117,                                 /* colNo */
  "edgeProcessed",                     /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo bd_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  112,                                 /* lineNo */
  102,                                 /* colNo */
  "zeroedgeIndexMatrixFiltNoReverse",  /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo cd_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  121,                                 /* lineNo */
  123,                                 /* colNo */
  "E.origin",                          /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo ib_emlrtDCI = { 121,/* lineNo */
  123,                                 /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo dd_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  121,                                 /* lineNo */
  55,                                  /* colNo */
  "E.dir",                             /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo ed_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  121,                                 /* lineNo */
  77,                                  /* colNo */
  "E.dir",                             /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo fd_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  126,                                 /* lineNo */
  66,                                  /* colNo */
  "E.twinID",                          /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo gd_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  127,                                 /* lineNo */
  65,                                  /* colNo */
  "E.origin",                          /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo hd_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  123,                                 /* lineNo */
  54,                                  /* colNo */
  "angleMat",                          /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo id_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  117,                                 /* lineNo */
  46,                                  /* colNo */
  "angleMat",                          /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo jd_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  140,                                 /* lineNo */
  36,                                  /* colNo */
  "edgeCollectionList",                /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo kd_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  141,                                 /* lineNo */
  31,                                  /* colNo */
  "edgeProcessed",                     /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo jb_emlrtDCI = { 141,/* lineNo */
  31,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo ld_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  145,                                 /* lineNo */
  29,                                  /* colNo */
  "E.origin",                          /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo md_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  150,                                 /* lineNo */
  59,                                  /* colNo */
  "E.origin",                          /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo nd_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  150,                                 /* lineNo */
  42,                                  /* colNo */
  "vertexCollectionList",              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo od_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  151,                                 /* lineNo */
  64,                                  /* colNo */
  "vertexCollectionList",              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo pd_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  152,                                 /* lineNo */
  64,                                  /* colNo */
  "vertexCollectionList",              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo qd_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  153,                                 /* lineNo */
  35,                                  /* colNo */
  "parentEdge",                        /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo kb_emlrtDCI = { 153,/* lineNo */
  35,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo rd_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  156,                                 /* lineNo */
  65,                                  /* colNo */
  "E.twinID",                          /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo sd_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  156,                                 /* lineNo */
  36,                                  /* colNo */
  "parentEdge",                        /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo td_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  154,                                 /* lineNo */
  65,                                  /* colNo */
  "E.twinID",                          /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo ud_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  154,                                 /* lineNo */
  36,                                  /* colNo */
  "parentEdge",                        /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo vd_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  159,                                 /* lineNo */
  34,                                  /* colNo */
  "childEdge",                         /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo lb_emlrtDCI = { 159,/* lineNo */
  34,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo wd_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  162,                                 /* lineNo */
  35,                                  /* colNo */
  "childEdge",                         /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo xd_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  160,                                 /* lineNo */
  35,                                  /* colNo */
  "childEdge",                         /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo yd_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  165,                                 /* lineNo */
  68,                                  /* colNo */
  "E.origin",                          /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo ae_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  165,                                 /* lineNo */
  31,                                  /* colNo */
  "E.dist",                            /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo be_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  168,                                 /* lineNo */
  58,                                  /* colNo */
  "E.twinID",                          /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo ce_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  171,                                 /* lineNo */
  47,                                  /* colNo */
  "E.dist",                            /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo de_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  171,                                 /* lineNo */
  32,                                  /* colNo */
  "distMatrix",                        /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo ee_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  172,                                 /* lineNo */
  45,                                  /* colNo */
  "V.rad",                             /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo mb_emlrtDCI = { 172,/* lineNo */
  45,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo fe_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  172,                                 /* lineNo */
  66,                                  /* colNo */
  "vertexCollectionList",              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo ge_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  172,                                 /* lineNo */
  31,                                  /* colNo */
  "radMatrix",                         /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo nb_emlrtDCI = { 227,/* lineNo */
  16,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo he_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  227,                                 /* lineNo */
  16,                                  /* colNo */
  "isOnBridge",                        /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo ie_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  284,                                 /* lineNo */
  17,                                  /* colNo */
  "betweenness",                       /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo je_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  235,                                 /* lineNo */
  24,                                  /* colNo */
  "s2rV",                              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo ob_emlrtDCI = { 235,/* lineNo */
  24,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo ke_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  235,                                 /* lineNo */
  48,                                  /* colNo */
  "vertexTerminal_circList",           /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo le_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  245,                                 /* lineNo */
  30,                                  /* colNo */
  "parentEdge",                        /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo pb_emlrtDCI = { 245,/* lineNo */
  30,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo me_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  245,                                 /* lineNo */
  35,                                  /* colNo */
  "r2sV",                              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo qb_emlrtDCI = { 245,/* lineNo */
  35,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo ne_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  251,                                 /* lineNo */
  40,                                  /* colNo */
  "vertTerminal_circList_rootNode",    /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo oe_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  252,                                 /* lineNo */
  23,                                  /* colNo */
  "parentEdge",                        /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo rb_emlrtDCI = { 252,/* lineNo */
  23,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo pe_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  252,                                 /* lineNo */
  47,                                  /* colNo */
  "vertexTerminal_circList",           /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo qe_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  256,                                 /* lineNo */
  44,                                  /* colNo */
  "E.dist",                            /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo sb_emlrtDCI = { 256,/* lineNo */
  44,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo re_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  257,                                 /* lineNo */
  32,                                  /* colNo */
  "E.origin",                          /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo se_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  265,                                 /* lineNo */
  34,                                  /* colNo */
  "parentEdge",                        /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo tb_emlrtDCI = { 265,/* lineNo */
  34,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo te_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  265,                                 /* lineNo */
  39,                                  /* colNo */
  "r2sV",                              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo ub_emlrtDCI = { 265,/* lineNo */
  39,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo ue_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  273,                                 /* lineNo */
  48,                                  /* colNo */
  "vertTerminal_circList_rootNode",    /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo ve_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  276,                                 /* lineNo */
  17,                                  /* colNo */
  "distMat",                           /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo we_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  277,                                 /* lineNo */
  29,                                  /* colNo */
  "V.rad",                             /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo vb_emlrtDCI = { 277,/* lineNo */
  29,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo xe_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  277,                                 /* lineNo */
  60,                                  /* colNo */
  "vertTerminal_circList_rootNode",    /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo ye_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  277,                                 /* lineNo */
  88,                                  /* colNo */
  "V.rad",                             /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo wb_emlrtDCI = { 277,/* lineNo */
  88,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo af_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  277,                                 /* lineNo */
  119,                                 /* colNo */
  "vertTerminal_circList_rootNode",    /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo bf_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  280,                                 /* lineNo */
  33,                                  /* colNo */
  "V.rad",                             /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo xb_emlrtDCI = { 280,/* lineNo */
  33,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo cf_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  280,                                 /* lineNo */
  64,                                  /* colNo */
  "vertTerminal_circList_rootNode",    /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo df_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  278,                                 /* lineNo */
  32,                                  /* colNo */
  "V.rad",                             /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo yb_emlrtDCI = { 278,/* lineNo */
  32,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo ef_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  278,                                 /* lineNo */
  63,                                  /* colNo */
  "vertTerminal_circList_rootNode",    /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo ff_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  278,                                 /* lineNo */
  21,                                  /* colNo */
  "distMat",                           /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo gf_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  266,                                 /* lineNo */
  53,                                  /* colNo */
  "r2sV",                              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo ac_emlrtDCI = { 266,/* lineNo */
  53,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo hf_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  267,                                 /* lineNo */
  52,                                  /* colNo */
  "E.dist",                            /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo bc_emlrtDCI = { 267,/* lineNo */
  52,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo if_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  268,                                 /* lineNo */
  40,                                  /* colNo */
  "E.origin",                          /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtBCInfo jf_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  246,                                 /* lineNo */
  49,                                  /* colNo */
  "r2sV",                              /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo cc_emlrtDCI = { 246,/* lineNo */
  49,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo kf_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  247,                                 /* lineNo */
  46,                                  /* colNo */
  "E.dist",                            /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtDCInfo dc_emlrtDCI = { 247,/* lineNo */
  46,                                  /* colNo */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo lf_emlrtBCI = { -1, /* iFirst */
  -1,                                  /* iLast */
  248,                                 /* lineNo */
  36,                                  /* colNo */
  "E.origin",                          /* aName */
  "mexBetweenessCentrality",           /* fName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m",/* pName */
  0                                    /* checkKind */
};

static emlrtRSInfo rb_emlrtRSI = { 281,/* lineNo */
  "mexBetweenessCentrality",           /* fcnName */
  "A:\\delta\\OneDrive\\Graduate School\\Fortunes Git\\PrePost_Processing\\mexBetweenessCentrality.m"/* pathName */
};

/* Function Declarations */
static void disp(const emlrtStack *sp, const mxArray *b, emlrtMCInfo *location);

/* Function Definitions */
static void disp(const emlrtStack *sp, const mxArray *b, emlrtMCInfo *location)
{
  const mxArray *pArray;
  pArray = b;
  emlrtCallMATLABR2012b(sp, 0, NULL, 1, &pArray, "disp", true, location);
}

void mexBetweenessCentrality(const emlrtStack *sp, const struct0_T *V, const
  struct1_T *E, real_T color, const emxArray_boolean_T *vertFilterList, real_T
  location, const emxArray_real_T *r2sV, const emxArray_real_T *s2rV, const
  emxArray_boolean_T *nonLeafVerts, emxArray_real_T *betweenness)
{
  emxArray_boolean_T *edgeFilterList;
  int32_T partialTrueCount;
  int32_T loop_ub;
  emxArray_boolean_T *x;
  int32_T n;
  real_T d0;
  int32_T idx;
  emxArray_int32_T *ii;
  int32_T nx;
  boolean_T overflow;
  boolean_T exitg1;
  int32_T b_V[2];
  emxArray_int32_T *validStartPoints;
  int32_T vsp;
  emxArray_real_T *vertexCollectionList;
  emxArray_real_T *edgeCollectionList;
  emxArray_int8_T *edgeProcessed;
  emxArray_boolean_T *vertexTerminal;
  emxArray_boolean_T *vertexTerminal_SubGraph_Proc;
  emxArray_real_T *vertexTerminal_circList;
  emxArray_real_T *childEdge;
  emxArray_real_T *parentEdge;
  emxArray_real_T *radMatrix;
  emxArray_real_T *distMatrix;
  emxArray_real_T *dirMat;
  emxArray_int32_T *r0;
  emxArray_int32_T *r1;
  emxArray_int32_T *r2;
  emxArray_int32_T *r3;
  int32_T iv0[2];
  int32_T trueCount;
  int32_T i;
  uint32_T iter;
  uint32_T terminals;
  int32_T startingVertexInd;
  int32_T exitg2;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  real_T c_edgeIndexMatrixFiltConnected_[4];
  int32_T tmp_data[4];
  uint32_T d_edgeIndexMatrixFiltConnected_[4];
  boolean_T b_tmp_data[4];
  real_T parEdge;
  int32_T b_trueCount;
  int32_T c_tmp_data[4];
  int32_T d_tmp_data[4];
  uint32_T e_edgeIndexMatrixFiltConnected_[4];
  boolean_T e_tmp_data[4];
  int32_T V_size[2];
  int32_T f_tmp_data[4];
  int32_T g_tmp_data[4];
  int32_T h_tmp_data[4];
  int32_T i_tmp_data[4];
  int32_T j_tmp_data[4];
  int32_T k_tmp_data[4];
  int32_T tmp_size[2];
  int32_T l_tmp_data[4];
  int32_T m_tmp_data[4];
  int32_T n_tmp_data[4];
  real_T twinEdge;
  int32_T o_tmp_data[4];
  int32_T p_tmp_data[4];
  int32_T c_trueCount;
  int32_T q_tmp_data[4];
  int32_T r_tmp_data[4];
  int32_T s_tmp_data[4];
  int32_T t_tmp_data[4];
  int32_T angleMat_size_idx_1;
  int32_T b_loop_ub;
  real_T angleMat_data[4];
  int32_T u_tmp_data[4];
  int32_T v_tmp_data[4];
  int32_T w_tmp_data[4];
  int32_T x_tmp_data[4];
  int32_T y_tmp_data[4];
  int32_T ab_tmp_data[4];
  int32_T bb_tmp_data[4];
  boolean_T b_guard1 = false;
  int32_T cb_tmp_data[4];
  real_T distTempB;
  int32_T db_tmp_data[4];
  int32_T eb_tmp_data[4];
  int32_T fb_tmp_data[4];
  int32_T gb_tmp_data[4];
  int32_T end;
  int32_T c_loop_ub;
  int32_T b_end;
  int32_T c_end;
  int32_T hb_tmp_data[4];
  const mxArray *y;
  const mxArray *m0;
  static const int32_T iv1[2] = { 1, 50 };

  static const char_T u[50] = { 'S', 'e', 'v', 'e', 'r', 'e', ' ', 'p', 'r', 'e',
    'c', 'i', 's', 'i', 'o', 'n', ' ', 'e', 'r', 'r', 'o', 'r', ' ', 'd', 'e',
    't', 'e', 'c', 't', 'e', 'd', ',', ' ', 'r', 'e', 'v', 'i', 'e', 'w', ' ',
    'l', 'o', 'o', 'p', ' ', 'p', 'l', 'o', 't', 's' };

  int32_T ib_tmp_data[4];
  int32_T itmp;
  int32_T jb_tmp_data[4];
  int32_T kb_tmp_data[4];
  int32_T lb_tmp_data[4];
  int32_T mb_tmp_data[4];
  int32_T nb_tmp_data[4];
  int32_T ob_tmp_data[4];
  int32_T pb_tmp_data[4];
  int32_T qb_tmp_data[4];
  int32_T rb_tmp_data[4];
  int32_T sb_tmp_data[4];
  int32_T tb_tmp_data[4];
  int32_T noEdgeFound;
  real_T b_dirMat[2];
  real_T parEdge_T;
  real_T twinVert;
  real_T b_E[2];
  int32_T exitg3;
  real_T c_zeroedgeIndexMatrixFiltConnec[4];
  int32_T b_V_size[2];
  int32_T ub_tmp_data[4];
  int32_T vb_tmp_data[4];
  int32_T wb_tmp_data[4];
  uint32_T c_zeroedgeIndexMatrixFiltNoReve[4];
  int32_T xb_tmp_data[4];
  int32_T b_tmp_size[2];
  int32_T yb_tmp_data[4];
  int32_T ac_tmp_data[4];
  int32_T bc_tmp_data[4];
  int32_T cc_tmp_data[4];
  int32_T dc_tmp_data[4];
  int32_T ec_tmp_data[4];
  int32_T fc_tmp_data[4];
  int32_T gc_tmp_data[4];
  int32_T hc_tmp_data[4];
  int32_T ic_tmp_data[4];
  int32_T d_loop_ub;
  int32_T d_end;
  int32_T jc_tmp_data[4];
  int32_T c_E;
  int32_T d_E;
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
  emxInit_boolean_T(sp, &edgeFilterList, 1, &c_emlrtRTEI, true);

  /*  r2sV(vertFilterList) = 1:length(s2rV); */
  partialTrueCount = edgeFilterList->size[0];
  edgeFilterList->size[0] = E->color->size[0];
  emxEnsureCapacity(sp, (emxArray__common *)edgeFilterList, partialTrueCount,
                    sizeof(boolean_T), &emlrtRTEI);
  loop_ub = E->color->size[0];
  for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
    edgeFilterList->data[partialTrueCount] = (E->color->data[partialTrueCount] ==
      color);
  }

  emxInit_boolean_T(sp, &x, 1, &emlrtRTEI, true);
  loop_ub = E->origin->size[0];
  n = V->borderRegions->size[0];
  partialTrueCount = x->size[0];
  x->size[0] = loop_ub;
  emxEnsureCapacity(sp, (emxArray__common *)x, partialTrueCount, sizeof
                    (boolean_T), &emlrtRTEI);
  for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
    d0 = E->origin->data[partialTrueCount];
    if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
      emlrtIntegerCheckR2012b(d0, &p_emlrtDCI, sp);
    }

    idx = (int32_T)d0;
    if (!((idx >= 1) && (idx <= n))) {
      emlrtDynamicBoundsCheckR2012b(idx, 1, n, &nb_emlrtBCI, sp);
    }

    x->data[partialTrueCount] = (V->borderRegions->data[idx - 1] == location);
  }

  partialTrueCount = edgeFilterList->size[0];
  idx = x->size[0];
  if (partialTrueCount != idx) {
    emlrtSizeEqCheck1DR2012b(partialTrueCount, idx, &b_emlrtECI, sp);
  }

  partialTrueCount = edgeFilterList->size[0];
  emxEnsureCapacity(sp, (emxArray__common *)edgeFilterList, partialTrueCount,
                    sizeof(boolean_T), &emlrtRTEI);
  loop_ub = edgeFilterList->size[0];
  for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
    edgeFilterList->data[partialTrueCount] = (edgeFilterList->
      data[partialTrueCount] && x->data[partialTrueCount]);
  }

  /*  s2rE                 = find(edgeFilterList); */
  /*  r2sE                 = sparse(size(edgeFilterList)); */
  /*  r2sE(edgeFilterList) = 1:length(s2rE); */
  /* edgeSubGraph         = records.halfEdge(edgeFilterList,:); */
  /*  fullGraphBinary = zeros(size(records.vorVert,1),1); */
  partialTrueCount = vertFilterList->size[0];
  idx = nonLeafVerts->size[0];
  if (partialTrueCount != idx) {
    emlrtSizeEqCheck1DR2012b(partialTrueCount, idx, &emlrtECI, sp);
  }

  st.site = &emlrtRSI;
  partialTrueCount = x->size[0];
  x->size[0] = vertFilterList->size[0];
  emxEnsureCapacity(&st, (emxArray__common *)x, partialTrueCount, sizeof
                    (boolean_T), &emlrtRTEI);
  loop_ub = vertFilterList->size[0];
  for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
    x->data[partialTrueCount] = (vertFilterList->data[partialTrueCount] &&
      nonLeafVerts->data[partialTrueCount]);
  }

  emxInit_int32_T(&st, &ii, 1, &p_emlrtRTEI, true);
  b_st.site = &v_emlrtRSI;
  nx = x->size[0];
  idx = 0;
  partialTrueCount = ii->size[0];
  ii->size[0] = x->size[0];
  emxEnsureCapacity(&b_st, (emxArray__common *)ii, partialTrueCount, sizeof
                    (int32_T), &emlrtRTEI);
  c_st.site = &w_emlrtRSI;
  overflow = ((!(1 > x->size[0])) && (x->size[0] > 2147483646));
  if (overflow) {
    d_st.site = &y_emlrtRSI;
    check_forloop_overflow_error(&d_st);
  }

  n = 1;
  exitg1 = false;
  while ((!exitg1) && (n <= nx)) {
    if (x->data[n - 1]) {
      idx++;
      ii->data[idx - 1] = n;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        n++;
      }
    } else {
      n++;
    }
  }

  if (!(idx <= x->size[0])) {
    emlrtErrorWithMessageIdR2012b(&b_st, &v_emlrtRTEI,
      "Coder:builtins:AssertionFailed", 0);
  }

  if (x->size[0] == 1) {
    if (idx == 0) {
      partialTrueCount = ii->size[0];
      ii->size[0] = 0;
      emxEnsureCapacity(&b_st, (emxArray__common *)ii, partialTrueCount, sizeof
                        (int32_T), &emlrtRTEI);
    }
  } else {
    if (1 > idx) {
      partialTrueCount = 0;
    } else {
      partialTrueCount = idx;
    }

    b_V[0] = 1;
    b_V[1] = partialTrueCount;
    c_st.site = &x_emlrtRSI;
    indexShapeCheck(&c_st, ii->size[0], b_V);
    idx = ii->size[0];
    ii->size[0] = partialTrueCount;
    emxEnsureCapacity(&b_st, (emxArray__common *)ii, idx, sizeof(int32_T),
                      &b_emlrtRTEI);
  }

  emxInit_int32_T(&b_st, &validStartPoints, 1, &d_emlrtRTEI, true);
  partialTrueCount = validStartPoints->size[0];
  validStartPoints->size[0] = ii->size[0];
  emxEnsureCapacity(&st, (emxArray__common *)validStartPoints, partialTrueCount,
                    sizeof(int32_T), &emlrtRTEI);
  loop_ub = ii->size[0];
  for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
    validStartPoints->data[partialTrueCount] = ii->data[partialTrueCount];
  }

  partialTrueCount = betweenness->size[0];
  betweenness->size[0] = validStartPoints->size[0];
  emxEnsureCapacity(sp, (emxArray__common *)betweenness, partialTrueCount,
                    sizeof(real_T), &emlrtRTEI);
  loop_ub = validStartPoints->size[0];
  for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
    betweenness->data[partialTrueCount] = 0.0;
  }

  vsp = 0;
  emxInit_real_T(sp, &vertexCollectionList, 1, &e_emlrtRTEI, true);
  emxInit_real_T(sp, &edgeCollectionList, 1, &f_emlrtRTEI, true);
  emxInit_int8_T(sp, &edgeProcessed, 1, &g_emlrtRTEI, true);
  emxInit_boolean_T(sp, &vertexTerminal, 1, &h_emlrtRTEI, true);
  emxInit_boolean_T(sp, &vertexTerminal_SubGraph_Proc, 1, &i_emlrtRTEI, true);
  emxInit_real_T(sp, &vertexTerminal_circList, 1, &j_emlrtRTEI, true);
  emxInit_real_T1(sp, &childEdge, 2, &k_emlrtRTEI, true);
  emxInit_real_T1(sp, &parentEdge, 2, &l_emlrtRTEI, true);
  emxInit_real_T(sp, &radMatrix, 1, &m_emlrtRTEI, true);
  emxInit_real_T(sp, &distMatrix, 1, &n_emlrtRTEI, true);
  emxInit_real_T1(sp, &dirMat, 2, &o_emlrtRTEI, true);
  emxInit_int32_T(sp, &r0, 1, &emlrtRTEI, true);
  emxInit_int32_T(sp, &r1, 1, &emlrtRTEI, true);
  emxInit_int32_T(sp, &r2, 1, &emlrtRTEI, true);
  emxInit_int32_T1(sp, &r3, 2, &emlrtRTEI, true);
  while (vsp <= validStartPoints->size[0] - 1) {
    st.site = &b_emlrtRSI;
    d0 = sum(&st, vertFilterList);
    partialTrueCount = vertexCollectionList->size[0];
    if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
      emlrtIntegerCheckR2012b(d0, &q_emlrtDCI, sp);
    }

    vertexCollectionList->size[0] = (int32_T)d0;
    emxEnsureCapacity(sp, (emxArray__common *)vertexCollectionList,
                      partialTrueCount, sizeof(real_T), &emlrtRTEI);
    if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
      emlrtIntegerCheckR2012b(d0, &q_emlrtDCI, sp);
    }

    loop_ub = (int32_T)d0;
    for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
      vertexCollectionList->data[partialTrueCount] = 0.0;
    }

    st.site = &c_emlrtRSI;
    d0 = sum(&st, edgeFilterList);
    partialTrueCount = edgeCollectionList->size[0];
    if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
      emlrtIntegerCheckR2012b(d0, &r_emlrtDCI, sp);
    }

    edgeCollectionList->size[0] = (int32_T)d0;
    emxEnsureCapacity(sp, (emxArray__common *)edgeCollectionList,
                      partialTrueCount, sizeof(real_T), &emlrtRTEI);
    if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
      emlrtIntegerCheckR2012b(d0, &r_emlrtDCI, sp);
    }

    loop_ub = (int32_T)d0;
    for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
      edgeCollectionList->data[partialTrueCount] = 0.0;
    }

    iv0[0] = edgeFilterList->size[0];
    partialTrueCount = edgeProcessed->size[0];
    edgeProcessed->size[0] = iv0[0];
    emxEnsureCapacity(sp, (emxArray__common *)edgeProcessed, partialTrueCount,
                      sizeof(int8_T), &emlrtRTEI);
    loop_ub = iv0[0];
    for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
      edgeProcessed->data[partialTrueCount] = 0;
    }

    partialTrueCount = vertexTerminal->size[0];
    vertexTerminal->size[0] = V->vertexCoorID->size[0];
    emxEnsureCapacity(sp, (emxArray__common *)vertexTerminal, partialTrueCount,
                      sizeof(boolean_T), &emlrtRTEI);
    loop_ub = V->vertexCoorID->size[0];
    for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
      vertexTerminal->data[partialTrueCount] = (V->vertexCoorID->
        data[partialTrueCount] != -1.0);
    }

    n = vertFilterList->size[0] - 1;
    trueCount = 0;
    for (i = 0; i <= n; i++) {
      if (vertFilterList->data[i]) {
        trueCount++;
      }
    }

    partialTrueCount = r0->size[0];
    r0->size[0] = trueCount;
    emxEnsureCapacity(sp, (emxArray__common *)r0, partialTrueCount, sizeof
                      (int32_T), &emlrtRTEI);
    partialTrueCount = 0;
    for (i = 0; i <= n; i++) {
      if (vertFilterList->data[i]) {
        r0->data[partialTrueCount] = i + 1;
        partialTrueCount++;
      }
    }

    n = V->vertexCoorID->size[0];
    loop_ub = r0->size[0];
    for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
      idx = r0->data[partialTrueCount];
      if (!((idx >= 1) && (idx <= n))) {
        emlrtDynamicBoundsCheckR2012b(idx, 1, n, &ob_emlrtBCI, sp);
      }
    }

    n = vertFilterList->size[0] - 1;
    trueCount = 0;
    for (i = 0; i <= n; i++) {
      if (vertFilterList->data[i]) {
        trueCount++;
      }
    }

    partialTrueCount = r1->size[0];
    r1->size[0] = trueCount;
    emxEnsureCapacity(sp, (emxArray__common *)r1, partialTrueCount, sizeof
                      (int32_T), &emlrtRTEI);
    partialTrueCount = 0;
    for (i = 0; i <= n; i++) {
      if (vertFilterList->data[i]) {
        r1->data[partialTrueCount] = i + 1;
        partialTrueCount++;
      }
    }

    partialTrueCount = vertexTerminal_SubGraph_Proc->size[0];
    vertexTerminal_SubGraph_Proc->size[0] = r1->size[0];
    emxEnsureCapacity(sp, (emxArray__common *)vertexTerminal_SubGraph_Proc,
                      partialTrueCount, sizeof(boolean_T), &emlrtRTEI);
    loop_ub = r1->size[0];
    for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
      vertexTerminal_SubGraph_Proc->data[partialTrueCount] = (V->
        vertexCoorID->data[r1->data[partialTrueCount] - 1] != -1.0);
    }

    n = vertFilterList->size[0] - 1;
    trueCount = 0;
    for (i = 0; i <= n; i++) {
      if (vertFilterList->data[i]) {
        trueCount++;
      }
    }

    partialTrueCount = r2->size[0];
    r2->size[0] = trueCount;
    emxEnsureCapacity(sp, (emxArray__common *)r2, partialTrueCount, sizeof
                      (int32_T), &emlrtRTEI);
    partialTrueCount = 0;
    for (i = 0; i <= n; i++) {
      if (vertFilterList->data[i]) {
        r2->data[partialTrueCount] = i + 1;
        partialTrueCount++;
      }
    }

    st.site = &d_emlrtRSI;
    partialTrueCount = x->size[0];
    x->size[0] = r2->size[0];
    emxEnsureCapacity(&st, (emxArray__common *)x, partialTrueCount, sizeof
                      (boolean_T), &emlrtRTEI);
    loop_ub = r2->size[0];
    for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
      x->data[partialTrueCount] = (V->vertexCoorID->data[r2->
        data[partialTrueCount] - 1] != -1.0);
    }

    b_st.site = &v_emlrtRSI;
    nx = x->size[0];
    idx = 0;
    partialTrueCount = ii->size[0];
    ii->size[0] = x->size[0];
    emxEnsureCapacity(&b_st, (emxArray__common *)ii, partialTrueCount, sizeof
                      (int32_T), &emlrtRTEI);
    c_st.site = &w_emlrtRSI;
    overflow = ((!(1 > x->size[0])) && (x->size[0] > 2147483646));
    if (overflow) {
      d_st.site = &y_emlrtRSI;
      check_forloop_overflow_error(&d_st);
    }

    n = 1;
    exitg1 = false;
    while ((!exitg1) && (n <= nx)) {
      if (x->data[n - 1]) {
        idx++;
        ii->data[idx - 1] = n;
        if (idx >= nx) {
          exitg1 = true;
        } else {
          n++;
        }
      } else {
        n++;
      }
    }

    if (!(idx <= x->size[0])) {
      emlrtErrorWithMessageIdR2012b(&b_st, &v_emlrtRTEI,
        "Coder:builtins:AssertionFailed", 0);
    }

    if (x->size[0] == 1) {
      if (idx == 0) {
        partialTrueCount = ii->size[0];
        ii->size[0] = 0;
        emxEnsureCapacity(&b_st, (emxArray__common *)ii, partialTrueCount,
                          sizeof(int32_T), &emlrtRTEI);
      }
    } else {
      if (1 > idx) {
        partialTrueCount = 0;
      } else {
        partialTrueCount = idx;
      }

      b_V[0] = 1;
      b_V[1] = partialTrueCount;
      c_st.site = &x_emlrtRSI;
      indexShapeCheck(&c_st, ii->size[0], b_V);
      idx = ii->size[0];
      ii->size[0] = partialTrueCount;
      emxEnsureCapacity(&b_st, (emxArray__common *)ii, idx, sizeof(int32_T),
                        &b_emlrtRTEI);
    }

    iv0[0] = ii->size[0];
    partialTrueCount = vertexTerminal_circList->size[0];
    vertexTerminal_circList->size[0] = iv0[0];
    emxEnsureCapacity(sp, (emxArray__common *)vertexTerminal_circList,
                      partialTrueCount, sizeof(real_T), &emlrtRTEI);
    loop_ub = iv0[0];
    for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
      vertexTerminal_circList->data[partialTrueCount] = 0.0;
    }

    partialTrueCount = childEdge->size[0] * childEdge->size[1];
    childEdge->size[0] = s2rV->size[0];
    childEdge->size[1] = 2;
    emxEnsureCapacity(sp, (emxArray__common *)childEdge, partialTrueCount,
                      sizeof(real_T), &emlrtRTEI);
    loop_ub = s2rV->size[0] << 1;
    for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
      childEdge->data[partialTrueCount] = 0.0;
    }

    partialTrueCount = parentEdge->size[0] * parentEdge->size[1];
    parentEdge->size[0] = s2rV->size[0];
    parentEdge->size[1] = 2;
    emxEnsureCapacity(sp, (emxArray__common *)parentEdge, partialTrueCount,
                      sizeof(real_T), &emlrtRTEI);
    loop_ub = s2rV->size[0] << 1;
    for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
      parentEdge->data[partialTrueCount] = 0.0;
    }

    /* '2' because concave edges can have two parents */
    partialTrueCount = radMatrix->size[0];
    radMatrix->size[0] = s2rV->size[0];
    emxEnsureCapacity(sp, (emxArray__common *)radMatrix, partialTrueCount,
                      sizeof(real_T), &emlrtRTEI);
    loop_ub = s2rV->size[0];
    for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
      radMatrix->data[partialTrueCount] = 0.0;
    }

    partialTrueCount = distMatrix->size[0];
    distMatrix->size[0] = s2rV->size[0];
    emxEnsureCapacity(sp, (emxArray__common *)distMatrix, partialTrueCount,
                      sizeof(real_T), &emlrtRTEI);
    loop_ub = s2rV->size[0];
    for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
      distMatrix->data[partialTrueCount] = 0.0;
    }

    partialTrueCount = dirMat->size[0] * dirMat->size[1];
    dirMat->size[0] = s2rV->size[0];
    dirMat->size[1] = 2;
    emxEnsureCapacity(sp, (emxArray__common *)dirMat, partialTrueCount, sizeof
                      (real_T), &emlrtRTEI);
    loop_ub = s2rV->size[0] << 1;
    for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
      dirMat->data[partialTrueCount] = 0.0;
    }

    partialTrueCount = validStartPoints->size[0];
    idx = vsp + 1;
    if (!((idx >= 1) && (idx <= partialTrueCount))) {
      emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &mb_emlrtBCI, sp);
    }

    /* s2rV(startPointID);%records.vorVert(s2rV(startPointID),:); */
    partialTrueCount = r2sV->size[0];
    idx = validStartPoints->data[vsp];
    if (!((idx >= 1) && (idx <= partialTrueCount))) {
      emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &lb_emlrtBCI, sp);
    }

    n = s2rV->size[0];
    if (!(1 <= n)) {
      emlrtDynamicBoundsCheckR2012b(1, 1, n, &w_emlrtBCI, sp);
    }

    for (partialTrueCount = 0; partialTrueCount < 2; partialTrueCount++) {
      dirMat->data[dirMat->size[0] * partialTrueCount] = -0.0 - (real_T)
        partialTrueCount;
    }

    /* downward at start */
    partialTrueCount = s2rV->size[0];
    if (!(1 <= partialTrueCount)) {
      emlrtDynamicBoundsCheckR2012b(1, 1, partialTrueCount, &e_emlrtBCI, sp);
    }

    partialTrueCount = V->rad->size[0];
    idx = validStartPoints->data[vsp];
    if (!((idx >= 1) && (idx <= partialTrueCount))) {
      emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &kb_emlrtBCI, sp);
    }

    /* startPoint(3); */
    partialTrueCount = s2rV->size[0];
    if (!(1 <= partialTrueCount)) {
      emlrtDynamicBoundsCheckR2012b(1, 1, partialTrueCount, &d_emlrtBCI, sp);
    }

    partialTrueCount = vertexCollectionList->size[0];
    if (!(1 <= partialTrueCount)) {
      emlrtDynamicBoundsCheckR2012b(1, 1, partialTrueCount, &jb_emlrtBCI, sp);
    }

    vertexCollectionList->data[0] = validStartPoints->data[vsp];

    /* s2rV(startPointID); */
    n = s2rV->size[0];
    d0 = r2sV->data[validStartPoints->data[vsp] - 1];
    if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
      emlrtIntegerCheckR2012b(d0, &s_emlrtDCI, sp);
    }

    partialTrueCount = (int32_T)d0;
    if (!((partialTrueCount >= 1) && (partialTrueCount <= n))) {
      emlrtDynamicBoundsCheckR2012b(partialTrueCount, 1, n, &pb_emlrtBCI, sp);
    }

    parentEdge->data[partialTrueCount - 1] = -1.0;
    iter = 1U;

    /*      reversing = 0; */
    terminals = 0U;
    partialTrueCount = vertexCollectionList->size[0];
    if (!(1 <= partialTrueCount)) {
      emlrtDynamicBoundsCheckR2012b(1, 1, partialTrueCount, &ib_emlrtBCI, sp);
    }

    startingVertexInd = (int32_T)vertexCollectionList->data[0];

    /* loop until a termination condition has been met */
    do {
      exitg2 = 0;
      st.site = &e_emlrtRSI;
      toLogicalCheck(&st, 0.0);

      /*      if(totalCount == 187) */
      /*          disp('pause') */
      /*      end */
      partialTrueCount = vertexCollectionList->size[0];
      idx = (int32_T)iter;
      if (!((idx >= 1) && (idx <= partialTrueCount))) {
        emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &qb_emlrtBCI, sp);
      }

      /* records.vorVert(vertexCollectionList(iter),:); */
      partialTrueCount = vertexTerminal->size[0];
      idx = vertexCollectionList->size[0];
      nx = (int32_T)iter;
      if (!((nx >= 1) && (nx <= idx))) {
        emlrtDynamicBoundsCheckR2012b(nx, 1, idx, &sb_emlrtBCI, sp);
      }

      d0 = vertexCollectionList->data[nx - 1];
      if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
        emlrtIntegerCheckR2012b(d0, &t_emlrtDCI, sp);
      }

      idx = (int32_T)d0;
      if (!((idx >= 1) && (idx <= partialTrueCount))) {
        emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &rb_emlrtBCI, sp);
      }

      guard1 = false;
      guard2 = false;
      if (!vertexTerminal->data[idx - 1]) {
        /* If it is not a terminal vertex... */
        partialTrueCount = parentEdge->size[0];
        idx = r2sV->size[0];
        nx = vertexCollectionList->size[0];
        n = (int32_T)iter;
        if (!((n >= 1) && (n <= nx))) {
          emlrtDynamicBoundsCheckR2012b(n, 1, nx, &fc_emlrtBCI, sp);
        }

        d0 = vertexCollectionList->data[n - 1];
        if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
          emlrtIntegerCheckR2012b(d0, &bb_emlrtDCI, sp);
        }

        nx = (int32_T)d0;
        if (!((nx >= 1) && (nx <= idx))) {
          emlrtDynamicBoundsCheckR2012b(nx, 1, idx, &ec_emlrtBCI, sp);
        }

        d0 = r2sV->data[nx - 1];
        if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
          emlrtIntegerCheckR2012b(d0, &ab_emlrtDCI, sp);
        }

        idx = (int32_T)d0;
        if (!((idx >= 1) && (idx <= partialTrueCount))) {
          emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &dc_emlrtBCI,
            sp);
        }

        if (parentEdge->data[(idx + parentEdge->size[0]) - 1] == 0.0) {
          /* Store the parent edge */
          partialTrueCount = parentEdge->size[0];
          idx = r2sV->size[0];
          nx = vertexCollectionList->size[0];
          n = (int32_T)iter;
          if (!((n >= 1) && (n <= nx))) {
            emlrtDynamicBoundsCheckR2012b(n, 1, nx, &lc_emlrtBCI, sp);
          }

          d0 = vertexCollectionList->data[n - 1];
          if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
            emlrtIntegerCheckR2012b(d0, &fb_emlrtDCI, sp);
          }

          nx = (int32_T)d0;
          if (!((nx >= 1) && (nx <= idx))) {
            emlrtDynamicBoundsCheckR2012b(nx, 1, idx, &kc_emlrtBCI, sp);
          }

          d0 = r2sV->data[nx - 1];
          if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
            emlrtIntegerCheckR2012b(d0, &eb_emlrtDCI, sp);
          }

          idx = (int32_T)d0;
          if (!((idx >= 1) && (idx <= partialTrueCount))) {
            emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &jc_emlrtBCI,
              sp);
          }

          parEdge = parentEdge->data[idx - 1];
        } else {
          partialTrueCount = parentEdge->size[0];
          idx = r2sV->size[0];
          nx = vertexCollectionList->size[0];
          n = (int32_T)iter;
          if (!((n >= 1) && (n <= nx))) {
            emlrtDynamicBoundsCheckR2012b(n, 1, nx, &ic_emlrtBCI, sp);
          }

          d0 = vertexCollectionList->data[n - 1];
          if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
            emlrtIntegerCheckR2012b(d0, &db_emlrtDCI, sp);
          }

          nx = (int32_T)d0;
          if (!((nx >= 1) && (nx <= idx))) {
            emlrtDynamicBoundsCheckR2012b(nx, 1, idx, &hc_emlrtBCI, sp);
          }

          d0 = r2sV->data[nx - 1];
          if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
            emlrtIntegerCheckR2012b(d0, &cb_emlrtDCI, sp);
          }

          idx = (int32_T)d0;
          if (!((idx >= 1) && (idx <= partialTrueCount))) {
            emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &gc_emlrtBCI,
              sp);
          }

          parEdge = parentEdge->data[(idx + parentEdge->size[0]) - 1];
        }

        partialTrueCount = V->degree->size[0];
        d0 = vertexCollectionList->data[(int32_T)iter - 1];
        if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
          emlrtIntegerCheckR2012b(d0, &o_emlrtDCI, sp);
        }

        idx = (int32_T)d0;
        if (!((idx >= 1) && (idx <= partialTrueCount))) {
          emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &gb_emlrtBCI,
            sp);
        }

        if (1.0 > V->degree->data[(int32_T)vertexCollectionList->data[(int32_T)
            iter - 1] - 1]) {
          loop_ub = 0;
        } else {
          d0 = V->degree->data[(int32_T)vertexCollectionList->data[(int32_T)iter
            - 1] - 1];
          if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
            emlrtIntegerCheckR2012b(d0, &n_emlrtDCI, sp);
          }

          loop_ub = (int32_T)d0;
          if (!((loop_ub >= 1) && (loop_ub <= 4))) {
            emlrtDynamicBoundsCheckR2012b(loop_ub, 1, 4, &fb_emlrtBCI, sp);
          }
        }

        partialTrueCount = V->edgeIDList->size[0];
        n = (int32_T)vertexCollectionList->data[(int32_T)iter - 1];
        if (!((n >= 1) && (n <= partialTrueCount))) {
          emlrtDynamicBoundsCheckR2012b(n, 1, partialTrueCount, &hb_emlrtBCI, sp);
        }

        for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount
             ++) {
          c_edgeIndexMatrixFiltConnected_[partialTrueCount] = V->
            edgeIDList->data[(n + V->edgeIDList->size[0] * partialTrueCount) - 1];
        }

        /* curVert(9:8+curVert(8));		%%Edges connected to this vertex */
        V_size[0] = 1;
        V_size[1] = loop_ub;
        for (partialTrueCount = 0; partialTrueCount < 2; partialTrueCount++) {
          b_V[partialTrueCount] = V_size[partialTrueCount];
        }

        st.site = &f_emlrtRSI;
        indexShapeCheck(&st, edgeFilterList->size[0], b_V);
        nx = edgeFilterList->size[0];
        for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount
             ++) {
          if (c_edgeIndexMatrixFiltConnected_[partialTrueCount] != (int32_T)
              muDoubleScalarFloor
              (c_edgeIndexMatrixFiltConnected_[partialTrueCount])) {
            emlrtIntegerCheckR2012b
              (c_edgeIndexMatrixFiltConnected_[partialTrueCount], &gb_emlrtDCI,
               sp);
          }

          idx = (int32_T)c_edgeIndexMatrixFiltConnected_[partialTrueCount];
          if (!((idx >= 1) && (idx <= nx))) {
            emlrtDynamicBoundsCheckR2012b(idx, 1, nx, &mc_emlrtBCI, sp);
          }
        }

        for (i = 0; i < loop_ub; i++) {
          if (edgeFilterList->data[(int32_T)c_edgeIndexMatrixFiltConnected_[i] -
              1] && (!((i + 1 >= 1) && (i + 1 <= loop_ub)))) {
            emlrtDynamicBoundsCheckR2012b(i + 1, 1, loop_ub, &b_emlrtBCI, sp);
          }
        }

        /* Edges in subgraph region */
        n = loop_ub - 1;
        trueCount = 0;
        for (i = 0; i <= n; i++) {
          if (edgeFilterList->data[(int32_T)c_edgeIndexMatrixFiltConnected_[i] -
              1]) {
            trueCount++;
          }
        }

        partialTrueCount = 0;
        for (i = 0; i <= n; i++) {
          if (edgeFilterList->data[(int32_T)c_edgeIndexMatrixFiltConnected_[i] -
              1]) {
            f_tmp_data[partialTrueCount] = i + 1;
            partialTrueCount++;
          }
        }

        for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount
             ++) {
          d_edgeIndexMatrixFiltConnected_[partialTrueCount] = (uint32_T)
            c_edgeIndexMatrixFiltConnected_[partialTrueCount];
        }

        for (partialTrueCount = 0; partialTrueCount < trueCount;
             partialTrueCount++) {
          b_tmp_data[partialTrueCount] =
            (d_edgeIndexMatrixFiltConnected_[f_tmp_data[partialTrueCount] - 1]
             != parEdge);
        }

        n = trueCount - 1;
        trueCount = 0;
        for (i = 0; i <= n; i++) {
          if (b_tmp_data[i]) {
            trueCount++;
          }
        }

        partialTrueCount = 0;
        for (i = 0; i <= n; i++) {
          if (b_tmp_data[i]) {
            h_tmp_data[partialTrueCount] = i + 1;
            partialTrueCount++;
          }
        }

        n = loop_ub - 1;
        b_trueCount = 0;
        for (i = 0; i <= n; i++) {
          if (edgeFilterList->data[(int32_T)c_edgeIndexMatrixFiltConnected_[i] -
              1]) {
            b_trueCount++;
          }
        }

        for (partialTrueCount = 0; partialTrueCount < trueCount;
             partialTrueCount++) {
          if (!((h_tmp_data[partialTrueCount] >= 1) &&
                (h_tmp_data[partialTrueCount] <= b_trueCount))) {
            emlrtDynamicBoundsCheckR2012b(h_tmp_data[partialTrueCount], 1,
              b_trueCount, &nc_emlrtBCI, sp);
          }
        }

        /* Edge is not an immediate reversal */
        n = loop_ub - 1;
        trueCount = 0;
        for (i = 0; i <= n; i++) {
          if (edgeFilterList->data[(int32_T)c_edgeIndexMatrixFiltConnected_[i] -
              1]) {
            trueCount++;
          }
        }

        partialTrueCount = 0;
        for (i = 0; i <= n; i++) {
          if (edgeFilterList->data[(int32_T)c_edgeIndexMatrixFiltConnected_[i] -
              1]) {
            k_tmp_data[partialTrueCount] = i + 1;
            partialTrueCount++;
          }
        }

        for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount
             ++) {
          d_edgeIndexMatrixFiltConnected_[partialTrueCount] = (uint32_T)
            c_edgeIndexMatrixFiltConnected_[partialTrueCount];
        }

        for (partialTrueCount = 0; partialTrueCount < trueCount;
             partialTrueCount++) {
          b_tmp_data[partialTrueCount] =
            (d_edgeIndexMatrixFiltConnected_[k_tmp_data[partialTrueCount] - 1]
             != parEdge);
        }

        n = trueCount - 1;
        trueCount = 0;
        for (i = 0; i <= n; i++) {
          if (b_tmp_data[i]) {
            trueCount++;
          }
        }

        tmp_size[0] = 1;
        tmp_size[1] = trueCount;
        st.site = &g_emlrtRSI;
        indexShapeCheck(&st, edgeProcessed->size[0], tmp_size);
        n = loop_ub - 1;
        trueCount = 0;
        for (i = 0; i <= n; i++) {
          if (edgeFilterList->data[(int32_T)c_edgeIndexMatrixFiltConnected_[i] -
              1]) {
            trueCount++;
          }
        }

        partialTrueCount = 0;
        for (i = 0; i <= n; i++) {
          if (edgeFilterList->data[(int32_T)c_edgeIndexMatrixFiltConnected_[i] -
              1]) {
            n_tmp_data[partialTrueCount] = i + 1;
            partialTrueCount++;
          }
        }

        for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount
             ++) {
          d_edgeIndexMatrixFiltConnected_[partialTrueCount] = (uint32_T)
            c_edgeIndexMatrixFiltConnected_[partialTrueCount];
        }

        for (partialTrueCount = 0; partialTrueCount < trueCount;
             partialTrueCount++) {
          b_tmp_data[partialTrueCount] =
            (d_edgeIndexMatrixFiltConnected_[n_tmp_data[partialTrueCount] - 1]
             != parEdge);
        }

        n = loop_ub - 1;
        b_trueCount = 0;
        for (i = 0; i <= n; i++) {
          if (edgeFilterList->data[(int32_T)c_edgeIndexMatrixFiltConnected_[i] -
              1]) {
            b_trueCount++;
          }
        }

        partialTrueCount = 0;
        for (i = 0; i <= n; i++) {
          if (edgeFilterList->data[(int32_T)c_edgeIndexMatrixFiltConnected_[i] -
              1]) {
            q_tmp_data[partialTrueCount] = i + 1;
            partialTrueCount++;
          }
        }

        n = trueCount - 1;
        c_trueCount = 0;
        for (i = 0; i <= n; i++) {
          if (b_tmp_data[i]) {
            c_trueCount++;
          }
        }

        partialTrueCount = 0;
        for (i = 0; i <= n; i++) {
          if (b_tmp_data[i]) {
            t_tmp_data[partialTrueCount] = i + 1;
            partialTrueCount++;
          }
        }

        for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount
             ++) {
          d_edgeIndexMatrixFiltConnected_[partialTrueCount] = (uint32_T)
            c_edgeIndexMatrixFiltConnected_[partialTrueCount];
        }

        for (partialTrueCount = 0; partialTrueCount < b_trueCount;
             partialTrueCount++) {
          e_edgeIndexMatrixFiltConnected_[partialTrueCount] =
            d_edgeIndexMatrixFiltConnected_[q_tmp_data[partialTrueCount] - 1];
        }

        nx = edgeProcessed->size[0];
        for (partialTrueCount = 0; partialTrueCount < c_trueCount;
             partialTrueCount++) {
          idx = (int32_T)
            e_edgeIndexMatrixFiltConnected_[t_tmp_data[partialTrueCount] - 1];
          if (!((idx >= 1) && (idx <= nx))) {
            emlrtDynamicBoundsCheckR2012b(idx, 1, nx, &oc_emlrtBCI, sp);
          }

          e_tmp_data[partialTrueCount] = !(edgeProcessed->data[idx - 1] != 0);
        }

        n = c_trueCount - 1;
        b_trueCount = 0;
        for (i = 0; i <= n; i++) {
          if (e_tmp_data[i]) {
            b_trueCount++;
          }
        }

        partialTrueCount = 0;
        for (i = 0; i <= n; i++) {
          if (e_tmp_data[i]) {
            u_tmp_data[partialTrueCount] = i + 1;
            partialTrueCount++;
          }
        }

        n = trueCount - 1;
        trueCount = 0;
        for (i = 0; i <= n; i++) {
          if (b_tmp_data[i]) {
            trueCount++;
          }
        }

        for (partialTrueCount = 0; partialTrueCount < b_trueCount;
             partialTrueCount++) {
          if (!((u_tmp_data[partialTrueCount] >= 1) &&
                (u_tmp_data[partialTrueCount] <= trueCount))) {
            emlrtDynamicBoundsCheckR2012b(u_tmp_data[partialTrueCount], 1,
              trueCount, &pc_emlrtBCI, sp);
          }
        }

        /* Edge has not been touched */
        n = loop_ub - 1;
        trueCount = 0;
        for (i = 0; i <= n; i++) {
          if (edgeFilterList->data[(int32_T)c_edgeIndexMatrixFiltConnected_[i] -
              1]) {
            trueCount++;
          }
        }

        partialTrueCount = 0;
        for (i = 0; i <= n; i++) {
          if (edgeFilterList->data[(int32_T)c_edgeIndexMatrixFiltConnected_[i] -
              1]) {
            y_tmp_data[partialTrueCount] = i + 1;
            partialTrueCount++;
          }
        }

        for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount
             ++) {
          d_edgeIndexMatrixFiltConnected_[partialTrueCount] = (uint32_T)
            c_edgeIndexMatrixFiltConnected_[partialTrueCount];
        }

        for (partialTrueCount = 0; partialTrueCount < trueCount;
             partialTrueCount++) {
          b_tmp_data[partialTrueCount] =
            (d_edgeIndexMatrixFiltConnected_[y_tmp_data[partialTrueCount] - 1]
             != parEdge);
        }

        n = loop_ub - 1;
        b_trueCount = 0;
        for (i = 0; i <= n; i++) {
          if (edgeFilterList->data[(int32_T)c_edgeIndexMatrixFiltConnected_[i] -
              1]) {
            b_trueCount++;
          }
        }

        partialTrueCount = 0;
        for (i = 0; i <= n; i++) {
          if (edgeFilterList->data[(int32_T)c_edgeIndexMatrixFiltConnected_[i] -
              1]) {
            db_tmp_data[partialTrueCount] = i + 1;
            partialTrueCount++;
          }
        }

        n = trueCount - 1;
        trueCount = 0;
        for (i = 0; i <= n; i++) {
          if (b_tmp_data[i]) {
            trueCount++;
          }
        }

        partialTrueCount = 0;
        for (i = 0; i <= n; i++) {
          if (b_tmp_data[i]) {
            fb_tmp_data[partialTrueCount] = i + 1;
            partialTrueCount++;
          }
        }

        for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount
             ++) {
          d_edgeIndexMatrixFiltConnected_[partialTrueCount] = (uint32_T)
            c_edgeIndexMatrixFiltConnected_[partialTrueCount];
        }

        for (partialTrueCount = 0; partialTrueCount < b_trueCount;
             partialTrueCount++) {
          e_edgeIndexMatrixFiltConnected_[partialTrueCount] =
            d_edgeIndexMatrixFiltConnected_[db_tmp_data[partialTrueCount] - 1];
        }

        for (partialTrueCount = 0; partialTrueCount < trueCount;
             partialTrueCount++) {
          e_tmp_data[partialTrueCount] = !(edgeProcessed->data[(int32_T)
            e_edgeIndexMatrixFiltConnected_[fb_tmp_data[partialTrueCount] - 1] -
            1] != 0);
        }

        n = trueCount - 1;
        trueCount = 0;
        for (i = 0; i <= n; i++) {
          if (e_tmp_data[i]) {
            trueCount++;
          }
        }

        if (trueCount == 0) {
          partialTrueCount = vertexCollectionList->size[0];
          idx = (int32_T)iter;
          if (!((idx >= 1) && (idx <= partialTrueCount))) {
            emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &qc_emlrtBCI,
              sp);
          }

          if (vertexCollectionList->data[idx - 1] == startingVertexInd) {
            st.site = &h_emlrtRSI;
            toLogicalCheck(&st, 1.0);

            /* all paths exhausted, terminate... */
            iter++;

            /* to not purge information... */
            exitg2 = 1;
          } else {
            guard2 = true;
          }
        } else {
          guard2 = true;
        }
      } else {
        partialTrueCount = vertexTerminal_SubGraph_Proc->size[0];
        idx = r2sV->size[0];
        nx = vertexCollectionList->size[0];
        n = (int32_T)iter;
        if (!((n >= 1) && (n <= nx))) {
          emlrtDynamicBoundsCheckR2012b(n, 1, nx, &vb_emlrtBCI, sp);
        }

        d0 = vertexCollectionList->data[n - 1];
        if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
          emlrtIntegerCheckR2012b(d0, &v_emlrtDCI, sp);
        }

        nx = (int32_T)d0;
        if (!((nx >= 1) && (nx <= idx))) {
          emlrtDynamicBoundsCheckR2012b(nx, 1, idx, &ub_emlrtBCI, sp);
        }

        d0 = r2sV->data[nx - 1];
        if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
          emlrtIntegerCheckR2012b(d0, &u_emlrtDCI, sp);
        }

        idx = (int32_T)d0;
        if (!((idx >= 1) && (idx <= partialTrueCount))) {
          emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &tb_emlrtBCI,
            sp);
        }

        if (vertexTerminal_SubGraph_Proc->data[idx - 1]) {
          partialTrueCount = vertexTerminal_SubGraph_Proc->size[0];
          idx = r2sV->size[0];
          nx = vertexCollectionList->size[0];
          n = (int32_T)iter;
          if (!((n >= 1) && (n <= nx))) {
            emlrtDynamicBoundsCheckR2012b(n, 1, nx, &yb_emlrtBCI, sp);
          }

          d0 = vertexCollectionList->data[n - 1];
          if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
            emlrtIntegerCheckR2012b(d0, &x_emlrtDCI, sp);
          }

          nx = (int32_T)d0;
          if (!((nx >= 1) && (nx <= idx))) {
            emlrtDynamicBoundsCheckR2012b(nx, 1, idx, &xb_emlrtBCI, sp);
          }

          d0 = r2sV->data[nx - 1];
          if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
            emlrtIntegerCheckR2012b(d0, &w_emlrtDCI, sp);
          }

          idx = (int32_T)d0;
          if (!((idx >= 1) && (idx <= partialTrueCount))) {
            emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &wb_emlrtBCI,
              sp);
          }

          vertexTerminal_SubGraph_Proc->data[idx - 1] = false;

          /* Found */
          terminals++;
          partialTrueCount = r2sV->size[0];
          idx = vertexCollectionList->size[0];
          nx = (int32_T)iter;
          if (!((nx >= 1) && (nx <= idx))) {
            emlrtDynamicBoundsCheckR2012b(nx, 1, idx, &bc_emlrtBCI, sp);
          }

          d0 = vertexCollectionList->data[nx - 1];
          if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
            emlrtIntegerCheckR2012b(d0, &y_emlrtDCI, sp);
          }

          idx = (int32_T)d0;
          if (!((idx >= 1) && (idx <= partialTrueCount))) {
            emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &ac_emlrtBCI,
              sp);
          }

          partialTrueCount = vertexTerminal_circList->size[0];
          nx = (int32_T)terminals;
          if (!((nx >= 1) && (nx <= partialTrueCount))) {
            emlrtDynamicBoundsCheckR2012b(nx, 1, partialTrueCount, &cc_emlrtBCI,
              sp);
          }

          vertexTerminal_circList->data[nx - 1] = r2sV->data[idx - 1];

          /*                  if(dbgplot) */
          /*                      plot(V.pos(curVert,1),V.pos(curVert,2),'go','MarkerSize',6,'MarkerFaceColor','g'); */
          /*                      plot(V.pos(curVert,1),V.pos(curVert,2),'rx','MarkerSize',6,'MarkerFaceColor','r'); */
          /*                      xlim([V.pos(curVert,1)-20,V.pos(curVert,1)+20]); */
          /*                      ylim([V.pos(curVert,2)-20,V.pos(curVert,2)+20]); */
          /*                      %                 f = getframe; */
          /*                      %                 imwrite(f.cdata,strcat('D:\Miracles\uglyAGAIN',num2str(totalCount), '.tiff')); */
          /*                      drawnow; */
          /*                  end */
        }

        iter = (uint32_T)((int32_T)iter - 1);
        guard1 = true;
      }

      if (guard2) {
        n = loop_ub - 1;
        trueCount = 0;
        for (i = 0; i <= n; i++) {
          if (edgeFilterList->data[(int32_T)c_edgeIndexMatrixFiltConnected_[i] -
              1]) {
            trueCount++;
          }
        }

        partialTrueCount = 0;
        for (i = 0; i <= n; i++) {
          if (edgeFilterList->data[(int32_T)c_edgeIndexMatrixFiltConnected_[i] -
              1]) {
            tmp_data[partialTrueCount] = i + 1;
            partialTrueCount++;
          }
        }

        for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount
             ++) {
          d_edgeIndexMatrixFiltConnected_[partialTrueCount] = (uint32_T)
            c_edgeIndexMatrixFiltConnected_[partialTrueCount];
        }

        for (partialTrueCount = 0; partialTrueCount < trueCount;
             partialTrueCount++) {
          b_tmp_data[partialTrueCount] =
            (d_edgeIndexMatrixFiltConnected_[tmp_data[partialTrueCount] - 1] !=
             parEdge);
        }

        n = loop_ub - 1;
        b_trueCount = 0;
        for (i = 0; i <= n; i++) {
          if (edgeFilterList->data[(int32_T)c_edgeIndexMatrixFiltConnected_[i] -
              1]) {
            b_trueCount++;
          }
        }

        partialTrueCount = 0;
        for (i = 0; i <= n; i++) {
          if (edgeFilterList->data[(int32_T)c_edgeIndexMatrixFiltConnected_[i] -
              1]) {
            c_tmp_data[partialTrueCount] = i + 1;
            partialTrueCount++;
          }
        }

        n = trueCount - 1;
        trueCount = 0;
        for (i = 0; i <= n; i++) {
          if (b_tmp_data[i]) {
            trueCount++;
          }
        }

        partialTrueCount = 0;
        for (i = 0; i <= n; i++) {
          if (b_tmp_data[i]) {
            d_tmp_data[partialTrueCount] = i + 1;
            partialTrueCount++;
          }
        }

        for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount
             ++) {
          d_edgeIndexMatrixFiltConnected_[partialTrueCount] = (uint32_T)
            c_edgeIndexMatrixFiltConnected_[partialTrueCount];
        }

        for (partialTrueCount = 0; partialTrueCount < b_trueCount;
             partialTrueCount++) {
          e_edgeIndexMatrixFiltConnected_[partialTrueCount] =
            d_edgeIndexMatrixFiltConnected_[c_tmp_data[partialTrueCount] - 1];
        }

        for (partialTrueCount = 0; partialTrueCount < trueCount;
             partialTrueCount++) {
          e_tmp_data[partialTrueCount] = !(edgeProcessed->data[(int32_T)
            e_edgeIndexMatrixFiltConnected_[d_tmp_data[partialTrueCount] - 1] -
            1] != 0);
        }

        n = trueCount - 1;
        trueCount = 0;
        for (i = 0; i <= n; i++) {
          if (e_tmp_data[i]) {
            trueCount++;
          }
        }

        if (trueCount == 0) {
          /* If no edges are valid, reverse */
          iter = (uint32_T)((int32_T)iter - 1);

          /*                  if(dbgplot) */
          /*                      plot(V.pos(curVert,1),V.pos(curVert,2),'rx','MarkerSize',6,'MarkerFaceColor','r'); */
          /*                      xlim([V.pos(curVert,1)-20,V.pos(curVert,1)+20]); */
          /*                      ylim([V.pos(curVert,2)-20,V.pos(curVert,2)+20]); */
          /*                      %                 f = getframe; */
          /*                      totalCount = totalCount + 1; */
          /*                      %                 imwrite(f.cdata,strcat('D:\Miracles\uglyAGAIN',num2str(totalCount), '.tiff')); */
          /*                      drawnow; */
          /*                  end */
          /*                  reversing = 1; */
          guard1 = true;
        } else {
          /*                  if(dbgplot && ~reversing) */
          /*                      plot(V.pos(curVert,1),V.pos(curVert,2),'go','MarkerSize',6,'MarkerFaceColor','g'); */
          /*                      xlim([V.pos(curVert,1)-20,V.pos(curVert,1)+20]); */
          /*                      ylim([V.pos(curVert,2)-20,V.pos(curVert,2)+20]); */
          /*                      totalCount = totalCount + 1; */
          /*                      %                 f = getframe; */
          /*                      %                 imwrite(f.cdata,strcat('D:\Miracles\uglyAGAIN',num2str(totalCount), '.tiff')); */
          /*                      drawnow; */
          /*                  end */
          /*                  reversing = 0; */
          n = loop_ub - 1;
          trueCount = 0;
          for (i = 0; i <= n; i++) {
            if (edgeFilterList->data[(int32_T)c_edgeIndexMatrixFiltConnected_[i]
                - 1]) {
              trueCount++;
            }
          }

          partialTrueCount = 0;
          for (i = 0; i <= n; i++) {
            if (edgeFilterList->data[(int32_T)c_edgeIndexMatrixFiltConnected_[i]
                - 1]) {
              g_tmp_data[partialTrueCount] = i + 1;
              partialTrueCount++;
            }
          }

          for (partialTrueCount = 0; partialTrueCount < loop_ub;
               partialTrueCount++) {
            d_edgeIndexMatrixFiltConnected_[partialTrueCount] = (uint32_T)
              c_edgeIndexMatrixFiltConnected_[partialTrueCount];
          }

          for (partialTrueCount = 0; partialTrueCount < trueCount;
               partialTrueCount++) {
            b_tmp_data[partialTrueCount] =
              (d_edgeIndexMatrixFiltConnected_[g_tmp_data[partialTrueCount] - 1]
               != parEdge);
          }

          n = loop_ub - 1;
          b_trueCount = 0;
          for (i = 0; i <= n; i++) {
            if (edgeFilterList->data[(int32_T)c_edgeIndexMatrixFiltConnected_[i]
                - 1]) {
              b_trueCount++;
            }
          }

          partialTrueCount = 0;
          for (i = 0; i <= n; i++) {
            if (edgeFilterList->data[(int32_T)c_edgeIndexMatrixFiltConnected_[i]
                - 1]) {
              i_tmp_data[partialTrueCount] = i + 1;
              partialTrueCount++;
            }
          }

          n = trueCount - 1;
          trueCount = 0;
          for (i = 0; i <= n; i++) {
            if (b_tmp_data[i]) {
              trueCount++;
            }
          }

          partialTrueCount = 0;
          for (i = 0; i <= n; i++) {
            if (b_tmp_data[i]) {
              j_tmp_data[partialTrueCount] = i + 1;
              partialTrueCount++;
            }
          }

          for (partialTrueCount = 0; partialTrueCount < loop_ub;
               partialTrueCount++) {
            d_edgeIndexMatrixFiltConnected_[partialTrueCount] = (uint32_T)
              c_edgeIndexMatrixFiltConnected_[partialTrueCount];
          }

          for (partialTrueCount = 0; partialTrueCount < b_trueCount;
               partialTrueCount++) {
            e_edgeIndexMatrixFiltConnected_[partialTrueCount] =
              d_edgeIndexMatrixFiltConnected_[i_tmp_data[partialTrueCount] - 1];
          }

          for (partialTrueCount = 0; partialTrueCount < trueCount;
               partialTrueCount++) {
            e_tmp_data[partialTrueCount] = !(edgeProcessed->data[(int32_T)
              e_edgeIndexMatrixFiltConnected_[j_tmp_data[partialTrueCount] - 1]
              - 1] != 0);
          }

          n = trueCount - 1;
          trueCount = 0;
          for (i = 0; i <= n; i++) {
            if (e_tmp_data[i]) {
              trueCount++;
            }
          }

          if (trueCount == 1) {
            /* Don't test if only one edge is there */
            n = loop_ub - 1;
            trueCount = 0;
            for (i = 0; i <= n; i++) {
              if (edgeFilterList->data[(int32_T)
                  c_edgeIndexMatrixFiltConnected_[i] - 1]) {
                trueCount++;
              }
            }

            partialTrueCount = 0;
            for (i = 0; i <= n; i++) {
              if (edgeFilterList->data[(int32_T)
                  c_edgeIndexMatrixFiltConnected_[i] - 1]) {
                m_tmp_data[partialTrueCount] = i + 1;
                partialTrueCount++;
              }
            }

            for (partialTrueCount = 0; partialTrueCount < loop_ub;
                 partialTrueCount++) {
              d_edgeIndexMatrixFiltConnected_[partialTrueCount] = (uint32_T)
                c_edgeIndexMatrixFiltConnected_[partialTrueCount];
            }

            for (partialTrueCount = 0; partialTrueCount < trueCount;
                 partialTrueCount++) {
              b_tmp_data[partialTrueCount] =
                (d_edgeIndexMatrixFiltConnected_[m_tmp_data[partialTrueCount] -
                 1] != parEdge);
            }

            n = loop_ub - 1;
            b_trueCount = 0;
            for (i = 0; i <= n; i++) {
              if (edgeFilterList->data[(int32_T)
                  c_edgeIndexMatrixFiltConnected_[i] - 1]) {
                b_trueCount++;
              }
            }

            partialTrueCount = 0;
            for (i = 0; i <= n; i++) {
              if (edgeFilterList->data[(int32_T)
                  c_edgeIndexMatrixFiltConnected_[i] - 1]) {
                p_tmp_data[partialTrueCount] = i + 1;
                partialTrueCount++;
              }
            }

            n = trueCount - 1;
            trueCount = 0;
            for (i = 0; i <= n; i++) {
              if (b_tmp_data[i]) {
                trueCount++;
              }
            }

            partialTrueCount = 0;
            for (i = 0; i <= n; i++) {
              if (b_tmp_data[i]) {
                s_tmp_data[partialTrueCount] = i + 1;
                partialTrueCount++;
              }
            }

            for (partialTrueCount = 0; partialTrueCount < loop_ub;
                 partialTrueCount++) {
              d_edgeIndexMatrixFiltConnected_[partialTrueCount] = (uint32_T)
                c_edgeIndexMatrixFiltConnected_[partialTrueCount];
            }

            for (partialTrueCount = 0; partialTrueCount < b_trueCount;
                 partialTrueCount++) {
              e_edgeIndexMatrixFiltConnected_[partialTrueCount] =
                d_edgeIndexMatrixFiltConnected_[p_tmp_data[partialTrueCount] - 1];
            }

            for (partialTrueCount = 0; partialTrueCount < trueCount;
                 partialTrueCount++) {
              e_tmp_data[partialTrueCount] = !(edgeProcessed->data[(int32_T)
                e_edgeIndexMatrixFiltConnected_[s_tmp_data[partialTrueCount] - 1]
                - 1] != 0);
            }

            n = trueCount - 1;
            trueCount = 0;
            for (i = 0; i <= n; i++) {
              if (e_tmp_data[i]) {
                trueCount++;
              }
            }

            if (!(1 <= trueCount)) {
              emlrtDynamicBoundsCheckR2012b(1, 1, trueCount, &eb_emlrtBCI, sp);
            }

            n = loop_ub - 1;
            trueCount = 0;
            for (i = 0; i <= n; i++) {
              if (edgeFilterList->data[(int32_T)
                  c_edgeIndexMatrixFiltConnected_[i] - 1]) {
                trueCount++;
              }
            }

            partialTrueCount = 0;
            for (i = 0; i <= n; i++) {
              if (edgeFilterList->data[(int32_T)
                  c_edgeIndexMatrixFiltConnected_[i] - 1]) {
                v_tmp_data[partialTrueCount] = i + 1;
                partialTrueCount++;
              }
            }

            for (partialTrueCount = 0; partialTrueCount < loop_ub;
                 partialTrueCount++) {
              d_edgeIndexMatrixFiltConnected_[partialTrueCount] = (uint32_T)
                c_edgeIndexMatrixFiltConnected_[partialTrueCount];
            }

            for (partialTrueCount = 0; partialTrueCount < trueCount;
                 partialTrueCount++) {
              b_tmp_data[partialTrueCount] =
                (d_edgeIndexMatrixFiltConnected_[v_tmp_data[partialTrueCount] -
                 1] != parEdge);
            }

            n = loop_ub - 1;
            b_trueCount = 0;
            for (i = 0; i <= n; i++) {
              if (edgeFilterList->data[(int32_T)
                  c_edgeIndexMatrixFiltConnected_[i] - 1]) {
                b_trueCount++;
              }
            }

            partialTrueCount = 0;
            for (i = 0; i <= n; i++) {
              if (edgeFilterList->data[(int32_T)
                  c_edgeIndexMatrixFiltConnected_[i] - 1]) {
                x_tmp_data[partialTrueCount] = i + 1;
                partialTrueCount++;
              }
            }

            n = trueCount - 1;
            c_trueCount = 0;
            for (i = 0; i <= n; i++) {
              if (b_tmp_data[i]) {
                c_trueCount++;
              }
            }

            partialTrueCount = 0;
            for (i = 0; i <= n; i++) {
              if (b_tmp_data[i]) {
                bb_tmp_data[partialTrueCount] = i + 1;
                partialTrueCount++;
              }
            }

            for (partialTrueCount = 0; partialTrueCount < loop_ub;
                 partialTrueCount++) {
              d_edgeIndexMatrixFiltConnected_[partialTrueCount] = (uint32_T)
                c_edgeIndexMatrixFiltConnected_[partialTrueCount];
            }

            for (partialTrueCount = 0; partialTrueCount < b_trueCount;
                 partialTrueCount++) {
              e_edgeIndexMatrixFiltConnected_[partialTrueCount] =
                d_edgeIndexMatrixFiltConnected_[x_tmp_data[partialTrueCount] - 1];
            }

            for (partialTrueCount = 0; partialTrueCount < c_trueCount;
                 partialTrueCount++) {
              e_tmp_data[partialTrueCount] = !(edgeProcessed->data[(int32_T)
                e_edgeIndexMatrixFiltConnected_[bb_tmp_data[partialTrueCount] -
                1] - 1] != 0);
            }

            n = loop_ub - 1;
            partialTrueCount = 0;
            for (i = 0; i <= n; i++) {
              if (edgeFilterList->data[(int32_T)
                  c_edgeIndexMatrixFiltConnected_[i] - 1]) {
                eb_tmp_data[partialTrueCount] = i + 1;
                partialTrueCount++;
              }
            }

            n = trueCount - 1;
            partialTrueCount = 0;
            for (i = 0; i <= n; i++) {
              if (b_tmp_data[i]) {
                gb_tmp_data[partialTrueCount] = i + 1;
                partialTrueCount++;
              }
            }

            n = c_trueCount - 1;
            partialTrueCount = 0;
            for (i = 0; i <= n; i++) {
              if (e_tmp_data[i]) {
                hb_tmp_data[partialTrueCount] = i + 1;
                partialTrueCount++;
              }
            }

            n = (int32_T)vertexCollectionList->data[(int32_T)iter - 1];
            parEdge = V->edgeIDList->data[(n + V->edgeIDList->size[0] *
              (eb_tmp_data[gb_tmp_data[hb_tmp_data[0] - 1] - 1] - 1)) - 1];
          } else {
            n = loop_ub - 1;
            trueCount = 0;
            for (i = 0; i <= n; i++) {
              if (edgeFilterList->data[(int32_T)
                  c_edgeIndexMatrixFiltConnected_[i] - 1]) {
                trueCount++;
              }
            }

            partialTrueCount = 0;
            for (i = 0; i <= n; i++) {
              if (edgeFilterList->data[(int32_T)
                  c_edgeIndexMatrixFiltConnected_[i] - 1]) {
                l_tmp_data[partialTrueCount] = i + 1;
                partialTrueCount++;
              }
            }

            for (partialTrueCount = 0; partialTrueCount < loop_ub;
                 partialTrueCount++) {
              d_edgeIndexMatrixFiltConnected_[partialTrueCount] = (uint32_T)
                c_edgeIndexMatrixFiltConnected_[partialTrueCount];
            }

            for (partialTrueCount = 0; partialTrueCount < trueCount;
                 partialTrueCount++) {
              b_tmp_data[partialTrueCount] =
                (d_edgeIndexMatrixFiltConnected_[l_tmp_data[partialTrueCount] -
                 1] != parEdge);
            }

            n = loop_ub - 1;
            b_trueCount = 0;
            for (i = 0; i <= n; i++) {
              if (edgeFilterList->data[(int32_T)
                  c_edgeIndexMatrixFiltConnected_[i] - 1]) {
                b_trueCount++;
              }
            }

            partialTrueCount = 0;
            for (i = 0; i <= n; i++) {
              if (edgeFilterList->data[(int32_T)
                  c_edgeIndexMatrixFiltConnected_[i] - 1]) {
                o_tmp_data[partialTrueCount] = i + 1;
                partialTrueCount++;
              }
            }

            n = trueCount - 1;
            trueCount = 0;
            for (i = 0; i <= n; i++) {
              if (b_tmp_data[i]) {
                trueCount++;
              }
            }

            partialTrueCount = 0;
            for (i = 0; i <= n; i++) {
              if (b_tmp_data[i]) {
                r_tmp_data[partialTrueCount] = i + 1;
                partialTrueCount++;
              }
            }

            for (partialTrueCount = 0; partialTrueCount < loop_ub;
                 partialTrueCount++) {
              d_edgeIndexMatrixFiltConnected_[partialTrueCount] = (uint32_T)
                c_edgeIndexMatrixFiltConnected_[partialTrueCount];
            }

            for (partialTrueCount = 0; partialTrueCount < b_trueCount;
                 partialTrueCount++) {
              e_edgeIndexMatrixFiltConnected_[partialTrueCount] =
                d_edgeIndexMatrixFiltConnected_[o_tmp_data[partialTrueCount] - 1];
            }

            for (partialTrueCount = 0; partialTrueCount < trueCount;
                 partialTrueCount++) {
              e_tmp_data[partialTrueCount] = !(edgeProcessed->data[(int32_T)
                e_edgeIndexMatrixFiltConnected_[r_tmp_data[partialTrueCount] - 1]
                - 1] != 0);
            }

            n = trueCount - 1;
            trueCount = 0;
            for (i = 0; i <= n; i++) {
              if (e_tmp_data[i]) {
                trueCount++;
              }
            }

            b_V[0] = 1;
            b_V[1] = trueCount;
            for (partialTrueCount = 0; partialTrueCount < 2; partialTrueCount++)
            {
              iv0[partialTrueCount] = b_V[partialTrueCount];
            }

            angleMat_size_idx_1 = iv0[1];
            b_loop_ub = iv0[1];
            for (partialTrueCount = 0; partialTrueCount < b_loop_ub;
                 partialTrueCount++) {
              angleMat_data[partialTrueCount] = 0.0;
            }

            n = loop_ub - 1;
            trueCount = 0;
            for (i = 0; i <= n; i++) {
              if (edgeFilterList->data[(int32_T)
                  c_edgeIndexMatrixFiltConnected_[i] - 1]) {
                trueCount++;
              }
            }

            partialTrueCount = 0;
            for (i = 0; i <= n; i++) {
              if (edgeFilterList->data[(int32_T)
                  c_edgeIndexMatrixFiltConnected_[i] - 1]) {
                w_tmp_data[partialTrueCount] = i + 1;
                partialTrueCount++;
              }
            }

            for (partialTrueCount = 0; partialTrueCount < loop_ub;
                 partialTrueCount++) {
              d_edgeIndexMatrixFiltConnected_[partialTrueCount] = (uint32_T)
                c_edgeIndexMatrixFiltConnected_[partialTrueCount];
            }

            for (partialTrueCount = 0; partialTrueCount < trueCount;
                 partialTrueCount++) {
              b_tmp_data[partialTrueCount] =
                (d_edgeIndexMatrixFiltConnected_[w_tmp_data[partialTrueCount] -
                 1] != parEdge);
            }

            n = loop_ub - 1;
            b_trueCount = 0;
            for (i = 0; i <= n; i++) {
              if (edgeFilterList->data[(int32_T)
                  c_edgeIndexMatrixFiltConnected_[i] - 1]) {
                b_trueCount++;
              }
            }

            partialTrueCount = 0;
            for (i = 0; i <= n; i++) {
              if (edgeFilterList->data[(int32_T)
                  c_edgeIndexMatrixFiltConnected_[i] - 1]) {
                ab_tmp_data[partialTrueCount] = i + 1;
                partialTrueCount++;
              }
            }

            n = trueCount - 1;
            trueCount = 0;
            for (i = 0; i <= n; i++) {
              if (b_tmp_data[i]) {
                trueCount++;
              }
            }

            partialTrueCount = 0;
            for (i = 0; i <= n; i++) {
              if (b_tmp_data[i]) {
                cb_tmp_data[partialTrueCount] = i + 1;
                partialTrueCount++;
              }
            }

            for (partialTrueCount = 0; partialTrueCount < loop_ub;
                 partialTrueCount++) {
              d_edgeIndexMatrixFiltConnected_[partialTrueCount] = (uint32_T)
                c_edgeIndexMatrixFiltConnected_[partialTrueCount];
            }

            for (partialTrueCount = 0; partialTrueCount < b_trueCount;
                 partialTrueCount++) {
              e_edgeIndexMatrixFiltConnected_[partialTrueCount] =
                d_edgeIndexMatrixFiltConnected_[ab_tmp_data[partialTrueCount] -
                1];
            }

            for (partialTrueCount = 0; partialTrueCount < trueCount;
                 partialTrueCount++) {
              e_tmp_data[partialTrueCount] = !(edgeProcessed->data[(int32_T)
                e_edgeIndexMatrixFiltConnected_[cb_tmp_data[partialTrueCount] -
                1] - 1] != 0);
            }

            n = trueCount - 1;
            trueCount = 0;
            for (i = 0; i <= n; i++) {
              if (e_tmp_data[i]) {
                trueCount++;
              }
            }

            if (0 <= trueCount - 1) {
              end = loop_ub - 1;
              c_loop_ub = loop_ub;
              b_end = loop_ub - 1;
              c_end = loop_ub - 1;
            }

            i = 0;
            while (i <= trueCount - 1) {
              b_trueCount = 0;
              for (nx = 0; nx <= end; nx++) {
                if (edgeFilterList->data[(int32_T)
                    c_edgeIndexMatrixFiltConnected_[nx] - 1]) {
                  b_trueCount++;
                }
              }

              partialTrueCount = 0;
              for (nx = 0; nx <= end; nx++) {
                if (edgeFilterList->data[(int32_T)
                    c_edgeIndexMatrixFiltConnected_[nx] - 1]) {
                  ib_tmp_data[partialTrueCount] = nx + 1;
                  partialTrueCount++;
                }
              }

              for (partialTrueCount = 0; partialTrueCount < c_loop_ub;
                   partialTrueCount++) {
                d_edgeIndexMatrixFiltConnected_[partialTrueCount] = (uint32_T)
                  c_edgeIndexMatrixFiltConnected_[partialTrueCount];
              }

              for (partialTrueCount = 0; partialTrueCount < b_trueCount;
                   partialTrueCount++) {
                b_tmp_data[partialTrueCount] =
                  (d_edgeIndexMatrixFiltConnected_[ib_tmp_data[partialTrueCount]
                   - 1] != parEdge);
              }

              c_trueCount = 0;
              for (nx = 0; nx <= b_end; nx++) {
                if (edgeFilterList->data[(int32_T)
                    c_edgeIndexMatrixFiltConnected_[nx] - 1]) {
                  c_trueCount++;
                }
              }

              partialTrueCount = 0;
              for (nx = 0; nx <= b_end; nx++) {
                if (edgeFilterList->data[(int32_T)
                    c_edgeIndexMatrixFiltConnected_[nx] - 1]) {
                  jb_tmp_data[partialTrueCount] = nx + 1;
                  partialTrueCount++;
                }
              }

              n = b_trueCount - 1;
              idx = 0;
              for (nx = 0; nx <= n; nx++) {
                if (b_tmp_data[nx]) {
                  idx++;
                }
              }

              partialTrueCount = 0;
              for (nx = 0; nx <= n; nx++) {
                if (b_tmp_data[nx]) {
                  kb_tmp_data[partialTrueCount] = nx + 1;
                  partialTrueCount++;
                }
              }

              for (partialTrueCount = 0; partialTrueCount < c_loop_ub;
                   partialTrueCount++) {
                d_edgeIndexMatrixFiltConnected_[partialTrueCount] = (uint32_T)
                  c_edgeIndexMatrixFiltConnected_[partialTrueCount];
              }

              for (partialTrueCount = 0; partialTrueCount < c_trueCount;
                   partialTrueCount++) {
                e_edgeIndexMatrixFiltConnected_[partialTrueCount] =
                  d_edgeIndexMatrixFiltConnected_[jb_tmp_data[partialTrueCount]
                  - 1];
              }

              for (partialTrueCount = 0; partialTrueCount < idx;
                   partialTrueCount++) {
                e_tmp_data[partialTrueCount] = !(edgeProcessed->data[(int32_T)
                  e_edgeIndexMatrixFiltConnected_[kb_tmp_data[partialTrueCount]
                  - 1] - 1] != 0);
              }

              partialTrueCount = 0;
              for (nx = 0; nx <= c_end; nx++) {
                if (edgeFilterList->data[(int32_T)
                    c_edgeIndexMatrixFiltConnected_[nx] - 1]) {
                  mb_tmp_data[partialTrueCount] = nx + 1;
                  partialTrueCount++;
                }
              }

              n = b_trueCount - 1;
              partialTrueCount = 0;
              for (nx = 0; nx <= n; nx++) {
                if (b_tmp_data[nx]) {
                  nb_tmp_data[partialTrueCount] = nx + 1;
                  partialTrueCount++;
                }
              }

              n = idx - 1;
              b_trueCount = 0;
              for (nx = 0; nx <= n; nx++) {
                if (e_tmp_data[nx]) {
                  b_trueCount++;
                }
              }

              partialTrueCount = 0;
              for (nx = 0; nx <= n; nx++) {
                if (e_tmp_data[nx]) {
                  pb_tmp_data[partialTrueCount] = nx + 1;
                  partialTrueCount++;
                }
              }

              partialTrueCount = i + 1;
              if (!((partialTrueCount >= 1) && (partialTrueCount <= b_trueCount)))
              {
                emlrtDynamicBoundsCheckR2012b(partialTrueCount, 1, b_trueCount,
                  &db_emlrtBCI, sp);
              }

              /* records.halfEdge(edgeIndexMatrixFinal(i),:); */
              partialTrueCount = E->twinID->size[0];
              idx = (int32_T)(uint32_T)
                c_edgeIndexMatrixFiltConnected_[mb_tmp_data[nb_tmp_data[pb_tmp_data
                [i] - 1] - 1] - 1];
              if (!((idx >= 1) && (idx <= partialTrueCount))) {
                emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount,
                  &rc_emlrtBCI, sp);
              }

              twinEdge = E->twinID->data[idx - 1];

              /* records.halfEdge(edge(1),:); */
              partialTrueCount = E->dir->size[0];
              idx = (int32_T)(uint32_T)
                c_edgeIndexMatrixFiltConnected_[mb_tmp_data[nb_tmp_data[pb_tmp_data
                [i] - 1] - 1] - 1];
              if (!((idx >= 1) && (idx <= partialTrueCount))) {
                emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount,
                  &sc_emlrtBCI, sp);
              }

              partialTrueCount = E->dir->size[0];
              nx = (int32_T)(uint32_T)
                c_edgeIndexMatrixFiltConnected_[mb_tmp_data[nb_tmp_data[pb_tmp_data
                [i] - 1] - 1] - 1];
              if (!((nx >= 1) && (nx <= partialTrueCount))) {
                emlrtDynamicBoundsCheckR2012b(nx, 1, partialTrueCount,
                  &tc_emlrtBCI, sp);
              }

              st.site = &i_emlrtRSI;
              d0 = mpower(E->dir->data[idx - 1]) + mpower(E->dir->data[(nx +
                E->dir->size[0]) - 1]);
              st.site = &i_emlrtRSI;
              b_sqrt(&st, &d0);
              distTempB = 2.2204460492503131E-16;
              st.site = &i_emlrtRSI;
              b_sqrt(&st, &distTempB);
              if (d0 < distTempB) {
                /* This code branch is outdated, but there for safety */
                noEdgeFound = 1;
                partialTrueCount = E->twinID->size[0];
                idx = (int32_T)(uint32_T)
                  c_edgeIndexMatrixFiltConnected_[mb_tmp_data[nb_tmp_data[pb_tmp_data
                  [i] - 1] - 1] - 1];
                if (!((idx >= 1) && (idx <= partialTrueCount))) {
                  emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount,
                    &vc_emlrtBCI, sp);
                }

                parEdge_T = E->twinID->data[idx - 1];

                /* edge(1); %%Twin edge, temporary parent edge for this cycle */
                partialTrueCount = E->origin->size[0];
                idx = (int32_T)(uint32_T)
                  c_edgeIndexMatrixFiltConnected_[mb_tmp_data[nb_tmp_data[pb_tmp_data
                  [i] - 1] - 1] - 1];
                if (!((idx >= 1) && (idx <= partialTrueCount))) {
                  emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount,
                    &wc_emlrtBCI, sp);
                }

                twinVert = E->origin->data[(idx + E->origin->size[0]) - 1];

                /* records.vorVert(edge(4),:); */
                do {
                  exitg3 = 0;
                  st.site = &j_emlrtRSI;
                  toLogicalCheck(&st, noEdgeFound);
                  if (noEdgeFound != 0) {
                    partialTrueCount = V->degree->size[0];
                    if (twinVert != (int32_T)muDoubleScalarFloor(twinVert)) {
                      emlrtIntegerCheckR2012b(twinVert, &m_emlrtDCI, sp);
                    }

                    idx = (int32_T)twinVert;
                    if (!((idx >= 1) && (idx <= partialTrueCount))) {
                      emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount,
                        &bb_emlrtBCI, sp);
                    }

                    if (1.0 > V->degree->data[(int32_T)twinVert - 1]) {
                      b_loop_ub = 0;
                    } else {
                      d0 = V->degree->data[(int32_T)twinVert - 1];
                      if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
                        emlrtIntegerCheckR2012b(d0, &l_emlrtDCI, sp);
                      }

                      b_loop_ub = (int32_T)d0;
                      if (!((b_loop_ub >= 1) && (b_loop_ub <= 4))) {
                        emlrtDynamicBoundsCheckR2012b(b_loop_ub, 1, 4,
                          &ab_emlrtBCI, sp);
                      }
                    }

                    partialTrueCount = V->edgeIDList->size[0];
                    nx = (int32_T)twinVert;
                    if (!((nx >= 1) && (nx <= partialTrueCount))) {
                      emlrtDynamicBoundsCheckR2012b(nx, 1, partialTrueCount,
                        &cb_emlrtBCI, sp);
                    }

                    for (partialTrueCount = 0; partialTrueCount < b_loop_ub;
                         partialTrueCount++) {
                      c_zeroedgeIndexMatrixFiltConnec[partialTrueCount] =
                        V->edgeIDList->data[(nx + V->edgeIDList->size[0] *
                        partialTrueCount) - 1];
                    }

                    /* twinVert(9:8+twinVert(8));		%%Edges connected to this vertex */
                    b_V_size[0] = 1;
                    b_V_size[1] = b_loop_ub;
                    for (partialTrueCount = 0; partialTrueCount < 2;
                         partialTrueCount++) {
                      b_V[partialTrueCount] = b_V_size[partialTrueCount];
                    }

                    st.site = &k_emlrtRSI;
                    indexShapeCheck(&st, edgeFilterList->size[0], b_V);
                    nx = edgeFilterList->size[0];
                    for (partialTrueCount = 0; partialTrueCount < b_loop_ub;
                         partialTrueCount++) {
                      if (c_zeroedgeIndexMatrixFiltConnec[partialTrueCount] !=
                          (int32_T)muDoubleScalarFloor
                          (c_zeroedgeIndexMatrixFiltConnec[partialTrueCount])) {
                        emlrtIntegerCheckR2012b
                          (c_zeroedgeIndexMatrixFiltConnec[partialTrueCount],
                           &hb_emlrtDCI, sp);
                      }

                      idx = (int32_T)
                        c_zeroedgeIndexMatrixFiltConnec[partialTrueCount];
                      if (!((idx >= 1) && (idx <= nx))) {
                        emlrtDynamicBoundsCheckR2012b(idx, 1, nx, &xc_emlrtBCI,
                          sp);
                      }
                    }

                    for (nx = 0; nx < b_loop_ub; nx++) {
                      if (edgeFilterList->data[(int32_T)
                          c_zeroedgeIndexMatrixFiltConnec[nx] - 1] && (!((nx + 1
                             >= 1) && (nx + 1 <= b_loop_ub)))) {
                        emlrtDynamicBoundsCheckR2012b(nx + 1, 1, b_loop_ub,
                          &emlrtBCI, sp);
                      }
                    }

                    /* Edges in subgraph region */
                    n = b_loop_ub - 1;
                    b_trueCount = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (edgeFilterList->data[(int32_T)
                          c_zeroedgeIndexMatrixFiltConnec[nx] - 1]) {
                        b_trueCount++;
                      }
                    }

                    partialTrueCount = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (edgeFilterList->data[(int32_T)
                          c_zeroedgeIndexMatrixFiltConnec[nx] - 1]) {
                        ub_tmp_data[partialTrueCount] = nx + 1;
                        partialTrueCount++;
                      }
                    }

                    for (partialTrueCount = 0; partialTrueCount < b_loop_ub;
                         partialTrueCount++) {
                      d_edgeIndexMatrixFiltConnected_[partialTrueCount] =
                        (uint32_T)
                        c_zeroedgeIndexMatrixFiltConnec[partialTrueCount];
                    }

                    for (partialTrueCount = 0; partialTrueCount < b_trueCount;
                         partialTrueCount++) {
                      b_tmp_data[partialTrueCount] =
                        (d_edgeIndexMatrixFiltConnected_[ub_tmp_data[partialTrueCount]
                         - 1] != parEdge_T);
                    }

                    n = b_loop_ub - 1;
                    c_trueCount = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (edgeFilterList->data[(int32_T)
                          c_zeroedgeIndexMatrixFiltConnec[nx] - 1]) {
                        c_trueCount++;
                      }
                    }

                    partialTrueCount = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (edgeFilterList->data[(int32_T)
                          c_zeroedgeIndexMatrixFiltConnec[nx] - 1]) {
                        vb_tmp_data[partialTrueCount] = nx + 1;
                        partialTrueCount++;
                      }
                    }

                    n = b_trueCount - 1;
                    b_trueCount = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (b_tmp_data[nx]) {
                        b_trueCount++;
                      }
                    }

                    partialTrueCount = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (b_tmp_data[nx]) {
                        wb_tmp_data[partialTrueCount] = nx + 1;
                        partialTrueCount++;
                      }
                    }

                    for (partialTrueCount = 0; partialTrueCount < b_loop_ub;
                         partialTrueCount++) {
                      d_edgeIndexMatrixFiltConnected_[partialTrueCount] =
                        (uint32_T)
                        c_zeroedgeIndexMatrixFiltConnec[partialTrueCount];
                    }

                    for (partialTrueCount = 0; partialTrueCount < c_trueCount;
                         partialTrueCount++) {
                      e_edgeIndexMatrixFiltConnected_[partialTrueCount] =
                        d_edgeIndexMatrixFiltConnected_[vb_tmp_data[partialTrueCount]
                        - 1];
                    }

                    for (partialTrueCount = 0; partialTrueCount < b_trueCount;
                         partialTrueCount++) {
                      idx = wb_tmp_data[partialTrueCount];
                      if (!((idx >= 1) && (idx <= c_trueCount))) {
                        emlrtDynamicBoundsCheckR2012b(idx, 1, c_trueCount,
                          &yc_emlrtBCI, sp);
                      }

                      c_zeroedgeIndexMatrixFiltNoReve[partialTrueCount] =
                        e_edgeIndexMatrixFiltConnected_[idx - 1];
                    }

                    /* Edge is not an immediate reversal */
                    n = b_loop_ub - 1;
                    c_trueCount = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (edgeFilterList->data[(int32_T)
                          c_zeroedgeIndexMatrixFiltConnec[nx] - 1]) {
                        c_trueCount++;
                      }
                    }

                    partialTrueCount = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (edgeFilterList->data[(int32_T)
                          c_zeroedgeIndexMatrixFiltConnec[nx] - 1]) {
                        xb_tmp_data[partialTrueCount] = nx + 1;
                        partialTrueCount++;
                      }
                    }

                    for (partialTrueCount = 0; partialTrueCount < b_loop_ub;
                         partialTrueCount++) {
                      d_edgeIndexMatrixFiltConnected_[partialTrueCount] =
                        (uint32_T)
                        c_zeroedgeIndexMatrixFiltConnec[partialTrueCount];
                    }

                    for (partialTrueCount = 0; partialTrueCount < c_trueCount;
                         partialTrueCount++) {
                      b_tmp_data[partialTrueCount] =
                        (d_edgeIndexMatrixFiltConnected_[xb_tmp_data[partialTrueCount]
                         - 1] != parEdge_T);
                    }

                    n = c_trueCount - 1;
                    c_trueCount = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (b_tmp_data[nx]) {
                        c_trueCount++;
                      }
                    }

                    b_tmp_size[0] = 1;
                    b_tmp_size[1] = c_trueCount;
                    st.site = &l_emlrtRSI;
                    indexShapeCheck(&st, edgeProcessed->size[0], b_tmp_size);
                    n = b_loop_ub - 1;
                    c_trueCount = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (edgeFilterList->data[(int32_T)
                          c_zeroedgeIndexMatrixFiltConnec[nx] - 1]) {
                        c_trueCount++;
                      }
                    }

                    partialTrueCount = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (edgeFilterList->data[(int32_T)
                          c_zeroedgeIndexMatrixFiltConnec[nx] - 1]) {
                        yb_tmp_data[partialTrueCount] = nx + 1;
                        partialTrueCount++;
                      }
                    }

                    for (partialTrueCount = 0; partialTrueCount < b_loop_ub;
                         partialTrueCount++) {
                      d_edgeIndexMatrixFiltConnected_[partialTrueCount] =
                        (uint32_T)
                        c_zeroedgeIndexMatrixFiltConnec[partialTrueCount];
                    }

                    for (partialTrueCount = 0; partialTrueCount < c_trueCount;
                         partialTrueCount++) {
                      b_tmp_data[partialTrueCount] =
                        (d_edgeIndexMatrixFiltConnected_[yb_tmp_data[partialTrueCount]
                         - 1] != parEdge_T);
                    }

                    n = b_loop_ub - 1;
                    idx = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (edgeFilterList->data[(int32_T)
                          c_zeroedgeIndexMatrixFiltConnec[nx] - 1]) {
                        idx++;
                      }
                    }

                    partialTrueCount = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (edgeFilterList->data[(int32_T)
                          c_zeroedgeIndexMatrixFiltConnec[nx] - 1]) {
                        ac_tmp_data[partialTrueCount] = nx + 1;
                        partialTrueCount++;
                      }
                    }

                    n = c_trueCount - 1;
                    itmp = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (b_tmp_data[nx]) {
                        itmp++;
                      }
                    }

                    partialTrueCount = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (b_tmp_data[nx]) {
                        bc_tmp_data[partialTrueCount] = nx + 1;
                        partialTrueCount++;
                      }
                    }

                    for (partialTrueCount = 0; partialTrueCount < b_loop_ub;
                         partialTrueCount++) {
                      d_edgeIndexMatrixFiltConnected_[partialTrueCount] =
                        (uint32_T)
                        c_zeroedgeIndexMatrixFiltConnec[partialTrueCount];
                    }

                    for (partialTrueCount = 0; partialTrueCount < idx;
                         partialTrueCount++) {
                      e_edgeIndexMatrixFiltConnected_[partialTrueCount] =
                        d_edgeIndexMatrixFiltConnected_[ac_tmp_data[partialTrueCount]
                        - 1];
                    }

                    nx = edgeProcessed->size[0];
                    for (partialTrueCount = 0; partialTrueCount < itmp;
                         partialTrueCount++) {
                      idx = (int32_T)
                        e_edgeIndexMatrixFiltConnected_[bc_tmp_data[partialTrueCount]
                        - 1];
                      if (!((idx >= 1) && (idx <= nx))) {
                        emlrtDynamicBoundsCheckR2012b(idx, 1, nx, &ad_emlrtBCI,
                          sp);
                      }

                      e_tmp_data[partialTrueCount] = !(edgeProcessed->data[idx -
                        1] != 0);
                    }

                    n = itmp - 1;
                    idx = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (e_tmp_data[nx]) {
                        idx++;
                      }
                    }

                    partialTrueCount = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (e_tmp_data[nx]) {
                        cc_tmp_data[partialTrueCount] = nx + 1;
                        partialTrueCount++;
                      }
                    }

                    n = c_trueCount - 1;
                    c_trueCount = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (b_tmp_data[nx]) {
                        c_trueCount++;
                      }
                    }

                    for (partialTrueCount = 0; partialTrueCount < idx;
                         partialTrueCount++) {
                      if (!((cc_tmp_data[partialTrueCount] >= 1) &&
                            (cc_tmp_data[partialTrueCount] <= c_trueCount))) {
                        emlrtDynamicBoundsCheckR2012b
                          (cc_tmp_data[partialTrueCount], 1, c_trueCount,
                           &bd_emlrtBCI, sp);
                      }
                    }

                    /* Edge has not been touched */
                    n = b_loop_ub - 1;
                    c_trueCount = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (edgeFilterList->data[(int32_T)
                          c_zeroedgeIndexMatrixFiltConnec[nx] - 1]) {
                        c_trueCount++;
                      }
                    }

                    partialTrueCount = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (edgeFilterList->data[(int32_T)
                          c_zeroedgeIndexMatrixFiltConnec[nx] - 1]) {
                        dc_tmp_data[partialTrueCount] = nx + 1;
                        partialTrueCount++;
                      }
                    }

                    for (partialTrueCount = 0; partialTrueCount < b_loop_ub;
                         partialTrueCount++) {
                      d_edgeIndexMatrixFiltConnected_[partialTrueCount] =
                        (uint32_T)
                        c_zeroedgeIndexMatrixFiltConnec[partialTrueCount];
                    }

                    for (partialTrueCount = 0; partialTrueCount < c_trueCount;
                         partialTrueCount++) {
                      b_tmp_data[partialTrueCount] =
                        (d_edgeIndexMatrixFiltConnected_[dc_tmp_data[partialTrueCount]
                         - 1] != parEdge_T);
                    }

                    n = b_loop_ub - 1;
                    idx = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (edgeFilterList->data[(int32_T)
                          c_zeroedgeIndexMatrixFiltConnec[nx] - 1]) {
                        idx++;
                      }
                    }

                    partialTrueCount = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (edgeFilterList->data[(int32_T)
                          c_zeroedgeIndexMatrixFiltConnec[nx] - 1]) {
                        ec_tmp_data[partialTrueCount] = nx + 1;
                        partialTrueCount++;
                      }
                    }

                    n = c_trueCount - 1;
                    c_trueCount = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (b_tmp_data[nx]) {
                        c_trueCount++;
                      }
                    }

                    partialTrueCount = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (b_tmp_data[nx]) {
                        fc_tmp_data[partialTrueCount] = nx + 1;
                        partialTrueCount++;
                      }
                    }

                    for (partialTrueCount = 0; partialTrueCount < b_loop_ub;
                         partialTrueCount++) {
                      d_edgeIndexMatrixFiltConnected_[partialTrueCount] =
                        (uint32_T)
                        c_zeroedgeIndexMatrixFiltConnec[partialTrueCount];
                    }

                    for (partialTrueCount = 0; partialTrueCount < idx;
                         partialTrueCount++) {
                      e_edgeIndexMatrixFiltConnected_[partialTrueCount] =
                        d_edgeIndexMatrixFiltConnected_[ec_tmp_data[partialTrueCount]
                        - 1];
                    }

                    for (partialTrueCount = 0; partialTrueCount < c_trueCount;
                         partialTrueCount++) {
                      e_tmp_data[partialTrueCount] = !(edgeProcessed->data
                        [(int32_T)
                        e_edgeIndexMatrixFiltConnected_[fc_tmp_data[partialTrueCount]
                        - 1] - 1] != 0);
                    }

                    n = c_trueCount - 1;
                    c_trueCount = 0;
                    for (nx = 0; nx <= n; nx++) {
                      if (e_tmp_data[nx]) {
                        c_trueCount++;
                      }
                    }

                    if (c_trueCount == 0) {
                      /* If this is true, this path might lead to */
                      /* a vertex? - Or on terminating iteration */
                      noEdgeFound = 0;
                      partialTrueCount = 1 + i;
                      if (!((partialTrueCount >= 1) && (partialTrueCount <=
                            angleMat_size_idx_1))) {
                        emlrtDynamicBoundsCheckR2012b(partialTrueCount, 1,
                          angleMat_size_idx_1, &id_emlrtBCI, sp);
                      }

                      angleMat_data[partialTrueCount - 1] = -2.0;

                      /* Only occurs on the terminating iteration... */
                    } else {
                      n = b_loop_ub - 1;
                      c_trueCount = 0;
                      for (nx = 0; nx <= n; nx++) {
                        if (edgeFilterList->data[(int32_T)
                            c_zeroedgeIndexMatrixFiltConnec[nx] - 1]) {
                          c_trueCount++;
                        }
                      }

                      partialTrueCount = 0;
                      for (nx = 0; nx <= n; nx++) {
                        if (edgeFilterList->data[(int32_T)
                            c_zeroedgeIndexMatrixFiltConnec[nx] - 1]) {
                          gc_tmp_data[partialTrueCount] = nx + 1;
                          partialTrueCount++;
                        }
                      }

                      for (partialTrueCount = 0; partialTrueCount < b_loop_ub;
                           partialTrueCount++) {
                        d_edgeIndexMatrixFiltConnected_[partialTrueCount] =
                          (uint32_T)
                          c_zeroedgeIndexMatrixFiltConnec[partialTrueCount];
                      }

                      for (partialTrueCount = 0; partialTrueCount < c_trueCount;
                           partialTrueCount++) {
                        b_tmp_data[partialTrueCount] =
                          (d_edgeIndexMatrixFiltConnected_[gc_tmp_data[partialTrueCount]
                           - 1] != parEdge_T);
                      }

                      n = b_loop_ub - 1;
                      idx = 0;
                      for (nx = 0; nx <= n; nx++) {
                        if (edgeFilterList->data[(int32_T)
                            c_zeroedgeIndexMatrixFiltConnec[nx] - 1]) {
                          idx++;
                        }
                      }

                      partialTrueCount = 0;
                      for (nx = 0; nx <= n; nx++) {
                        if (edgeFilterList->data[(int32_T)
                            c_zeroedgeIndexMatrixFiltConnec[nx] - 1]) {
                          hc_tmp_data[partialTrueCount] = nx + 1;
                          partialTrueCount++;
                        }
                      }

                      n = c_trueCount - 1;
                      c_trueCount = 0;
                      for (nx = 0; nx <= n; nx++) {
                        if (b_tmp_data[nx]) {
                          c_trueCount++;
                        }
                      }

                      partialTrueCount = 0;
                      for (nx = 0; nx <= n; nx++) {
                        if (b_tmp_data[nx]) {
                          ic_tmp_data[partialTrueCount] = nx + 1;
                          partialTrueCount++;
                        }
                      }

                      for (partialTrueCount = 0; partialTrueCount < b_loop_ub;
                           partialTrueCount++) {
                        d_edgeIndexMatrixFiltConnected_[partialTrueCount] =
                          (uint32_T)
                          c_zeroedgeIndexMatrixFiltConnec[partialTrueCount];
                      }

                      for (partialTrueCount = 0; partialTrueCount < idx;
                           partialTrueCount++) {
                        e_edgeIndexMatrixFiltConnected_[partialTrueCount] =
                          d_edgeIndexMatrixFiltConnected_[hc_tmp_data[partialTrueCount]
                          - 1];
                      }

                      for (partialTrueCount = 0; partialTrueCount < c_trueCount;
                           partialTrueCount++) {
                        e_tmp_data[partialTrueCount] = !(edgeProcessed->data
                          [(int32_T)
                          e_edgeIndexMatrixFiltConnected_[ic_tmp_data[partialTrueCount]
                          - 1] - 1] != 0);
                      }

                      n = c_trueCount - 1;
                      c_trueCount = 0;
                      for (nx = 0; nx <= n; nx++) {
                        if (e_tmp_data[nx]) {
                          c_trueCount++;
                        }
                      }

                      if (0 <= c_trueCount - 1) {
                        d_loop_ub = b_trueCount;
                        d_end = b_trueCount - 1;
                        partialTrueCount = V->pos->size[0];
                        idx = E->origin->size[0];
                        d0 = E->twinID->data[(int32_T)(uint32_T)
                          c_edgeIndexMatrixFiltConnected_[mb_tmp_data[nb_tmp_data
                          [pb_tmp_data[i] - 1] - 1] - 1] - 1];
                        if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
                          emlrtIntegerCheckR2012b(d0, &ib_emlrtDCI, sp);
                        }

                        nx = (int32_T)d0;
                        if (!((nx >= 1) && (nx <= idx))) {
                          emlrtDynamicBoundsCheckR2012b(nx, 1, idx, &cd_emlrtBCI,
                            sp);
                        }

                        d0 = E->origin->data[nx - 1];
                        if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
                          emlrtIntegerCheckR2012b(d0, &k_emlrtDCI, sp);
                        }

                        idx = (int32_T)d0;
                        if (!((idx >= 1) && (idx <= partialTrueCount))) {
                          emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount,
                            &x_emlrtBCI, sp);
                        }

                        c_E = (int32_T)E->origin->data[(int32_T)twinEdge - 1];
                        d_E = (int32_T)E->origin->data[(int32_T)twinEdge - 1];
                      }

                      n = 0;
                      while (n <= c_trueCount - 1) {
                        for (partialTrueCount = 0; partialTrueCount < d_loop_ub;
                             partialTrueCount++) {
                          e_tmp_data[partialTrueCount] = !(edgeProcessed->data
                            [(int32_T)
                            c_zeroedgeIndexMatrixFiltNoReve[partialTrueCount] -
                            1] != 0);
                        }

                        b_trueCount = 0;
                        for (nx = 0; nx <= d_end; nx++) {
                          if (e_tmp_data[nx]) {
                            b_trueCount++;
                          }
                        }

                        partialTrueCount = 0;
                        for (nx = 0; nx <= d_end; nx++) {
                          if (e_tmp_data[nx]) {
                            jc_tmp_data[partialTrueCount] = nx + 1;
                            partialTrueCount++;
                          }
                        }

                        partialTrueCount = n + 1;
                        if (!((partialTrueCount >= 1) && (partialTrueCount <=
                              b_trueCount))) {
                          emlrtDynamicBoundsCheckR2012b(partialTrueCount, 1,
                            b_trueCount, &y_emlrtBCI, sp);
                        }

                        /* records.halfEdge(zeroedgeIndexMatrixFinal(j),:); */
                        idx = 1;
                        distTempB = V->pos->data[c_E - 1];
                        if (muDoubleScalarIsNaN(V->pos->data[d_E - 1])) {
                          nx = 2;
                          exitg1 = false;
                          while ((!exitg1) && (nx < 3)) {
                            idx = 2;
                            nx = (int32_T)E->origin->data[(int32_T)twinEdge - 1];
                            if (!muDoubleScalarIsNaN(V->pos->data[(nx + V->
                                  pos->size[0]) - 1])) {
                              nx = (int32_T)E->origin->data[(int32_T)twinEdge -
                                1];
                              distTempB = V->pos->data[(nx + V->pos->size[0]) -
                                1];
                              exitg1 = true;
                            } else {
                              nx = 3;
                            }
                          }
                        }

                        if (idx < 2) {
                          nx = (int32_T)E->origin->data[(int32_T)twinEdge - 1];
                          if (V->pos->data[(nx + V->pos->size[0]) - 1] >
                              distTempB) {
                            nx = (int32_T)E->origin->data[(int32_T)twinEdge - 1];
                            distTempB = V->pos->data[(nx + V->pos->size[0]) - 1];
                          }
                        }

                        partialTrueCount = E->dir->size[0];
                        idx = (int32_T)
                          c_zeroedgeIndexMatrixFiltNoReve[jc_tmp_data[n] - 1];
                        if (!((idx >= 1) && (idx <= partialTrueCount))) {
                          emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount,
                            &dd_emlrtBCI, sp);
                        }

                        partialTrueCount = E->dir->size[0];
                        nx = (int32_T)
                          c_zeroedgeIndexMatrixFiltNoReve[jc_tmp_data[n] - 1];
                        if (!((nx >= 1) && (nx <= partialTrueCount))) {
                          emlrtDynamicBoundsCheckR2012b(nx, 1, partialTrueCount,
                            &ed_emlrtBCI, sp);
                        }

                        st.site = &m_emlrtRSI;
                        d0 = mpower(E->dir->data[idx - 1]) + mpower(E->dir->
                          data[(nx + E->dir->size[0]) - 1]);
                        st.site = &m_emlrtRSI;
                        b_sqrt(&st, &d0);
                        distTempB = eps(distTempB);
                        st.site = &m_emlrtRSI;
                        b_sqrt(&st, &distTempB);
                        if (d0 > distTempB) {
                          /* as long as the edge has a valid direction and its not a reversal it is fine.  The left most edge of one branch can not be to the left of the rightmost edge of the other if it is truly to the right */
                          partialTrueCount = dirMat->size[0];
                          nx = (int32_T)iter;
                          if (!((nx >= 1) && (nx <= partialTrueCount))) {
                            emlrtDynamicBoundsCheckR2012b(nx, 1,
                              partialTrueCount, &v_emlrtBCI, sp);
                          }

                          for (partialTrueCount = 0; partialTrueCount < 2;
                               partialTrueCount++) {
                            b_dirMat[partialTrueCount] = dirMat->data[(nx +
                              dirMat->size[0] * partialTrueCount) - 1];
                          }

                          partialTrueCount = E->dir->size[0];
                          nx = (int32_T)
                            c_zeroedgeIndexMatrixFiltNoReve[jc_tmp_data[n] - 1];
                          if (!((nx >= 1) && (nx <= partialTrueCount))) {
                            emlrtDynamicBoundsCheckR2012b(nx, 1,
                              partialTrueCount, &u_emlrtBCI, sp);
                          }

                          for (partialTrueCount = 0; partialTrueCount < 2;
                               partialTrueCount++) {
                            b_E[partialTrueCount] = E->dir->data[(nx + E->
                              dir->size[0] * partialTrueCount) - 1];
                          }

                          partialTrueCount = 1 + i;
                          if (!((partialTrueCount >= 1) && (partialTrueCount <=
                                angleMat_size_idx_1))) {
                            emlrtDynamicBoundsCheckR2012b(partialTrueCount, 1,
                              angleMat_size_idx_1, &hd_emlrtBCI, sp);
                          }

                          angleMat_data[partialTrueCount - 1] = angleBetween
                            (b_dirMat, b_E);

                          /* zeroEdge(6:7)); %Alt - grab a linear dist calculation from the previous point */
                          noEdgeFound = 0;
                        } else {
                          partialTrueCount = E->twinID->size[0];
                          idx = (int32_T)
                            c_zeroedgeIndexMatrixFiltNoReve[jc_tmp_data[n] - 1];
                          if (!((idx >= 1) && (idx <= partialTrueCount))) {
                            emlrtDynamicBoundsCheckR2012b(idx, 1,
                              partialTrueCount, &fd_emlrtBCI, sp);
                          }

                          parEdge_T = E->twinID->data[idx - 1];

                          /* zeroEdge(1); */
                          partialTrueCount = E->origin->size[0];
                          idx = (int32_T)
                            c_zeroedgeIndexMatrixFiltNoReve[jc_tmp_data[n] - 1];
                          if (!((idx >= 1) && (idx <= partialTrueCount))) {
                            emlrtDynamicBoundsCheckR2012b(idx, 1,
                              partialTrueCount, &gd_emlrtBCI, sp);
                          }

                          twinVert = E->origin->data[(idx + E->origin->size[0])
                            - 1];

                          /* records.vorVert(zeroEdge(4),:); */
                        }

                        n++;
                        if (*emlrtBreakCheckR2012bFlagVar != 0) {
                          emlrtBreakCheckR2012b(sp);
                        }
                      }
                    }

                    if (*emlrtBreakCheckR2012bFlagVar != 0) {
                      emlrtBreakCheckR2012b(sp);
                    }
                  } else {
                    exitg3 = 1;
                  }
                } while (exitg3 == 0);
              } else {
                partialTrueCount = dirMat->size[0];
                nx = (int32_T)iter;
                if (!((nx >= 1) && (nx <= partialTrueCount))) {
                  emlrtDynamicBoundsCheckR2012b(nx, 1, partialTrueCount,
                    &t_emlrtBCI, sp);
                }

                for (partialTrueCount = 0; partialTrueCount < 2;
                     partialTrueCount++) {
                  b_dirMat[partialTrueCount] = dirMat->data[(nx + dirMat->size[0]
                    * partialTrueCount) - 1];
                }

                for (partialTrueCount = 0; partialTrueCount < loop_ub;
                     partialTrueCount++) {
                  d_edgeIndexMatrixFiltConnected_[partialTrueCount] = (uint32_T)
                    c_edgeIndexMatrixFiltConnected_[partialTrueCount];
                }

                partialTrueCount = E->dir->size[0];
                nx = (int32_T)
                  d_edgeIndexMatrixFiltConnected_[mb_tmp_data[nb_tmp_data[pb_tmp_data
                  [i] - 1] - 1] - 1];
                if (!((nx >= 1) && (nx <= partialTrueCount))) {
                  emlrtDynamicBoundsCheckR2012b(nx, 1, partialTrueCount,
                    &s_emlrtBCI, sp);
                }

                for (partialTrueCount = 0; partialTrueCount < 2;
                     partialTrueCount++) {
                  b_E[partialTrueCount] = E->dir->data[(nx + E->dir->size[0] *
                    partialTrueCount) - 1];
                }

                partialTrueCount = 1 + i;
                if (!((partialTrueCount >= 1) && (partialTrueCount <=
                      angleMat_size_idx_1))) {
                  emlrtDynamicBoundsCheckR2012b(partialTrueCount, 1,
                    angleMat_size_idx_1, &uc_emlrtBCI, sp);
                }

                angleMat_data[partialTrueCount - 1] = angleBetween(b_dirMat, b_E);

                /* edge(6:7)); */
              }

              i++;
              if (*emlrtBreakCheckR2012bFlagVar != 0) {
                emlrtBreakCheckR2012b(sp);
              }
            }

            st.site = &n_emlrtRSI;
            b_st.site = &ib_emlrtRSI;
            c_st.site = &jb_emlrtRSI;
            if ((iv0[1] == 1) || (iv0[1] != 1)) {
              overflow = true;
            } else {
              overflow = false;
            }

            if (!overflow) {
              emlrtErrorWithMessageIdR2012b(&c_st, &u_emlrtRTEI,
                "Coder:toolbox:autoDimIncompatibility", 0);
            }

            if (!(iv0[1] > 0)) {
              emlrtErrorWithMessageIdR2012b(&c_st, &t_emlrtRTEI,
                "Coder:toolbox:eml_min_or_max_varDimZero", 0);
            }

            idx = 1;
            n = iv0[1];
            distTempB = angleMat_data[0];
            itmp = 0;
            if (iv0[1] > 1) {
              if (muDoubleScalarIsNaN(angleMat_data[0])) {
                nx = 2;
                exitg1 = false;
                while ((!exitg1) && (nx <= n)) {
                  idx = nx;
                  if (!muDoubleScalarIsNaN(angleMat_data[nx - 1])) {
                    distTempB = angleMat_data[nx - 1];
                    itmp = nx - 1;
                    exitg1 = true;
                  } else {
                    nx++;
                  }
                }
              }

              if (idx < iv0[1]) {
                while (idx + 1 <= n) {
                  if (angleMat_data[idx] < distTempB) {
                    distTempB = angleMat_data[idx];
                    itmp = idx;
                  }

                  idx++;
                }
              }
            }

            /* for CCW selection */
            n = loop_ub - 1;
            trueCount = 0;
            for (i = 0; i <= n; i++) {
              if (edgeFilterList->data[(int32_T)
                  c_edgeIndexMatrixFiltConnected_[i] - 1]) {
                trueCount++;
              }
            }

            partialTrueCount = 0;
            for (i = 0; i <= n; i++) {
              if (edgeFilterList->data[(int32_T)
                  c_edgeIndexMatrixFiltConnected_[i] - 1]) {
                lb_tmp_data[partialTrueCount] = i + 1;
                partialTrueCount++;
              }
            }

            for (partialTrueCount = 0; partialTrueCount < loop_ub;
                 partialTrueCount++) {
              d_edgeIndexMatrixFiltConnected_[partialTrueCount] = (uint32_T)
                c_edgeIndexMatrixFiltConnected_[partialTrueCount];
            }

            for (partialTrueCount = 0; partialTrueCount < trueCount;
                 partialTrueCount++) {
              b_tmp_data[partialTrueCount] =
                (d_edgeIndexMatrixFiltConnected_[lb_tmp_data[partialTrueCount] -
                 1] != parEdge);
            }

            n = loop_ub - 1;
            b_trueCount = 0;
            for (i = 0; i <= n; i++) {
              if (edgeFilterList->data[(int32_T)
                  c_edgeIndexMatrixFiltConnected_[i] - 1]) {
                b_trueCount++;
              }
            }

            partialTrueCount = 0;
            for (i = 0; i <= n; i++) {
              if (edgeFilterList->data[(int32_T)
                  c_edgeIndexMatrixFiltConnected_[i] - 1]) {
                ob_tmp_data[partialTrueCount] = i + 1;
                partialTrueCount++;
              }
            }

            n = trueCount - 1;
            c_trueCount = 0;
            for (i = 0; i <= n; i++) {
              if (b_tmp_data[i]) {
                c_trueCount++;
              }
            }

            partialTrueCount = 0;
            for (i = 0; i <= n; i++) {
              if (b_tmp_data[i]) {
                qb_tmp_data[partialTrueCount] = i + 1;
                partialTrueCount++;
              }
            }

            for (partialTrueCount = 0; partialTrueCount < loop_ub;
                 partialTrueCount++) {
              d_edgeIndexMatrixFiltConnected_[partialTrueCount] = (uint32_T)
                c_edgeIndexMatrixFiltConnected_[partialTrueCount];
            }

            for (partialTrueCount = 0; partialTrueCount < b_trueCount;
                 partialTrueCount++) {
              e_edgeIndexMatrixFiltConnected_[partialTrueCount] =
                d_edgeIndexMatrixFiltConnected_[ob_tmp_data[partialTrueCount] -
                1];
            }

            for (partialTrueCount = 0; partialTrueCount < c_trueCount;
                 partialTrueCount++) {
              e_tmp_data[partialTrueCount] = !(edgeProcessed->data[(int32_T)
                e_edgeIndexMatrixFiltConnected_[qb_tmp_data[partialTrueCount] -
                1] - 1] != 0);
            }

            n = loop_ub - 1;
            partialTrueCount = 0;
            for (i = 0; i <= n; i++) {
              if (edgeFilterList->data[(int32_T)
                  c_edgeIndexMatrixFiltConnected_[i] - 1]) {
                rb_tmp_data[partialTrueCount] = i + 1;
                partialTrueCount++;
              }
            }

            n = trueCount - 1;
            partialTrueCount = 0;
            for (i = 0; i <= n; i++) {
              if (b_tmp_data[i]) {
                sb_tmp_data[partialTrueCount] = i + 1;
                partialTrueCount++;
              }
            }

            n = c_trueCount - 1;
            trueCount = 0;
            for (i = 0; i <= n; i++) {
              if (e_tmp_data[i]) {
                trueCount++;
              }
            }

            partialTrueCount = 0;
            for (i = 0; i <= n; i++) {
              if (e_tmp_data[i]) {
                tb_tmp_data[partialTrueCount] = i + 1;
                partialTrueCount++;
              }
            }

            partialTrueCount = itmp + 1;
            if (!((partialTrueCount >= 1) && (partialTrueCount <= trueCount))) {
              emlrtDynamicBoundsCheckR2012b(partialTrueCount, 1, trueCount,
                &r_emlrtBCI, sp);
            }

            n = (int32_T)vertexCollectionList->data[(int32_T)iter - 1];
            parEdge = V->edgeIDList->data[(n + V->edgeIDList->size[0] *
              (rb_tmp_data[sb_tmp_data[tb_tmp_data[itmp] - 1] - 1] - 1)) - 1];
          }

          partialTrueCount = edgeCollectionList->size[0];
          idx = (int32_T)iter;
          if (!((idx >= 1) && (idx <= partialTrueCount))) {
            emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &jd_emlrtBCI,
              sp);
          }

          edgeCollectionList->data[idx - 1] = parEdge;
          partialTrueCount = edgeProcessed->size[0];
          if (parEdge != (int32_T)muDoubleScalarFloor(parEdge)) {
            emlrtIntegerCheckR2012b(parEdge, &jb_emlrtDCI, sp);
          }

          idx = (int32_T)parEdge;
          if (!((idx >= 1) && (idx <= partialTrueCount))) {
            emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &kd_emlrtBCI,
              sp);
          }

          edgeProcessed->data[idx - 1] = 1;

          /* records.halfEdge(edgeInd,:); */
          iter++;
          partialTrueCount = E->origin->size[0];
          idx = (int32_T)parEdge;
          if (!((idx >= 1) && (idx <= partialTrueCount))) {
            emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &ld_emlrtBCI,
              sp);
          }

          if (E->origin->data[(idx + E->origin->size[0]) - 1] ==
              startingVertexInd) {
            /* TERMINATE LOOP - DO NOT STORE MORE INFORMATION */
            exitg2 = 1;
          } else {
            partialTrueCount = E->origin->size[0];
            idx = (int32_T)parEdge;
            if (!((idx >= 1) && (idx <= partialTrueCount))) {
              emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount,
                &md_emlrtBCI, sp);
            }

            partialTrueCount = vertexCollectionList->size[0];
            nx = (int32_T)iter;
            if (!((nx >= 1) && (nx <= partialTrueCount))) {
              emlrtDynamicBoundsCheckR2012b(nx, 1, partialTrueCount,
                &nd_emlrtBCI, sp);
            }

            vertexCollectionList->data[nx - 1] = E->origin->data[(idx +
              E->origin->size[0]) - 1];

            /* (edge(4)); */
            partialTrueCount = r2sV->size[0];
            idx = vertexCollectionList->size[0];
            nx = (int32_T)iter - 1;
            if (!((nx >= 1) && (nx <= idx))) {
              emlrtDynamicBoundsCheckR2012b(nx, 1, idx, &od_emlrtBCI, sp);
            }

            d0 = vertexCollectionList->data[nx - 1];
            if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
              emlrtIntegerCheckR2012b(d0, &j_emlrtDCI, sp);
            }

            idx = (int32_T)d0;
            if (!((idx >= 1) && (idx <= partialTrueCount))) {
              emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount,
                &q_emlrtBCI, sp);
            }

            partialTrueCount = r2sV->size[0];
            idx = vertexCollectionList->size[0];
            nx = (int32_T)iter;
            if (!((nx >= 1) && (nx <= idx))) {
              emlrtDynamicBoundsCheckR2012b(nx, 1, idx, &pd_emlrtBCI, sp);
            }

            d0 = vertexCollectionList->data[nx - 1];
            if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
              emlrtIntegerCheckR2012b(d0, &i_emlrtDCI, sp);
            }

            idx = (int32_T)d0;
            if (!((idx >= 1) && (idx <= partialTrueCount))) {
              emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount,
                &p_emlrtBCI, sp);
            }

            partialTrueCount = parentEdge->size[0];
            d0 = r2sV->data[(int32_T)vertexCollectionList->data[(int32_T)iter -
              1] - 1];
            if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
              emlrtIntegerCheckR2012b(d0, &kb_emlrtDCI, sp);
            }

            idx = (int32_T)d0;
            if (!((idx >= 1) && (idx <= partialTrueCount))) {
              emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount,
                &qd_emlrtBCI, sp);
            }

            if (parentEdge->data[idx - 1] == 0.0) {
              partialTrueCount = E->twinID->size[0];
              idx = (int32_T)parEdge;
              if (!((idx >= 1) && (idx <= partialTrueCount))) {
                emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount,
                  &td_emlrtBCI, sp);
              }

              partialTrueCount = parentEdge->size[0];
              nx = (int32_T)r2sV->data[(int32_T)vertexCollectionList->data
                [(int32_T)iter - 1] - 1];
              if (!((nx >= 1) && (nx <= partialTrueCount))) {
                emlrtDynamicBoundsCheckR2012b(nx, 1, partialTrueCount,
                  &ud_emlrtBCI, sp);
              }

              parentEdge->data[nx - 1] = E->twinID->data[idx - 1];

              /* edge(1); */
            } else {
              partialTrueCount = E->twinID->size[0];
              idx = (int32_T)parEdge;
              if (!((idx >= 1) && (idx <= partialTrueCount))) {
                emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount,
                  &rd_emlrtBCI, sp);
              }

              partialTrueCount = parentEdge->size[0];
              nx = (int32_T)r2sV->data[(int32_T)vertexCollectionList->data
                [(int32_T)iter - 1] - 1];
              if (!((nx >= 1) && (nx <= partialTrueCount))) {
                emlrtDynamicBoundsCheckR2012b(nx, 1, partialTrueCount,
                  &sd_emlrtBCI, sp);
              }

              parentEdge->data[(nx + parentEdge->size[0]) - 1] = E->twinID->
                data[idx - 1];

              /* edge(1); */
            }

            partialTrueCount = childEdge->size[0];
            d0 = r2sV->data[(int32_T)vertexCollectionList->data[(int32_T)iter -
              2] - 1];
            if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
              emlrtIntegerCheckR2012b(d0, &lb_emlrtDCI, sp);
            }

            idx = (int32_T)d0;
            if (!((idx >= 1) && (idx <= partialTrueCount))) {
              emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount,
                &vd_emlrtBCI, sp);
            }

            if (childEdge->data[idx - 1] == 0.0) {
              partialTrueCount = childEdge->size[0];
              idx = (int32_T)r2sV->data[(int32_T)vertexCollectionList->data
                [(int32_T)iter - 2] - 1];
              if (!((idx >= 1) && (idx <= partialTrueCount))) {
                emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount,
                  &xd_emlrtBCI, sp);
              }

              childEdge->data[idx - 1] = parEdge;
            } else {
              partialTrueCount = childEdge->size[0];
              idx = (int32_T)r2sV->data[(int32_T)vertexCollectionList->data
                [(int32_T)iter - 2] - 1];
              if (!((idx >= 1) && (idx <= partialTrueCount))) {
                emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount,
                  &wd_emlrtBCI, sp);
              }

              childEdge->data[(idx + childEdge->size[0]) - 1] = parEdge;
            }

            partialTrueCount = V->pos->size[0];
            idx = E->origin->size[0];
            nx = (int32_T)parEdge;
            if (!((nx >= 1) && (nx <= idx))) {
              emlrtDynamicBoundsCheckR2012b(nx, 1, idx, &yd_emlrtBCI, sp);
            }

            d0 = E->origin->data[(nx + E->origin->size[0]) - 1];
            if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
              emlrtIntegerCheckR2012b(d0, &h_emlrtDCI, sp);
            }

            idx = (int32_T)d0;
            if (!((idx >= 1) && (idx <= partialTrueCount))) {
              emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount,
                &o_emlrtBCI, sp);
            }

            idx = 1;
            nx = (int32_T)E->origin->data[((int32_T)parEdge + E->origin->size[0])
              - 1];
            distTempB = V->pos->data[nx - 1];
            nx = (int32_T)E->origin->data[((int32_T)parEdge + E->origin->size[0])
              - 1];
            if (muDoubleScalarIsNaN(V->pos->data[nx - 1])) {
              nx = 2;
              exitg1 = false;
              while ((!exitg1) && (nx < 3)) {
                idx = 2;
                nx = (int32_T)E->origin->data[((int32_T)parEdge + E->
                  origin->size[0]) - 1];
                if (!muDoubleScalarIsNaN(V->pos->data[(nx + V->pos->size[0]) - 1]))
                {
                  nx = (int32_T)E->origin->data[((int32_T)parEdge + E->
                    origin->size[0]) - 1];
                  distTempB = V->pos->data[(nx + V->pos->size[0]) - 1];
                  exitg1 = true;
                } else {
                  nx = 3;
                }
              }
            }

            if (idx < 2) {
              nx = (int32_T)E->origin->data[((int32_T)parEdge + E->origin->size
                [0]) - 1];
              if (V->pos->data[(nx + V->pos->size[0]) - 1] > distTempB) {
                nx = (int32_T)E->origin->data[((int32_T)parEdge + E->
                  origin->size[0]) - 1];
                distTempB = V->pos->data[(nx + V->pos->size[0]) - 1];
              }
            }

            d0 = eps(distTempB);
            st.site = &o_emlrtRSI;
            b_sqrt(&st, &d0);
            partialTrueCount = E->dist->size[0];
            idx = (int32_T)parEdge;
            if (!((idx >= 1) && (idx <= partialTrueCount))) {
              emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount,
                &ae_emlrtBCI, sp);
            }

            if (E->dist->data[idx - 1] < d0) {
              n = dirMat->size[0];
              partialTrueCount = (int32_T)iter - 1;
              if (!((partialTrueCount >= 1) && (partialTrueCount <= n))) {
                emlrtDynamicBoundsCheckR2012b(partialTrueCount, 1, n,
                  &n_emlrtBCI, sp);
              }

              n = dirMat->size[0];
              partialTrueCount = (int32_T)iter;
              if (!((partialTrueCount >= 1) && (partialTrueCount <= n))) {
                emlrtDynamicBoundsCheckR2012b(partialTrueCount, 1, n,
                  &m_emlrtBCI, sp);
              }

              for (partialTrueCount = 0; partialTrueCount < 2; partialTrueCount
                   ++) {
                b_dirMat[partialTrueCount] = dirMat->data[((int32_T)iter +
                  dirMat->size[0] * partialTrueCount) - 2];
              }

              for (partialTrueCount = 0; partialTrueCount < 2; partialTrueCount
                   ++) {
                dirMat->data[((int32_T)iter + dirMat->size[0] * partialTrueCount)
                  - 1] = b_dirMat[partialTrueCount];
              }
            } else {
              partialTrueCount = E->dir->size[0];
              idx = E->twinID->size[0];
              nx = (int32_T)parEdge;
              if (!((nx >= 1) && (nx <= idx))) {
                emlrtDynamicBoundsCheckR2012b(nx, 1, idx, &be_emlrtBCI, sp);
              }

              d0 = E->twinID->data[nx - 1];
              if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
                emlrtIntegerCheckR2012b(d0, &g_emlrtDCI, sp);
              }

              nx = (int32_T)d0;
              if (!((nx >= 1) && (nx <= partialTrueCount))) {
                emlrtDynamicBoundsCheckR2012b(nx, 1, partialTrueCount,
                  &l_emlrtBCI, sp);
              }

              n = dirMat->size[0];
              partialTrueCount = (int32_T)iter;
              if (!((partialTrueCount >= 1) && (partialTrueCount <= n))) {
                emlrtDynamicBoundsCheckR2012b(partialTrueCount, 1, n,
                  &k_emlrtBCI, sp);
              }

              for (partialTrueCount = 0; partialTrueCount < 2; partialTrueCount
                   ++) {
                dirMat->data[((int32_T)iter + dirMat->size[0] * partialTrueCount)
                  - 1] = -E->dir->data[(nx + E->dir->size[0] * partialTrueCount)
                  - 1];
              }

              /* -records.halfEdge(edge(1),6:7); */
            }

            partialTrueCount = E->dist->size[0];
            idx = (int32_T)parEdge;
            if (!((idx >= 1) && (idx <= partialTrueCount))) {
              emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount,
                &ce_emlrtBCI, sp);
            }

            partialTrueCount = distMatrix->size[0];
            nx = (int32_T)iter;
            if (!((nx >= 1) && (nx <= partialTrueCount))) {
              emlrtDynamicBoundsCheckR2012b(nx, 1, partialTrueCount,
                &de_emlrtBCI, sp);
            }

            distMatrix->data[nx - 1] = E->dist->data[idx - 1];

            /* edge(5); */
            partialTrueCount = V->rad->size[0];
            idx = vertexCollectionList->size[0];
            nx = (int32_T)iter;
            if (!((nx >= 1) && (nx <= idx))) {
              emlrtDynamicBoundsCheckR2012b(nx, 1, idx, &fe_emlrtBCI, sp);
            }

            d0 = vertexCollectionList->data[nx - 1];
            if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
              emlrtIntegerCheckR2012b(d0, &mb_emlrtDCI, sp);
            }

            idx = (int32_T)d0;
            if (!((idx >= 1) && (idx <= partialTrueCount))) {
              emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount,
                &ee_emlrtBCI, sp);
            }

            partialTrueCount = radMatrix->size[0];
            nx = (int32_T)iter;
            if (!((nx >= 1) && (nx <= partialTrueCount))) {
              emlrtDynamicBoundsCheckR2012b(nx, 1, partialTrueCount,
                &ge_emlrtBCI, sp);
            }

            radMatrix->data[nx - 1] = V->rad->data[idx - 1];
            guard1 = true;
          }
        }
      }

      if (guard1 && (*emlrtBreakCheckR2012bFlagVar != 0)) {
        emlrtBreakCheckR2012b(sp);
      }
    } while (exitg2 == 0);

    terminals = (uint32_T)vertexCollectionList->size[0];
    partialTrueCount = r3->size[0] * r3->size[1];
    r3->size[0] = 1;
    r3->size[1] = (int32_T)(terminals - iter) + 1;
    emxEnsureCapacity(sp, (emxArray__common *)r3, partialTrueCount, sizeof
                      (int32_T), &emlrtRTEI);
    loop_ub = (int32_T)(terminals - iter);
    for (partialTrueCount = 0; partialTrueCount <= loop_ub; partialTrueCount++)
    {
      r3->data[r3->size[0] * partialTrueCount] = (int32_T)(iter +
        partialTrueCount);
    }

    st.site = &p_emlrtRSI;
    nullAssignment(&st, vertexCollectionList, r3);

    /*  edgeCollectionList(iter:end) = []; */
    /*      dirMat(iter:end,:) = []; */
    /*  radMatrix(iter:end) = []; */
    /*  distMatrix(iter:end) = []; */
    /*  loopStruct.Vertices = vertexCollectionList; */
    /*  loopStruct.EL = edgeCollectionList; */
    /*  loopStruct.subGraphVerts = vertSubGraph; */
    /*  loopStruct.subGraphParentEdge = parentEdge; */
    /*  loopStruct.subGraphChildEdge = childEdge; */
    /*  loopStruct.direction = dirMat; */
    /*  loopStruct.incrDist = distMatrix; */
    /*  loopStruct.distance = cumsum(distMatrix); */
    /*  if(nonCycleFlag) */
    /*      loopStruct.totalDistance = 0; */
    /*  else */
    /*      loopStruct.totalDistance = loopStruct.distance(end) + E.dist(edgeCollectionList(end));%records.halfEdge(edgeCollectionList(end),5); */
    /*  end */
    /*  loopStruct.radius = radMatrix; */
    /*  loopStruct.records2SubgraphMap_Vertices = r2sV; */
    /*  loopStruct.subgraph2RecordsMap_Vertices = s2rV; */
    /*  loopStruct.binaryFilt = vertFilterList; */
    /*  loopStruct.color = color; */
    /*  loopStruct.inObject = inObject; */
    /*  loopStruct.subGraphLeafFilter = vertexTerminal_SubGraph; */
    /*  loopStruct.nonCycle = nonCycleFlag; */
    d0 = V->length;
    if (!(d0 >= 0.0)) {
      emlrtNonNegativeCheckR2012b(d0, &f_emlrtDCI, sp);
    }

    if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
      emlrtIntegerCheckR2012b(d0, &e_emlrtDCI, sp);
    }

    loop_ub = vertexCollectionList->size[0];
    for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
      d0 = vertexCollectionList->data[partialTrueCount];
      if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
        emlrtIntegerCheckR2012b(d0, &nb_emlrtDCI, sp);
      }

      idx = (int32_T)V->length;
      nx = (int32_T)d0;
      if (!((nx >= 1) && (nx <= idx))) {
        emlrtDynamicBoundsCheckR2012b(nx, 1, idx, &he_emlrtBCI, sp);
      }
    }

    iv0[0] = vertexTerminal_circList->size[0];
    partialTrueCount = vertexCollectionList->size[0];
    vertexCollectionList->size[0] = iv0[0];
    emxEnsureCapacity(sp, (emxArray__common *)vertexCollectionList,
                      partialTrueCount, sizeof(real_T), &emlrtRTEI);
    loop_ub = iv0[0];
    for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
      vertexCollectionList->data[partialTrueCount] = 0.0;
    }

    iv0[0] = vertexTerminal_circList->size[0];
    partialTrueCount = edgeCollectionList->size[0];
    edgeCollectionList->size[0] = iv0[0];
    emxEnsureCapacity(sp, (emxArray__common *)edgeCollectionList,
                      partialTrueCount, sizeof(real_T), &emlrtRTEI);
    loop_ub = iv0[0];
    for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
      edgeCollectionList->data[partialTrueCount] = 0.0;
    }

    partialTrueCount = childEdge->size[0] * childEdge->size[1];
    childEdge->size[0] = iv0[0];
    childEdge->size[1] = 2;
    emxEnsureCapacity(sp, (emxArray__common *)childEdge, partialTrueCount,
                      sizeof(real_T), &emlrtRTEI);
    loop_ub = iv0[0] << 1;
    for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
      childEdge->data[partialTrueCount] = 0.0;
    }

    i = 1;
    while (i - 1 <= vertexTerminal_circList->size[0] - 1) {
      /*      if(i == 498) */
      /*          disp('rev') */
      /*      end */
      partialTrueCount = s2rV->size[0];
      idx = vertexTerminal_circList->size[0];
      if (!((i >= 1) && (i <= idx))) {
        emlrtDynamicBoundsCheckR2012b(i, 1, idx, &ke_emlrtBCI, sp);
      }

      d0 = vertexTerminal_circList->data[i - 1];
      if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
        emlrtIntegerCheckR2012b(d0, &ob_emlrtDCI, sp);
      }

      idx = (int32_T)d0;
      if (!((idx >= 1) && (idx <= partialTrueCount))) {
        emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &je_emlrtBCI, sp);
      }

      parEdge = s2rV->data[idx - 1];
      partialTrueCount = V->pos->size[0];
      d0 = s2rV->data[(int32_T)vertexTerminal_circList->data[i - 1] - 1];
      if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
        emlrtIntegerCheckR2012b(d0, &d_emlrtDCI, sp);
      }

      nx = (int32_T)d0;
      if (!((nx >= 1) && (nx <= partialTrueCount))) {
        emlrtDynamicBoundsCheckR2012b(nx, 1, partialTrueCount, &j_emlrtBCI, sp);
      }

      n = childEdge->size[0];
      if (!((i >= 1) && (i <= n))) {
        emlrtDynamicBoundsCheckR2012b(i, 1, n, &c_emlrtBCI, sp);
      }

      for (partialTrueCount = 0; partialTrueCount < 2; partialTrueCount++) {
        childEdge->data[(i + childEdge->size[0] * partialTrueCount) - 1] =
          V->pos->data[(nx + V->pos->size[0] * partialTrueCount) - 1];
      }

      /* records.vorVert(vertInd,1:2); */
      twinEdge = 0.0;
      st.site = &q_emlrtRSI;
      toLogicalCheck(&st, 1.0);
      do {
        exitg2 = 0;
        partialTrueCount = parentEdge->size[0];
        idx = r2sV->size[0];
        if (parEdge != (int32_T)muDoubleScalarFloor(parEdge)) {
          emlrtIntegerCheckR2012b(parEdge, &qb_emlrtDCI, sp);
        }

        nx = (int32_T)parEdge;
        if (!((nx >= 1) && (nx <= idx))) {
          emlrtDynamicBoundsCheckR2012b(nx, 1, idx, &me_emlrtBCI, sp);
        }

        d0 = r2sV->data[nx - 1];
        if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
          emlrtIntegerCheckR2012b(d0, &pb_emlrtDCI, sp);
        }

        idx = (int32_T)d0;
        if (!((idx >= 1) && (idx <= partialTrueCount))) {
          emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &le_emlrtBCI,
            sp);
        }

        if (parentEdge->data[idx - 1] != -1.0) {
          partialTrueCount = parentEdge->size[0];
          idx = r2sV->size[0];
          if (parEdge != (int32_T)muDoubleScalarFloor(parEdge)) {
            emlrtIntegerCheckR2012b(parEdge, &cc_emlrtDCI, sp);
          }

          nx = (int32_T)parEdge;
          if (!((nx >= 1) && (nx <= idx))) {
            emlrtDynamicBoundsCheckR2012b(nx, 1, idx, &jf_emlrtBCI, sp);
          }

          d0 = r2sV->data[nx - 1];
          if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
            emlrtIntegerCheckR2012b(d0, &c_emlrtDCI, sp);
          }

          idx = (int32_T)d0;
          if (!((idx >= 1) && (idx <= partialTrueCount))) {
            emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &i_emlrtBCI,
              sp);
          }

          /* records.halfEdge(parentEdge(r2sV(vertInd),1),:); */
          partialTrueCount = E->dist->size[0];
          d0 = parentEdge->data[(int32_T)r2sV->data[(int32_T)parEdge - 1] - 1];
          if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
            emlrtIntegerCheckR2012b(d0, &dc_emlrtDCI, sp);
          }

          idx = (int32_T)d0;
          if (!((idx >= 1) && (idx <= partialTrueCount))) {
            emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &kf_emlrtBCI,
              sp);
          }

          twinEdge += E->dist->data[idx - 1];
          partialTrueCount = E->origin->size[0];
          idx = (int32_T)parentEdge->data[(int32_T)r2sV->data[(int32_T)parEdge -
            1] - 1];
          if (!((idx >= 1) && (idx <= partialTrueCount))) {
            emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &lf_emlrtBCI,
              sp);
          }

          parEdge = E->origin->data[(idx + E->origin->size[0]) - 1];
          if (*emlrtBreakCheckR2012bFlagVar != 0) {
            emlrtBreakCheckR2012b(sp);
          }
        } else {
          exitg2 = 1;
        }
      } while (exitg2 == 0);

      partialTrueCount = edgeCollectionList->size[0];
      if (!((i >= 1) && (i <= partialTrueCount))) {
        emlrtDynamicBoundsCheckR2012b(i, 1, partialTrueCount, &ne_emlrtBCI, sp);
      }

      edgeCollectionList->data[i - 1] = parEdge;
      partialTrueCount = parentEdge->size[0];
      idx = vertexTerminal_circList->size[0];
      if (!((i >= 1) && (i <= idx))) {
        emlrtDynamicBoundsCheckR2012b(i, 1, idx, &pe_emlrtBCI, sp);
      }

      d0 = vertexTerminal_circList->data[i - 1];
      if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
        emlrtIntegerCheckR2012b(d0, &rb_emlrtDCI, sp);
      }

      idx = (int32_T)d0;
      if (!((idx >= 1) && (idx <= partialTrueCount))) {
        emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &oe_emlrtBCI, sp);
      }

      if (parentEdge->data[(idx + parentEdge->size[0]) - 1] != 0.0) {
        partialTrueCount = vertexTerminal_circList->size[0];
        idx = (i - 1) + 1;
        if (!((idx >= 1) && (idx <= partialTrueCount))) {
          emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &h_emlrtBCI,
            sp);
        }

        partialTrueCount = parentEdge->size[0];
        d0 = vertexTerminal_circList->data[i - 1];
        if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
          emlrtIntegerCheckR2012b(d0, &b_emlrtDCI, sp);
        }

        idx = (int32_T)d0;
        if (!((idx >= 1) && (idx <= partialTrueCount))) {
          emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &g_emlrtBCI,
            sp);
        }

        /* parentEdge(vertInd,2)records.halfEdge(parentEdge(vertInd,2),:); */
        partialTrueCount = E->dist->size[0];
        d0 = parentEdge->data[((int32_T)vertexTerminal_circList->data[i - 1] +
          parentEdge->size[0]) - 1];
        if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
          emlrtIntegerCheckR2012b(d0, &sb_emlrtDCI, sp);
        }

        idx = (int32_T)d0;
        if (!((idx >= 1) && (idx <= partialTrueCount))) {
          emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &qe_emlrtBCI,
            sp);
        }

        distTempB = E->dist->data[idx - 1];

        /* edgeTraversal(5); */
        partialTrueCount = E->origin->size[0];
        idx = (int32_T)parentEdge->data[((int32_T)vertexTerminal_circList->
          data[i - 1] + parentEdge->size[0]) - 1];
        if (!((idx >= 1) && (idx <= partialTrueCount))) {
          emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &re_emlrtBCI,
            sp);
        }

        parEdge = E->origin->data[(idx + E->origin->size[0]) - 1];

        /* edgeTraversal(4); */
        st.site = &r_emlrtRSI;
        toLogicalCheck(&st, 1.0);
        do {
          exitg2 = 0;
          partialTrueCount = parentEdge->size[0];
          idx = r2sV->size[0];
          if (parEdge != (int32_T)muDoubleScalarFloor(parEdge)) {
            emlrtIntegerCheckR2012b(parEdge, &ub_emlrtDCI, sp);
          }

          nx = (int32_T)parEdge;
          if (!((nx >= 1) && (nx <= idx))) {
            emlrtDynamicBoundsCheckR2012b(nx, 1, idx, &te_emlrtBCI, sp);
          }

          d0 = r2sV->data[nx - 1];
          if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
            emlrtIntegerCheckR2012b(d0, &tb_emlrtDCI, sp);
          }

          idx = (int32_T)d0;
          if (!((idx >= 1) && (idx <= partialTrueCount))) {
            emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &se_emlrtBCI,
              sp);
          }

          if (parentEdge->data[idx - 1] != -1.0) {
            partialTrueCount = parentEdge->size[0];
            idx = r2sV->size[0];
            if (parEdge != (int32_T)muDoubleScalarFloor(parEdge)) {
              emlrtIntegerCheckR2012b(parEdge, &ac_emlrtDCI, sp);
            }

            nx = (int32_T)parEdge;
            if (!((nx >= 1) && (nx <= idx))) {
              emlrtDynamicBoundsCheckR2012b(nx, 1, idx, &gf_emlrtBCI, sp);
            }

            d0 = r2sV->data[nx - 1];
            if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
              emlrtIntegerCheckR2012b(d0, &emlrtDCI, sp);
            }

            idx = (int32_T)d0;
            if (!((idx >= 1) && (idx <= partialTrueCount))) {
              emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount,
                &f_emlrtBCI, sp);
            }

            /* records.halfEdge(parentEdge(r2sV(vertInd),1),:); */
            partialTrueCount = E->dist->size[0];
            d0 = parentEdge->data[(int32_T)r2sV->data[(int32_T)parEdge - 1] - 1];
            if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
              emlrtIntegerCheckR2012b(d0, &bc_emlrtDCI, sp);
            }

            idx = (int32_T)d0;
            if (!((idx >= 1) && (idx <= partialTrueCount))) {
              emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount,
                &hf_emlrtBCI, sp);
            }

            distTempB += E->dist->data[idx - 1];
            partialTrueCount = E->origin->size[0];
            idx = (int32_T)parentEdge->data[(int32_T)r2sV->data[(int32_T)parEdge
              - 1] - 1];
            if (!((idx >= 1) && (idx <= partialTrueCount))) {
              emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount,
                &if_emlrtBCI, sp);
            }

            parEdge = E->origin->data[(idx + E->origin->size[0]) - 1];
            if (*emlrtBreakCheckR2012bFlagVar != 0) {
              emlrtBreakCheckR2012b(sp);
            }
          } else {
            exitg2 = 1;
          }
        } while (exitg2 == 0);

        if (distTempB < twinEdge) {
          twinEdge = distTempB;
          partialTrueCount = edgeCollectionList->size[0];
          if (!((i >= 1) && (i <= partialTrueCount))) {
            emlrtDynamicBoundsCheckR2012b(i, 1, partialTrueCount, &ue_emlrtBCI,
              sp);
          }

          edgeCollectionList->data[i - 1] = parEdge;
        }
      }

      partialTrueCount = vertexCollectionList->size[0];
      if (!((i >= 1) && (i <= partialTrueCount))) {
        emlrtDynamicBoundsCheckR2012b(i, 1, partialTrueCount, &ve_emlrtBCI, sp);
      }

      vertexCollectionList->data[i - 1] = twinEdge;
      partialTrueCount = V->rad->size[0];
      idx = edgeCollectionList->size[0];
      if (!((i >= 1) && (i <= idx))) {
        emlrtDynamicBoundsCheckR2012b(i, 1, idx, &xe_emlrtBCI, sp);
      }

      d0 = edgeCollectionList->data[i - 1];
      if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
        emlrtIntegerCheckR2012b(d0, &vb_emlrtDCI, sp);
      }

      idx = (int32_T)d0;
      if (!((idx >= 1) && (idx <= partialTrueCount))) {
        emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &we_emlrtBCI, sp);
      }

      b_guard1 = false;
      if (twinEdge - V->rad->data[idx - 1] < 0.0) {
        d0 = 2.2204460492503131E-16;
        st.site = &s_emlrtRSI;
        b_sqrt(&st, &d0);
        partialTrueCount = V->rad->size[0];
        idx = edgeCollectionList->size[0];
        if (!((i >= 1) && (i <= idx))) {
          emlrtDynamicBoundsCheckR2012b(i, 1, idx, &af_emlrtBCI, sp);
        }

        distTempB = edgeCollectionList->data[i - 1];
        if (distTempB != (int32_T)muDoubleScalarFloor(distTempB)) {
          emlrtIntegerCheckR2012b(distTempB, &wb_emlrtDCI, sp);
        }

        idx = (int32_T)distTempB;
        if (!((idx >= 1) && (idx <= partialTrueCount))) {
          emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &ye_emlrtBCI,
            sp);
        }

        if (twinEdge - V->rad->data[idx - 1] > -d0) {
          partialTrueCount = V->rad->size[0];
          idx = edgeCollectionList->size[0];
          if (!((i >= 1) && (i <= idx))) {
            emlrtDynamicBoundsCheckR2012b(i, 1, idx, &ef_emlrtBCI, sp);
          }

          d0 = edgeCollectionList->data[i - 1];
          if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
            emlrtIntegerCheckR2012b(d0, &yb_emlrtDCI, sp);
          }

          idx = (int32_T)d0;
          if (!((idx >= 1) && (idx <= partialTrueCount))) {
            emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &df_emlrtBCI,
              sp);
          }

          partialTrueCount = vertexCollectionList->size[0];
          if (!((i >= 1) && (i <= partialTrueCount))) {
            emlrtDynamicBoundsCheckR2012b(i, 1, partialTrueCount, &ff_emlrtBCI,
              sp);
          }

          vertexCollectionList->data[i - 1] = V->rad->data[idx - 1];

          /* records.vorVert(vertTerminal_circList_rootNode(i),3); */
          /*          disp('Minor precision error in radius caught and accounted for...'); */
        } else {
          b_guard1 = true;
        }
      } else {
        b_guard1 = true;
      }

      if (b_guard1) {
        d0 = 2.2204460492503131E-16;
        st.site = &t_emlrtRSI;
        b_sqrt(&st, &d0);
        partialTrueCount = V->rad->size[0];
        idx = edgeCollectionList->size[0];
        if (!((i >= 1) && (i <= idx))) {
          emlrtDynamicBoundsCheckR2012b(i, 1, idx, &cf_emlrtBCI, sp);
        }

        distTempB = edgeCollectionList->data[i - 1];
        if (distTempB != (int32_T)muDoubleScalarFloor(distTempB)) {
          emlrtIntegerCheckR2012b(distTempB, &xb_emlrtDCI, sp);
        }

        idx = (int32_T)distTempB;
        if (!((idx >= 1) && (idx <= partialTrueCount))) {
          emlrtDynamicBoundsCheckR2012b(idx, 1, partialTrueCount, &bf_emlrtBCI,
            sp);
        }

        if (twinEdge - V->rad->data[idx - 1] <= -d0) {
          y = NULL;
          m0 = emlrtCreateCharArray(2, iv1);
          emlrtInitCharArrayR2013a(sp, 50, m0, &u[0]);
          emlrtAssign(&y, m0);
          st.site = &rb_emlrtRSI;
          disp(&st, y, &emlrtMCI);
        }
      }

      i++;
      if (*emlrtBreakCheckR2012bFlagVar != 0) {
        emlrtBreakCheckR2012b(sp);
      }
    }

    partialTrueCount = betweenness->size[0];
    if (!((vsp + 1 >= 1) && (vsp + 1 <= partialTrueCount))) {
      emlrtDynamicBoundsCheckR2012b(vsp + 1, 1, partialTrueCount, &ie_emlrtBCI,
        sp);
    }

    st.site = &u_emlrtRSI;
    betweenness->data[vsp] = b_sum(&st, vertexCollectionList);

    /*  loopStruct.isRootNode = isOnBridge; */
    /*  loopStruct.parEdge = parentEdge; */
    /*  loopStruct.boundaryVerts = s2rV(vertexTerminal_circList); */
    /*  loopStruct.boundaryVertexCoor = boundaryVertexCoor; %Num = perim, Area requires calculation */
    /*  loopStruct.boundaryProfile = distMat; */
    /*  loopStruct.boundaryToCycleNode = vertTerminal_circList_rootNode; */
    /*  loopStruct.boundaryRatio = distMat./V.rad(vertTerminal_circList_rootNode);%records.vorVert(vertTerminal_circList_rootNode,3); */
    /*  loopStruct.boundaryDiff = distMat - V.rad(vertTerminal_circList_rootNode); */
    vsp++;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b(sp);
    }
  }

  emxFree_int32_T(&r3);
  emxFree_int32_T(&ii);
  emxFree_boolean_T(&x);
  emxFree_int32_T(&r2);
  emxFree_int32_T(&r1);
  emxFree_int32_T(&r0);
  emxFree_real_T(&dirMat);
  emxFree_real_T(&distMatrix);
  emxFree_real_T(&radMatrix);
  emxFree_real_T(&parentEdge);
  emxFree_real_T(&childEdge);
  emxFree_real_T(&vertexTerminal_circList);
  emxFree_boolean_T(&vertexTerminal_SubGraph_Proc);
  emxFree_boolean_T(&vertexTerminal);
  emxFree_int8_T(&edgeProcessed);
  emxFree_real_T(&edgeCollectionList);
  emxFree_real_T(&vertexCollectionList);
  emxFree_int32_T(&validStartPoints);
  emxFree_boolean_T(&edgeFilterList);
  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

/* End of code generation (mexBetweenessCentrality.c) */
