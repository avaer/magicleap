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

ML_EXTERN_C_BEGIN

/*!
  \addtogroup Raycast
  \brief APIs for the Raycast system.

  - The Raycast system is for raycast.
  @{
*/

/*! Request information for a raycast. */
typedef struct MLRaycastQuery {
  /*! Where the ray is cast from. */
  MLVec3f position;
  /*! Direction of the ray to fire. */
  MLVec3f direction;
  /*! Up vector of the ray to fire. Use (0, 0, 0) to use the up vector of the rig frame. */
  MLVec3f up_vector;
  /*! The number of horizontal rays. For single point raycast, set this to 1. */
  uint32_t width;
  /*! The number of vertical rays. For single point raycast, set this to 1. */
  uint32_t height;
  /*! The horizontal field of view, in degrees. */
  float horizontal_fov_degrees;
  /*!
    \brief If \c true, a ray will terminate when encountering an
    unobserved area and return a surface or the ray will continue until
    it ends or hits a observed surface.
  */
  bool collide_with_unobserved;
} MLRaycastQuery;

/*! The states of a raycast result. */
typedef enum MLRaycastResultState {
  /*! The raycast request failed. */
  MLRaycastResultState_RequestFailed = -1,
  /*! The ray passed beyond maximum raycast distance and it doesn't hit any surface. */
  MLRaycastResultState_NoCollision,
  /*! The ray hit unobserved area. This will on occur when collide_with_unobserved is set to true. */
  MLRaycastResultState_HitUnobserved,
  /*! The ray hit only observed area. */
  MLRaycastResultState_HitObserved,
  /*! Ensure enum is represented as 32 bits. */
  MLRaycastResultState_Ensure32Bits = 0x7FFFFFFF
} MLRaycastResultState;

/*! Result of a raycast. */
typedef struct MLRaycastResult {
  /*!
    \brief Where in the world the collision happened.
    This field is only valid if the state is either #MLRaycastResultState_HitUnobserved
    or #MLRaycastResultState_HitObserved.
  */
  MLVec3f hitpoint;
  /*!
    \brief Normal to the surface where the ray collided.
    This field is only valid if the state is either
    #MLRaycastResultState_HitUnobserved or #MLRaycastResultState_HitObserved.
  */
  MLVec3f normal;
  /*!
    \brief Confidence of the raycast result. Confidence is a non-negative value from 0 to 1 where closer
    to 1 indicates a higher quality. It is an indication of how confident we are about raycast result
    and underlying 3D shape. This field is only valid if the state is
    either #MLRaycastResultState_HitUnobserved or #MLRaycastResultState_HitObserved.
  */
  float confidence;
  /*!
    \brief The raycast result. If this field is either #MLRaycastResultState_RequestFailed or
    #MLRaycastResultState_NoCollision, fields in this structure are invalid.
  */
  MLRaycastResultState state;
} MLRaycastResult;

/*!
  \brief Create the raycast system.

  This function must be called with the the required settings prior to MLRaycastRequest.

  \return The handle of the created tracker if it was created successfully,
          #ML_INVALID_HANDLE otherwise.
*/
ML_API MLHandle ML_CALL MLRaycastCreate();

/*!
  \brief Destroy a raycast tracker.
  \param[in] raycast_handle A handle to the raycast request.
  \return \c true if the raycast tracker was released properly.
*/
ML_API bool ML_CALL MLRaycastDestroy(MLHandle tracker_handle);

/*!
  \brief Begin a query to a raycast.
  \param[in] tracker_handle A handle to the tracker created by MLRaycastCreate.
  \param[in] request Query parameters for the raycast.
  \return A handle to query for the result which will be available in the
          future from MLRaycastGetResult.
*/
ML_API MLHandle ML_CALL MLRaycastRequest(MLHandle tracker_handle, const MLRaycastQuery *request);

/*!
  \brief Get the result of a call to MLRaycastRequest.

  After this function has returned successfully, the handle
  is invalid.

  \param[in] raycast_request A handle to the raycast request.
  \param[out] out_result The target to populate the result.
  \return \c true if the result is available, \c false otherwise.
*/
ML_API bool ML_CALL MLRaycastGetResult(MLHandle tracker_handle, MLHandle raycast_request, MLRaycastResult *out_result);

/*! @} */

ML_EXTERN_C_END
