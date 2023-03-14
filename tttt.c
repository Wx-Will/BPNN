/* Include Files */
#include "tttt.h"
#include "tttt_data.h"
#include "tttt_emxutil.h"
#include "tttt_initialize.h"
#include "tttt_types.h"
#include <math.h>
#include "F28x_Project.h"

/* Function Definitions */
/*
 * Arguments    : const float u[4]
 *                float sys[3]
 * Return Type  : void
 */
void tttt(const float u[4], float sys[3])
{
  emxArray_real32_T *K;
  emxArray_real32_T *K1;
  emxArray_real32_T *Oh;
  emxArray_real32_T *b_I;
  emxArray_real32_T *dK;
  emxArray_real32_T *dO;
  emxArray_real32_T *d_wo;
  emxArray_real32_T *delta2;
  emxArray_real32_T *delta3;
  emxArray_real32_T *r;
  float c[5];
  float b_c[3];
  float xi[3];
  float z[3];
  float c_tmp;
  float f;
  float out;
  float out_tmp;
  int i;
  int j;
  int loop_ub;
  if (!isInitialized_tttt) {
    tttt_initialize();
  }

  emxInit_real32_T(&Oh, 2);
  beta[0] = 10000.0F;
  beta[1] = 2000.0F;
  beta[2] = 147.0F;

  /*  global K; */
  IN = 3.0F;
  H = 5.0F;
  OUT = 3.0F;
  j = Oh->size[0] * Oh->size[1];
  Oh->size[0] = 1;
  Oh->size[1] = 5;
  emxEnsureCapacity_real32_T(Oh, j);
  for (j = 0; j < 5; j++) {
    Oh->data[j] = 0.0F;
  }

  emxInit_real32_T(&K, 2);
  j = K->size[0] * K->size[1];
  K->size[0] = 1;
  K->size[1] = 3;
  emxEnsureCapacity_real32_T(K, j);
  for (j = 0; j < 3; j++) {
    K->data[j] = 0.0F;
  }

  emxInit_real32_T(&dK, 2);
  j = dK->size[0] * dK->size[1];
  dK->size[0] = 1;
  dK->size[1] = 3;
  emxEnsureCapacity_real32_T(dK, j);
  for (j = 0; j < 3; j++) {
    dK->data[j] = 0.0F;
  }

  emxInit_real32_T(&delta3, 2);
  j = delta3->size[0] * delta3->size[1];
  delta3->size[0] = 1;
  delta3->size[1] = 3;
  emxEnsureCapacity_real32_T(delta3, j);
  for (j = 0; j < 3; j++) {
    delta3->data[j] = 0.0F;
  }

  emxInit_real32_T(&d_wo, 2);
  j = d_wo->size[0] * d_wo->size[1];
  d_wo->size[0] = 3;
  d_wo->size[1] = 5;
  emxEnsureCapacity_real32_T(d_wo, j);
  for (j = 0; j < 15; j++) {
    d_wo->data[j] = 0.0F;
  }

  emxInit_real32_T(&delta2, 2);
  j = delta2->size[0] * delta2->size[1];
  delta2->size[0] = 1;
  delta2->size[1] = 5;
  emxEnsureCapacity_real32_T(delta2, j);
  for (j = 0; j < 5; j++) {
    delta2->data[j] = 0.0F;
  }

  emxInit_real32_T(&dO, 2);
  j = dO->size[0] * dO->size[1];
  dO->size[0] = 1;
  dO->size[1] = 5;
  emxEnsureCapacity_real32_T(dO, j);
  for (j = 0; j < 5; j++) {
    dO->data[j] = 0.0F;
  }

  emxInit_real32_T(&b_I, 2);
  xi[0] = u[0];
  xi[1] = u[1];
  xi[2] = u[2];


  j = b_I->size[0] * b_I->size[1];
  b_I->size[0] = 1;
  b_I->size[1] = 5;
  emxEnsureCapacity_real32_T(b_I, j);
  out_tmp = u[0];
  out = u[1];
  f = u[2];
  for (j = 0; j < 5; j++) {
    c_tmp = (out_tmp * wi[j] + out * wi[j + 5]) + f * wi[j + 10];
    c[j] = c_tmp;
    b_I->data[j] = c_tmp;
  }


  for (j = 0; j < 5; j++) {
    out_tmp = b_I->data[j];
    out = expf(out_tmp);
    out_tmp = expf(-out_tmp);
    Oh->data[j] = (out - out_tmp) / (out + out_tmp);


  }

  emxFree_real32_T(&b_I);
  emxInit_real32_T(&K1, 1);
  j = K1->size[0];
  K1->size[0] = Oh->size[1];
  emxEnsureCapacity_real32_T(K1, j);
  loop_ub = Oh->size[1];
  for (j = 0; j < loop_ub; j++) {
    K1->data[j] = Oh->data[j];
  }

  for (j = 0; j < 3; j++) {
    out_tmp = 0.0F;
    out = 0.0F;
    for (i = 0; i < 5; i++) {
      f = wo[j + 3 * i] * K1->data[i];
      out_tmp += f;
      out += f;
    }

    z[j] = out;
    b_c[j] = out_tmp;
  }

  j = K1->size[0];
  K1->size[0] = 3;
  emxEnsureCapacity_real32_T(K1, j);
  K1->data[0] = z[0];
  K1->data[1] = z[1];
  K1->data[2] = z[2];


  for (i = 0; i < 3; i++) {
    out_tmp = K1->data[i];
    out = expf(out_tmp);
    K->data[i] = out / (out + expf(-out_tmp));

    /* Êä³ö²ãµÄÊä³ö */
    /* wx... */
    /* wx... */
  }

  emxFree_real32_T(&K1);


  out_tmp = u[1] - u[3];
  out = out_tmp / ((K->data[0] - 10000.0F) + 0.01F);
  if (out < 0.0F) {
    out = -1.0F;
  } else if (out > 0.0F) {
    out = 1.0F;
  } else {
    if (out == 0.0F) {
      out = 0.0F;
    }
  }

  z[0] = out;
  out = out_tmp / ((K->data[1] - 2000.0F) + 0.01F);
  if (out < 0.0F) {
    out = -1.0F;
  } else if (out > 0.0F) {
    out = 1.0F;
  } else {
    if (out == 0.0F) {
      out = 0.0F;
    }
  }

  z[1] = out;
  out = out_tmp / ((K->data[2] - 147.0F) + 0.01F);
  if (out < 0.0F) {
    out = -1.0F;
  } else if (out > 0.0F) {
    out = 1.0F;
  } else {
    if (out == 0.0F) {
      out = 0.0F;
    }
  }

  z[2] = out;

  /* wx... */
  /* wx... */
  for (j = 0; j < 3; j++) {
    out_tmp = b_c[j];
    out_tmp = expf(out_tmp) + expf(-out_tmp);
    dK->data[j] = 2.0F / (out_tmp * out_tmp);

    /* wx... */
    /* wx... */
    /* wx... */
  }

  for (i = 0; i < 3; i++) {
    delta3->data[i] = u[0] * z[i] * dK->data[i];
  }

  emxFree_real32_T(&dK);
  for (j = 0; j < 3; j++) {
    for (i = 0; i < 5; i++) {
      loop_ub = j + 3 * i;
      d_wo->data[j + d_wo->size[0] * i] = 0.2F * delta3->data[j] * Oh->data[i] +
        1.0E-5F * (wo_1[loop_ub] - wo_2[loop_ub]);
      /* wx... */
    }
  }

  for (j = 0; j < 15; j++) {
    out_tmp = wo_1[j];
    wo[j] = (out_tmp + d_wo->data[j]) + 1.0E-5F * (out_tmp - wo_2[j]);
  }

  emxFree_real32_T(&d_wo);

  /* wx... */
  for (i = 0; i < 5; i++) {
    out_tmp = c[i];
    out_tmp = expf(out_tmp) + expf(-out_tmp);
    dO->data[i] = 4.0F / (out_tmp * out_tmp);
  }

  j = Oh->size[0] * Oh->size[1];
  Oh->size[0] = 1;
  Oh->size[1] = 5;
  emxEnsureCapacity_real32_T(Oh, j);
  for (j = 0; j < 5; j++) {
    Oh->data[j] = (delta3->data[0] * wo[3 * j] + delta3->data[1] * wo[3 * j + 1])
      + delta3->data[2] * wo[3 * j + 2];
  }

  emxFree_real32_T(&delta3);

  /* wx...  delta3_LSEF-2;  wo_LSEF-2 */
  for (i = 0; i < 5; i++) {
    /*      delta2(i)=dO(i)*segma(i); */
    delta2->data[i] = Oh->data[i] * dO->data[i];
  }

  emxFree_real32_T(&dO);
  emxFree_real32_T(&Oh);
  emxInit_real32_T(&r, 2);

  /* for i=1:1:5 */
  /*  for j=1:1:3 */
  /*   d_wi=xite*delta2(i)*xi(j)+alfa*(wi_1-wi_2); */
  /*  end */
  /* end */
  /* wx...  */
  j = r->size[0] * r->size[1];
  r->size[0] = delta2->size[1];
  r->size[1] = 3;
  emxEnsureCapacity_real32_T(r, j);
  loop_ub = delta2->size[1];
  for (j = 0; j < 3; j++) {
    for (i = 0; i < loop_ub; i++) {
      r->data[i + r->size[0] * j] = 0.2F * delta2->data[i] * xi[j];
    }
  }

  emxFree_real32_T(&delta2);

  /* wx...  */
  for (j = 0; j < 15; j++) {
    out_tmp = wi_1[j];
    out = wi_2[j];
    f = (out_tmp + r->data[j]) + 1.0E-5F * (out_tmp - out);
    wi[j] = f;
    wo_3[j] = wo_2[j];
    wo_2[j] = wo_1[j];
    wo_1[j] = wo[j];
    wi_3[j] = out;
    wi_2[j] = out_tmp;
    wi_1[j] = f;
  }

  emxFree_real32_T(&r);
  sys[0] = K->data[0];
  sys[1] = K->data[1];
  sys[2] = K->data[2];
  emxFree_real32_T(&K);
}

/*
 * File trailer for tttt.c
 *
 * [EOF]
 */
