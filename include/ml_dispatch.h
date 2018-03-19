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
#include "ml_fileinfo.h"

ML_EXTERN_C_BEGIN

/*!
  \brief This interface lets an application query the platform to handle things
  that the app itself cannot or wants someone else to handle.
  For example, if an application comes across a schema tag that it doesn't know
  what to do with, it can query the platform to see if some other application might.
  This can be useful for handling http://, https:// or other customSchema://<arg1>/<arg2>
  Apart from handling schema tags in URIs, this interface can also be used
  to query the platform to handle a type of file based on file-extension or mime-type.
*/

typedef enum MLDispatchErrorCode {
  MLDispatchErrorCode_None = 0,
  MLDispatchErrorCode_CannotStartApp,
  MLDispatchErrorCode_InvalidPacket,
  MLDispatchErrorCode_NoAppFound,
  MLDispatchErrorCode_Internal,
  MLDispatchErrorCode_Ensure32Bits = 0x7FFFFFFF
} MLDispatchErrorCode;

/*!
  \brief #MLDispatchPacket type can be used with this interface.
  It can be used to pass a URI string or #MLFileInfo objects
  to the platform.
*/
typedef struct MLDispatchPacket MLDispatchPacket;

/*!
  \brief Create empty dispatch packet.

  The MLFileInfo array in the #MLDispatchPacket returned by this function
  will be NULL as will the uri. In order to allocate memory for these
  members, caller will have to explicitly call #MLDispatchAllocateFileInfoList
  and #MLDispatchAllocateUri respectively.

  The caller will need to free this structure by calling
  #MLDispatchReleasePacket.

  \return Returns a pointer to #MLDispatchPacket structure on success and NULL on failure.
*/
ML_API MLDispatchPacket *ML_CALL MLDispatchAllocateEmptyPacket();

/*!
  \brief Release the #MLDispatchPacket that is allocated by #MLDispatchAllocateEmptyPacket
  and all its resources. The pointer to the #MLDispatchPacket struct will point to NULL after this call.
  \param[in] packet Pointer to #MLDispatchPacket struct pointer.
  \param[in] release_members If \c true, function will attempt to release/free
             #MLFileInfo array and uri members from the MLDispatchPacket.
  \param[in] close_fds If \c true, function will attempt to close the fds in #MLFileInfo,
             If \c false, caller will have to close fds.
  \return \c true or \c false if #MLDispatchPacket could be released or not.
*/
ML_API bool ML_CALL MLDispatchReleasePacket(MLDispatchPacket **packet, bool release_members, bool close_fds);

/*!
  \brief Allocate an empty #MLFileInfo array in the #MLDispatchPacket for given length.

  The caller can release/free by calling MLDispatchReleaseFileInfo() or by calling
  MLDispatchReleasePacket()

  \param[in/out] packet Pointer to #MLDispatchPacket whose #MLFileInfo* member will be
                 allocated file_info_list_length entries.
  \param[in] file_info_list_length Maximum length of the file info array to be allocated.
  \return \c true or \c false if allocation of #MLFileInfo array was successful or not.
*/
ML_API bool ML_CALL MLDispatchAllocateFileInfoList(MLDispatchPacket *packet, int64_t file_info_list_length);

/*!
  \brief This API retrieves length of the #MLFileInfo array in the given #MLDispatchPacket.

  This function can return length of 0 which implies there is no file info
  available.

  \param[in] init_arg Pointer to #MLLifecycleInitArg array.
  \return Returns length of #MLLifecycleInitArg array on success and -1 on failure.
*/
ML_API int64_t ML_CALL MLDispatchGetFileInfoListLength(const MLDispatchPacket *packet);

/*!
  \brief Get the #MLFileInfo at the given index.

  The #MLFileInfo array should have been allocated by calling MLDispatchAllocateFileInfoList().
  \param[in] packet Pointer to #MLDispatchPacket whose #MLFileInfo array for given index will be returned.
  \param[in] index Index of the #MLFileInfo array.
  \return #MLFileInfo* is returned if successful and NULL if not.
*/
ML_API MLFileInfo *ML_CALL MLDispatchGetFileInfoByIndex(const MLDispatchPacket *packet, int64_t index);

/*!
  \brief Populate #MLFileInfo array in the #MLDispatchPacket for current index.

  The caller will have to call MLDispatchAllocateFileInfoList() before calling this
  function. After obtaining the length of the list through MLDispatchGetFileInfoListLength(),
  the caller should get each #MLFileInfo structures in the array through
  MLDispatchGetFileInfoByIndex(). After setting the fields of #MLFileInfo using mutator
  functions, this function should be called to add the #MLFileInfo just set to the
  dispatch packet.

  \param[in/out] packet Pointer to #MLDispatchPacket whose #MLFileInfo* member will be populated.
  \param[in] finfo #MLFileInfo structure that will be added to the #MLDispatchPacket.
  \return \c true or \c false if adding to #MLFileInfo array was successful or not.
*/
ML_API bool ML_CALL MLDispatchAddFileInfo(MLDispatchPacket *packet, const MLFileInfo *finfo);

/*!
  \brief Release the pointer to #MLFileInfo array that is allocated by MLDispatchAllocateFileInfoList().

  The caller will have to call MLDispatchAllocateFileInfoList() before calling this
  function. The #MLFileInfo pointer in #MLDispatchPacket will point to NULL after
  this call.

  \param[in] packet Pointer to MLDispatchPacket.
  \param[in] close_fds If \c true, function will attempt to close the fds in #MLFileInfo,
             if \c false, caller will have to close fds.
  \return \c true or \c false if #MLFileInfo array could be released or not.
*/
ML_API bool ML_CALL MLDispatchReleaseFileInfoList(MLDispatchPacket *packet, bool close_fds);

/*!
  \brief Allocate and assign URI in the #MLDispatchPacket.

  The caller can release/free by calling MLDispatchReleaseUri() or by calling
  MLDispatchReleasePacket().

  \param[in/out] packet Pointer to #MLDispatchPacket whose uri member will be allocated and populated.
  \param[in] uri Value assigned to #MLDispatchPacket's uri member.
  \return \c true or \c false if adding to uri field was successful or not.
*/
ML_API bool ML_CALL MLDispatchSetUri(MLDispatchPacket *packet, const char *uri);

/*!
  \brief Release uri that is allocated by MLDispatchAllocateUri().

  The caller will have to call MLDispatchSetUri() before calling this
  function. The char pointer uri in #MLDispatchPacket will point to NULL after
  this call.

  \param[in] packet Pointer to #MLDispatchPacket struct pointer.
  \return \c true or \c false if uri field could be released or not.
*/
ML_API bool ML_CALL MLDispatchReleaseUri(MLDispatchPacket *packet);

/*!
  \brief Try to open the application that supports a given mime type or schema type.

  If the caller does not specify a mime-type or schema type in the dispatch packet,
  dispatch service will try to open an application which supports the file extension
  specified in the file name.

  Note: Lookup based on file name's file extension is not yet implemented in dispatch service.

  \param[in] packet Pointer to #MLDispatchPacket structure.
  \return \c true if an application was found that can open a given mime or schema type,
          \c false if no application was found or there was an error opening the application.
*/
ML_API MLDispatchErrorCode ML_CALL MLDispatchTryOpenApplication(const MLDispatchPacket *packet);

ML_EXTERN_C_END
