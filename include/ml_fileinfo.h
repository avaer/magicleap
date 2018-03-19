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

/*! \brief This typedef can be used directly with POSIX APIs like open(), close() etc. */
typedef int32_t MLFileDescriptor;

/*!
  \brief Opaque structure containing file information like mime type, fd, file name.

  The fields in this structure can be obtained by:
  File descriptor - Can be obtained by calling MLFileInfoGetFD().
  File mime type  - Can be obtained by calling MLFileInfoGetMimeType().
  File name       - Can be obtained by calling MLFileInfoGetFileName().
*/
typedef struct MLFileInfo MLFileInfo;

/*!
  \brief This API allocates an empty #MLFileInfo structure.

  The mime type, file name fields will be set to NULL and file descriptor
  will be set to -1.

  \return Returns a pointer to #MLFileInfo on successful allocation and NULL on failure.
  The caller should free the pointer by calling MLFileInfoRelease().
*/
ML_API MLFileInfo *ML_CALL MLFileInfoAllocateEmpty();

/*!
  \brief This API retrieves the mime type of the given #MLFileInfo.

  This returned mime type can be of the pattern <type/sub-type>.
  e.g application/xml where "application" is type and "xml" is sub-type.

  \param[in] file_info Pointer to #MLFileInfo struct pointer.
  \return Returns a pointer to mime type of the given #MLFileInfo on success and
          NULL on failure to find mime type. The caller should not free the pointer returned.
*/
ML_API const char *ML_CALL MLFileInfoGetMimeType(const MLFileInfo *file_info);

/*!
  \brief This API retrieves the file name associated with the given #MLFileInfo.

  This is for information purposes only and cannot be used to access the file
  itself. That can only be accessed via the file descriptor obtained from
  MLFileInfoGetFD().

  \param[in] file_info Pointer to #MLFileInfo struct pointer.
  \return Returns a pointer to file name of the given #MLFileInfo on success and NULL on failure
          to find file name. The caller should not free the pointer returned which remains
          valid until the file_info gets released or modified.
*/
ML_API const char *ML_CALL MLFileInfoGetFileName(const MLFileInfo *file_info);

/*!
  \brief This API retrieves the file descriptor of the given #MLFileInfo.

  \param[in] file_info Pointer to #MLFileInfo struct pointer.
  \return Returns the file descriptor of the given #MLFileInfo on success and -1 on
          failure to find valid FD.
*/
ML_API MLFileDescriptor ML_CALL MLFileInfoGetFD(const MLFileInfo *file_info);

/*!
  \brief Sets the file descriptor for the given #MLFileInfo structure.

  This makes a copy/dup of the file descriptor, so the caller has to
  close fd when no longer needed.

  \param[in] file_info #MLFileInfo structure whose file descriptor field will be set.
  \param[in] fd file descriptor that will be set in #MLFileInfo.
  \return \c true if setting file descriptor was successful and \c false on failure.
*/
ML_API bool ML_CALL MLFileInfoSetFD(MLFileInfo *file_info, int fd);

/*!
  \brief Sets the file name for the given #MLFileInfo structure.

  The memory used to store the string will be released in MLFileInfoRelease().

  \param[in] file_info #MLFileInfo structure who's file name field will be set.
  \param[in] file_name file name associated with the fd that will be set in #MLFileInfo.
  \return \c true if setting file name was successful and \c false on failure.
*/
ML_API bool ML_CALL MLFileInfoSetFileName(MLFileInfo *file_info, const char *file_name);

/*!
  \brief Sets the file mime type for the given #MLFileInfo structure.

  The memory used to store the string will be released in MLFileInfoRelease().

  \param[in] file_info #MLFileInfo structure who's mime type field will be set.
  \param[in] mime_type mime type of the file that will be set in #MLFileInfo.
  \return \c true if setting mime type was successful and \c false on failure.
*/
ML_API bool ML_CALL MLFileInfoSetMimeType(MLFileInfo *file_info, const char *mime_type);

/*!
  \brief Frees the pointer to #MLFileInfo that is allocated by MLFileInfoAllocateEmpty()

  The memory used to store the file info and mime type strings will be released in
  MLFileInfoRelease(). The file descriptor stored in the #MLFileInfo structure is also
  closed.

  \param[in] file_info pointer to #MLFileInfo structure pointer that will be freed.
  \return \c true if freeing #MLFileInfo was successful and \c false on failure.
*/
ML_API bool ML_CALL MLFileInfoRelease(MLFileInfo **file_info);

ML_EXTERN_C_END
