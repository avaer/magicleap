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

ML_EXTERN_C_BEGIN

/*!
  \brief Image API

  - Image API provides structures to represent images in multiple formats.

  \addtogroup Image
  @{
*/

/*! Information about the data contained inside the image. */
typedef enum MLImageType {
  /*! Bit mask storing 8-bit unsigned int per pixel. */
  MLImageType_BitMask,
  /*! RGB format (linear color space). */
  MLImageType_RGB24,
  /*! RGBA format (linear color space). */
  MLImageType_RGBA32,
  MLImageType_Ensure32Bits = 0x7FFFFFFF
} MLImageType;

/*! Image and its meta-data. */
typedef struct MLImage {
  /*! Image width in pixels. */
  uint32_t width;
  /*! Image height in pixels. */
  uint32_t height;
  /*! Type of image. */
  MLImageType image_type;
  /*!
    \brief Row alignment (in bytes).

    It defines the amount of extra bytes to be used as padding,
    such that the stride must be a multiple of this alignment.
    The accepted values are 1, 2, 4, 8 or 16. (1 means no padding).

    The stride of the image should be considered as:
      stride = width * numberOfChannels * bytesPerChannel + padding.

    Example:
    Let's say we have an RGB image (3 channels) of width 111 and alignment 4, then:
      stride = 111 * 3 * 1 + 3 = 336.
    The padding is 3 and the stride is 336, multiple of the alignment 4.
  */
  uint8_t alignment;
  /*!
    \brief The image data stored without compression in row major order.
    Image origin is the upper left corner.
  */
  uint8_t *data;
} MLImage;

/*! @} */

ML_EXTERN_C_END
