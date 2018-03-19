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
  \addtogroup MediaPlayer
  @{
*/

/*!
  \brief Called to request data from the given position.

  Implementations should should write up to \p size bytes into
  \p buffer, and return the number of bytes written.

  Return 0 to indicate that end of stream is reached.
  Return -1 on error.

  \param[in] media_data_source #MLHandle as returned by MLMediaDataSourceCreate().
  \param[in] position The position in the data source to read from.
  \param[in] size The number of bytes to read.
  \param[out] buffer The buffer to read the data into.
  \param[in,out] context User data as passed to MLMediaDataSourceCreate().
  \return The number of bytes read, or -1 if there was an error.
*/
typedef int64_t (*MLMediaDataSourceReadAt) (MLHandle media_data_source, size_t position, size_t size, uint8_t *buffer, void *context);

/*!
  \brief Called to get the size of the data source.
  \param[in] media_data_source #MLHandle as returned by MLMediaDataSourceCreate().
  \param[in,out] context User data as passed to MLMediaDataSourceCreate().
  \return the size of data source in bytes, or -1 if the size is unknown.
*/
typedef int64_t (*MLMediaDataSourceGetSize) (MLHandle media_data_source, void *context);

/*!
  \brief Called before deleting |this|. The other methods may return errors
  if they're called after calling close().
  \param[in] media_data_source #MLHandle as returned by MLMediaDataSourceCreate().
  \param[in,out] context User data as passed to MLMediaDataSourceCreate().
*/
typedef void (*MLMediaDataSourceClose) (MLHandle media_data_source, void *context);

/*!
  \brief Create a new MediaDataSource object.
  \param[in] read_at MLMediaDataSourceReadAt callback.
  \param[in] get_size MLMediaDataSourceGetSize callback.
  \param[in] close MLMediaDataSourceClose callback.
  \param[in] context User data to be passed to callbacks.
  \return A handle to the created MediaDataSource.
*/
ML_API MLHandle ML_CALL MLMediaDataSourceCreate(MLMediaDataSourceReadAt read_at, MLMediaDataSourceGetSize get_size, MLMediaDataSourceClose close, void *context);

/*!
  \brief Destroy a #MediaDataSource object.
  \param[in] media_data_source #MLHandle to the #MediaDataSource object to destroy.
  \return true if #MediaDataSource object was successfully destroyed.
*/
ML_API bool ML_CALL MLMediaDataSourceDestroy(MLHandle media_data_source);

/*! @} */

ML_EXTERN_C_END
