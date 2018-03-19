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
  \addtogroup Audio
  \brief APIs for the Audio system.

  - The Audio system is for audio.
  @{
*/

typedef enum MLAudioSampleFormat {
  MLAudioSampleFormat_Int,
  MLAudioSampleFormat_Float,
  MLAudioSampleFormat_Ensure32Bits = 0x7FFFFFFF
} MLAudioSampleFormat;

typedef struct MLAudioBufferFormat {
  uint32_t channel_count;
  uint32_t samples_per_second;
  uint32_t bits_per_sample;
  uint32_t valid_bits_per_sample;
  MLAudioSampleFormat sample_format;
  uint32_t reserved;
} MLAudioBufferFormat;

typedef struct MLAudioBuffer {
  uint8_t *ptr;
  uint32_t size;
} MLAudioBuffer;

typedef enum MLAudioError {
  MLAudioError_Success,
  MLAudioError_NotImplemented,
  MLAudioError_UnspecifiedFailure,
  MLAudioError_UnauthorizedCommand,
  MLAudioError_HandleNotFound,
  MLAudioError_InvalidArgument,
  MLAudioError_InvalidSampleRate,
  MLAudioError_InvalidBitsPerSample,
  MLAudioError_InvalidValidBits,
  MLAudioError_InvalidSampleFormat,
  MLAudioError_InvalidChannelCount,
  MLAudioError_InvalidChannelFormat,
  MLAudioError_InvalidBufferSize,
  MLAudioError_BufferAllocFailure,
  MLAudioError_BufferNotReady,
  MLAudioError_FileNotFound,
  MLAudioError_FileNotRecognized,
  MLAudioError_Ensure32Bits = 0x7FFFFFFF
} MLAudioError;

typedef void (*MLAudioBufferCallback)(void *callback_context);

/*
 ********************************************************************
 *
 *************************** AUDIO OUTPUT ***************************
 *
 ********************************************************************
 */

/*!
  \brief Create a new audio output stream.

  Create an output stream that streams audio data to the audio output
  (built in speakers or headset). After creating the stream, it can be started
  by calling MLAudioStartSound(). Output streaming uses a double-buffer scheme.
  Data can optionally be pre-buffered by calling MLAudioGetOutputStreamBuffer()
  and MLAudioReleaseOutputStreamBuffer() either once or twice before
  calling MLAudioStartSound(). To determine the preferred buffer format
  settings, call MLAudioGetOutputStreamDefaults() before calling this function.

  \param[in] format #MLAudioBufferFormat specifying audio format of stream.
  \param[in] buffer_size Requested stream buffer size in bytes.
  \param[in] callback #MLAudioBufferCallback function pointer.
  \param[in] callback_context Generic data pointer passed back to callback.
  \param[out] out_handle #MLHandle used in subsequent calls for this stream.
  \param[out] out_error Provides more detail in case of failure.
  \return \c true if stream creation was successful and \c false if it failed.
*/
ML_API bool ML_CALL MLAudioCreateSoundWithOutputStream(const MLAudioBufferFormat *format, uint32_t buffer_size, MLAudioBufferCallback callback, void *callback_context, MLHandle *out_handle, MLAudioError *out_error);

/*!
  \brief Destroy a previously created output stream.
  \param[in] id #MLHandle used to identify the output stream.
  \param[out] out_error Provides more detail in case of failure.
  \return \c true if stream destruction was successful and \c false if it failed.
*/
ML_API bool ML_CALL MLAudioDestroySound(MLHandle handle, MLAudioError *out_error);

/*!
  \brief Start streaming for a previously created output stream.

  From within MLAudioStartSound(), the buffer_callback that was set
  in MLAudioCreateSoundWithOutputStream() will be called anywhere from
  zero to two times, depending on how many stream buffers of audio
  data have been pre-buffered.

  \param[in] id #MLHandle used to identify the output stream.
  \param[out] out_error Provides more detail in case of failure.
  \return \c true if starting was successful and \c false if it failed.
*/
ML_API bool ML_CALL MLAudioStartSound(MLHandle handle, MLAudioError *out_error);

/*!
  \brief Stop streaming for a previously started output stream.
  \param[in] handle #MLHandle used to identify the output stream.
  \param[out] out_error Provides more detail in case of failure.
  \return \c true if stopping was successful and \c false if it failed.
*/
ML_API bool ML_CALL MLAudioStopSound(MLHandle handle, MLAudioError *out_error);

/*!
  \brief Return the preferred (i.e. best performing) settings for streaming.
  \param[in] channel_count Number of audio channels (e.g. 2 for stereo).
  \param[in] samples_per_second Sample rate for the audio stream.
  \param[out] out_format Preferred settings for #MLAudioBufferFormat.
  \param[out] out_recommended_size Recommended size for the streaming buffers.
  \param[out] out_min_size Minimum allowable size for the streaming buffers.
  \param[out] out_error Provides more detail in case of failure.
  \return \c true if call was successful and \c false if it failed.
*/
ML_API bool ML_CALL MLAudioGetOutputStreamDefaults(uint32_t channel_count, uint32_t samples_per_second, MLAudioBufferFormat *out_format, uint32_t *out_recommended_size, uint32_t *out_min_size, MLAudioError *out_error);

/*!
  \brief Return a buffer for writing more stream data.

  This function returns true with a buffer when one of the two
  streaming buffers is empty and needs more data. It is possible
  to use this function in a polling fashion to feed the output stream.
  However it is recommended to use the buffer_callback (set via the
  call to MLAudioCreateSoundWithOutputStream()) for efficiency reasons,
  in which case this function may be called from within the callback.

  \param[in] handle #MLHandle used to identify the output stream.
  \param[out] out_buf #MLAudioBuffer containing buf to write into.
  \param[out] out_error Provides more detail in case of failure.
  \return \c true if buffer is available and \c false if not, or if it failed.
*/
ML_API bool ML_CALL MLAudioGetOutputStreamBuffer(MLHandle handle, MLAudioBuffer *out_buf, MLAudioError *out_error);

/*!
  \brief Release a buffer once it has been filled.

  After receiving an empty buffer from MLAudioGetOutputStreamBuffer(),
  and after filling that buffer with audio data, call this function to
  indicate that the buffer is filled and can now be streamed out.

  \param[in] handle #MLHandle used to identify the output stream.
  \param[out] out_error Provides more detail in case of failure.
  \return \c true if call was successful and \c false if it failed.
*/
ML_API bool ML_CALL MLAudioReleaseOutputStreamBuffer(MLHandle handle, MLAudioError *out_error);

/*
 ********************************************************************
 *
 **************************** AUDIO INPUT ***************************
 *
 ********************************************************************
 */

/*!
  \brief Create a new audio input stream.

  Creates an input stream that streams audio data from the headset mics.
  After creating the stream, it can be started by calling MLAudioStartInput().
  Input streaming uses a double-buffer scheme. To determine the preferred
  buffer format settings, call MLAudioGetInputStreamDefaults() before
  calling this function.

  \param[in] format #MLAudioBufferFormat specifying audio format of stream.
  \param[in] buffer_size Requested stream buffer size in bytes.
  \param[in] callback #MLAudioBufferCallback function pointer.
  \param[in] callback_context Generic data pointer passed back to callback.
  \param[out] out_handle #MLHandle used in subsequent calls for this stream.
  \param[out] out_error Provides more detail in case of failure.
  \return \c true if stream creation was successful and \c false if it failed.
*/
ML_API bool ML_CALL MLAudioCreateInputFromVoiceComm(const MLAudioBufferFormat *format, uint32_t buffer_size, MLAudioBufferCallback callback, void *callback_context, MLHandle *out_handle, MLAudioError *out_error);

/*!
  \brief Destroy a previously created input stream.
  \param[in] handle #MLHandle used to identify the input stream.
  \param[out] out_error Provides more detail in case of failure.
  \return \c true if stream destruction was successful and \c false if it failed.
*/
ML_API bool ML_CALL MLAudioDestroyInput(MLHandle handle, MLAudioError *out_error);

/*!
  \brief Start streaming for a previously created input stream.
  \param[in] handle #MLHandle used to identify the input stream.
  \param[out] out_error Provides more detail in case of failure.
  \return \c true if starting was successful and \c false if it failed.
*/
ML_API bool ML_CALL MLAudioStartInput(MLHandle handle, MLAudioError *out_error);

/*!
  \brief Stop streaming for a previously started input stream.
  \param[in] handle #MLHandle used to identify the input stream.
  \param[out] out_error Provides more detail in case of failure.
  \return \c true if stopping was successful and \c false if it failed.
*/
ML_API bool ML_CALL MLAudioStopInput(MLHandle handle, MLAudioError *out_error);

/*!
  \brief Return the preferred (i.e. best performing) settings for streaming.
  \param[in] channel_count Number of audio channels (e.g. 2 for stereo).
  \param[in] samples_per_second Sample rate for the audio stream.
  \param[out] out_format Preferred settings for #MLAudioBufferFormat.
  \param[out] out_recommended_size Recommended size for the streaming buffers.
  \param[out] out_min_size minimum Allowable size for the streaming buffers.
  \param[out] out_error Provides more detail in case of failure.
  \return \c true if call was successful and \c false if it failed.
*/
ML_API bool ML_CALL MLAudioGetInputStreamDefaults(uint32_t channel_count, uint32_t samples_per_second, MLAudioBufferFormat *out_format, uint32_t *out_recommended_size, uint32_t *out_min_size, MLAudioError *out_error);

/*!
  \brief Return a buffer for reading more stream data.

  This function returns true with a buffer when one of the two
  streaming buffers is full and needs to be read. It is possible
  to use this function in a polling fashion to read the input stream.
  However it is recommended to use the buffer_callback (set via the
  call to MLAudioCreateInputFromVoiceComm()) for efficiency reasons,
  in which case this function may be called from within the callback.

  \param[in] handle #MLHandle used to identify the input stream.
  \param[out] out_buf #MLAudioBuffer containing buf to read from.
  \param[out] out_error Provides more detail in case of failure.
  \return \c true if buffer is available and \c false if not, or if it failed.
*/
ML_API bool ML_CALL MLAudioGetInputStreamBuffer(MLHandle handle, MLAudioBuffer *out_buf, MLAudioError *out_error);

/*!
  \brief Release a buffer once it has been read.

  After receiving a full buffer from MLAudioGetInputStreamBuffer(),
  and after reading the audio data from that buffer, call this function to
  indicate that the buffer has been read and can now be re-used.

  \param[in] handle #MLHandle used to identify the input stream.
  \param[out] out_error Provides more detail in case of failure.
  \return \c true if call was successful and \c false if it failed.
 */
ML_API bool ML_CALL MLAudioReleaseInputStreamBuffer(MLHandle handle, MLAudioError *out_error);

/*! @} */

ML_EXTERN_C_END
