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
#include "ml_pose.h"

ML_EXTERN_C_BEGIN

/*!
  \defgroup HeadTracking Head Tracking
  \addtogroup HeadTracking
  \brief APIs for the Head Tracking system.

  - The Head Tracking system is for head tracking.
  @{
*/

/*!
  \brief Static information about a Head Tracker. Populate this structure with
  MLHeadTrackingGetStaticData().
*/
typedef struct MLHeadTrackingStaticData {
  MLCoordinateFrameUID coord_frame_head;
} MLHeadTrackingStaticData;

/*!
  \brief A set of possible error conditions that can cause Head Tracking to
  be less than ideal.
*/
typedef enum MLHeadTrackingError {
  /*! No error, tracking is nominal. */
  MLHeadTrackingError_None,
  /*! There are not enough features in the environment. */
  MLHeadTrackingError_Featureless,
  /*! Lighting in the environment is not sufficient to track accurately. */
  MLHeadTrackingError_LowLight,
  /*! There is too much movement in the environment. */
  MLHeadTrackingError_DynamicScene,
  /*! Head motion is too fast to track accurately. */
  MLHeadTrackingError_DynamicMotion,
  /*! Ensure enum is represented as 32 bits. */
  MLHeadTrackingError_Ensure32Bits = 0x7FFFFFFF
} MLHeadTrackingError;

/*! A set of possible tracking modes the Head Tracking system can be in. */
typedef enum MLHeadTrackingMode {
  /*! Full 6 degrees of freedom tracking (position and orientation). */
  MLHeadTrackingMode_6DOF,
  /*! Limited 3 degrees of freedom tracking (orientation only). */
  MLHeadTrackingMode_3DOF,
  /*! Ensure enum is represented as 32 bits. */
  MLHeadTrackingMode_Ensure32Bits = 0x7FFFFFFF
} MLHeadTrackingMode;

/*!
  \brief A structure containing information on the current state of the
  Head Tracking system.
*/
typedef struct MLHeadTrackingState {
  /*! What tracking mode the Head Tracking system is currently in. */
  MLHeadTrackingMode mode;
  /*! A confidence value (from [0, 1]) representing the confidence in the current pose estimation.
      <b>WARNING: Currently always set to 1.</b>
  */
  float confidence;
  /*! Represents what tracking error (if any) is present.
      <b>WARNING: Currently always set to MLHeadTrackingerror_None.</b>
  */
  MLHeadTrackingError error;
} MLHeadTrackingState;

/*!
  \brief Create a Head Tracker.
  \return A handle to the created Head Tracker. If there is an error during creation,
          it will return #ML_INVALID_HANDLE.
*/
ML_API MLHandle ML_CALL MLHeadTrackingCreate();

/*!
  \brief Destroy a Head Tracker.
  \param[in] head_tracker A handle to a Head Tracker created by MLHeadTrackingCreate().
  \return \c true if it successfully destroyed the tracker.
*/
ML_API bool ML_CALL MLHeadTrackingDestroy(MLHandle head_tracker);

/*!
  \brief Return static information about the Head Tracker.
  \param[in] head_tracker A handle to the tracker.
  \param[out] out_data Target to populate the data about that Head Tracker.
  \return \c true if the data has been populated, \c false otherwise.
*/
ML_API bool ML_CALL MLHeadTrackingGetStaticData(MLHandle head_tracker, MLHeadTrackingStaticData *out_data);

/*!
  \brief Return the most recent Head Tracking state.
  \param head_tracker A handle to the tracker
  \param out_state Pointer to valid #MLHeadTrackingState object to be filled with current state information.
  \return \c true if out_state has been filled with current state, \c false otherwise.
*/
ML_API bool ML_CALL MLHeadTrackingGetState(MLHandle head_tracker, MLHeadTrackingState *out_state);

/*! @} */

ML_EXTERN_C_END
