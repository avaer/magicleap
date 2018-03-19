// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
//
// Copyright (c) 2017 Magic Leap, Inc. (COMPANY) All Rights Reserved.
// Magic Leap, Inc. Confidential and Proprietary
//
// NOTICE:  All information contained herein is, and remains the property
// of COMPANY. The intellectual and technical concepts contained herein
// are proprietary to COMPANY and may be covered by U.S. and Foreign
// Patents, patents in process, and are protected by trade secret or
// copyright law.  Dissemination of this information or reproduction of
// this material is strictly forbidden unless prior written permission is
// obtained from COMPANY.  Access to the source code contained herein is
// hereby forbidden to anyone except current COMPANY employees, managers
// or contractors who have executed Confidentiality and Non-disclosure
// agreements explicitly covering such access.
//
// The copyright notice above does not evidence any actual or intended
// publication or disclosure  of  this source code, which includes
// information that is confidential and/or proprietary, and is a trade
// secret, of  COMPANY.   ANY REPRODUCTION, MODIFICATION, DISTRIBUTION,
// PUBLIC  PERFORMANCE, OR PUBLIC DISPLAY OF OR THROUGH USE  OF THIS
// SOURCE CODE  WITHOUT THE EXPRESS WRITTEN CONSENT OF COMPANY IS
// STRICTLY PROHIBITED, AND IN VIOLATION OF APPLICABLE LAWS AND
// INTERNATIONAL TREATIES.  THE RECEIPT OR POSSESSION OF  THIS SOURCE
// CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS
// TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE,
// USE, OR SELL ANYTHING THAT IT  MAY DESCRIBE, IN WHOLE OR IN PART.
//
// %COPYRIGHT_END%
// --------------------------------------------------------------------*/
// %BANNER_END%

#pragma once

#include "ml_api.h"

ML_EXTERN_C_BEGIN

/*! This header *MUST* be in sync with MediaErrors.h on C++ native side ! */

/*! Detailed error codes for the multimedia framework. */
typedef enum MLMediaError {
  MLMediaError_Base                      = -1000,
  MLMediaError_AlreadyConnected          = MLMediaError_Base,
  MLMediaError_NotConnected              = MLMediaError_Base - 1,
  MLMediaError_UnknownHost               = MLMediaError_Base - 2,
  MLMediaError_CannotConnect             = MLMediaError_Base - 3,
  MLMediaError_IO                        = MLMediaError_Base - 4,
  MLMediaError_ConnectionLost            = MLMediaError_Base - 5,
  MLMediaError_Malformed                 = MLMediaError_Base - 7,
  MLMediaError_OutOfRange                = MLMediaError_Base - 8,
  MLMediaError_BufferTooSmall            = MLMediaError_Base - 9,
  MLMediaError_Unsupported               = MLMediaError_Base - 10,
  MLMediaError_EndOfStream               = MLMediaError_Base - 11,
  MLMediaInfo_FormatChanged              = MLMediaError_Base - 12,
  MLMediaInfo_Discontinuity              = MLMediaError_Base - 13,
  MLMediaInfo_OutputBuffersChanged       = MLMediaError_Base - 14,
  MLMediaError_PermissionRevoked         = MLMediaError_Base - 15,

  MLMediaError_DRM_Base                         = -2000,
  MLMediaError_DRM_Unknown                      = MLMediaError_DRM_Base,
  MLMediaError_DRM_NoLicense                    = MLMediaError_DRM_Base - 1,
  MLMediaError_DRM_LicenseExpired               = MLMediaError_DRM_Base - 2,
  MLMediaError_DRM_SessionNotOpened             = MLMediaError_DRM_Base - 3,
  MLMediaError_DRM_DecryptUnitNotInitialized    = MLMediaError_DRM_Base - 4,
  MLMediaError_DRM_Decrypt                      = MLMediaError_DRM_Base - 5,
  MLMediaError_DRM_CannotHandle                 = MLMediaError_DRM_Base - 6,
  MLMediaError_DRM_TamperDetect                 = MLMediaError_DRM_Base - 7,
  MLMediaError_DRM_NotProvisioned               = MLMediaError_DRM_Base - 8,
  MLMediaError_DRM_DeviceRevoked                = MLMediaError_DRM_Base - 9,
  MLMediaError_DRM_ResourceBusy                 = MLMediaError_DRM_Base - 10,
  MLMediaError_DRM_InsufficientOutputProtection = MLMediaError_DRM_Base - 11,
  MLMediaError_DRM_LastUsedErrorCode            = MLMediaError_DRM_Base - 11,

  MLMediaError_DRM_VendorMax                    = MLMediaError_DRM_Base - 500,
  MLMediaError_DRM_VendorMin                    = MLMediaError_DRM_Base - 999,

  MLMediaError_HeartbeatTerminateRequested      = -3000,

  /*! Codec errors are permitted from 0x80001000 through 0x9000FFFF. */
  MLMediaError_CODEC_Max    = (signed)0x9000FFFF,
  MLMediaError_CODEC_Min    = (signed)0x80001000,

  /*! Unsupported audio format / channels */
  MLMediaError_UnsupportedAudioFormat     = -19,
  /*! Operation takes too long to complete. */
  MLMediaError_TimedOut                   = -110,
  /*! Unspecified low-level system error. */
  MLMediaError_System                     = -2147483647 - 1,

  MLMediaError_Ensure32Bits = 0x7FFFFFFF
} MLMediaError;

/*! \brief Translate a media error code into a human-readable string

    \param[in]  code Error code to translate to a string
    \param[out] out_string Pointer to C-style error string. Note that user should
                not keep a reference to the returned char pointer for future
                use as subsequent calls to MLMediaErrorGetString will overwrite
                its content. Consequently, user *must not* explicitly free the
                returned out_string memory.
    \return true if code could successfully get translated into a string
 */
ML_API bool ML_CALL MLMediaErrorGetString(int code, char **out_string);

ML_EXTERN_C_END
