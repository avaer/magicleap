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
#include "ml_types.h"
#include "ml_image.h"

ML_EXTERN_C_BEGIN

/*!
  \brief APIs for the Screens system

  Screens API provides functions to:
    - add, remove, list and update the watch history.
    - list the screen information.

  \addtogroup Screens
  @{
*/

/*! An item that may be displayed in the Screens Launcher application. */
typedef struct MLScreensWatchHistoryEntry {
  /*! Entry identification. */
  int64_t id;
  /*! Media title. */
  char *title;
  /*! Media subtitle. */
  char *subtitle;
  /*! Current media playback position in milliseconds. */
  uint32_t playback_position_ms;
  /*! Total duration of the media in milliseconds. */
  uint32_t playback_duration_ms;
  /*! Custom data as C-String (NUL-terminated). This may represent an URL or any
      other generic custom information. */
  char *custom_data;
} MLScreensWatchHistoryEntry;

/*! List of items returned by MLScreensGetWatchHistoryList(). */
typedef struct MLScreensWatchHistoryList {
  /*! Number of elements in the list. */
  uint32_t count;
  /*! An array containing "count" entries. */
  MLScreensWatchHistoryEntry *entries;
} MLScreensWatchHistoryList;

/*! This contains the information necessary for positioning of a screen. */
typedef struct MLScreensScreenInfo {
  /*! Position and orientation of screen. */
  MLTransform transform;
  /*! Scale of the screen. */
  MLVec3f scale;
} MLScreensScreenInfo;

/*! List of items returned by MLScreensGetScreenInfoList(). */
typedef struct MLScreensScreenInfoList {
  /*! Total number of elements in the list. */
  uint32_t count;
  /*! An array containing "count" entries. */
  MLScreensScreenInfo *entries;
} MLScreensScreenInfoList;

/*!
  \brief Release the watch history thumbnail.
  \param[in] thumbnail The thumbnail to be released.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLScreensReleaseWatchHistoryThumbnail(MLImage *thumbnail);

/*!
  \brief Clean up the content of a list of type #MLScreensWatchHistoryList.

  The watch history entry list can be obtained using MLScreensGetWatchHistoryList().
  Use this function in order to clean up "the content" of the list.

  \param[in,out] list The watch history list.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLScreensReleaseWatchHistoryList(MLScreensWatchHistoryList *list);

/*!
  \brief Clean up the content of a list of type #MLScreensScreenInfoList.

  The screens info list can be obtained using MLScreensGetScreenInfoList().
  Use this function in order to clean up "the content" of the list.

  \param[in] list A list of #MLScreensScreenInfo elements.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLScreensReleaseScreenInfoList(MLScreensScreenInfoList *list);

/*!
  \brief Insert a new watch history entry.

  This should receive a complete #MLScreensWatchHistoryEntry object with exception of the id.
  The \ref id will be filled and returned by this function in the same object.

  \param[in,out] entry A new entry to the watch history.
  \param[in] thumbnail The thumbnail associated with the entry.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLScreensInsertWatchHistoryEntry(MLScreensWatchHistoryEntry *entry, const MLImage *thumbnail);

/*!
  \brief Remove an existing entry from the watch history.

  \param[in] id The id of the entry to be removed from the watch history.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLScreensRemoveWatchHistoryEntry(const int64_t id);


/*!
  \brief Update a watch history entry.

  \param[in] entry The entry to be updated in the watch history.
  \param[in] thumbnail The thumbnail associated with the entry.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLScreensUpdateWatchHistoryEntry(const MLScreensWatchHistoryEntry *entry, const MLImage *thumbnail);

/*!
  \brief Get a list with the watch history that belongs to the calling client.

  The #MLScreensWatchHistoryList argument itself must be allocated by the caller.
  The "content" of #MLScreensWatchHistoryList is allocated by this function and therefore
  must be cleaned up by #MLScreensReleaseWatchHistoryList() after no longer needed.

 \xrefitem req Example \"Example\"
  \code{.cpp}
  MLScreensWatchHistoryList my_list;           // reserve my_list on the stack
  MLScreensGetWatchHistoryList(&my_list);      // initialize my_list with the watch history
  //
  // ... do something with my_list...
  //
  MLScreensReleaseWatchHistoryList(&my_list);  // clean up the content of my_list
  \endcode

  \param[out] out_list The watch history list.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLScreensGetWatchHistoryList(MLScreensWatchHistoryList *out_list);

/*!
  \brief Retrieve the watch history thumbnail.
  \param[in] id The id of the watch history entry.
  \param[out] out_thumbnail The thumbnail.
              It must be released by MLScreensReleaseWatchHistoryThumbnail() after used.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLScreensGetWatchHistoryThumbnail(const int64_t id, MLImage *out_thumbnail);

/*!
  \brief Get a list with all screens information.
  \param[in,out] out_list A list of #MLScreensScreenInfo elements.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLScreensGetScreenInfoList(MLScreensScreenInfoList *out_list);

/*! @} */

ML_EXTERN_C_END
