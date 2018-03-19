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
// --------------------------------------------------------------------*/
// %BANNER_END%

#pragma once

#include "ml_api.h"
#include "ml_types.h"

ML_EXTERN_C_BEGIN

/*!
  \addtogroup Graphics
  \brief The APIs for the graphics system.

  The enclosed APIs allow for interaction with the graphics system. In general,
  to integrate with the graphics system you will do so with a graphics client
  handle. There are two types of clients currently supported, a GL/GLES client
  supporting all GL/GLES APIs from 3.0 to 4.5, and a VK client which supports
  the latest VK definition on the platform. Once created, the client handle
  can be used to start/end frames, set the requested timing characteristics for
  the client, and query useful information about the client.

  All timing, alignment, etc. of the CPU domain of the client with the asynchronous
  composition is also handled automatically by the API through the blocking
  behavior in #MLGraphicsBeginFrame.

  Note : In the current definition of the API, perception must have already been
  started prior to interacting with the graphics system and the perception lifetime
  is managed separate of the graphics system.
  @{
*/

/*!
  \brief The graphics flags used as part of client creation.

  The flags are used to define the #graphics_flags member of the #MLGraphicsOptions as
  part of the definition to create the client.
*/
typedef enum MLGraphicsFlags {
  /*!
    The client will not provide a depth buffer to the graphics system
    as part of rendering. Therefore the handle returned for all depth related
    resources from the graphics APIs will be invalid.
  */
  MLGraphicsFlags_NoDepth = 1 << 0,
  /*!
    The client is requesting a rendering convention such that the upper
    left hand corner of the screen is the default origin (rather than lower left).
  */
  MLGraphicsFlags_OriginUpperLeft = 1 << 1,
  /*!
    Create a debug client with a debug configuration that provides extended logcat
    error logging. Useful to debug failures in API calls to the graphics system.
  */
  MLGraphicsFlags_DebugMode = 1 << 2,
  /*!
    When #graphics_flags is set to default, the client configuration returned
    is the default configuration (color/depth, origin lower left, non-debug).
  */
  MLGraphicsFlags_Default = 0,

  MLGraphicsFlags_Ensure32Bits = 0x7FFFFFFF
} MLGraphicsFlags;

/*!
  \brief The definition of the supported color/depth surface formats.

  Formats that can be specified for the #color_format and #depth_format in
  #MLGraphicsOptions. For the best quality the recommended color format is
  #MLSurfaceFormat_RGBA8UNormSRGB, and for depth (when defined) either
  #MLSurfaceFormat_D32Float or #MLSurfaceFormat_D32FloatS8.
*/
typedef enum MLSurfaceFormat {
  /*! Invalid format for color/depth. */
  MLSurfaceFormat_Unknown = 0,
  /*! 32bit linear color format (RGBA8). */
  MLSurfaceFormat_RGBA8UNorm,
  /*!
    Gamma 2.2 32bit sRGB color format (RGBA8). Clients requesting this format
    are required to encode the final color into this surface as defined by the
    IEC 61966-2-1 specification.
  */
  MLSurfaceFormat_RGBA8UNormSRGB,
  /*! 32bit linear color format (R10G10B10A2). */
  MLSurfaceFormat_RGB10A2UNorm,
  /*! 64bit linear color format (R16G16B16A16). */
  MLSurfaceFormat_RGBA16Float,
  /*! 32bit floating point depth buffer (D32F). */
  MLSurfaceFormat_D32Float,
  /*! 24bit linear depth format with 8bit stencil (D24S8). */
  MLSurfaceFormat_D24NormS8,
  /*! 32bit floating point depth format with 8bit stencil (D32FS8). */
  MLSurfaceFormat_D32FloatS8,

  MLSurfaceFormat_Ensure32Bits = 0x7FFFFFFF
} MLSurfaceFormat;

/*!
  \brief The graphics options provided for client creation.

  #MLGraphicsOptions defines the requested client configuration for
  creating GL/GLES or VK clients.
*/
typedef struct MLGraphicsOptions {
  /*! The combined graphics flags, as defined by #MLGraphicsFlags. */
  uint32_t graphics_flags;
  /*! The color surface format, defined in #MLSurfaceFormat. */
  MLSurfaceFormat color_format;
  /*! The depth surface format, defined in #MLSurfaceFormat. */
  MLSurfaceFormat depth_format;
} MLGraphicsOptions;

/*!
  \brief Frame timing hint specified at runtime to control the client cadence.

  Timing hint defines the requested client rate when interacting with
  the graphics system and is used as part of the blocking behavior specified by
  #MLGraphicsBeginFrame. The timing hit can be updated at runtime for a valid client
  at any time and will take effect on the next frame period for the client.

  The recommended setting for the timing hint is #MLGraphicsFrameTimingHint_60Hz.
*/
typedef enum MLGraphicsFrameTimingHint {
  /*! Default rate is unspecified, adjusted based on system conditions. */
  MLGraphicsFrameTimingHint_Unspecified = 0,
  /*! Run at the maximum rate allowed by the system. */
  MLGraphicsFrameTimingHint_Maximum,
  /*! Run at a specified rate of 60Hz (i.e. one frame every ~16.67 ms). */
  MLGraphicsFrameTimingHint_60Hz,
  /*! Run at a specified rate of 120Hz (i.e. one frame every ~8.33 ms). */
  MLGraphicsFrameTimingHint_120Hz,

  MLGraphicsFrameTimingHint_Ensure32Bits = 0x7FFFFFFF
} MLGraphicsFrameTimingHint;

/*!
  \brief The metadata name associated with each virtual camera.

  APIs within the graphics system will return information specific to
  a single virtual camera or both. The metadata name informs the client
  how to correlate the outputs of the API to a specific camera or both
  cameras.
*/
typedef enum MLGraphicsVirtualCameraName {
  /*! Name of the combined camera, the union of all virtual cameras. */
  MLGraphicsVirtualCameraName_Combined = -1,
  /*! Name of virtual camera for left display. */
  MLGraphicsVirtualCameraName_Left = 0,
  /*! Name of virtual camera for right display. */
  MLGraphicsVirtualCameraName_Right,
  /*! The maximum number of render virtual cameras. */
  MLGraphicsVirtualCameraName_Count,

  MLGraphicsVirtualCameraName_Ensure32Bits = 0x7FFFFFFF
} MLGraphicsVirtualCameraName;

/*!
  \brief Definitions for Graphics system maximums.
*/
enum {
  /*! The number of buffered entries for each virtual camera. */
  MLGraphics_BufferCount = 3
};

/*!
  \brief Defines the requested projection matrix model for rendering.

  Provided as part of the #MLGraphicsFrameParams, defines the requested
  projection model for the intrinsic definition returned for each virtual
  camera from #MLGraphicsBeginFrame.
*/
typedef enum MLGraphicsProjectionType {
  /*! Standard projection model. */
  MLGraphicsProjectionType_Default = 0,
  /*! Reversed infinite z projection model. */
  MLGraphicsProjectionType_ReversedInfiniteZ,

  MLGraphicsProjectionType_Ensure32Bits = 0x7FFFFFFF
} MLGraphicsProjectionType;

/*!
  \brief The frame parameters requested for the next rendered frame.

  The parameters defined by #MLGraphicsFrameParams are supplied to
  #MLGraphicsBeginFrame from the client to defined the requested
  characteristics of the next rendered frame.

  Note : If a near clip is provided that is closer than the #min_clip returned from
  #MLGraphicsRenderTargetsInfo the provided near clip will be clamped up to the
  min clip.
*/
typedef struct MLGraphicsFrameParams {
  /*! Requested near clip plane distance in meters. */
  float near_clip;
  /*! Far clipping plane distance in meters. */
  float far_clip;
  /*!
    Distance, in meters, to defined focus point for the client content. The focus
    distance should be calculated as the positive distance to the client determined
    object of interest (relative to the forward vector of the Lightwear).
  */
  float focus_distance;
  /*!
    The scale factor for the render surfaces, valid range is 0.0->1.0. When
    supplying a scale factor < 1.0 the viewport returned from #MLGraphicsBeginFrame
    will be adjusted to the closest width/height match to the request that can
    be supported by the graphics system.
  */
  float surface_scale;
  /*!
    Content for this frame is protected and should not be recorded or captured
    outside the graphics system.
  */
  bool protected_surface;
  /*! Requested projection model for rendering. */
  MLGraphicsProjectionType projection_type;
} MLGraphicsFrameParams;

/*!
  \brief The static clip extents defined for all possible eye positions.

  Defines the conservative clip extents for the camera name that can be used for early
  update frustum culling in the client update path (prior to calling #MLGraphicsBeginFrame).

  Note: The client will need to obtain a headpose to combine with the provided matrices
  (transform and projection) to define the frustum. The general definition for camera from
  world (for the specified camera name) is MATprojection * inv(MATtransform) * MATheadpose
  for RHS multiplication.
*/
typedef struct MLGraphicsClipExtentsInfo {
  /*! The virtual camera meta data name. */
  MLGraphicsVirtualCameraName virtual_camera_name;
  /*!
    The projection matrix, defined with infinite far clip plane distance. If the client
    is using a different projection model the matrix will need to be adjusted to match
    the client model prior to frustum culling.
  */
  MLMat4f projection;
  /*! The camera to world transform (i.e. local space relative to the head). */
  MLTransform transform;
} MLGraphicsClipExtentsInfo;

/*!
  \brief The clip extents array returned from #MLGraphicsGetClipExtents.

  The clip extents array provides the conservative clip extents per metadata
  camera as defined by #MLGraphicsClipExtentsInfo.
*/
typedef struct MLGraphicsClipExtentsInfoArray {
  /*! The number of virtual cameras. */
  uint32_t num_virtual_cameras;
  /*!
    The combined extents for all the virtual cameras, can be used for conservative frustum
    culling of all visible content defined by the union of what is visible from all of
    the defined virtual cameras.
  */
  MLGraphicsClipExtentsInfo full_extents;
  /*! The per virtual camera clip extents. */
  MLGraphicsClipExtentsInfo virtual_camera_extents[MLGraphicsVirtualCameraName_Count];
} MLGraphicsClipExtentsInfoArray;

/*!
  \brief Definition of a single render target defined in #MLGraphicsRenderBufferInfo.

  Each render target defines one of the buffered entries color/depth surfaces (with
  maximum count defined by #MLGraphics_BufferCount). Clients can assume that the handle
  provided here will be in the list of handles returned from #MLGraphicsBeginFrame.
*/
typedef struct MLGraphicsRenderTarget {
  /*! The width of the target. */
  uint32_t width;
  /*! The height of the target. */
  uint32_t height;
  /*! The handle (ID) of the 2D texture array, each layer represents a virtual camera. */
  MLHandle id;
  /*! The surface format of the target. */
  MLSurfaceFormat format;
} MLGraphicsRenderTarget;

/*!
  \brief Definition of a single buffer entry for all virtual cameras as defined
         in #MLGraphicsRenderTargetsInfo.

  Each buffer entry can contain a color / depth target and the target is valid
  if the handle != 0.

  Note : When the client specifies the #MLGraphicsFlags_NoDepth flag as part of
  client creation the depth targets will always be 0.
*/
typedef struct MLGraphicsRenderBufferInfo {
  /*! The color target for this entry. */
  MLGraphicsRenderTarget color;
  /*! The depth target for this entry. */
  MLGraphicsRenderTarget depth;
} MLGraphicsRenderBufferInfo;

/*!
  \brief The complete definition of all possible buffered entries along with associated metadata.

  Statically defined after successfully creating the client, the #MLGraphicsRenderTargetsInfo
  provides the definition of all of the buffered entries along with the global metadata. The
  client can assume that once queried the definition will not change and therefore does not need
  to be queried more than once at runtime.
 */
typedef struct MLGraphicsRenderTargetsInfo {
  /*! The enforced minimum clip distance for rendering content, in meters. */
  float min_clip;
  /*! The un-enforced, but recommended maximum clip distance for rendering content, in meters. */
  float max_clip;
  /*!
    The total number of virtual camera for this platform,
    i.e (num_virtual_cameras <= #MLGraphicsVirtualCameraName_Count).
  */
  uint32_t num_virtual_cameras;
  /*! The buffer entries for all virtual cameras. */
  MLGraphicsRenderBufferInfo buffers[MLGraphics_BufferCount];
} MLGraphicsRenderTargetsInfo;

/*!
  \brief The per virtual camera information as defined in #MLGraphicsVirtualCameraInfoArray.

  For each virtual camera the client is provided the exact definition of the camera properties
  along with the matrices needed to construct the full transform chain. In general the
  transform chain for each virtual camera is defined as MATprojection * inv(MATtransform) for
  RHS multiplication.

  Note : The projection model is assymetric and clients should not assume any of the
  symmetric properties of projection. Additionally both the transform and projection will
  change per frame and cannot be assumed to be static.
*/
typedef struct MLGraphicsVirtualCameraInfo {
  /*! The FOV left half angle, in radians. */
  float left_half_angle;
  /*! The FOV right half angle, in radians. */
  float right_half_angle;
  /*! The FOV top half angle, in radians. */
  float top_half_angle;
  /*! The FOV bottom half angle, in radians. */
  float bottom_half_angle;
  /*!
    The handle of the sync object to signal after submitting all GPU work for the
    virtual camera.
  */
  MLHandle sync_object;
  /*! The projection matrix for the virtual camera. */
  MLMat4f projection;
  /*!
    The local space (relative to world) camera transform needed to render content,
    inverse is view matrix.
  */
  MLTransform transform;
  /*! The name of the virtual camera */
  MLGraphicsVirtualCameraName virtual_camera_name;
} MLGraphicsVirtualCameraInfo;

/*!
  \brief The virtual camera info array populated by #MLGraphicsBeginFrame.

  The info array defines the single color and depth (if #MLGraphicsFlags_NoDepth is
  not specified) handles along with all the required metadata.
*/
typedef struct MLGraphicsVirtualCameraInfoArray {
  /*! The number of virtual cameras for the frame, each virtual camera is a layer. */
  uint32_t num_virtual_cameras;
  /*! The handle (ID) of the color surface for the virtual cameras. */
  MLHandle color_id;
  /*! The handle (ID) of the depth surface for the virtual cameras. */
  MLHandle depth_id;
  /*! The common viewport definition for all virtual cameras. */
  MLRectf viewport;
  /*! The array of virtual cameras to render to for the frame. */
  MLGraphicsVirtualCameraInfo virtual_cameras[MLGraphicsVirtualCameraName_Count];
} MLGraphicsVirtualCameraInfoArray;

/*!
  \brief Performance timing information for the graphics client.

  Populated by #MLGraphicsGetClientPerformanceInfo, the performance information
  contains all metrics tracked by the graphics system for the specified client.
  Metrics are calculated using a sliding window and can be used to adjust the
  client workload characteristics (i.e. scale, fidelity, etc).

  Note : The internal metrics are also provided, informing the client of both the
  CPU and GPU cost of the internal operations of the graphics system (in the client
  process).
*/
typedef struct MLGraphicsClientPerformanceInfo {
  /*! The average frame start CPU to composition acquisition of the frame, in nanoseconds. */
  uint64_t frame_start_cpu_comp_acquire_cpu_ns;
  /*! The average frame start CPU to frame end GPU, in nanoseconds. */
  uint64_t frame_start_cpu_frame_end_gpu_ns;
  /*! The average frame cadence, CPU start to CPU start, in nanoseconds. */
  uint64_t frame_start_cpu_frame_start_cpu_ns;
  /*! The average frame CPU duration, in nanoseconds. */
  uint64_t frame_duration_cpu_ns;
  /*! The average frame GPU duration, in nanoseconds. */
  uint64_t frame_duration_gpu_ns;
  /*! The average CPU duration for internal operations per frame, in nanoseconds. */
  uint64_t frame_internal_duration_cpu_ns;
  /*! The average GPU duration for internal operations per frame, in nanoseconds. */
  uint64_t frame_internal_duration_gpu_ns;
} MLGraphicsClientPerformanceInfo;

/*!
  \brief Create the GL/GLES graphics client.

  Create a graphics client for use with GL/GLES APIs using the provided options and
  specified opengl context. It is required that the opengl context specified here is
  only bound on the thread used to render the client frame and is the same context
  used to render the frame using the provided information from #MLGraphicsBeginFrame.

  \param options The graphics options for resource creation.
  \param opengl_context The OpenGL context to use for resource creation.
  \param out_gfx_client The handle to the created graphics client.
  \param out_status MLStatus code indicating success as ML_STATUS_OK or failure.
  \return true if successful.
*/
ML_API bool ML_CALL MLGraphicsCreateClientGL(const MLGraphicsOptions *options, const MLHandle opengl_context, MLHandle *out_graphics_client, MLStatus *out_status);

/*!
  \brief Convert MLSurfaceFormat to OpenGL internal format.

  \param format The MLSurfaceFormat to convert.
  \return The returned internal format.
*/
ML_API uint32_t ML_CALL MLGraphicsGLFormatFromMLSurfaceFormat(const MLSurfaceFormat format);

/*!
  \brief Convert OpenGL internal format to MLSurfaceFormat.

  \param format The internal format to convert.
  \return The returned MLSurfaceFormat.
*/
ML_API MLSurfaceFormat ML_CALL MLGraphicsMLSurfaceFormatFromGLFormat(const uint32_t format);

#ifdef VK_VERSION_1_0
/*!
  \brief Create the VK graphics client.

  Create a graphics client for use with VK API using the provided options and specified
  physical and logical device.

  \param options The graphics options for resource creation.
  \param vulkan_physical_device The Vulkan physical device used to create the specified logical device.
  \param vulkan_logical_device The Vulkan logical device to use for resource creation.
  \param out_graphics_client The handle to the created graphics client.
  \param out_status MLStatus code indicating success as ML_STATUS_OK or failure.
  \return true if successful.
*/
ML_API bool ML_CALL MLGraphicsCreateClientVk(const MLGraphicsOptions *options, const VkPhysicalDevice vulkan_physical_device, const VkDevice vulkan_logical_device, MLHandle *out_graphics_client, MLStatus *out_status);

/*!
  \brief Convert MLSurfaceFormat to VkFormat.

  \param format The MLSurfaceFormat to convert.
  \return The returned VkFormat.
*/
ML_API VkFormat ML_CALL MLGraphicsVkFormatFromMLSurfaceFormat(const MLSurfaceFormat format);

/*!
  \brief Convert VkFormat to MLSurfaceFormat.

  \param format The VkFormat to convert.
  \return The returned MLSurfaceFormat.
*/
ML_API MLSurfaceFormat ML_CALL MLGraphicsMLSurfaceFormatFromVkFormat(const VkFormat format);
#endif

/*!
  \brief Destroy a GL/GLES or VK client.

  Destroying the client will invalidate all resources associated with the client handle
  and invalidate the provided handle.

  \param graphics_client The graphics client to destroy.
  \param out_status MLStatus code indicating success as ML_STATUS_OK or failure.
  \return true if successful.
*/
ML_API bool ML_CALL MLGraphicsDestroyClient(MLHandle *graphics_client, MLStatus *out_status);

/*!
  \brief Set the frame timing hint, can be set at runtime and is updated on the
         next call to #MLGraphicsBeginFrame.

  \param graphics_client The graphics client to modify.
  \param out_status MLStatus code indicating success as ML_STATUS_OK or failure.
  \return true if successful.
*/
ML_API bool ML_CALL MLGraphicsSetFrameTimingHint(const MLHandle graphics_client, MLGraphicsFrameTimingHint hint, MLStatus *out_status);

/*!
  \brief Initializes a MLGraphicsFrameParams with the default parameters.

  \param data The object to initialize with default settings.
*/
ML_API bool ML_CALL MLGraphicsInitFrameParams(MLGraphicsFrameParams *data, MLStatus *out_status);

/*!
  \brief Request to begin rendering a new frame in the graphics system.

  Called to request the start of a new render frame and should be called as close as possible to
  the start of rendering to minimize the motion to photon latency. Only one frame can be rendered
  at a time and must be submitted by providing the returned handle to #MLGraphicsEndFrame prior to
  another call to #MLGraphicsBeginFrame. The call to begin/end frame should be made on the render
  thread alone of the client.

  Note : Calls to #MLGraphicsBeginFrame can and will block the calling process. There are several reasons
  that lead to a block, including, the client is executing faster than the defined timing requested (and the
  block re-aligns the client timing), the client is not yet visible in the system, and the compositor has
  not yet moved to the next buffered entry (i.e. wraparound cases from fast client rendering).

  \param graphics_client The graphics client to query.
  \param params The frame parameters for the frame.
  \param out_handle A reference handle for this frame to be provided at end of frame.
  \param out_array The virtual camera info array with all information required for rendering to each virtual camera.
  \param out_status MLStatus code indicating success as ML_STATUS_OK or failure.
  \return true if successful.
*/
ML_API bool ML_CALL MLGraphicsBeginFrame(const MLHandle graphics_client, const MLGraphicsFrameParams *params, MLHandle *out_handle, MLGraphicsVirtualCameraInfoArray *out_array, MLStatus *out_status);

/*!
  \brief Signal the sync object provided for each virtual camera for GL/GLES clients.

  Required for each frame, after rendering each virtual camera (or multiple if stereo rendering)
  to signal the sync object in order to inform the graphics system that the rendering for the
  camera(s) has completed. All sync objects can be signaled after rendering all cameras, but
  results in lower fidelity in the graphics system.

  Note: Vulkan clients are required to cast the sync object to VkSemaphore and add it to
  the signal semaphore list when submitting the last command buffer for the virtual camera(s).

  \param graphics_client The graphics client owning the sync object.
  \param sync_object The sync object to be signaled.
  \param out_status MLStatus code indicating success as ML_STATUS_OK or failure.
  \return true if successful.
*/
ML_API bool ML_CALL MLGraphicsSignalSyncObjectGL(const MLHandle graphics_client, const MLHandle sync_object, MLStatus *out_status);

/*!
  \brief Get the conservative clip extents information for each virtual camera.

  Clients can assume the definition is unchanging and therefore only need to call once
  after client initialization.

  \param graphics_client The graphics client to query.
  \param out_array The clip extents info array with all information required for update of each virtual camera.
  \param out_status MLStatus code indicating success as ML_STATUS_OK or failure.
  \return true if successful.
*/
ML_API bool ML_CALL MLGraphicsGetClipExtents(const MLHandle graphics_client, MLGraphicsClipExtentsInfoArray *out_array, MLStatus *out_status);

/*!
  \brief Get a list of all buffered entries.

  Called after client initialization to obtain the definition of all buffered entries
  along with the associated metadata. Like #MLGraphicsGetClipExtents can be assumed that
  the output is unchanging for the lifetime of the client.

  \param graphics_client The graphics client to query.
  \param out_array The render target info array.
  \param out_status MLStatus code indicating success as ML_STATUS_OK or failure.
  \return true if successful.
*/
ML_API bool ML_CALL MLGraphicsGetRenderTargets(const MLHandle graphics_client, MLGraphicsRenderTargetsInfo *out_targets, MLStatus *out_status);

/*!
  \brief Submit a completed frame to the graphics system.

  Submit a completed frame to the graphics system using the handle provided from
  #MLGraphicsBeginFrame. Prior to submiting the frame the client must signal the sync objects
  provided by #MLGraphicsBeginFrame, for GL/GLES clients with #MLGraphicsSignalSyncObjectGL or
  for VK clients including that sync object as part of the signal semaphore list.

  \param graphics_client The graphics client to update.
  \param handle The handle provided from the call to MLGraphicsBeginFrame.
  \param out_status MLStatus code indicating success as ML_STATUS_OK or failure.
  \return true if successful.
*/
ML_API bool ML_CALL MLGraphicsEndFrame(const MLHandle graphics_client, MLHandle handle, MLStatus *out_status);

/*!
  \brief Obtain latest performance metrics for the client.

  Can be called any time after the client has begun rendering frames to obtain the internally tracked
  performance metrics for the client and graphics system. Updated internally once per completed frame.

  \param graphics_client The graphics client in which to query the performance.
  \param out_performance Current performance information for the client.
*/
ML_API bool ML_CALL MLGraphicsGetClientPerformanceInfo(const MLHandle graphics_client, MLGraphicsClientPerformanceInfo *out_info, MLStatus *out_status);

/*! @} */

ML_EXTERN_C_END
