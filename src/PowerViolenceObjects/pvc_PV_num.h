#ifndef _PVC_num_H
#define _PVC_num_H

#include "pvc_PV_55p8.h"
#include "pvc_PV_119p8.h"

#define MAX_DERIVED 17

#define PVC_O_NUM 0
#define PVC_I_PID 1
#define PVC_I_SID 2
#define PVC_I_NRS 3
#define PVC_I_LRS 4
#define PVC_F_11P 5
#define PVC_F_27P 6
#define PVC_F_55P 7
#define PVC_F_119 8
#define PVC_C_64C 9
#define PVC_C_128 10
#define PVC_C_256 11
#define PVC_H_SRT 12
#define PVC_H_NOR 13
#define PVC_O_NOR 14
#define PVC_F_447 15
#define PVC_O_PFT 16

#define PVC_C_POW PVC_C_256
#define PVC_C_LVS PVC_C_128

/**
 * @brief   int (*)(void *, const void *)
 * @param   self the entity being modified
 * @param   other the initialization parameter
 * @return  int
 * @retval  if self or other is NULL, return -1;
 *          else if overflowed, set self to 0 and return 1;
 *          else return 0.
 * @note    
 * @author  ljx
 * @date    2026-05-23 11:52
 */
typedef int (*PVcTypeTransFunc)(void *, const void *);
typedef PVcTypeTransFunc PVcTTF;
extern const PVcTTF pvc_type_trans_func[MAX_DERIVED][MAX_DERIVED];

#endif /* _PY_PV_num_H */
