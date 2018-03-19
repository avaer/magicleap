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
  \brief Store the specified blob under the specified alias. An existing alias would be overwritten.
  \param[in] alias The NULL-terminated alias associated with the blob. Must not be NULL.
  \param[in] blob The blob to store.
  \param[in] blob_length The length of the blob to store.
  \return \c true or \c false, whether or not the blob was stored successfully.
*/
ML_API bool ML_CALL MLSecureStoragePutBlob(const char *alias, const uint8_t *blob, size_t blob_length);

/*!
  \brief Retrieve the blob associated with the specified alias. Note that the caller must invoke
  MLSecureStorageFreeBlobBuffer() on the blob pointer.
  \param[in] alias The NULL-terminated alias to look for. Must not be NULL.
  \param[in] blob A pointer to the internally allocated buffer.
  \param[in] blob_length The length of the internally allocated blob.
  \return \c true or \c false, whether or not the blob was found and retrieved successfully.
*/
ML_API bool ML_CALL MLSecureStorageGetBlob(const char *alias, uint8_t **blob, size_t *blob_length);

/*!
  \brief Delete the item associated with the specified alias.
  \param[in] alias The NULL-terminated alias of the item to delete. Must not be NULL.
  \return \c true if the item was deleted successfully or did not exist altogether.
*/
ML_API bool ML_CALL MLSecureStorageDeleteBlob(const char *alias);

/*!
  \brief Free the buffer allocated internally when MLSecureStorageGetBlob() is called.
  \param[out] blob Pointer to the internally allocated buffer.
*/
ML_API void ML_CALL MLSecureStorageFreeBlobBuffer(uint8_t *blob);

ML_EXTERN_C_END
