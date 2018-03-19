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
  \defgroup LightingTracking Lighting Tracking
  \addtogroup LightingTracking
  \brief APIs for the Lighting Tracking system.

  - The Lighting Tracking system is for ALS and lighting state
  @{
*/

typedef enum MLLightingTrackingCamera {
  MLLightingTrackingCamera_Left,
  MLLightingTrackingCamera_Right,
  MLLightingTrackingCamera_FarLeft,
  MLLightingTrackingCamera_FarRight,
  MLLightingTrackingCamera_Count,
} MLLightingTrackingCamera;

enum {
  MLLightingTracking_GridWidth = 8,
  MLLightingTracking_GridHeight = 6,
};

/*!
  \brief    Create a Lighting Tracker.
  \returns  A handle to the created Lighting Tracker. If there is an error during
            creation, it will return #ML_INVALID_HANDLE.
*/
ML_API MLHandle ML_CALL MLLightingTrackingCreate();

/*!
  \brief    Destroy a Lighting Tracker.
  \param    lighting_tracker A handle to a lighting Tracker created by MLLightingTrackingCreate().
  \returns  True if the Lighting Tracker was successfully destroyed, false otherwise.
*/
ML_API bool ML_CALL MLLightingTrackingDestroy(const MLHandle lighting_tracker);

/*! Information about the ambient light sensor global state. */
typedef struct MLLightingTrackingAmbientGlobalState {
  /*! \brief Array stores values for each world camera, ordered left, right, far left, far right.
             Luminance estimate is in nits (cd/m^2).
  */
  uint16_t als_global[MLLightingTrackingCamera_Count];
} MLLightingTrackingAmbientGlobalState;

/*!
  \brief    Gets information about the ambient light sensor global state.
  \param    lighting_tracker A handle to a Lighting Tracker created by MLLightingTrackingCreate().
  \param    out_state Information about the global lighting state.
  \returns  True if the state has been populated, false otherwise.
*/
ML_API bool ML_CALL MLLightingTrackingGetAmbientGlobalState(const MLHandle lighting_tracker, MLLightingTrackingAmbientGlobalState *out_state);

/*! Information about the ambient light sensor grid state. */
typedef struct MLLightingTrackingAmbientGridState {
  /*! \brief Array stores grid for each world camera, ordered left, right, far left, far right.
             Luminance estimate is in nits (cd/m^2).
  */
  uint16_t als_grid[MLLightingTrackingCamera_Count][MLLightingTracking_GridHeight][MLLightingTracking_GridWidth];
} MLLightingTrackingAmbientGridState;

/*!
  \brief    Gets information about the ambient light sensor grid state.
  \param    lighting_tracker A handle to a Lighting Tracker created by MLLightingTrackingCreate().
  \param    out_state Information about the grid lighting state.
  \returns  True if the state has been populated, false otherwise.
*/
ML_API bool ML_CALL MLLightingTrackingGetAmbientGridState(const MLHandle lighting_tracker, MLLightingTrackingAmbientGridState *out_state);

/*! Information about the color temperature state. */
typedef struct MLLightingTrackingColorTemperatureState {
  /*! Color temperature is in Kelvin. */
  uint16_t color_temp;
} MLLightingTrackingColorTemperatureState;

/*!
  \brief    Gets information about the color temperature state.
  \param    lighting_tracker A handle to a Lighting Tracker created by MLLightingTrackingCreate().
  \param    out_state Information about the color temperature state.
  \returns  True if the state has been populated, false otherwise.
*/
ML_API bool ML_CALL MLLightingTrackingGetColorTemperatureState(const MLHandle lighting_tracker, MLLightingTrackingColorTemperatureState *out_state);


/*! @} */

ML_EXTERN_C_END
