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
#include "ml_media_data_source.h"
#include "ml_media_stream_source.h"
#include "ml_types.h"
#include <stddef.h>

ML_EXTERN_C_BEGIN

/*!
  \addtogroup MediaPlayer
  @{
*/

/*! Codes for setting video scaling mode in internal #MediaPlayer. */
typedef enum MLMediaPlayerVideoScalingMode {
  MLMediaPlayerVideoScalingMode_ScaleToFit = 1,
  MLMediaPlayerVideoScalingMode_ScaleToFitWithCropping = 2,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaPlayerVideoScalingMode_Ensure32Bits = 0x7FFFFFFF
} MLMediaPlayerVideoScalingMode;

typedef enum MLMediaPlayerPollingStateFlags {
  MLMediaPlayerPollingStateFlag_IsPlaying            = 1 << 0,
  MLMediaPlayerPollingStateFlag_IsLooping            = 1 << 1,
  MLMediaPlayerPollingStateFlag_IsBufferAvailable    = 1 << 2,
  MLMediaPlayerPollingStateFlag_HasBeenPrepared      = 1 << 3,
  MLMediaPlayerPollingStateFlag_HasPlaybackCompleted = 1 << 4,
  MLMediaPlayerPollingStateFlag_HasSeekCompleted     = 1 << 5,
  MLMediaPlayerPollingStateFlag_HasSizeChanged       = 1 << 6,
  MLMediaPlayerPollingStateFlag_HasBufferingUpdated  = 1 << 7,
  MLMediaPlayerPollingStateFlag_HasReceivedInfo      = 1 << 8,
  MLMediaPlayerPollingStateFlag_HasReceivedError     = 1 << 9,
  MLMediaPlayerPollingStateFlag_HasTimedTextUpdated  = 1 << 10,
  MLMediaPlayerPollingStateFlag_HasSubtitleUpdated   = 1 << 11,
  MLMediaPlayerPollingStateFlag_HasMetadataUpdated   = 1 << 12,
} MLMediaPlayerPollingStateFlags;

/*!
  \brief Generic error codes for the media player framework. Errors are fatal, the
  playback must abort. NOTE: ** this MUST be in sync with its C++ native
  counterpart in MediaPlayerErrors.h. **
*/
typedef enum MLMediaPlayerError {
  MLMediaPlayerError_Generic                        = 1,   /*! Media Player generic errors, see Media_ERROR_ enums. */
  MLMediaPlayerError_ServerDied                     = 100, /*! Media errors (eg. Codec not supported). */
  MLMediaPlayerError_NotValidForProgressivePlayback = 200, /*! Runtime errors. */
  MLMediaPlayerError_Ensure32Bits                   = 0x7FFFFFFF
} MLMediaPlayerError;

/*!
  \brief Info and warning codes for the media player framework. These are non fatal,
  the playback is going on but there might be some user visible issues.

  Info and warning messages are communicated back to the client using the
  #MediaPlayerListener::onInfo method. In this situation,
  this method is invoked with the following:

  'what'  should be a value from the #MediaPlayerInfo.
  'extra' contains an implementation dependent info code to provide
  more details. Should default to 0 when not used.
*/
typedef enum MLMediaPlayerInfo {
  MLMediaPlayerInfo_Unknown           = 1,
  MLMediaPlayerInfo_StartedAsNext     = 2,   /*! The player was started because it was used as
                                                 the next player. */
  MLMediaPlayerInfo_RenderingStart    = 3,   /*! The player just pushed the very first video
                                                 frame for rendering. */
  MLMediaPlayerInfo_Looping           = 4,   /*! The player just reached EOS and started
                                                 from beginning (loop). */
  MLMediaPlayerInfo_VideoTrackLagging = 700, /*! The video is too complex for the decoder:
                                                 it can't decode frames fast enough. */
  MLMediaPlayerInfo_BufferingStart    = 701, /*! Media player is temporarily pausing playback. */
  MLMediaPlayerInfo_BufferingEnd      = 702, /*! Media player is resuming playback after filling buffers. */
  MLMediaPlayerInfo_NetworkBandwidth  = 703, /*! Network bandwidth info. */
  MLMediaPlayerInfo_BadInterleaving   = 800, /*! Bad interleaving means that a media has been
                                                 improperly interleaved. */
  MLMediaPlayerInfo_NotSeekable       = 801, /*! The media is not seekable (e.g live stream). */
  MLMediaPlayerInfo_MetadataUpdate    = 802, /*! New media metadata is available. */
  MLMediaPlayerInfo_TimedTextError    = 900, /*! Media timed text error. */
  MLMediaPlayerInfo_Ensure32Bits      = 0x7FFFFFFF
} MLMediaPlayerInfo;

/*!
  \brief MediaTrack types.
  There are types returned by MLMediaPlayerGetTrackType(...).
*/
typedef enum MLMediaPlayerTrackType {
    MediaPlayerTrackType_Unknown      = 0,
    MediaPlayerTrackType_Video        = 1,
    MediaPlayerTrackType_Audio        = 2,
    MediaPlayerTrackType_TimedText    = 3,
    MediaPlayerTrackType_Subtitle     = 4,
    MediaPlayerTrackType_Metadata     = 5,
    MediaPlayerTrackType_Ensure32Bits = 0x7FFFFFFF
} MLMediaPlayerTrackType;

/*!
  \brief Callbacks for notifying client about #MediaPlayer error events.
  Those are async mechanisms that should not be used in parallel with their
  sync counterpart, i.e. poll-based queries for the same events using
  MLMediaPlayerPollStatespoll().
*/
typedef struct MLMediaPlayerEventCallbacks {
    /*!
      \brief This callback function is invoked when buffered contents percentage changed.
      \param[in] media_player #MLHandle is a #MediaPlayer instance on which callback was set.
      \param[in] percent The new percentage of buffered content.
      \param[in] data User data as passed to MLMediaPlayerSetEventCallbacks().
    */
    void (*on_buffering_update)(MLHandle media_player, int percent, void *data);
    /*!
      \brief This callback function is invoked when media player played back until end of
      media and has now come to a stop.

      Note that this callback does not fire when 'looping = true',
      because #MediaPlayer does not "stop" in that case, but rather
      loops to beginning of media.

      To get notified when EOS is reached (when looping = true),
      set a proper callback function for the below on_info and look for the
      #MEDIA_PLAYER_INFO_LOOPING info code.

      \param[in] media_player #MLHandle is a #MediaPlayer instance on which callback was set.
      \param[in] data User data as passed to MLMediaPlayerSetEventCallbacks().
    */
    void (*on_completion)(MLHandle media_player, void *data);
    /*!
      \brief This callback function is invoked when media player encounters an error.
      \param[in] media_player #MLHandle is a #MediaPlayer instance on which callback was set.
      \param[in] error Type of error.
      \param[in] extra Extra information, #MediaError code or pid if binder died.
      \param[in] data User data as passed to MLMediaPlayerSetEventCallbacks().
    */
    void (*on_error)(MLHandle media_player, MLMediaPlayerError error, int extra, void *data);
    /*!
      \brief This callback function is invoked when #MediaPlayer generates informational events.
      \param[in] media_player #MLHandle is a #MediaPlayer instance on which callback was set.
      \param[in] info Type of informational event.
      \param[in] extra Extra information.
      \param[in] data User data as passed to MLMediaPlayerSetEventCallbacks().
    */
    void (*on_info)(MLHandle media_player, MLMediaPlayerInfo info, int extra, void *data);
    /*!
      \brief This callback function is invoked when the player has finished preparing
      media and is ready to playback.
      \param[in] media_player #MLHandle is a #MediaPlayer instance on which callback was set.
      \param[in] data User data as passed to MLMediaPlayerSetEventCallbacks().
    */
    void (*on_prepared)(MLHandle media_player, void *data);
    /*!
      \brief This callback function is invoked when a seek operation has completed.
      \param[in] media_player #MLHandle is a #MediaPlayer instance on which callback was set.
      \param[in] data User data as passed to MLMediaPlayerSetEventCallbacks().
    */
    void (*on_seek_complete)(MLHandle media_player, void *data);
    /*!
      \brief This callback function is invoked when the internal surface has changed size.
      \param[in] media_player #MLHandle is a #MediaPlayer instance on which callback was set.
      \param[in] width The new surface width.
      \param[in] height The new surface height.
      \param[in] data User data as passed to MLMediaPlayerSetEventCallbacks().
    */
    void (*on_video_size_changed)(MLHandle media_player, int width, int height, void *data);
} MLMediaPlayerEventCallbacks;

/*!
  \brief Callback signature called when decoded frame is available for consumption.
  \param[in] media_player #MLHandle is a #MediaPlayer instance for which callback was called.
  \param[in,out] void * data is some custom data to be returned when callback is fired.
*/
typedef void(*MLMediaPlayerOnFrameAvailableCallback)(MLHandle media_player, void *data);

/*!
  \brief Create a new #MediaPlayer object.
  \return A handle to the created #MediaPlayer. If there is an error during
          creation, it will return #ML_INVALID_HANDLE.
*/
ML_API MLHandle ML_CALL MLMediaPlayerCreate();

/*!
  \brief Destroy a MediaPlayer object.
  \param[in] handle #MLHandle to the #MediaPlayer object to destroy.
  \return \c true if #MediaPlayer object was successfully destroyed.
*/
ML_API bool ML_CALL MLMediaPlayerDestroy(MLHandle media_player);

/*!
  \brief Translate a media player error code into a human-readable string.
  \param[in] code Error code to translate to a string.
  \param[in] extra Extra error code needed for translation.
  \param[out] out_string Pointer to C-style error string. Note that user should
              not keep a reference to the returned char pointer for future
              use as subsequent calls to MLMediaPlayerErrorGetString() will
              overwrite its content. Consequently, user *must not* explicitly
              free the returned out_string memory.
  \return \c true if code could successfully get translated into a string.
*/
bool ML_CALL MLMediaPlayerErrorGetString(int32_t code, int32_t extra, char **out_string);

/*!
  \brief Set a file descriptor as the data source.

  The file descriptor must be seekable. It is the caller's responsibility to
  close the file descriptor. It is safe to do so as soon as this call returns.

  \param[in] handle #MLHandle to the #MediaPlayer instance.
  \param[in] fd The file descriptor for the file you want to play.
  \return \c true if operation succeeded and \c false if fd is not a valid file descriptor.
*/
ML_API bool ML_CALL MLMediaPlayerSetDataSourceForFD(MLHandle media_player, int32_t fd);

/*!
  \brief Set a file descriptor as the data source with offset.

  The file descriptor must be seekable. It is the caller's responsibility to
  close the file descriptor. It is safe to do so as soon as this call returns.
  This API is useful for specifying playable media located in resource files.

  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[in] fd The file descriptor for the file you want to play.
  \param[in] offset The offset (in bytes) of the source's start.
  \param[in] length The number of bytes of media to load after offset.
  \return \c true if operation succeeded and \c false if fd is not a valid file descriptor.
*/
ML_API bool ML_CALL MLMediaPlayerSetOffsetDataSourceForFD(MLHandle media_player, int32_t fd, int64_t offset, int64_t length);

/*!
  \brief Set a local file path as the data source.

  The path should be an absolute path and should reference a world-readable
  file.

  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[in] path The linux-style path of the file.
  \return \c true if DataSource path was correctly added, \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerSetDataSourceForPath(MLHandle media_player, const char *path);

/*!
  \brief Set a Uri string as the data source.
  \param[in] uri The C-style string representing the URI complete string.
  \return \c true if DataSource path was correctly added, \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerSetDataSourceForURI(MLHandle media_player, const char *uri);

/*!
  \brief Set a Url string as the remote data source.
  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[in] uri The C-style string representing the complete URL.
  \param[in] headers Array of char * headers to be sent.
  \param[in] len Number of headers passed-in.
  \return \c true if DataSource path was correctly added, \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerSetRemoteDataSourceForURI(MLHandle media_player, const char *uri, char **headers, size_t len);

/*!
  \brief Set the data source to use.
  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[in] media_data_source #MLHandle returned by MLMediaDataSourceCreate().
  \return \c true if #DataSource was correctly added, \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerSetMediaDataSource(MLHandle media_player, MLHandle media_data_source);

/*!
  \brief Set the data source to use.
  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[in] media_stream_source #MLHandle returned by MLMediaStreamSourceCreate().
  \return \c true if #DataSource was correctly added, \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerSetMediaStreamSource(MLHandle media_player, MLHandle media_stream_source);

/*!
  \brief Add a timedtext source from a URL.
  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[in] uri The C-style string representing the complete URL.
  \param[in] mimeType The MIME type of the file.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerAddTimedTextSourceForURI(MLHandle media_player, const char *uri, const char *mimeType);

/*!
  \brief Add a timedtext source from a file descriptor.

  The file descriptor must be seekable. It is the caller's responsibility to
  close the file descriptor. It is safe to do so as soon as this call returns.

  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[in] fd The file descriptor for the timed text source.
  \param[in] offset The offset (in bytes) of the source's start.
  \param[in] length The number of bytes of media to load after offset.
  \param[in] mimeType The MIME type of the file.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerAddTimedTextSourceForFD(MLHandle media_player, int32_t fd, int64_t offset, int64_t length, const char *mimeType);

/*!
  \brief Set the 'next' #MediaPlayer to automatically 'start'
  when current #MediaPlayer playback completes.
  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[in] nextHandle #MLHandle of an already created #MediaPlayer instance.
  \return \c true if next #MediaPlayer was correctly registered internally.
*/
ML_API bool ML_CALL MLMediaPlayerSetNextPlayer(MLHandle media_player, MLHandle next_media_player);

/*!
  \brief Count the number of tracks found in the data source.
  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[out] out_track_count A pointer to the number of tracks found in the player source.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerGetTrackCount(MLHandle media_player, uint32_t *out_track_count);

/*!
  \brief Get the type of a track.
  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[in] track The track number.
  \param[out] out_track_type A pointer to the type of the track of type #MLMediaPlayerTrackType.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerGetTrackType(MLHandle media_player, uint32_t track, MLMediaPlayerTrackType *out_track_type);

/*!
  \brief Get the language of a track.
  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[in] track The track number.
  \param[out] out_track_language A pointer to the language of the track.
              Free it when you no longer need it.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerGetTrackLanguage(MLHandle media_player, uint32_t track, char **out_track_language);

/*!
  \brief Select a track.
  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[in] track The track number.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerSelectTrack(MLHandle media_player, uint32_t track);

/*!
  \brief Prepare the player for playback, synchronously.

  After setting the data source and the #GraphicBufferProducer, you need to
  either call prepare() or prepareAsync(). For files, it is OK to call
  prepare(), which blocks until #MediaPlayer is ready for playback.

  \param[in] media_player #MLHandle to the #MediaPlayer instance.
             To 'remove' the next player, set handle = 0.
  \return \c true if media preparation was successful and \c false if it failed for any reason.
*/
ML_API bool ML_CALL MLMediaPlayerPrepare(MLHandle media_player);

/*!
  \brief Prepare the player for playback, asynchronously.

  After setting the data's source and the #GraphicBufferProducer, you need to
  either call prepare() or prepareAsync(). For streams, you should call
  prepareAsync(), which returns immediately, rather than blocking until
  enough data has been buffered. Prepared state will then be polled by
  MLMediaPlayerPollIsPrepared().

  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \return \c true if media preparation was successful and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerPrepareAsync(MLHandle media_player);

/*!
  \brief Start or resumes playback.

  If playback had previously been paused, playback will continue from where
  it was paused. If playback had been stopped, or never started before,
  playback will start at the beginning.

  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \return \c true if internal video sink startup was successful and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerStart(MLHandle media_player);

/*!
  \brief Stop playback after playback has been stopped or paused.

  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \return \c true if the call succeeded and \c false if it failed because
          it was in any other state than #MEDIA_PLAYER_STARTED, #MEDIA_PLAYER_PREPARED,
          #MEDIA_PLAYER_PAUSED or #MEDIA_PLAYER_PLAYBACK_COMPLETE.
*/
ML_API bool ML_CALL MLMediaPlayerStop(MLHandle media_player);

/*!
  \brief Pause playback.

  Calling pause() is a NOOP if #MediaPlayer is in state #MEDIA_PLAYER_PAUSED
  or #MEDIA_PLAYER_PLAYBACK_COMPLETE.

  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerPause(MLHandle media_player);

/*!
  \brief Reset the #MediaPlayer to its uninitialized state.

  After calling this method, you will have to initialize it again by setting the
  data source and calling prepare().

  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerReset(MLHandle media_player);

/*!
  \brief Seek to specified time position.
  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[in] msec The offset in milliseconds from the start, to seek to
  \return \c true if seek operation succeeded and \c false if it failed because
          it is not in either #MEDIA_PLAYER_STARTED, #MEDIA_PLAYER_PREPARED,
          #MEDIA_PLAYER_PAUSED or #MEDIA_PLAYER_PLAYBACK_COMPLETE modes.
*/
ML_API bool ML_CALL MLMediaPlayerSeekTo(MLHandle media_player, int msec);

/*!
  \brief Set callback to get notified when a decoded frame is available.

  When on_buffer_available() function gets called because there is a
  buffer available for consumption, one should immediately call
  MLMediaPlayerAcquireNextAvailableBuffer(...) to get the buffer and
  render from it.

  Setting this callback does not prevent caller from using the the poll-based
  buffer interrogation API (MLMediaPlayerPollStates() with the
  #MLMediaPlayerPollingState_IsBufferAvailable flag).

  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[in] on_buffer_available Function pointer to be called.
            This can be 'NULL' to unset the callback. See MLMediaPlayerOnFrameAvailable().
            Callback typedef declaration and comments for explanation on expected callback parameters.
  \param[in] data Custom data to be returned when callback is fired.
  \return \c true if callback has been successfully set and \c false if not.
*/
ML_API bool ML_CALL MLMediaPlayerSetOnBufferAvailableCallback(MLHandle media_player, MLMediaPlayerOnFrameAvailableCallback on_buffer_available, void *data);

/*!
  \brief Consume next available buffer.

  Note: This function is non-blocking and should only be called after
  MLMediaPlayerPollStates() with #MLMediaPlayerPollingState_IsBufferAvailable
  mask returned \c true.

  Note: The returned buffer's color format is multi-planar YUV420. Since our
  underlying hardware interops do not support multiplanar formats, advanced
  texture features like mipmaping, anisotropic filtering and MSAA will *not*
  work on those returned buffers. If such advanced texturing features are
  required, one has to acquire the YUV buffers as usual and *render* to an
  RGB texture and only then, will one be able to enable hardware optimization
  for such advanced texture features.

  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[out] out_native_buffer A pointer to the acquired android native buffer
              When buffer is not required anymore, caller must call
              MLMediaPlayerReleaseBuffer() with this nativeBuffer handle to free up
              queuing space for upcoming buffers.
  \return \c true if a buffer was returned and \c false if no buffer is available.
*/
ML_API bool ML_CALL MLMediaPlayerAcquireNextAvailableBuffer(MLHandle media_player, uint64_t *out_native_buffer);

/*!
  \brief Release a native buffer previously acquired.
  \param[in] media_player MLHandle to the MediaPlayer instance.
  \param[in] nativeBuffer The android native buffer to release.
  \return \c true if the buffer was successfully released and \c false if not.
*/
ML_API bool ML_CALL MLMediaPlayerReleaseBuffer(MLHandle media_player, uint64_t native_buffer);

/*!
  \brief Set callbacks to notify clients about player events.

  Client needs to implement the callback functions declared in
  #MLMediaPlayerEventCallbacks, but can set to NULL the ones he does not
  care about.

  \param[in] handle #MLHandle to the #MediaCodec.
  \param[in] callbacks Set of event callbacks. Can be set to NULL to unset
             the callbacks altogether.
  \param[in] data custom data to be returned when any callback is fired.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerSetEventCallbacks(MLHandle media_player, MLMediaPlayerEventCallbacks *callbacks, void *data);

/*!
  \brief Return the size of the video frame.
  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[out] out_width A pointer to the returned video width.
  \param[out] out_height A pointer to the returned video height.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerGetVideoSize(MLHandle media_player, int32_t *out_width, int32_t *out_height);

/*!
  \brief Return current position of playback.
  \param[out] out_msec A pointer to the returned position in milliseconds.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerGetCurrentPosition(MLHandle media_player, int32_t *out_msec);

/*!
  \brief Return media duration.
  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[out] out_msec A pointer to the returned duration in milliseconds.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerGetDuration(MLHandle media_player, int32_t *out_msec);

/*!
  \brief Return current buffering percentage.
  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[out] out_percentage A pointer to the returned buffering percentage in the range [0, 100].
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerGetBufferingUpdate(MLHandle media_player, int32_t *out_percentage);

/*!
  \brief Return last info received by internal #MediaPlayer.
  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[out] out_code A pointer to the main info code.
  \param[out] out_extra A pointer to the secondary code/data.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerGetInfo(MLHandle media_player, int32_t *out_code, int32_t *out_extra);

/*!
  \brief Return last error received by internal #MediaPlayer.
  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[out] out_code A pointer to the main error code.
  \param[out] out_extra A pointer to the secondary code/data.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerGetError(MLHandle media_player, int32_t *out_code, int32_t *out_extra);

/*!
  \brief Return last timed text event information.
  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[out] out_text A pointer to the text of the timed text event.
  \param[out] out_start A pointer to the start time.
  \param[out] out_end A pointer to the end time.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerGetTimedText(MLHandle media_player, const char **out_text, int32_t *out_start, int32_t *out_end);

/*!
  \brief Return last subtitle event information.
  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[out] out_track A pointer to the track of the subtitle event.
  \param[out] out_time A pointer to the start time.
  \param[out] out_duration A pointer to the duration of the event.
  \param[out] out_buffer A pointer to the event buffer. The returned buffer
              is only valid until the next metadata event arrives, so make a copy if you
              need to use the buffer later.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerGetSubtitle(MLHandle media_player, int32_t *out_track, int64_t *out_time, int64_t *out_duration, uint8_t **out_buffer);

/*!
  \brief Return last metadata event information.
  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[out] out_time A pointer to the event time.
  \param[out] out_size A pointer to the event buffer size.
  \param[out] out_buffer A pointer to the event buffer.
              The returned buffer is only valid until the next metadata event arrives,
              so make a copy if you need to use the buffer later.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerGetMetadata(MLHandle media_player, int64_t *out_time, int32_t *out_size, uint8_t **out_buffer);

/*!
  \brief Set video scaling mode.
  \param[in] media_player MLHandle to the MediaPlayer instance
  \param[in] mode The video scaling mode to set.
             For a list of valid values, see #media_video_scaling_mode_type declaration.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerSetVideoScalingMode(MLHandle media_player, MLMediaPlayerVideoScalingMode mode);

/*!
  \brief Set the looping mode of the player.
  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[in] loop The looping mode.
             \c true if player should loop to beginning of #MediaPlayer when EOS reached.
             \c false if #MediaPlayer should simply stop playback at end of media.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerSetLooping(MLHandle media_player, bool loop);

/*!
  \brief Set the volume on this player.
  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[in] volume The new volume in the [0.0, 1.0] range.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaPlayerSetVolume(MLHandle media_player, float volume);

/*!
  \brief Get the handle of the audio stream.
  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \return A handle to the audio stream. If there is an error, it will return #ML_INVALID_HANDLE.
*/
ML_API MLHandle ML_CALL MLMediaPlayerGetAudioHandle(MLHandle media_player);

/*!
  \brief Poll the desired states from internal #MediaPlayer.

  Desired states have to be selected by passing a bitwise OR'ed mask of
  #MLMediaPlayerPollingStateFlags flags.

  The "is_XXX"  states can be polled multiples times and the return value will
  be the same if internal state hasn't changed since last call.

  When polling the "has_XXX" states however, internal state is set to \c false,
  since they mean : has <state> happened/changed since I last polled <state>

  Two-step state polling : The following states, when returning '1', indicate
                           there is some data ready to be retrieved, by calling
                           a getter function, as explained below :

  For '#MLMediaPlayerPollingState_IsBufferAvailable',
  call MLMediaPlayerAcquireNextAvailableBuffer() to get new buffer handle.

  For '#MLMediaPlayerPollingState_HasSizeChanged',
  call MLMediaPlayerGetVideoSize() to get the new size.

  For '#MLMediaPlayerPollingState_HasBufferingUpdated',
  call MLMediaPlayerGetBufferingUpdate() to get buffering progress value.

  For '#MLMediaPlayerPollingState_HasReceivedInfo,
  call MLMediaPlayerGetError() to get last info code and data.

  For '#MLMediaPlayerPollingState_HasReceivedError,
  call MLMediaPlayerGetError() to get last error code and data.

  Note: This API can still be used even if an #OnBufferAvailable callback has
  been set using MLMediaPlayerSetOnBufferAvailableCallback() method.

  \param[in] media_player #MLHandle to the #MediaPlayer instance.
  \param[in] mask Selection mask for picking which states to retrieve.
  \return Bitwise OR'ed integer of all the chosen bits from mask,
          and in the range [0 = false : 1 = true].
*/
ML_API uint16_t ML_CALL MLMediaPlayerPollStates(MLHandle media_player, uint16_t mask);

/*! @} */

ML_EXTERN_C_END
