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
#include "ml_types.h"
#include "ml_graphics.h"

ML_EXTERN_C_BEGIN

/*!
  \addtogroup Occlusion
  \brief APIs for the Occlusion system.

  - The Occlusion system is for visual occlusion
  @{
*/

/*! Per virtual camera information needed to render depth. */
typedef struct MLOcclusionVirtualCameraBufferInfo {
  /*! The projection matrix for the camera. */
  MLMat4f projection;
  /*! The local space (relative to world) camera transform needed to render content,
      inverse is view matrix. */
  MLTransform transform;
} MLOcclusionVirtualCameraBufferInfo;

/*! To be passed to PopulateDepth(). */
typedef struct MLOcclusionDepthBufferInfo {
  /*! The number of buffers to render to for the frame. */
  uint32_t num_buffers;
  /*![DEBUG_ONLY] The handle (ID) of the color surface to render to for the buffer. */
  MLHandle color_id;
  /*! The handle (ID) of the depth surface to render to for the buffer. */
  MLHandle depth_id;
  /*! The origin and extents to render to for the camera. */
  MLRectf viewport;
  /*! Controls use of far_clip and directionality of z in projection model. */
  MLGraphicsProjectionType projection_type;
  /*! The array of buffers to render to for the frame. */
  MLOcclusionVirtualCameraBufferInfo buffers[MLGraphicsVirtualCameraName_Count];
} MLOcclusionDepthBufferInfo;

/*!
  \brief Create the resources for the OpenGL context.
  \param[out] out_client The handle to the created client.
  \param[out] out_status #MLStatus code indicating success as #ML_STATUS_OK or failure.
  \return \c true if successful.
*/
ML_API bool ML_CALL MLOcclusionCreateClient(MLHandle *out_client, MLStatus *out_status);

/*!
  \brief Free the resources.
  \param[in] in_client The handle to the client to destroy.
  \param[out] out_status #MLStatus code indicating success as #ML_STATUS_OK or failure.
  \return \c true if successful.
*/
ML_API bool ML_CALL MLOcclusionDestroyClient(MLHandle *in_client, MLStatus *out_status);

/*!
  \brief To be called after MLGraphicsBeginFrame().
  \param[in] in_client The client created.
  \param[in] in_info The per virtual camera info for rendering depth.
  \param[out] out_status #MLStatus code indicating success as #ML_STATUS_OK or failure.
  \return \c true if successful.
*/
ML_API bool ML_CALL MLOcclusionPopulateDepth(const MLHandle in_client, const MLOcclusionDepthBufferInfo *in_info, MLStatus *out_status);

/*! @} */

ML_EXTERN_C_END
