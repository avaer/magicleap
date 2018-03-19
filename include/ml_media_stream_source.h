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
  \brief Called when buffers becomes available.

  Signal that at least one buffer is now available. Application should then
  call getBuffer() as much as possible until it returns false, or until no
  more data is currently available in the application.

  \param[in] media_stream_source #MLHandle as returned by MLMediaStreamSourceCreate().
  \param[in,out] context User data as passed to MLMediaStreamSourceCreate().
*/
typedef void (*MLMediaStreamSourceOnBufferAvailable) (MLHandle media_stream_source, void *context);

/*!
  \brief Create a new #MediaStreamSource object.
  \param[in] on_buffer_available #MLMediaStreamSourceOnBufferAvailable callback.
  \param[in] context User data to be passed to callbacks.
  \return A handle to the created #MediaStreamSource.
*/
ML_API MLHandle ML_CALL MLMediaStreamSourceCreate(MLMediaStreamSourceOnBufferAvailable on_buffer_available, void *context);

/*!
  \brief Destroy a #MediaStreamSource object.
  \param[in] media_stream_source #MLHandle to the #MediaStreamSource object to destroy.
*/
ML_API void ML_CALL MLMediaStreamSourceDestroy(MLHandle media_stream_source);

/*!
  \brief Get a buffer where data can be written.

  If a buffer is available, true is returned and outId, outPtr and outSize
  are set. Application can then write up to outSize bytes into outPtr and
  push that data using pushBuffer().

  If no buffer is available, false is returned and application should wait
  for onBufferAvailable() to be called before retrying.

  \param[in] media_stream_source #MLHandle as returned by MLMediaStreamSourceCreate().
  \param[out] out_id an opaque ID that should be passed to MLMediaStreamSourcePushBuffer().
  \param[out] out_ptr the location where to write data.
  \param[out] out_size maximum bytes that can be written in outPtr.
  \return \c true if a buffer is returned, \c false if none is currently available.
*/
ML_API bool ML_CALL MLMediaStreamSourceGetBuffer(MLHandle media_stream_source, size_t *out_id, uint8_t **out_ptr, size_t *out_size);

/*!
  \brief Push a buffer.

  Queue a buffer acquired from MLMediaStreamSourceGetBuffer() once data has been written.

  \param[in] media_stream_source #MLHandle as returned by MLMediaStreamSourceCreate().
  \param[in] id the ID of the buffer as given by MLMediaStreamSourceGetBuffer().
  \param[in] size the number of bytes actually written in the buffer.
*/
ML_API void ML_CALL MLMediaStreamSourcePushBuffer(MLHandle media_stream_source, size_t id, size_t size);

/*!
  \brief Push End-Of-Stream event.

  Signal that the end of stream is reached and no more data will be pushed.

  \param media_stream_source #MLHandle as returned by MLMediaStreamSourceCreate().
*/
ML_API void ML_CALL MLMediaStreamSourcePushEOS(MLHandle media_stream_source);

/*! @} */

ML_EXTERN_C_END
