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

/*!
  \mainpage Introduction

  All distances are in meters and all orientations are in RUB
  (Right, Up, Back) unless stated otherwise.
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#if defined(_MSC_VER) && _MSC_VER
#define ML_API __declspec(dllexport)
#define ML_CALL __cdecl
#define ML_DEPRECATED(x, msg) __declspec(deprecated(msg)) x
#define ML_INLINE __inline
#else
#define ML_API
#define ML_CALL
#define ML_DEPRECATED(x, msg) x __attribute__((deprecated(msg)))
#define ML_INLINE inline
#endif

#ifdef __cplusplus
#define ML_EXTERN_C_BEGIN extern "C" {
#define ML_EXTERN_C_END }
#else
#define ML_EXTERN_C_BEGIN
#define ML_EXTERN_C_END
#endif

#include "ml_coordinate_frame_uid.h"
#include "ml_version.h"

ML_EXTERN_C_BEGIN

/*!
  \brief Integer handle type used to reference many things returned by the API, instead of
  returning pointers directly. Use MLHandleIsValid() to check if a handle is valid or not.
*/
typedef uint64_t MLHandle;

/*! Value of an invalid handle. To test if a handle is invalid use MLHandleIsValid(). */
enum {
  ML_INVALID_HANDLE = 0xFFFFFFFFFFFFFFFF
};

enum {
  /*! Maximum character length of MLVersion build ID. */
  MLVersion_BuildIdMaxLength = 128
};

/*!
  \brief SDK version: [major].[minor].[revision].[build_id]
*/
typedef struct MLVersion {
  /*! Major version. */
  uint32_t major;
  /*! Minor version. */
  uint32_t minor;
  /*! Revision. */
  uint32_t revision;
  /*! Build ID. */
  char build_id[MLVersion_BuildIdMaxLength];
} MLVersion;

typedef enum MLStatus {
  MLStatus_OK = 0,
  MLStatus_InvalidParam,
  MLStatus_Fail,
  MLStatus_OutOfMemory,
  MLStatus_Ensure32Bits = 0x7FFFFFFF
} MLStatus;

/*!
  \brief Check if a handle is valid.
  \param[in] handle The handle to check.
  \return \c true if the handle is valid.
*/
ML_INLINE bool MLHandleIsValid(MLHandle handle) {
  return handle != ML_INVALID_HANDLE;
}

/*!
  \brief Get SDK version as c-style string.
*/
ML_INLINE const char *ML_CALL MLGetVersionName() {
  return MLSDK_VERSION_NAME;
}

/*!
  \brief Get SDK version as a struct with major, minor, revision, and build_id.
*/
ML_INLINE MLVersion MLGetVersion() {
  MLVersion version = {MLSDK_VERSION_MAJOR,
                       MLSDK_VERSION_MINOR,
                       MLSDK_VERSION_REVISION,
                       MLSDK_VERSION_BUILD_ID};
  return version;
}

ML_EXTERN_C_END
