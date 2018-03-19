// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
//
// Copyright (c) 2017 Magic Leap, Inc. (COMPANY) All Rights Reserved.
// Magic Leap, Inc. Confidential and Proprietary
//
// NOTICE:  All information contained herein is, and remains the property
// of COMPANY. The intellectual and technical concepts contained herein
// are proprietary to COMPANY and may be covered by U.S. and Foreign
// Patents, patents in process, and are protected by trade secret or
// copyright law.  Dissemination of this information or reproduction of
// this material is strictly forbidden unless prior written permission is
// obtained from COMPANY.  Access to the source code contained herein is
// hereby forbidden to anyone except current COMPANY employees, managers
// or contractors who have executed Confidentiality and Non-disclosure
// agreements explicitly covering such access.
//
// The copyright notice above does not evidence any actual or intended
// publication or disclosure  of  this source code, which includes
// information that is confidential and/or proprietary, and is a trade
// secret, of  COMPANY.   ANY REPRODUCTION, MODIFICATION, DISTRIBUTION,
// PUBLIC  PERFORMANCE, OR PUBLIC DISPLAY OF OR THROUGH USE  OF THIS
// SOURCE CODE  WITHOUT THE EXPRESS WRITTEN CONSENT OF COMPANY IS
// STRICTLY PROHIBITED, AND IN VIOLATION OF APPLICABLE LAWS AND
// INTERNATIONAL TREATIES.  THE RECEIPT OR POSSESSION OF  THIS SOURCE
// CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS
// TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE,
// USE, OR SELL ANYTHING THAT IT  MAY DESCRIBE, IN WHOLE OR IN PART.
//
// %COPYRIGHT_END%
// ---------------------------------------------------------------------
// %BANNER_END%

#pragma once

#include "ml_api.h"

ML_EXTERN_C_BEGIN

/*!
 \brief MusicService errors
*/
typedef enum MLMusicServiceError {
  MLMusicServiceError_None = 0,
  MLMusicServiceError_Connectivity,
  MLMusicServiceError_Timeout,
  MLMusicServiceError_GeneralPlayback,
  MLMusicServiceError_Privilege,
  MLMusicServiceError_ServiceSpecific,
  MLMusicServiceError_NoMemory,
  MLMusicServiceError_Unspecified,
  /*! Ensure enum is represented as 32 bits. */
  MLMusicServiceError_Ensure32Bits = 0x7FFFFFFF
} MLMusicServiceError;

/*!
 \brief MusicService info
*/
typedef enum MLMusicServiceStatus {
  MLMusicServiceStatus_ContextChanged = 0,
  MLMusicServiceStatus_Created,
  MLMusicServiceStatus_LoggedIn,
  MLMusicServiceStatus_LoggedOut,
  MLMusicServiceStatus_NextTrack,
  MLMusicServiceStatus_PrevTrack,
  MLMusicServiceStatus_TrackChanged,
  MLMusicServiceStatus_Unknown,
  /*! Ensure enum is represented as 32 bits. */
  MLMusicServiceStatus_Ensure32Bits = 0x7FFFFFFF
} MLMusicServiceStatus;

/*!
 \brief MusicService playback options
*/
typedef enum MLMusicServicePlaybackOption {
  MLMusicServicePlaybackOptions_Playback = 0,
  MLMusicServicePlaybackOptions_Repeat,
  MLMusicServicePlaybackOptions_Shuffle,
  MLMusicServicePlaybackOptions_Unknown,
  /*! Ensure enum is represented as 32 bits. */
  MLMusicServicePlaybackOptions_Ensure32Bits = 0x7FFFFFFF
} MLMusicServicePlaybackOptions;

/*!
 \brief Enumerations for MusicService playback state
*/
typedef enum MLMusicServicePlaybackState {
  MLMusicServicePlaybackState_Playing = 0,
  MLMusicServicePlaybackState_Paused,
  MLMusicServicePlaybackState_Stopped,
  MLMusicServicePlaybackState_Error,
  MLMusicServicePlaybackState_Unknown,
  /*! Ensure enum is represented as 32 bits. */
  MLMusicServicePlaybackState_Ensure32Bits = 0x7FFFFFFF
} MLMusicServicePlaybackState;

/*!
 \brief Enumerations for MusicService repeat setting
*/
typedef enum MLMusicServiceRepeatState {
  MLMusicServiceRepeatState_Off = 0,
  MLMusicServiceRepeatState_Song,
  MLMusicServiceRepeatState_Album,
  MLMusicServiceRepeatState_Unknown,
  /*! Ensure enum is represented as 32 bits. */
  MLMusicServiceRepeatState_Ensure32Bits = 0x7FFFFFFF
} MLMusicServiceRepeatState;

/*!
 \brief Enumerations for MusicService shuffle setting
*/
typedef enum MLMusicServiceShuffleState {
  MLMusicServiceShuffleState_On = 0,
  MLMusicServiceShuffleState_Off,
  MLMusicServiceShuffleState_Unknown,
  /*! Ensure enum is represented as 32 bits. */
  MLMusicServiceShuffleState_Ensure32Bits = 0x7FFFFFFF
} MLMusicServiceShuffleState;

/*!
 \brief Metadata
*/
typedef struct MLMusicServiceMetadata {
  const char *album_title;
  const char *album_info_name;
  const char *album_info_url;
  const char *album_info_cover_url;
  const char *artist_info_name;
  const char *artist_info_url;
  uint32_t   length;
  uint32_t   position;
} MLMusicServiceMetadata;

/*!
 \brief Callbacks to be implemented by client to receive information from
        MusicService if callback mechanism is used. Note that the data passed
        into callbacks is destroyed upon return.
*/
typedef struct MLMusicServiceCallbacks {
  void (*on_playback_state_change)(MLMusicServicePlaybackState state, void *data);
  void (*on_repeat_state_change)(MLMusicServiceRepeatState state, void *data);
  void (*on_shuffle_state_change)(MLMusicServiceShuffleState state, void *data);
  void (*on_metadata_change)(const MLMusicServiceMetadata *metadata, void *data);
  void (*on_position_change)(int32_t position, void *data);
  void (*on_error)(MLMusicServiceError error_type, int32_t error_code, void *data);
  void (*on_status_change)(MLMusicServiceStatus status, void *data);
} MLMusicServiceCallbacks;

/*! \brief Connects to MusicService
 *
 *  \param[in] name Name of the MusicService provider
 *  \return true if operation succeeded and false otherwise.
 */
ML_API bool ML_CALL MLMusicServiceConnect(const char *name);

/*! \brief Disconnects from MusicService
 *
 *  \return true if operation succeeded and false otherwise.
 */
ML_API bool ML_CALL MLMusicServiceDisconnect();

/*! \brief Sets the client-implemented callbacks to receive information from MusicService.
 *         Client needs to implement the callbacks defined by MLMusicServiceCallbacks.
 *         The library passes the MusicService info to the client via those callbacks.
 *
 *  \param[in] callbacks Client-implemented callbacks.
 *  \param[in] data User metadata.
 *  \return true if operation succeeded and false otherwise.
 */
ML_API bool ML_CALL MLMusicServiceSetCallbacks(MLMusicServiceCallbacks *callbacks, void *data);

/*! \brief Sets the authentication string on the MusicService
 *
 *  \param[in]  auth_string The authentication string
 *  \return true if operation succeeded and false otherwise.
 */
ML_API bool ML_CALL MLMusicServiceSetAuthString(const char *auth_string);

/*! \brief Sets a specified URL
 *
 *  \param[in]  url The URL to play
 *  \return true if operation succeeded and false otherwise.
 */
ML_API bool ML_CALL MLMusicServiceSetURL(const char *url);

/*! \brief Sets the the playlist on the MusicService
 *
 *  \param[in]  play_list List of URLs to play
 *  \param[in]  size Number of URLs in the list
 *  \return true if operation succeeded and false otherwise.
 */
ML_API bool ML_CALL MLMusicServiceSetPlayList(const char **play_list, uint64_t size);

/*! \brief Starts playing the current track
 *
 *  \return true if operation succeeded and false otherwise.
 */
ML_API bool ML_CALL MLMusicServiceStart();

/*! \brief Stops playing the current track
 *
 *  \return true if operation succeeded and false otherwise.
 */
ML_API bool ML_CALL MLMusicServiceStop();

/*! \brief Pauses the current track
 *
 *  \return true if operation succeeded and false otherwise.
 */
ML_API bool ML_CALL MLMusicServicePause();

/*! \brief Resumes playing the current track
 *
 *  \return true if operation succeeded and false otherwise.
 */
ML_API bool ML_CALL MLMusicServiceResume();

/*! \brief Seeks to the desired position
 *
 *  \param[in]  position The position(in milliseconds) to seek to
 *  \return true if operation succeeded and false otherwise.
 */
ML_API bool ML_CALL MLMusicServiceSeek(uint32_t position);

/*! \brief Advances to the next track in the playlist
 *
 *  \return true if operation succeeded and false otherwise.
 */
ML_API bool ML_CALL MLMusicServiceNext();

/*! \brief Rewinds to the previous track in the playlist
 *
 *  \return true if operation succeeded and false otherwise.
 */
ML_API bool ML_CALL MLMusicServicePrevious();

/*! \brief Sets the shuffle mode
 *
 *  \param[in]  mode Shuffle mode On/Off switch
 *  \return true if operation succeeded and false otherwise.
 */
ML_API bool ML_CALL MLMusicServiceSetShuffle(MLMusicServiceShuffleState mode);

/*! \brief Sets the repeat mode.
 *
 *  \param[in]  mode Repeat mode options
 *  \return true if operation succeeded and false otherwise.
 */
ML_API bool ML_CALL MLMusicServiceSetRepeat(MLMusicServiceRepeatState mode);

/*! \brief Sets the volume
 *
 *  \param[in]  volume The new volume in the [0.0, 1.0] range.
 *  \return true if operation succeeded and false otherwise.
 */
ML_API bool ML_CALL MLMusicServiceSetVolume(float volume);

/*! \brief Obtains the length of the current track
 *
 *  \param[out] out_length Length of the track in seconds
 *  \return true if operation succeeded and false otherwise.
 */
ML_API bool ML_CALL MLMusicServiceGetTrackLength(uint32_t *out_length);

/*! \brief Obtains the position of the current track
 *
 *  \param[out] out_position Position in milliseconds
 *  \return true if operation succeeded and false otherwise.
 */

ML_API bool ML_CALL MLMusicServiceGetCurrentPosition(uint32_t *out_position);

/*! \brief Obtains the MusicService status
 *
 *  \param[out] out_status MusicService status
 *  \return true if operation succeeded and false otherwise.
 */
ML_API bool ML_CALL MLMusicServiceGetStatus(MLMusicServiceStatus *out_status);

/*! \brief Obtains the error from MusicService
 *
 *  \param[out] out_type Error type
 *  \param[out] out_code Error code.
 *              For error types other than MLMusicServiceError_ServiceSpecific,
 *              the value of out_code uses the same enumeration as out_type.
 *              For MLMusicServiceError_ServiceSpecific, the out_code is known only
 *              between the music streaming service and the application, therefore
 *              the values are not documented in this file.
 *
 *  \return true if operation succeeded and false otherwise.
 */
ML_API bool ML_CALL MLMusicServiceGetError(MLMusicServiceError *out_type, int32_t *out_code);

/*! \brief Polls the state of playback from MusicService
 *
 *  \param[out] out_state Playback state
 *  \return true if operation succeeded and false otherwise.
 */
ML_API bool ML_CALL MLMusicServiceGetPlaybackState(MLMusicServicePlaybackState *out_state);

/*! \brief Polls the state of repeat setting from MusicService
 *
 *  \param[out] out_state Repeat setting
 *  \return true if operation succeeded and false otherwise.
 */
ML_API bool ML_CALL MLMusicServiceGetRepeatState(MLMusicServiceRepeatState *out_state);

/*! \brief Polls the state of shuffle setting from MusicService
 *
 *  \param[out] out_state shuffle setting
 *  \return true if operation succeeded and false otherwise.
 */
ML_API bool ML_CALL MLMusicServiceGetShuffleState(MLMusicServiceShuffleState *out_state);

/*! \brief Polls the metadata from MusicService for the current track
 *
 *         The library maintains the lifetime of the data. Call MLMusicServiceReleaseMetadata
 *         to release them.
 *
 *  \param[out] out_metadata Metadata received
 *  \return true if operation succeeded and false otherwise.
 */
ML_API bool ML_CALL MLMusicServiceGetMetadata(MLMusicServiceMetadata *out_metadata);

/*! \brief Releases the metadata
 *
 *  \param[in] metadata Metadata obtained by MLMusicServiceGetMetadata
 *  \return true if operation succeeded and false otherwise.
 */
ML_API bool ML_CALL MLMusicServiceReleaseMetadata(MLMusicServiceMetadata *metadata);

ML_EXTERN_C_END
