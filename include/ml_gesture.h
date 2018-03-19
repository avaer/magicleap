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
#include "ml_data_array.h"
#include "ml_image.h"
#include "ml_types.h"

ML_EXTERN_C_BEGIN

/*!
  \addtogroup Gestures
  \brief APIs for the Gestures system.

  - The Gestures system is for gestures.
  @{
*/

/*! Index into arrays which contain multiple gesture information. */
typedef enum MLGestureIndex {
  MLGestureIndex_LeftHand,
  MLGestureIndex_RightHand,
  MLGestureIndex_Count,
  /*! Ensure enum is represented as 32 bits. */
  MLGestureIndex_Ensure32Bits = 0x7FFFFFFF
} MLGestureIndex;

enum {
  /*! Maximum number of key points per gesture. */
  MLGestureStaticData_MaxKeyPoints = 6
};

/*! Static gesture types which are available when both hands are separated. */
typedef enum MLGestureStaticHandState {
  /*! One finger. */
  MLGestureStaticHandState_Finger,
  /*! A closed fist. */
  MLGestureStaticHandState_Fist,
  /*! A pinch. */
  MLGestureStaticHandState_Pinch,
  /*! A closed fist with the thumb pointed up. */
  MLGestureStaticHandState_Thumb,
  /*! An L shape */
  MLGestureStaticHandState_L,
  /*! An open hand with the back of the hand facing the user. */
  MLGestureStaticHandState_OpenHandBack,
  /*! \brief A pinch (between the index finger and thumb) with all other fingers extended. */
  MLGestureStaticHandState_Ok,
  /*! A rounded 'C' alphabet shape. */
  MLGestureStaticHandState_C,
  /*! No gesture was recognized. */
  MLGestureStaticHandState_NoHand,
  /*! Number of static gestures. */
  MLGestureStaticHandState_Count,
  /*! Ensure enum is represented as 32 bits. */
  MLGestureStaticHandState_Ensure32Bits = 0x7FFFFFFF
} MLGestureStaticHandState;

/*! Amount of filtering for different gesture information. */
typedef enum MLGestureFilterLevel {
  MLGestureFilterLevel_0,
  MLGestureFilterLevel_1,
  MLGestureFilterLevel_2,
  MLGestureFilterLevel_Count,
  MLGestureFilterLevel_Ensure32Bits = 0x7FFFFFFF
} MLGestureFilterLevel;

/*! Result of a gesture for one hand. */
typedef struct MLGestureOneHandedState {
  /*! The static gesture currently being performed by the single hand. */
  MLGestureStaticHandState static_gesture_category;
  /*!
    \brief The confidence level of a particular pose by the single hand.
    Value is between [0, 1], 0 is low, 1 is high degree of confidence.
    For a NoHand, the confidence is always set to 1.
  */
  float gesture_confidence;
  /*!
    \brief Total number of key points detected for the current static gesture.
    This is the number of indices with valid data in the array for the
    corresponding hand in #MLGestureStaticData.
    If the current static gesture category is NoHand, then this value and
    the corresponding keypoint transforms are carried over from the previous frame.
  */
  uint32_t num_key_points;
  /*! Normalized position of hand center within depth-sensor view. Each dimension is between [-1, 1]. */
  MLVec3f hand_center_normalized;
} MLGestureOneHandedState;

/*! Data which is received when querying gestures from MLGestureGetData(). */
typedef struct MLGestureData {
  /*! Gesture state of the left hand. */
  MLGestureOneHandedState left_hand_state;
  /*! Gesture state of the right hand. */
  MLGestureOneHandedState right_hand_state;
} MLGestureData;

/*!
  \brief Static information about a gesture tracker. Populate this structure with
  MLGestureGetStaticData().
*/
typedef struct MLGestureStaticData {
  /*! Key points detected on the left hand. Number of valid entries is
    MLGestureData::left_hand_state::num_key_points. */
  MLCoordinateFrameUID left_frame[MLGestureStaticData_MaxKeyPoints];
  /*! Key points detected on the right hand. Number of valid entries is
    MLGestureData::right_hand_state::num_key_points. */
  MLCoordinateFrameUID right_frame[MLGestureStaticData_MaxKeyPoints];
  /*! Hand center detected on the left hand. If the current static gesture is NoHand,
      then the corresponding transform is carried over from the previous frame. */
  MLCoordinateFrameUID left_hand_center;
  /*! Hand center detected on the right hand. If the current static gesture is NoHand,
      then the corresponding transform is carried over from the previous frame. */
  MLCoordinateFrameUID right_hand_center;
} MLGestureStaticData;

/*!
  \brief Hand bitmasks about a gesture tracker. Populate this structure with
  MLGestureGetHandMasks().
*/
typedef struct MLGestureHandMasks {
  /*! Handle to a custom Data Array type. This custom type is a two-element array with
    type #MLImage. The #MLImageType is of type #MLImageType_BitMask. */
  MLDataArrayHandle masks;
} MLGestureHandMasks;

/*!
  \brief Configuration of the gesture tracking system. This is used to activate or
  deactivate the gestures the system will look for.
*/
typedef struct MLGestureConfiguration {
  /*!
    \brief Configuration for the static gestures.
    \c true will enable the gesture to be tracked by the system, \c false will disable it.
    If a disabled gesture is performed, the most probable enabled gesture will be reported.
    Disabling NoHand has no effect.
  */
  bool static_gestures_config[MLGestureStaticHandState_Count];
  /*! True activates gesture tracking. False deactivates the gesture pipeline entirely
      and no recognition will take place. */
  bool gesture_pipeline_enabled;
  /*!
    \brief Configured level for gestures filtering of keypoints and hand centers.
    MLGestureFilterLevel_0 - Default value, no filtering is done, the points are raw.
    MLGestureFilterLevel_1 - Some smoothing at the cost of latency.
    MLGestureFilterLevel_2 - Predictive smoothing, at higher cost of latency.
  */
  MLGestureFilterLevel keypoints_filter_level;
  /*!
    \brief Configured level for gestures filtering of static gestures.
    MLGestureFilterLevel_0 - Default value, No filtering, the gestures are raw.
    MLGestureFilterLevel_1 - Some robustness to flicker at some cost of latency.
    MLGestureFilterLevel_2 - More robust to flicker at higher latency cost.
  */
  MLGestureFilterLevel pose_filter_level;
  /*!
    \brief Configured level for gestures filtering if the left or right hand is present.
    MLGestureFilterLevel_0 - Default value, No filtering, the hand types are raw.
    MLGestureFilterLevel_1 - Some robustness to flicker at some cost of latency.
    MLGestureFilterLevel_2 - More robust to flicker at higher latency cost.
  */
  MLGestureFilterLevel handtype_filter_level;
} MLGestureConfiguration;

/*!
  \brief Create a gesture tracker.
  \return A handle which can be used with MLGestureGetData() to get information about the gesture,
          or #ML_INVALID_HANDLE if the tracker could not be created.
*/
ML_API MLHandle ML_CALL MLGestureTrackingCreate();

/*!
  \brief Destroy a gesture tracker.
  \param[in] gesture_tracker A handle to a Gesture Tracker created by MLGestureTrackingCreate().
  \return \c true if it successfully destroyed the tracker.
*/
ML_API bool ML_CALL MLGestureTrackingDestroy(MLHandle gesture_tracker);

/*!
  \brief Query the current state of the gesture tracker.
  \param[in] gesture_tracker A handle to a Gesture Tracker created by MLGestureTrackingCreate().
  \param[out] out_data Pointer to a variable that receives information about the tracked gestures.
  \return \c true if the gesture information was available and the information in out_data is valid.
*/
ML_API bool ML_CALL MLGestureGetData(MLHandle gesture_tracker, MLGestureData *out_data);

/*!
  \brief Get static information about gesture tracking.
  \param[in] gesture_tracker A handle to a Gesture Tracker created by MLGestureTrackingCreate().
  \param[out] out_data Pointer to a variable that receives static data about the gesture tracker.
  \return \c true if the information in out_data is valid.
*/
ML_API bool ML_CALL MLGestureGetStaticData(MLHandle gesture_tracker, MLGestureStaticData *out_data);

/*!
  \brief Begin collecting hand masks.
  \param[in] handle A handle to the gesture tracker created from MLGestureTrackingCreate().
  \return \c true if the process to start hand masks collection has succeeded.
*/
ML_API bool ML_CALL MLGestureStartHandMasksTracking(MLHandle handle);

/*!
  \brief Stop collecting hand masks.
  \param[in] handle A handle to the gesture tracker created from MLGestureTrackingCreate().
  \return \c true if the process to stop hand masks collection has succeeded.
*/
ML_API bool ML_CALL MLGestureStopHandMasksTracking(MLHandle handle);

/*!
  \brief Get hand masks about gesture tracking.
  \param[in] handle A handle to the gesture tracker created from MLGestureTrackingCreate().
  \param[out] out_data Pointer to a variable that receives hand masks about the gesture tracker.
  \return true if the information in out_data is valid.
*/
ML_API bool ML_CALL MLGestureGetHandMasks(MLHandle handle, MLGestureHandMasks *out_data);

/*!
  \brief Set the configuration of the gesture tracking system.
  \param[in] gesture_tracker A handle to a Gesture Tracker created by MLGestureTrackingCreate().
  \param[in] config Pointer to a variable that contains the configuration.
  \return \c true if the gesture configuration was updated succesfully.
*/
ML_API bool ML_CALL MLGestureSetConfiguration(MLHandle gesture_tracker, const MLGestureConfiguration *config);

/*!
  \brief Get the current configuration of the gesture tracking system.
  \param[in] gesture_tracker A handle to a Gesture Tracker created by MLGestureTrackingCreate().
  \param[out] out_config Pointer to a variable that receives information about the current configuration.
  \return \c true if the information in out_config is valid.
*/
ML_API bool ML_CALL MLGestureGetConfiguration(MLHandle gesture_tracker, MLGestureConfiguration *out_config);

/*! @} */

ML_EXTERN_C_END
