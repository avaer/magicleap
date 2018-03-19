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
  \defgroup MediaPlayer Media Player
  \addtogroup MediaPlayer
  \brief APIs for the Media Player system.

  - The Media Player system is for media playing.
  @{
*/

typedef struct MLMediaCodecBufferInfo {
  size_t   offset;
  size_t   size;
  size_t   flags;
  int64_t  presentation_time_us;
} MLMediaCodecBufferInfo;

typedef enum MLMediaCodecCreation {
  MLMediaCodecCreation_ByName,
  MLMediaCodecCreation_ByType,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaCodecCreation_Ensure32Bits = 0x7FFFFFFF
} MLMediaCodecCreation;

typedef enum MLMediaCodecType {
  MLMediaCodecType_Encoder,
  MLMediaCodecType_Decoder,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaCodecType_Ensure32Bits = 0x7FFFFFFF
} MLMediaCodecType;

/*!
  \brief Indicate the type of data when queuing the input buffer via
  MLMediaCodecQueueInputBuffer() or MLMediaCodecQueueSecureInputBuffer().
*/
typedef enum MLMediaCodecBufferFlag {
  MLMediaCodecBufferFlag_KeyFrame     = 1,
  MLMediaCodecBufferFlag_CodecConfig  = 2,
  MLMediaCodecBufferFlag_EOS          = 4,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaCodecBufferFlag_Ensure32Bits = 0x7FFFFFFF
} MLMediaCodecBufferFlag;

/*!
  \brief Other than the normal buffer index, the output of MLMediaCodecDequeueOutputBuffer()
  can take on one of these statuses.
*/
typedef enum MLMediaCodecOutputBufferStatus {
  MLMediaCodec_OutputBuffersChanged           = -1014,
  MLMediaCodec_FormatChanged                  = -1012,
  MLMediaCodec_TryAgainLater                  = -11,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaCodecOutputBufferStatus_Ensure32Bits = 0x7FFFFFFF
} MLMediaCodecOutputBufferStatus;

#define MAX_CODEC_NAME_SIZE 64

/*!
  \brief Callbacks for notifying client about codec events. If not using the SYNC API
  calls hereunder, client is expected to implement these callbacks and take
  proper actions where appropriate.
*/
typedef struct MLMediaCodecCallbacks {
    /*!
      \brief This callback function is invoked when an input buffer
      becomes available.

      The input_buffer_index contains the index of the available input buffer.
      This should not be set to NULL as codec will not function properly if client has
      no means to specify incoming input buffers.
    */
    void (*on_input_buffer_available)(int input_buffer_index);
    /*!
      \brief This callback function is invoked when an output buffer
      becomes available. The output_buffer_index contains the index
      of the available out buffer. The buffer_info contains
      the buffer info about the available output buffer.

      This should not be set to NULL as codec will not function properly.
      Typical implementation on on_output_buffer_available is simply to
      1) render the buffer to audio subsystem [if codec is audio]
      2) release-and-render-to-surface with MLMediaCodecReleaseOutputBuffer(.., true) [if codec is video].
    */
    void (*on_output_buffer_available)(int output_buffer_index, MLMediaCodecBufferInfo *buffer_info);
    /*!
      \brief This callback function is invoked when the output format has
      changed. The new_output_format contains a handle to the new output format.
      This can be set to NULL if client is not interested in receiving this callback.
    */
    void (*on_output_format_changed)(MLHandle new_output_format);
    /*!
      \brief This callback function is invoked when #MediaCodec encountered
      an error. The error_code contains the error code. This can be set to NULL
      if client is not interested in receiving this callback.
    */
    void (*on_error)(int error_code);
    /*!
      \brief This callback function is invoked when an output frame has
      rendered on the output surface.

      The presentation_time_us contains the presentation time (media time)
      in microseconds of the frame rendered. This is usually the same as specified in
      MLMediaCodecQueueInputBuffer(); however, some codecs may alter the
      media time by applying some time-based transformation, such as frame
      rate conversion. In that case, presentation time corresponds
      to the actual output frame rendered.

      The system_time_nano contains system time when the frame
      was rendered.

      This callback is for informational purposes only: to get precise
      render timing samples, and can be significantly delayed and batched.
      Some frames may have been rendered even if there was no callback
      generated. This can be set to NULL if client is not interested in receiving
      this callback.
    */
    void (*on_frame_rendered)(int64_t presentation_time_us, int64_t system_time_nano);
    /*!
      \brief Callback called when decoded frame is available for consumption on client side.

      #MLHandle media_codec is a #MediaCodec instance for which callback was called
      void * data is some custom data to be returned when callback is fired.

      This is the callback clients should implement when they want to use decoded frame as
      a texture mapped to 3D geometry, for example.

      This callback is typically fired when MLMediaCodecReleaseOutputBuffer(.., true)'s
      rendering operation has not only finished (on_frame_rendered),
      but has reached client-side and is ready to be mapped and rendered from.
    */
    void (*on_frame_available)(MLHandle media_codec, void *data);
    /*!
      \brief Void pointer that is to be returned when #on_frame_available callback if
      fired. This can be NULL is client does not need any particular data returned
      with this callback.
    */
    void *on_frame_available_data;
} MLMediaCodecCallbacks;

/*!
  \brief Create a new #MediaCodec.
  \param[in] method One of the creation methods defined by #MLMediaCodecCreation.
  \param[in] type One of the codec types defined by #MLMediaCodecType.
  \param[in] name_str If creating a codec by name, this is the name of the codec.
             If creating a codec by type, this is the mime type of the codec.
             Refer to APIs in #MediaCodecList for retrieving the list of names
             and mime types of supported codecs.
  \return A handle to the created #MediaCodec. If there is an error during
          creation, it will return #ML_INVALID_HANDLE.
*/
ML_API MLHandle ML_CALL MLMediaCodecCreateCodec(MLMediaCodecCreation method, MLMediaCodecType type, const char *name_str);

/*!
  \brief Destroy a #MediaCodec.
  \param[in] handle #MLHandle to the #MediaCodec.
  \return \c true if #MediaCodec object was successfully destroyed.
*/
ML_API bool ML_CALL MLMediaCodecDestroy(MLHandle handle);

/*!
  \brief Set callbacks to notify client codec events. Client needs to implement the callback functions.
  \param[in] handle #MLHandle to the #MediaCodec.
  \param[in] callbacks Set of codec callbacks. Can be set to NULL to unset all the callback altogether.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaCodecSetCallbacks(MLHandle handle, MLMediaCodecCallbacks *callbacks);

/*!
  \brief Obtain the name of the created codec.

  User shall allocate at least #MAX_CODEC_NAME_SIZE bytes of memory for
  storing the output name string.

  \param[in] handle #MLHandle to the #MediaCodec.
  \param[out] out_name Pointer to the user-maintained buffer for storing
              the output C-style name string.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaCodecGetName(MLHandle handle, char *out_name);

/*!
  \brief Configure the #MediaCodec.
  \param[in] handle #MLHandle to the #MediaCodec.
  \param[in] format_handle #MLHandle to the #MediaFormat object.
  \param[in] crypto_handle #MLHandle to the #MediaCrypto object.
             Pass NULL for clear content.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaCodecConfigure(MLHandle handle, MLHandle format_handle, MLHandle crypto_handle);

/*!
  \brief Start the codec.

  Shall be called upon successful configuration.

  \param[in] handle #MLHandle to the #MediaCodec.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaCodecStart(MLHandle handle);

/*!
  \brief Stop the codec.

  Codec is stopped and not destroyed, therefore can be started again.

  \param[in] handle #MLHandle to the #MediaCodec.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaCodecStop(MLHandle handle);

/*!
  \brief Flush the both the input and output ports of the codec.

  Upon return, all indices previously returned in calls to
  MLMediaCodecDequeueInputBuffer() and MLMediaCodecDequeueOutputBuffer()
  become invalid, and all buffers are owned by the codec.

  \param[in] handle #MLHandle to the #MediaCodec.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaCodecFlush(MLHandle handle);

/*!
  \brief Obtain a writable buffer pointer for a dequeued
  input buffer index to contain the input data.

  After calling this method any buffer pointer previously
  returned for the same input index MUST no longer be used.

  \param[in] handle #MLHandle to the #MediaCodec.
  \param[in] buffer_handle The index of a client-owned input buffer
             previously returned from a call to
             MLMediaCodecDequeueInputBuffer().
  \param[out] out_buffer_ptr Pointer to returned input buffer.
  \param[out] out_buffer_size Size of returned input buffer.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaCodecGetInputBufferPointer(MLHandle handle, MLHandle buffer_handle, uint8_t **out_buffer_ptr, size_t *out_buffer_size);

/*!
  \brief Obtain a read-only buffer pointer for a dequeued output
  buffer index.

  The position and limit of the returned buffer are set to the valid output data.
  After calling this method any buffer pointer previously returned for the same output
  index MUST no longer be used.

  \param[in] handle #MLHandle to the #MediaCodec.
  \param[in] buffer_handle The index of a client-owned output buffer
             previously returned from a call to
             MLMediaCodecDequeueOutputBuffer().
  \param[out] out_buffer_ptr Pointer to returned output buffer.
  \param[out] out_buffer_size Size of returned output buffer.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaCodecGetOutputBufferPointer(MLHandle handle, MLHandle buffer_handle, const uint8_t **out_buffer_ptr, size_t *out_buffer_size);

/*!
  \brief After filling a range of the input buffer at the specified index
  submit it to the component.

  Once an input buffer is queued to the codec, it MUST NOT be used until it is later retrieved by
  MLMediaCodecGetInputBuffer() in response to a MLMediaCodecDequeueInputBuffer() return value.

  \param[in] handle #MLHandle to the #MediaCodec.
  \param[in] buffer_handle Index of a client-owned input buffer previously returned
             in a call to MLMediaCodecDequeueInputBuffer().
  \param[in] offset Byte offset into the input buffer at which the data starts.
  \param[in] size Number of bytes of valid input data.
  \param[in] timeout_us Presentation timestamp in microseconds for this buffer.
             This is normally the media time at which this buffer should
             be presented (rendered).
  \param[in] flags A bitmask of flags defined by #MLMediaCodecBufferFlag.
             While not prohibited, most codecs do not use the
             #MLMediaCodecBufferFlag_KeyFrame flag for input buffers.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaCodecQueueInputBuffer(MLHandle handle, MLHandle buffer_handle, int64_t offset, size_t size, uint64_t time_us, int flags);

/*!
  \brief Similar to queueInputBuffer but submits a buffer that is potentially encrypted.
  \param[in] handle #MLHandle to the #MediaCodec.
  \param[in] buffer_handle Index of a client-owned input buffer previously returned
             in a call to MLMediaCodecDequeueInputBuffer().
  \param[in] offset Byte offset into the input buffer at which the data starts.
  \param[in] crypto_info_handle Metadata required to facilitate decryption,
             the object can be reused immediately after this call returns.
  \param[in] timeout_us Presentation timestamp in microseconds for this
             buffer. This is normally the media time at which this
             buffer should be presented (rendered).
  \param[in] flags A bitmask of flags defined by #MLMediaCodecBufferFlag.
             While not prohibited, most codecs do not use the
             #MLMediaCodecBufferFlag_KeyFrame flag for input buffers.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaCodecQueueSecureInputBuffer(MLHandle handle, MLHandle buffer_handle, int64_t offset, MLHandle crypto_info_handle, uint64_t time_us, int flags);

/*!
  \brief Dequeue an input buffer from buffer queue.

  This method will return immediately if timeoutUs == 0, wait indefinitely
  for the availability of an input buffer if timeoutUs < 0 or wait up
  to "timeoutUs" microseconds if timeoutUs > 0.

  \param[in] handle #MLHandle to the #MediaCodec.
  \param[in] timeout_us Timeout in microseconds.
             Negative timeout indicates "infinite".
  \param[out] out_buffer_handle Index of an Input buffer from buffer queue,
              or #MLMediaCodec_TryAgainLater status.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaCodecDequeueInputBuffer(MLHandle handle, int64_t timeout_us, int64_t *out_buffer_handle);

/*!
  \brief Dequeue an output buffer from buffer queue.

  This method will return immediately if timeoutUs == 0, wait indefinitely
  for the availability of an input buffer if timeoutUs < 0 or wait up
  to "timeoutUs" microseconds if timeoutUs > 0.

  \param[in] handle #MLHandle to the #MediaCodec.
  \param[out] out_buffer_info Will be filled with buffer meta data.
  \param[in] timeout_us Timeout in microseconds.
             Negative timeout indicates "infinite".
  \param[out] out_buffer_handle Index of an output buffer from buffer queue,
              or one of the statuses defined by #MLMediaCodecOutputBufferStatus.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaCodecDequeueOutputBuffer(MLHandle handle, MLMediaCodecBufferInfo *out_buffer_info,int64_t timeout_us, int64_t *out_buffer_handle);

/*!
  \brief Obtain input format supported by the codec.

  Call this function, after successful codec configuration, to determine
  what optional configuration parameters were supported by the codec.

  \param[in] handle #MLHandle to the #MediaCodec.
  \param[out] out_format_handle Input format supported by the codec.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaCodecGetInputFormat(MLHandle handle, MLHandle *out_format_handle);

/*!
  \brief Return output format supported by the codec, or the format to which the configuration has changed.
  \param[in]  handle #MLHandle to the #MediaCodec.
  \param[out] out_format_handle Output format supported by the codec,
              or the format to which the configuration has changed.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaCodecGetOutputFormat(MLHandle handle, MLHandle *out_format_handle);

/*!
  \brief Release buffer to codec or to render it on output surface.

  If codec is configured with an output surface, setting render
  to \c true will send the buffer to that output surface. The surface
  will release the buffer back to the codec once it is no longer
  used/displayed.

  Once an output buffer is released to codec, it MUST NOT
  be used until it is later retrieved by MLMediaCodecGetOutputBuffer()
  in response to a MLMediaCodecDequeueOutputBuffer() return value.

  \param[in] handle #MLHandle to the #MediaCodec object.
  \param[in] buffer_handle Index of a client-owned output buffer previously returned
             from a call to MLMediaCodecDequeueOutputBuffer().
  \param[in] render If a valid surface was specified when configuring the
             codec, passing \c true renders this output buffer to the surface.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaCodecReleaseOutputBuffer(MLHandle handle, MLHandle buffer_handle, bool render);

/*!
  \brief Update surface timestamp and returns it to the codec to render
  it on the output surface. If codec is not configured with output
  surface, this call simply returns the buffer to codec.

  The timestamp may have special meaning depending on the destination
  surface.

  \param[in] handle #MLHandle to the #MediaCodec object.
  \param[in] buffer_handle Index of a client-owned output buffer previously returned
             from a call to MLMediaCodecDequeueOutputBuffer().
  \param[in] timestamp_ns The timestamp in nanoseconds to associate with this buffer when
             it is sent to the Surface.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaCodecReleaseOutputBufferAtTime(MLHandle handle, MLHandle buffer_handle, int64_t timestamp_ns);

/*!
  \brief Consume next available buffer.

  Note: This function is non-blocking and should only be called from the rendering
  thread *after* #MLMediaCodecOnFrameAvailableCallback callback has been fired.

  \param[in] handle #MLHandle to the #MediaCodec instance.
  \param[out] out_native_buffer A pointer to the acquired native buffer of the frame
              When buffer is not required anymore, caller must call
              MLMediaCodecReleaseFrame() with this nativeBuffer handle to free up
              queuing space for incoming buffers.
  \return \c true if a buffer was returned and \c false if no buffer is available.
*/
ML_API bool ML_CALL MLMediaCodecAcquireNextAvailableFrame(MLHandle handle, MLHandle *out_native_buffer);

/*!
  \brief Release a native buffer previously acquired.
  \param[in] handle #MLHandle to the #MediaCodec instance.
  \param[in] native_Buffer The native buffer for the frame to release.
  \return \c true if the buffer was successfully released and \c false if not.
*/
ML_API bool ML_CALL MLMediaCodecReleaseFrame(MLHandle handle, MLHandle native_buffer);

ML_EXTERN_C_END
