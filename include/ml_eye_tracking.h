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
  \defgroup EyeTracking Eye Tracking
  \addtogroup EyeTracking
  \brief APIs for the Eye Tracking system.

  - The Eye Tracking system is for eye tracking.
  @{
*/

/*! A set of possible error codes that the Eye Tracking system can report. */
typedef enum MLEyeTrackingError {
  /*! No error, tracking is nominal. */
  MLEyeTrackingError_None,
  /*! Eye Tracker failed. */
  MLEyeTrackingError_Generic,
  /*! Ensure enum is represented as 32 bits. */
  MLEyeTrackingError_Ensure32Bits = 0x7FFFFFFF
} MLEyeTrackingError;

/*! Static information about the Eye Tracker. Populate with MLEyeTrackingGetStaticData(). */
typedef struct MLEyeTrackingStaticData {
  MLCoordinateFrameUID fixation;
  MLCoordinateFrameUID left_center;
  MLCoordinateFrameUID right_center;
} MLEyeTrackingStaticData;

/*! Information about the state of the Eye Tracking system. */
typedef struct MLEyeTrackingState {
  /*! A quality metric confidence value to indicate accuracy of fixation. */
  float fixation_confidence;
  /*! A quality metric confidence value to indicate accuracy of left eye center. */
  float  left_center_confidence;
  /*! A quality metric confidence value to indicate accuracy of right eye center. */
  float right_center_confidence;
  /*! \c true if eyes are inside a blink. When not wearing the device, values can be arbitrary. */
  bool left_blink;
  bool right_blink;
  /*! Represents what eye tracking error (if any) is present. */
  MLEyeTrackingError error;
  /*! Has eye calibration been run. */
  bool calibration_complete;
} MLEyeTrackingState;

/*!
  \brief Create an Eye Tracker.
  \return A handle to the created Eye Tracker. If there is an error during creation,
          it will return #ML_INVALID_HANDLE.
*/
ML_API MLHandle ML_CALL MLEyeTrackingCreate();

/*!
  \brief Destroy an Eye Tracker.
  \param eye_tracker A handle to an Eye Tracker created by MLEyeTrackingCreate().
  \return \c true if the Eye Tracker was successfully destroyed, \c false otherwise.
*/
ML_API bool ML_CALL MLEyeTrackingDestroy(MLHandle eye_tracker);

/*!
  \brief Get static information about the eye tracker.
  \param eye_tracker A handle to an Eye Tracker created by MLEyeTrackingCreate().
  \param out_data Target to populate the data about the eye tracker.
  \return \c true if the data has been populated, \c false otherwise.
*/
ML_API bool ML_CALL MLEyeTrackingGetStaticData(MLHandle eye_tracker, MLEyeTrackingStaticData *out_data);

/*!
  \brief Get information about the user's eyes.
  \param eye_tracker A handle to an Eye Tracker created by MLEyeTrackingCreate().
  \param out_state Information about the eyes.
  \return \c true if the state has been populated, \c false otherwise.
*/
ML_API bool ML_CALL MLEyeTrackingGetState(MLHandle eye_tracker, MLEyeTrackingState *out_state);

/*! @} */

ML_EXTERN_C_END

