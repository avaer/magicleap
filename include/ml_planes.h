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

ML_EXTERN_C_BEGIN

/*!
  \addtogroup Planes
  \brief APIs for the Planes system.

  - The Planes system is for planes.
  @{
*/

/*! Control flags for plane queries. */
typedef enum MLPlanesQueryFlags {
  /*! Include planes whose normal is perpendicular to gravity. */
  MLPlanesQueryFlag_Vertical         = 1 << 0,
  /*! Include planes whose normal is parallel to gravity. */
  MLPlanesQueryFlag_Horizontal       = 1 << 1,
  /*! Include planes with arbitrary normals. */
  MLPlanesQueryFlag_Arbitrary        = 1 << 2,
  /*! Include all plane orientations. */
  MLPlanesQueryFlag_AllOrientations  = MLPlanesQueryFlag_Vertical |
                                       MLPlanesQueryFlag_Horizontal |
                                       MLPlanesQueryFlag_Arbitrary,
  /*! For non-horizontal planes, setting this flag will result in the top of
      the plane rectangle being perpendicular to gravity. */
  MLPlanesQueryFlag_OrientToGravity  = 1 << 3,
  /*! If this flag is set, inner planes will be returned; if it is not set,
      outer planes will be returned. */
  MLPlanesQueryFlag_Inner            = 1 << 4,
  /*! Instructs the plane system to ignore holes in planar surfaces. If set,
      planes can patch over holes in planar surfaces. Otherwise planes will
      be built around holes. */
  MLPlanesQueryFlag_IgnoreHoles      = 1 << 5,
  /*! Include planes semantically tagged as ceiling. */
  MLPlanesQueryFlag_Semantic_Ceiling = 1 << 6,
  /*! Include planes semantically tagged as floor. */
  MLPlanesQueryFlag_Semantic_Floor   = 1 << 7,
  /*! Include planes semantically tagged as wall. */
  MLPlanesQueryFlag_Semantic_Wall    = 1 << 8,
  /*! Include all planes that are semantically tagged. */
  MLPlanesQueryFlag_Semantic_All     = MLPlanesQueryFlag_Semantic_Ceiling |
                                       MLPlanesQueryFlag_Semantic_Floor |
                                       MLPlanesQueryFlag_Semantic_Wall,
} MLPlanesQueryFlags;

/*! A plane with width and height */
typedef struct MLPlane {
  /*! Plane center. */
  MLVec3f position;
  /*! Plane rotation. */
  MLQuaternionf rotation;
  /*! Plane width. */
  float width;
  /*! Plane height. */
  float height;
  /*! Flags which describe this plane. */
  uint32_t flags;
} MLPlane;

/*! Type used to represent a plane query. */
typedef struct MLPlanesQuery {
  /*! The flags to apply to this query. */
  uint32_t flags;
  /*! The center of the bounding box which defines where planes extraction should occur. */
  MLVec3f bounds_center;
  /*! The rotation of the bounding box where planes extraction will occur. */
  MLQuaternionf bounds_rotation;
  /*! The size of the bounding box where planes extraction will occur. */
  MLVec3f bounds_extents;
  /*! The maximum number of results that should be returned. This is also
      the minimum expected size of the array of results passed to the
      MLPlanesGetResult function. */
  uint32_t max_results;
  /*! If #MLPlanesQueryFlag_IgnoreHoles is set to false, holes with a perimeter
      (in meters) smaller than this value will be ignored, and can be part of the
      plane. This value cannot be lower than 0 (lower values will be capped to
      this minimum). A good default value is 0.5. */
  float min_hole_length;
  /*! The minimum area (in squared meters) of planes to be returned. This value
      cannot be lower than 0.04 (lower values will be capped to this minimum).
      A good default value is 0.25. */
  float min_plane_area;
} MLPlanesQuery;

/*! Possible results of a plane query. */
typedef enum MLPlanesQueryResult {
  /*! The plane query failed. */
  MLPlanesQueryResult_Failure = -1,
  /*! The plane query succeeded and has valid data. */
  MLPlanesQueryResult_Success,
  /*! The plane query is still being processed. */
  MLPlanesQueryResult_Pending,
  /*! Ensure enum is represented as 32 bits. */
  MLPlanesQueryResult_Ensure32Bits = 0x7FFFFFFF
} MLPlanesQueryResult;

/*!
  \brief Create a planes tracker.
  \return A handle to the created planes tracker. If there is an error during
          creation, it will return #ML_INVALID_HANDLE.
*/
ML_API MLHandle ML_CALL MLPlanesCreate();

/*!
  \brief Destroy a planes tracker.
  \param[in] planes_tracker #MLHandle to planes tracker to destroy.
  \return \c true if tracker was destroyed; \c false if otherwise.
*/
ML_API bool ML_CALL MLPlanesDestroy(MLHandle planes_tracker);

/*!
  \brief Initiates a plane query.
  \param[in] planes_tracker Handle produced by MLPlanesCreate().
  \param[in] query Pointer to #MLPlanesQuery structure containing query parameters.
  \return valid handle if plane query was successfully begun; #ML_INVALID_HANDLE
          otherwise.
*/
ML_API MLHandle ML_CALL MLPlanesQueryBegin(MLHandle planes_tracker, const MLPlanesQuery *query);

/*!
  \brief Gets the result of a plane query. After this function has returned successfully,
  the handle is invalid and should be discarded.
  \param[in] planes_tracker Handle produced by MLPlanesCreate().
  \param[in] planes_query Handle produced by MLPlanesQueryBegin().
  \param[out] out_results An array of #MLPlane structures.
  \param[out] out_num_results Number of results pointed to by out_results.
  \return #MLPlanesQueryResult indicating success or failure.
*/
ML_API MLPlanesQueryResult ML_CALL MLPlanesQueryGetResults(MLHandle planes_tracker, MLHandle planes_query, MLPlane *out_results, uint32_t *out_num_results);

ML_EXTERN_C_END
