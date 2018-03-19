// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
//
// Copyright (c) 2017 Magic Leap, Inc. (COMPANY) All Rights Reserved.
// Magic Leap, Inc. Confidential and Proprietary
//
// NOTICE: All information contained herein is, and remains the property
// of COMPANY. The intellectual and technical concepts contained herein
// are proprietary to COMPANY and may be covered by U.S. and Foreign
// Patents, patents in process, and are protected by trade secret or
// copyright law. Dissemination of this information or reproduction of
// this material is strictly forbidden unless prior written permission is
// obtained from COMPANY. Access to the source code contained herein is
// hereby forbidden to anyone except current COMPANY employees, managers
// or contractors who have executed Confidentiality and Non-disclosure
// agreements explicitly covering such access.
//
// The copyright notice above does not evidence any actual or intended
// publication or disclosure of this source code, which includes
// information that is confidential and/or proprietary, and is a trade
// secret, of COMPANY. ANY REPRODUCTION, MODIFICATION, DISTRIBUTION,
// PUBLIC PERFORMANCE, OR PUBLIC DISPLAY OF OR THROUGH USE OF THIS
// SOURCE CODE WITHOUT THE EXPRESS WRITTEN CONSENT OF COMPANY IS
// STRICTLY PROHIBITED, AND IN VIOLATION OF APPLICABLE LAWS AND
// INTERNATIONAL TREATIES. THE RECEIPT OR POSSESSION OF THIS SOURCE
// CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS
// TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE,
// USE, OR SELL ANYTHING THAT IT MAY DESCRIBE, IN WHOLE OR IN PART.
//
// %COPYRIGHT_END%
// ---------------------------------------------------------------------
// %BANNER_END%

#pragma once

#include "ml_api.h"

ML_EXTERN_C_BEGIN

/*!
  \brief Enumeration definitions for the various metadata entries.
*/

/*! Color Correction Mode. */
typedef enum MLCameraMetadataColorCorrectionMode {
  MLCameraMetadataColorCorrectionMode_TransformMatrix = 0,
  MLCameraMetadataColorCorrectionMode_Fast,
  MLCameraMetadataColorCorrectionMode_HighQuality,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataColorCorrectionMode_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataColorCorrectionMode;

/*! Color Correction Aberration Mode. */
typedef enum MLCameraMetadataColorCorrectionAberrationMode {
  MLCameraMetadataColorCorrectionAberrationMode_Off = 0,
  MLCameraMetadataColorCorrectionAberrationMode_Fast,
  MLCameraMetadataColorCorrectionAberrationMode_HighQuality,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataColorCorrectionAberrationMode_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataColorCorrectionAberrationMode;

/*! Control AE AntiBanding Mode. */
typedef enum MLCameraMetadataControlAEAntibandingMode {
  MLCameraMetadataControlAEAntibandingMode_Off = 0,
  MLCameraMetadataControlAEAntibandingMode_50Hz,
  MLCameraMetadataControlAEAntibandingMode_60Hz,
  MLCameraMetadataControlAEAntibandingMode_Auto,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataControlAEAntibandingMode_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataControlAEAntibandingMode;

/*! Control AE Lock. */
typedef enum MLCameraMetadataControlAELock {
  MLCameraMetadataControlAELock_Off = 0,
  MLCameraMetadataControlAELock_On,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataControlAELock_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataControlAELock;

/*! Control AE Mode. */
typedef enum MLCameraMetadataControlAEMode {
  MLCameraMetadataControlAEMode_Off = 0,
  MLCameraMetadataControlAEMode_On,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataControlAEMode_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataControlAEMode;

/*! Control AWB Lock. */
typedef enum MLCameraMetadataControlAWBLock {
  MLCameraMetadataControlAWBLock_Off = 0,
  MLCameraMetadataControlAWBLock_On,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataControlAWBLock_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataControlAWBLock;

/*! Control AWB Mode. */
typedef enum MLCameraMetadataControlAWBMode {
  MLCameraMetadataControlAWBMode_Off = 0,
  MLCameraMetadataControlAWBMode_Auto,
  MLCameraMetadataControlAWBMode_Incandescent,
  MLCameraMetadataControlAWBMode_Fluorescent,
  MLCameraMetadataControlAWBMode_WarmFluorescent,
  MLCameraMetadataControlAWBMode_Daylight,
  MLCameraMetadataControlAWBMode_CloudyDaylight,
  MLCameraMetadataControlAWBMode_Twilight,
  MLCameraMetadataControlAWBMode_Shade,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataControlAWBMode_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataControlAWBMode;

/*! Control AE State. */
typedef enum MLCameraMetadataControlAEState {
  MLCameraMetadataControlAEState_Inactive = 0,
  MLCameraMetadataControlAEState_Searching,
  MLCameraMetadataControlAEState_Converged,
  MLCameraMetadataControlAEState_Locked,
  MLCameraMetadataControlAEState_FlashRequired,
  MLCameraMetadataControlAEState_PreCapture,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataControlAEState_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataControlAEState;

/*! Control AWB State. */
typedef enum MLCameraMetadataControlAWBState {
  MLCameraMetadataControlAWBState_Inactive = 0,
  MLCameraMetadataControlAWBState_Searching,
  MLCameraMetadataControlAWBState_Converged,
  MLCameraMetadataControlAWBState_Locked,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataControlAWBState_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataControlAWBState;

/*! Control AE Lock Available. */
typedef enum MLCameraMetadataControlAELockAvailable {
  MLCameraMetadataControlAELockAvailable_False = 0,
  MLCameraMetadataControlAELockAvailable_True,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataControlAELockAvailable_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataControlAELockAvailable;

/*! Control AWB Lock Available. */
typedef enum MLCameraMetadataControlAWBLockAvailable {
  MLCameraMetadataControlAWBLockAvailable_False = 0,
  MLCameraMetadataControlAWBLockAvailable_True,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataControlAWBLockAvailable_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataControlAWBLockAvailable;

ML_EXTERN_C_END
