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
#include "ml_snapshot.h"

ML_EXTERN_C_BEGIN

/*!
  \addtogroup Perception
  \brief APIs for the Perception system.

  - The Perception system is for perception.
  @{
*/

/*! Settings for initializing the perception system. */
typedef struct MLPerceptionSettings {
  uint16_t override_port;
} MLPerceptionSettings;

/*!
  \brief Initialize the perception system with the passed in settings.
  \param[out] settings Initializes the perception system with these settings.
  \return \c true or \c false, whether or not the system started up properly.
*/
ML_API bool ML_CALL MLPerceptionInitSettings(MLPerceptionSettings *settings);

/*!
  \brief Start the perception system.

  This function should be called before any perception functions are called.

  \param[in] settings The perception system starts with these settings.
  \return \c true, or \c false, whether or not the system started up properly.
*/
ML_API bool ML_CALL MLPerceptionStartup(MLPerceptionSettings *settings);

/*!
  \brief Shut down and clean up all resources used by the perception system.

  This function should be called prior to exiting the program
  if a call to MLPerceptionStartup() was called.

  \return \c true, or \c false, whether or not the system shutdown properly.
*/
ML_API bool ML_CALL MLPerceptionShutdown();

/*!
  \brief Pull in the latest state of all persistent transforms and all
  enabled trackers extrapolated to the next frame time.

  Return a #MLSnapshot with this latest state. This snap should be
  used for the duration of the frame being constructed and then
  released with a call to MLPerceptionReleaseSnapshot().

  \return Valid pointer to a #MLSnapshot object on success, NULL otherwise.
*/
ML_API MLSnapshot *ML_CALL MLPerceptionGetSnapshot();

/*!
  \brief Release specified #MLSnapshot object.

  To be called exactly once for each call to MLPerceptionGetSnapshot().

  \param[out] snap Pointer to a valid snap object.
  \returns \c true on success, \c false otherwise.
*/
ML_API bool ML_CALL MLPerceptionReleaseSnapshot(MLSnapshot *out_snap);

/*! @} */

ML_EXTERN_C_END
