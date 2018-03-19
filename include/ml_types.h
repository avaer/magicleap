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

/*! 2D vector represented with X and Y floats. */
typedef struct MLVec2f {
  float x;
  float y;
} MLVec2f;

/*!
  \brief Internal structure used to simplify access of MLVec3f. Do not create
  this structure directly and always use MLVec3f instead.
*/
typedef struct MLXYZf {
  float x;
  float y;
  float z;
} MLXYZf;

/*! 3D vector represented with X, Y, and Z floats. */
typedef struct MLVec3f {
  /*! TODO(zwhaley): PF-609: This is is to account for different usages between the PIL and SDK. */
  union {
    MLXYZf xyz;
    float values[3];
    struct {
      float x;
      float y;
      float z;
    };
  };
} MLVec3f;

/*! Quaternion stored as X, Y, Z, W floats. */
typedef struct MLQuaternionf {
  /*! TODO(zwhaley): PF-609: This is is to account for different usages between the PIL and SDK. */
  union {
    /*! Values of the quaternions laid out as X, Y, Z, W. */
    float values[4];
    struct {
      float x;
      float y;
      float z;
      float w;
    };
  };
} MLQuaternionf;

/*! Information used to transform from one coordinate frame to another. */
typedef struct MLTransform {
  /*! The rotation of the coordinate frame to apply after the translation. */
  MLQuaternionf rotation;
  /*! The translation to apply to get to the coordinate frame in the proper
      location. */
  MLVec3f position;
} MLTransform;

/*! An arbitrary 4x4 matrix represented with an array of floats. */
typedef struct MLMat4f {
  float matrix_colmajor[16];
} MLMat4f;

/*! A 2D float rectangle. */
typedef struct MLRectf {
  float x;
  float y;
  float w;
  float h;
} MLRectf;

/*! A 2D integer rectangle. */
typedef struct MLRecti {
  int32_t x;
  int32_t y;
  int32_t w;
  int32_t h;
} MLRecti;

/*! Color represented by 4 unsigned bytes. */
typedef struct MLColor32 {
  union {
    struct {
      uint8_t a;
      uint8_t b;
      uint8_t g;
      uint8_t r;
    };
    uint32_t rgba;
  };
} MLColor32;

/*! Color represented by 4 floats. */
typedef struct MLColor4f {
  float r;
  float g;
  float b;
  float a;
} MLColor4f;

/*! Universally Unique Identifier. */
typedef struct MLUUID {
  union {
    struct {
      uint32_t time_low;
      uint16_t time_mid;
      uint16_t time_hi_and_version;
      uint8_t clock_seq_hi_and_reserved;
      uint8_t clock_seq_low;
      uint8_t node[6];
    };
    uint8_t data[16];
  };
} MLUUID;

ML_EXTERN_C_END
