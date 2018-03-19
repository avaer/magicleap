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
#include "ml_data_array.h"

ML_EXTERN_C_BEGIN

/*!
  \addtogroup Meshing
  \brief APIs for the Meshing system.

  - The Meshing system is for meshing.
  @{
*/

/*! Type of mesh to query from the underlying system. */
typedef enum MLMeshingType {
  /*! The full, high resolution mesh.
      Meshing should be done in a single connected mesh. */
  MLMeshingType_Full,
  /*! Meshes information will be returned in point cloud.
      This could be useful for the fast preview of meshes. */
  MLMeshingType_PointCloud,
  /*! Meshing should be done in blocks. */
  MLMeshingType_Blocks,
  /*! Ensure enum is represented as 32 bits. */
  MLMeshingType_Ensure32Bits = 0x7FFFFFFF
} MLMeshingType;

/*! Settings for initializing a mesh tracker. */
typedef struct MLMeshingSettings {
  /*!
    \brief How long in nanoseconds to wait in between polling intervals to get new mesh data.
    Use 0 to not automatically requery.
  */
  uint64_t meshing_poll_time;
  /*! The type of mesh to query. */
  MLMeshingType mesh_type;
  /*! The center of the bounding box which defines where meshing should occur. */
  MLVec3f bounds_center;
  /*! The rotation of the bounding box where meshing will occur. */
  MLQuaternionf bounds_rotation;
  /*! The size of the bounding box where meshing will occur. */
  MLVec3f bounds_extents;
  /*!
    \brief Requested number of triangles for the single connected mesh.
    Use 0 to not use this for simplification.
    This field is only valid when the mesh_type is not #MLMeshingType_Blocks or #MLMeshingType_PointCloud.
  */
  uint32_t target_number_triangles;
  /*!
    \brief Requested number of triangles per block for block meshes.
    Use 0 to not use this for simplification.
    This field is only valid when the mesh_type is #MLMeshingType_Blocks.
  */
  uint32_t target_number_triangles_per_block;
  /*!
    \brief If \c true, enable the meshing updates of the system.
  */
  bool enable_meshing;
  /*!
    \brief If \c true, winding order of indices will be be changed from clockwise to counter clockwise.
    This could be useful for face culling process in different engines.
  */
  bool index_order_ccw;
  /*!
    \brief If \c true, the system will attempt to fill small holes to create a more connected mesh.
  */
  bool fill_holes;
  /*!
    \brief Boundary distance (in meters) of holes you wish to have filled.
  */
  float fill_hole_length;
  /*!
    \brief If \c true, the system will compute the normals for the triangle vertices.
  */
  bool compute_normals;
  /*!
    \brief If \c true, the system will planarize the returned mesh (planar regions will be smoothed out).
  */
  bool planarize;
  /*!
    \brief If \c true, the system will attempt to remove components that are disconnected from
    the main mesh and which have an area less than #disconnected_component_area.
  */
  bool remove_disconnected_components;
  /*!
    \brief If #remove_disconnected_components is \c true, any component that is disconnected
    from the main mesh and which has an area less than this size will be removed.
  */
  float disconnected_component_area;
  /*!
    \brief If \c true, the system will generate the mesh confidence values for the triangle vertices
    and populate the confidence stream.
  */
  bool request_vertex_confidence;
  /*!
    \brief If \c true, the mesh skirt (overlapping area between two mesh blocks) will be removed.
    This field is only valid when the mesh_type is #MLMeshingType_Blocks.
  */
  bool remove_mesh_skirt;
} MLMeshingSettings;

/*! Static information about the mesh points tracker. */
typedef struct MLMeshingStaticData {
  /*!
    \brief Handle to an array of #MLDataArrayHandles which contain all of
    the generated meshes.
  */
  MLDataArrayHandle meshes;
  /*! Index in each mesh which contains all of the indices for triangles.
      Note: the stream index may be valid with null array. */
  uint32_t triangle_index_stream_index;
  /*! Index in each mesh which contains all of the positional information.
      Note: the stream index may be valid with null array. */
  uint32_t position_stream_index;
  /*! Index in each mesh which may contain all of the normals.
      Note: the stream index may be valid with null array. */
  uint32_t normal_stream_index;
  /*! Index in each mesh which may contain all of the confidence values.
      Note: the stream index may be valid with null array. */
  uint32_t confidence_stream_index;
  /*! The coordinate frame which the meshes are relative to. */
  MLCoordinateFrameUID frame;
} MLMeshingStaticData;

/*!
  \brief Create a tracker to monitor meshing.
  \param[in] settings The configuration for the meshing system.
  \return A handle which can be used to get information about the meshing,
          or #ML_INVALID_HANDLE if the tracker could not be created.
*/
ML_API MLHandle ML_CALL MLMeshingCreate(const MLMeshingSettings *settings);

/*!
  \brief Destroy a mesh tracker.
  \param[in] mesh_tracker A handle to the meshing tracker.
  \return \c true if it successfully destroyed the tracker.
*/
ML_API bool ML_CALL MLMeshingDestroy(MLHandle mesh_tracker);

/*!
  \brief Update a mesh tracker with the new settings.
  \param[in] mesh_tracker A handle to the meshing tracker.
  \param[in] settings The configuration of the new settings for the meshing system.
  \return \c true if the settings is updated, \c false otherwise.
*/
ML_API bool ML_CALL MLMeshingUpdate(MLHandle mesh_tracker, const MLMeshingSettings *settings);

/*!
  \brief Force an update on a non-live updating mesh tracker.
  \param[in] mesh_tracker A handle to the meshing tracker.
  \return \c true if the updating succeed, \c false otherwise.
*/
ML_API bool ML_CALL MLMeshingRefresh(MLHandle mesh_tracker);

/*!
  \brief Retrieve static information about the meshing tracker.
  \param[in] mesh_tracker A handle to the meshing tracker created from MLMeshingCreate().
  \param[out] out_data Target to populate the data about that meshing.
  \return \c true if the data has been populated, \c false otherwise.
*/
ML_API bool ML_CALL MLMeshingGetStaticData(MLHandle mesh_tracker, MLMeshingStaticData *out_data);

/*! @} */

ML_EXTERN_C_END
