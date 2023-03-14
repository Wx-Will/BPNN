#ifndef TTTT_EMXUTIL_H
#define TTTT_EMXUTIL_H

/* Include Files */
#include "tttt_types.h"
#include <stddef.h>
#include <stdlib.h>
#include "F28x_Project.h"
#ifdef __cplusplus

extern "C" {

#endif

  /* Function Declarations */
  extern void emxEnsureCapacity_real32_T(emxArray_real32_T *emxArray, int
    oldNumel);
  extern void emxFree_real32_T(emxArray_real32_T **pEmxArray);
  extern void emxInit_real32_T(emxArray_real32_T **pEmxArray, int numDimensions);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for tttt_emxutil.h
 *
 * [EOF]
 */
