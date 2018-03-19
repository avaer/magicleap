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
  \addtogroup MediaPlayer
  @{
*/

#define MAX_FORMAT_STRING_SIZE 512
#define MAX_KEY_STRING_SIZE    64

typedef enum MLMediaFormatType {
  MLMediaFormatType_Video,
  MLMediaFormatType_Audio,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaFormatType_Ensure32Bits = 0x7FFFFFFF
} MLMediaFormatType;

typedef const char *MLMediaFormatKey;

/*!
  \brief The format of media data (video/audio) is specified as key/value pairs.
  Below is a list of keys used to set/obtain format values.
*/
extern MLMediaFormatKey MLMediaFormat_Key_AAC_Encoded_Target_Level;
extern MLMediaFormatKey MLMediaFormat_Key_AAC_DRC_Boost_Factor;
extern MLMediaFormatKey MLMediaFormat_Key_AAC_DRC_Attenuation_Factor;
extern MLMediaFormatKey MLMediaFormat_Key_AAC_DRC_Heavy_Compression;
extern MLMediaFormatKey MLMediaFormat_Key_AAC_DRC_Target_Reference_Level;
extern MLMediaFormatKey MLMediaFormat_Key_AAC_Max_Output_Channel_Count;
extern MLMediaFormatKey MLMediaFormat_Key_AAC_Profile;
extern MLMediaFormatKey MLMediaFormat_Key_AAC_SBR_Mode;
extern MLMediaFormatKey MLMediaFormat_Key_Bit_Rate;
extern MLMediaFormatKey MLMediaFormat_Key_Capture_Rate;
extern MLMediaFormatKey MLMediaFormat_Key_Channel_Count;
extern MLMediaFormatKey MLMediaFormat_Key_Channel_Mask;
extern MLMediaFormatKey MLMediaFormat_Key_Color_Format;
extern MLMediaFormatKey MLMediaFormat_Key_Duration;
extern MLMediaFormatKey MLMediaFormat_Key_FLAC_Compression_Level;
extern MLMediaFormatKey MLMediaFormat_Key_Frame_Rate;
extern MLMediaFormatKey MLMediaFormat_Key_Height;
extern MLMediaFormatKey MLMediaFormat_Key_I_Frame_Interval;
extern MLMediaFormatKey MLMediaFormat_Key_Intra_Refresh_Period;
extern MLMediaFormatKey MLMediaFormat_Key_Is_ADTS;
extern MLMediaFormatKey MLMediaFormat_Key_Is_Autoselect;
extern MLMediaFormatKey MLMediaFormat_Key_Is_Default;
extern MLMediaFormatKey MLMediaFormat_Key_Is_Forced_Subtitle;
extern MLMediaFormatKey MLMediaFormat_Key_Language;
extern MLMediaFormatKey MLMediaFormat_Key_Max_Height;
extern MLMediaFormatKey MLMediaFormat_Key_Max_Input_Size;
extern MLMediaFormatKey MLMediaFormat_Key_Max_Width;
extern MLMediaFormatKey MLMediaFormat_Key_Mime;
extern MLMediaFormatKey MLMediaFormat_Key_PCM_Encoding;
extern MLMediaFormatKey MLMediaFormat_Key_Push_Blank_Buffers_On_Stop;
extern MLMediaFormatKey MLMediaFormat_Key_Repeat_Previous_Frame_After;
extern MLMediaFormatKey MLMediaFormat_Key_Sample_Rate;
extern MLMediaFormatKey MLMediaFormat_Key_Stride;
extern MLMediaFormatKey MLMediaFormat_Key_Temporal_Layering;
extern MLMediaFormatKey MLMediaFormat_Key_Width;
extern MLMediaFormatKey MLMediaFormat_Key_Crop_Left;
extern MLMediaFormatKey MLMediaFormat_Key_Crop_Right;
extern MLMediaFormatKey MLMediaFormat_Key_Crop_Bottom;
extern MLMediaFormatKey MLMediaFormat_Key_Crop_Top;

/*!
  \brief Create a video format object.
  \param[in] mime_type Mime type of the content.
  \param[in] width Width of the content in pixels.
  \param[in] height Height of the content in pixels.
  \return A handle to the created video format object.
          If there is an error during creation, it will
          return #ML_INVALID_HANDLE.
*/
ML_API MLHandle ML_CALL MLMediaFormatCreateVideo(const char *mime_type, int width, int height);

/*!
  \brief Create a audio format object.
  \param[in] mime_type Mime type of the content.
  \param[in] sample_rate Sample rate of the content.
  \param[in] channel_count Number of audio channels.
  \return A handle to the created audio format object.
          If there is an error during creation, it will
          return #ML_INVALID_HANDLE.
*/
ML_API MLHandle ML_CALL MLMediaFormatCreateAudio(const char *mime_type, int sample_rate, int channel_count);

/*!
  \brief Create a subtitle format object.
  \param[in] mime_type Mime type of the content.
  \param[in] language Language of the content, using either ISO 639-1 or
             639-2/T codes. Specify null or "und" if language information
             is only included in the content. (This will also work if there
             are multiple language tracks in the content.)
  \return A handle to the created subtitle format object.
          If there is an error during creation, it will
          return #ML_INVALID_HANDLE.
*/
ML_API MLHandle ML_CALL MLMediaFormatCreateSubtitle(const char *mime_type, const char *language);

/*!
  \brief Destroy a #MediaFormat object.
  \param[in] handle #MLHandle to the #MediaFormat object.
  \return \c \c true if #MediaCodec object was successfully destroyed.
 */
ML_API bool ML_CALL MLMediaFormatDestroy(MLHandle handle);

/*!
  \brief Obtain the human readable representation of the format.

  User shall allocate at least #MAX_FORMAT_STRING_SIZE bytes of memory for
  storing the output format string. The format string contains
  a list of key-value pairs, which can be extracted individually
  via the suitable "GetKeyValue" APIs.

  \param[in] handle #MLHandle to the #MediaFormat object.
  \param[out] out_string Pointer to the user-maintained buffer for storing
              the output C-style format string.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaFormatObjectToString(MLHandle handle, char *out_string);

/*!
  \brief Obtain the value of an integer key.

  For example, use #MLMediaFormat_Key_Frame_Rate key to get
  the framerate of a video track.

  \param[in] handle #MLHandle to the #MediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[out] out_key Value of the key.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaFormatGetKeyValueInt32(MLHandle handle, MLMediaFormatKey name, int32_t *out_key);

/*!
  \brief Obtain the value of an long key.
  For example, use MLMediaFormat_Key_Duration key to get
  duration of a track.

  \param[in] handle #MLHandle to the #MediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[out] out_key Value of the key.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaFormatGetKeyValueInt64(MLHandle handle, MLMediaFormatKey name, int64_t *out_key);

/*!
  \brief Obtain the value of an float key.
  \param[in] handle #MLHandle to the #MediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[out] out_key Value of the key.
  \return \c true if operation succeeded and \c \c false if it failed.
*/
ML_API bool ML_CALL MLMediaFormatGetKeyValueFloat(MLHandle handle, MLMediaFormatKey name, float *out_key);

/*!
  \brief Obtain the size of a key.
  \param[in] handle #MLHandle to the #MediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[out] out_size Size of the key.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaFormatGetKeySize(MLHandle handle, MLMediaFormatKey name, size_t *out_size);

/*!
  \brief Obtain the value of a string key.

  User shall allocate at least #MAX_KEY_STRING_SIZE bytes of memory for
  storing the output key string.

  \param[in] handle #MLHandle to the #MediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[out] out_string Pointer to the C-string representation of the string key.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaFormatGetKeyString(MLHandle handle, MLMediaFormatKey name, char *out_string);

/*!
  \brief Set the value of an integer key.
  \param[in] handle #MLHandle to the #MediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[in] key_value Key value.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaFormatSetKeyInt32(MLHandle handle, MLMediaFormatKey name, int32_t key_value);

/*!
  \brief Set the value of a long key.
  \param[in] handle #MLHandle to the #MediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[in] key_value Key value.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaFormatSetKeyInt64(MLHandle handle, MLMediaFormatKey name, int64_t key_value);

/*!
  \brief Set the value of a float key.
  \param[in] handle #MLHandle to the #MediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[in] key_value Key value.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaFormatSetKeyFloat(MLHandle handle, MLMediaFormatKey name, float key_value);

/*!
  \brief Set the size of a key.
  \param[in] handle #MLHandle to the #MediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[in] key_size Key size.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaFormatSetKeySize(MLHandle handle, MLMediaFormatKey name, size_t key_size);

/*!
  \brief Set the value of a string key.
  \param[in] handle #MLHandle to the #MediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[in] key_value C-string representation of key value.
  \return \c true if operation succeeded and \c false if it failed.
 */
ML_API bool ML_CALL MLMediaFormatSetKeyString(MLHandle handle, MLMediaFormatKey name, const char *key_value);

/*! @} */

ML_EXTERN_C_END
