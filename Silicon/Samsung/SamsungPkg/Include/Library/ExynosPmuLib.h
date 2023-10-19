/** @file
  Exynos 9820 Power Management Unit Library

  Copyright (c) 2015, Samsung Electronics Co., Ltd. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent
**/
#ifndef _EXYNOS_PMU_LIB_H_
#define _EXYNOS_PMU_LIB_H_

EFI_STATUS
PmuWrite (
  UINT32 PmuBaseAddr,
  UINT32 Offset,
  UINT32 Value
  );

EFI_STATUS
PmuUpdate (
  UINT32 PmuBaseAddr,
  UINT32 Offset,
  UINT32 Mask,
  UINT32 Value
  );

#endif /* _EXYNOS_PMU_LIB_H_ */