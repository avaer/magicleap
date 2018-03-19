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

/*!
  \addtogroup Logging
  \brief APIs for the Logging system.

  - The Logging system is for logging.
  @{
*/

/*!
  \brief The default log tag to apply to messages logged with the #ML_LOG and
  #ML_LOG_IF convenience macros. Define this before including this file
  in order to define a custom default tag. Tag will be truncated to
  #MLLogging_MaxTagLength characters when output.
*/
#if !defined(ML_DEFAULT_LOG_TAG)
#define ML_DEFAULT_LOG_TAG "NoTag"
#endif

#define ML_LOG_FULL(level, cond, tag, ...)             \
  do {                                                 \
    if ((cond) && MLLoggingLogLevelIsEnabled(MLLogLevel_##level)) {           \
        MLLoggingLogVargs(MLLogLevel_##level, tag, __VA_ARGS__);              \
    }                                                  \
  } while (false)

/*!
  \brief Convenience macro that allows a user to specify a custom tag when logging
  a particular message.
*/
#define ML_LOG_TAG(level, tag, ...) ML_LOG_FULL(level, true, tag, __VA_ARGS__)

/*!
  \brief Convenience macro for logging only if the specified condition is true. Note
  that the condition is always evaluated even if the specified log level is
  not enabled. You should explicitly test against #MLLoggingLogLevelIsEnabled
  if your condition is computationally intensive.
*/
#define ML_LOG_TAG_IF(level, cond, tag, ...) ML_LOG_FULL(level, cond, tag, __VA_ARGS__)

/*!
  \brief User convenience macro. This macro will use the default tag defined by
  #ML_DEFAULT_LOG_TAG.
*/
#define ML_LOG(level, ...) ML_LOG_FULL(level, true, ML_DEFAULT_LOG_TAG, __VA_ARGS__)

/*!
  \brief Convenience macro for logging only if the specified condition is true. Note
  that the condition is always evaluated even if the specified log level is
  not enabled. You should explicitly test against #MLLoggingLogLevelIsEnabled
  if your condition is computationally intensive.
*/
#define ML_LOG_IF(level, cond, ...) ML_LOG_FULL(level, cond, ML_DEFAULT_LOG_TAG, __VA_ARGS__)

#if defined(__GNUC__) || defined(__clang__)
#define ML_PRINTF_ATTRIBUTE(fmt_arg, var_arg) __attribute__((format(printf, fmt_arg, var_arg)))
#else
#define ML_PRINTF_ATTRIBUTE(fmt_arg, var_arg)
#endif

ML_EXTERN_C_BEGIN

/*! The maximum length of a log tag. Tags will be truncated if longer. */
enum {
  MLLogging_MaxTagLength = 23
};

typedef enum MLLogLevel {
  /*! Output a fatal error which causes program termination. */
  MLLogLevel_Fatal = 0,
  /*! Output a serious error. The program may continue. */
  MLLogLevel_Error = 1,
  /*! Output a warning which may be ignorable. */
  MLLogLevel_Warning = 2,
  /*! Output an informational message. */
  MLLogLevel_Info = 3,
  /*! Output a message used during debugging. */
  MLLogLevel_Debug = 4,
  /*! Output a message used for noisier informational messages. */
  MLLogLevel_Verbose = 5,
  /*! Ensure enum is represented as 32 bits. */
  MLLogLevel_Ensure32Bits = 0x7FFFFFFF
} MLLogLevel;

/*!
  \brief Enable output of log messages up to and including the log level.

  Log level filtering is enforced only when logging through the convenience
  macros (ML_LOG, ML_LOG_TAG, etc.) Any log messages below or equal to the
  specified log level will be output. The default log level is #MLLogLevel_Info.

  \param[in] level The MLLogLevel to enable.
*/
ML_API void MLLoggingEnableLogLevel(MLLogLevel level);

/*!
  \brief Check whether or not a log level is currently enabled.
  \param[in] level The MLLogLevel to check.
  \return \c true if the log level is currently enabled, \c false otherwise.
*/
ML_API bool MLLoggingLogLevelIsEnabled(MLLogLevel level);

/*!
  \brief Convert a format specification string into single buffer that is then output.

  This function does not filter the message against the currently
  enabled log level, only the convenience macros filter against the log level.

  \param[in] level The #MLLogLevel at which to log the message.
  \param[in] tag The tag to use for this log message. Tag will be truncated to
             #MLLogging_MaxTagLength characters.
  \param[in] fmt The printf style format specification string.
  \param[in] ... Arguments for the format specification.
*/
ML_API void MLLoggingLogVargs(MLLogLevel level, const char *tag, const char *fmt, ...) ML_PRINTF_ATTRIBUTE(3, 4);

/*!
  \brief Raw logging function. This function does not filter the message against
  the currently enabled log level, it will simply output the given message.

  Only the convenience macros filter against the log level.

  \param[in] level The MLLogLevel at which to log the message.
  \param[in] tag The tag to use for this log message. Tag will be truncated to
             #MLLogging_MaxTagLength characters.
  \param[in] message The full contents of the log message
*/
ML_API void MLLoggingLog(MLLogLevel level, const char *tag, const char *message);

/*! @} */

ML_EXTERN_C_END
