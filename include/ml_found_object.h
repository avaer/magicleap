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

enum {
  /*! Maximum char size for a label size. */
  MLFoundObject_MaxLabelSize           = 64,
  /*! Maximum char size for a property key size. */
  MLFoundObject_MaxPropertiesKeySize   = 64,
  /*! Maximum char size for a property value size. */
  MLFoundObject_MaxPropertiesValueSize = 64,
};

ML_EXTERN_C_BEGIN

/*!
  \brief Properties are key value pair used for either filters or characteristics of
  an object.
*/
typedef struct MLFoundObjectProperty {
  /*! Key for an objects property. Type is string. Max size defined by
      #MLFoundObject_MaxPropertiesKeySize. Example of a key would be 'texture'. */
  char key[MLFoundObject_MaxPropertiesKeySize];
  /*! Value for an objects property. Type is string. Max size defined by
      #MLFoundObject_MaxPropertiesValueSize. Example of a value would be 'smooth'. */
  char value[MLFoundObject_MaxPropertiesValueSize];
} MLFoundObjectProperty;

/*! Struct used to identify the supported types of found objects. */
typedef enum MLFoundObjectType {
  MLFoundObjectType_None = -1,
  MLFoundObjectType_FoundOrigin,
  MLFoundObjectType_Plane,
  MLFoundObjectType_Generic,
  MLFoundObjectType_Ensure32Bits = 0x7FFFFFFF
} MLFoundObjectType;

/*! Struct used to compose a query that will go to PWService via PIL. */
typedef struct MLFoundObjectQueryFilter {
  /*! Valid id for a found object. */
  MLUUID id;
  /*! Labels are used to describe the object. Should be nouns. Example of a value would be
      'chair, hermon miller, furniture'. */
  const char **labels;
  /*! Number of labels. */
  uint32_t labels_count;
  /*! Which type of found object this query is looking for. */
  const MLFoundObjectType *types;
  /*! How many found object types are you looking for. */
  uint32_t types_count;
  /*! Attributes to be used as filters for the query. */
  const MLFoundObjectProperty *properties;
  /*! Amount of attributes. */
  uint32_t properties_count;
  /*! Vector3 float of where you want the spatial query to originate. */
  MLVec3f center;
  /*! Vector3 float of the max distance you want the spatial query to span. */
  MLVec3f max_distance;
  /*! Maximum number of results. Used to allocate memory. */
  uint32_t max_results;
} MLFoundObjectQueryFilter;

/*! Struct to represent a Found Object. */
typedef struct MLFoundObject {
  /*! Identifier of the Found Object. */
  MLUUID id;
  /*! Type of the found object. */
  MLFoundObjectType type;
  /*! Number of labels. */
  uint32_t label_count;
  /*! Number of properties. */
  uint32_t property_count;
  /*! Size of data including null terminator. */
  uint32_t data_size;
  /*! Vector3 float position at the center of the object. */
  MLVec3f position;
  /*! Vector4 float of the rotation of the object. If no rotation available
  defaults to identity. */
  MLQuaternionf rotation;
  /*! Vector3 float of the size of the objects bounded box. */
  MLVec3f size;
  /*! Id to a reference point. Could be another found object. */
  MLUUID reference_point_id;
} MLFoundObject;

/*!
  \brief Create a Found Object Query tracker.
  \return #MLHandle.
*/
ML_API MLHandle ML_CALL MLFoundObjectTrackerCreate();

/*!
  \brief Release the memory assigned to a query.

  If this is the last query should destroy the tracker fully.
  Else just deactivates the query to which this handle belongs.

  \param[in] tracker_handle Identifier to a #FoundObjectQueryHandle.
  \return \c true if succesful destruction of the handle and memory allocated to it.
*/
ML_API bool ML_CALL MLFoundObjectTrackerDestroy(MLHandle tracker_handle);

/*!
  \brief Create a new identifier for a Found Object Query by struct.

  Creates a new Found Object query by struct for found objects
  After the query has been created, you should poll results.
  Create the tracker before you try polling.

 \param[in] tracker_handle to a Found Object Query Tracker.
 \param[in] query Pointer to a #MLFoundObjectQuery struct.
 \param[out] query_id Pointer that will be the id to reference this query by.
 \return \c true if handle is a valid handle, query_id is not a null pointer, query is not a null pointer.
*/
ML_API bool ML_CALL MLFoundObjectQuery(MLHandle tracker_handle, const MLFoundObjectQueryFilter *query, uint32_t *out_query_id);

/*!
  \brief Get the result of an active MLFoundObjectQueryResultCount.
  param[in] tracker_handle to a Found Object Query Tracker.
  param[in] query_id id of an active query.
  param[out] out_num_results the number of max results from the query.
  return \c true if tracker_handle is a valid handle.
*/
ML_API bool ML_CALL MLFoundObjectGetResultCount(MLHandle tracker_handle, uint32_t query_id, uint32_t *out_num_results);

/*!
  \brief Get the result of a submitted query.
  \param[in] tracker_handle to a Found Object Query Tracker.
  \param[in] query_id of an active query.
  \param[in] index of a found object result.
  \param[out] out_found_object a #MLFoundObject to be hydrated.
  \return \c true if tracker_handle is a valid handle, index is within bounds.
*/
ML_API bool ML_CALL MLFoundObjectGetResult(MLHandle tracker_handle, uint32_t query_id, uint32_t index, MLFoundObject *out_found_object);

/*!
  \brief Get the label for a found object id by index.
  \param[in] tracker_handle to a Found Object Query Tracker.
  \param[in] id of a found object.
  \param[in] buffer_size should be of size #MLFoundObject_MaxLabelSize.
  \param[out] out_label semantic label.
  \return True if tracker_handle is valid, and id is valid, and index is within bounds.
*/
ML_API bool ML_CALL MLFoundObjectGetLabel(MLHandle tracker_handle, MLUUID id, uint32_t index, uint32_t buffer_size, char *out_label);

/*!
  \brief Get the property for a found object id by index.
  \param[in] tracker_handle to a Found Object Query Tracker.
  \param[in] id of a found object.
  \param[in] index of a found object property.
  \param[out] out_property a #MLFoundObjectProperty for a found object.
  \return \c true if tracker_handle is a valid #MLHandle, index is within bounds.
*/
ML_API bool ML_CALL MLFoundObjectGetProperty(MLHandle tracker_handle, MLUUID id, uint32_t index, MLFoundObjectProperty *out_property);

/*!
  \brief Request data for a found object.

  This does not return the data for the found object. It requests the data.
  You can then call MLFoundObjectGetDataById(). It will return \c false if no
  Data is available for the found object. If the Found object has not been
  cached this will add the found object to the cache.

  \param[in] tracker_handle is the handle to a Found Object Query.
  \param[in] id is an Id to a found object.
  \return \c true if tracker_handle is a valid tracker, id is a valid MLUUID.
*/
ML_API bool ML_CALL MLFoundObjectRequestData(MLHandle tracker_handle, MLUUID id);

/*!
  \brief Return the found data for an object.
  \param[in] tracker_handle to a Found Object Query Tracker.
  \param[in] id of a found object.
  \param[in] buffer_size should be at least the size of the found objects data size + 1.
  \param[out] out_data_container of a found object.
  \return \c true when id is a valid id and object has data.
*/
ML_API bool ML_CALL MLFoundObjectGetData(MLHandle tracker_handle, MLUUID id, uint32_t buffer_size, char *out_data_container);

ML_EXTERN_C_END
