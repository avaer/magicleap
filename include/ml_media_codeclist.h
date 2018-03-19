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

#define MAX_CODEC_NAME_LENGTH 64

/*!
  \brief Bit mask for specifying the type of codec being queried
  using MLMediaCodecListGetMatchingCodecs().
*/
typedef enum MLMediaCodecListCodecTypeFlag {
  MLMediaCodecListCodecTypeFlag_Software     = 1 << 0,
  MLMediaCodecListCodecTypeFlag_Hardware     = 1 << 1,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaCodecListCodecTypeFlag_Ensure32Bits = 0x7FFFFFFF
} MLMediaCodecListCodecTypeFlag;

/*!
  \brief Bit mask for checking the capability of a codec after
  queried via #MLMediaCodecListGetCapabilityFlag.
*/
typedef enum MLMediaCodecListCapabilityFlag {
  MLMediaCodecListCapabilityFlag_AdaptivePlayback = 1 << 0,
  MLMediaCodecListCapabilityFlag_SecurePlayback   = 1 << 1,
  MLMediaCodecListCapabilityFlag_TunneledPlayback = 1 << 2,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaCodecListCapabilityFlag_Ensure32Bits     = 0x7FFFFFFF
} MLMediaCodecListCapabilityFlag;

/*!
  \brief Used to store the list of available codec names
  or the list of supported mime types.
*/
typedef struct MLMediaCodecListQueryResults {
  size_t  count;
  char    **data;
} MLMediaCodecListQueryResults;

/*!
  \brief Obtain the number of available codecs.
  \param[out] out_codec_ount Number of available codecs.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaCodecListCountCodecs(uint64_t *out_codec_count);

/*!
  \brief Determine whether a codec is a software codec.
  \param[out] codec_name Name of the codec.
  \return \c true if the codec is a software codec and \c false otherwise.
*/
ML_API bool ML_CALL MLMediaCodecListIsSoftwareCodec(const char *codec_name);

/*!
  \brief Obtain a list of matching codecs for a given codec mime.

  The memory used to store the list is maintained by the library.
  User shall call MLMediaCodecListQueryResultsRelease() to release it.

  \param[in] mime Codec mime.
  \param[in] is_encoder \c true if querying for encoder and false otherwise.
  \param[in] flag Whether querying for software-only or hardware-only,
             defined by #MLMediaCodecListCodecTypeFlag.
  \param[out] out_matching_codecs List of codecs supporting the given mime.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaCodecListGetMatchingCodecs(const char *mime, bool is_encoder, MLMediaCodecListCodecTypeFlag flag, MLMediaCodecListQueryResults *out_matching_codecs);

/*!
  \brief Obtain the codec matching the given codec type from the codec list.
  \param[in] type Codec mime.
  \param[in] is_encoder \c true if querying for encoder and \c false otherwise.
  \param[in] start_index Index from which to search in the codec list.
             The number shall be between 0 and number of available codecs.
  \param[out] out_index Index of the matching codec or -2.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaCodecListGetCodecByType(const char *type, bool is_encoder, uint64_t start_index, int64_t *out_index);

/*!
  \brief Obtain the codec from the codec matching the given codec name from the codec list.
  \param[in] name Codec name.
  \param[out] out_index Index of the matching codec or -2.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaCodecListGetCodecByName(const char *name, int64_t *out_index);

/*!
  \brief Confirm whether a component is an Encoder or Decoder.
  \param[in] index Index of the codec in the codec list.
             The number shall be between 0 and number of available codecs.
  \return \c true if the codec is an Encoder and \c false otherwise.
*/
ML_API bool ML_CALL MLMediaCodecListIsEncoder(uint64_t index);

/*!
  \brief Obtain a codec name.

  User shall allocate at least #MAX_CODEC_NAME_LENGTH bytes of memory for
  storing the output name string.

  \param[in] index Index of the codec in the codec list.
             The number shall be between 0 and number of available codecs.
  \param[out] out_name Pointer to the user-maintained buffer for storing
              the output C-style name string.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaCodecListGetCodecName(uint64_t index, char *out_name);

/*!
  \brief Obtain the list of mime types supported by a codec.

  The memory used to store the list is maintained by the library.
  User shall call MLMediaCodecListQueryResultsRelease() to
  release it.

  \param[in] index Index of the codec in the codec list.
             The number shall be between 0 and number of available codecs.
  \param[out] out_supported_mimes List of supported mimes.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaCodecListGetSupportedMimes(uint64_t index, MLMediaCodecListQueryResults *out_supported_mimes);

/*!
  \brief Obtain the capability flag for a codec.
  \param[in] index Index of the codec in the codec list.
             The number shall be between 0 and number of available codecs.
  \param[in] mime Mime type of the codec being queried.
  \param[out] out_capability_flag Codec capability flag defined by #MLMediaCodecListCapabilityFlag.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaCodecListGetCapabilityFlag(uint64_t index, const char *mime, MLMediaCodecListCapabilityFlag *out_capability_flag);

/*!
  \brief Obtain the name of a secure codec for the given mime type.

  User shall allocate at least #MAX_CODEC_NAME_LENGTH bytes of memory for
  storing the output name string.

  \param[in] mime Mime type of the codec.
  \param[in] is_decoder \c true if querying for decoder and \c false otherwise.
  \param[out] out_name Pointer to the user-maintained buffer for storing
              the output C-style name string.
  \return \c true if operation succeeded and \c false if it failed.
*/
ML_API bool ML_CALL MLMediaCodecListGetSecureCodecName(const char *mime, bool is_decoder, char *out_name);

/*!
  \brief Release the query results.
  \param[in] query_result Query results such as the list of codecs acquired by
             MLMediaCodecListGetMatchingCodecs() or the list of supported mime types
             acquired by MLMediaCodecListGetSupportedMimes().
  \return \c true if the codec is a software codec and \c false otherwise.
*/
ML_API bool ML_CALL MLMediaCodecListQueryResultsRelease(MLMediaCodecListQueryResults *query_results);

/*! @} */

ML_EXTERN_C_END
