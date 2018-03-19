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
  \brief Camera errors.
*/
typedef enum MLCameraError {
  MLCameraError_None = 0,
  /*! Invalid state. */
  MLCameraError_Invalid,
  /*! Camera disabled. */
  MLCameraError_Disabled,
  /*! Camera device failed. */
  MLCameraError_DeviceFailed,
  /*! Camera service failed. */
  MLCameraError_ServiceFailed,
  /*! Capture failed. */
  MLCameraError_CaptureFailed,
  /*! Unknown capture error. */
  MLCameraError_Unknown,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraError_Ensure32Bits = 0x7FFFFFFF
} MLCameraError;

/*!
  \brief Captured output format.
*/
typedef enum MLCameraOutputFormat {
  MLCameraOutputFormat_Unknown,
  /*! YUV planar format. */
  MLCameraOutputFormat_YUV_420_888,
  /*! Compressed output stream. */
  MLCameraOutputFormat_JPEG,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraOutputFormat_Ensure32Bits = 0x7FFFFFFF
} MLCameraOutputFormat;

/*!
  \brief Per plane info for captured output.
*/
typedef struct MLCameraPlaneInfo {
  /*! Width of the output image in pixels. */
  uint32_t width;
  /*! Height of the output image in pixels. */
  uint32_t height;
  /*! Stride of the output image in bytes. */
  uint32_t stride;
  /*! Number of bytes used to represent a pixel. */
  uint32_t bytes_per_pixel;
  /*! Image data. */
  uint8_t  *data;
  /*! Number of bytes in the image output data. */
  uint32_t size;
} MLCameraPlaneInfo;

/*! Number of planes representing the image color space. */
enum {
  MLCamera_MaxImagePlanes = 3
};

/*!
  \brief Captured output.
*/
typedef struct MLCameraOutput {
  /*!
    \brief Number of output image planes:
    1 for compressed output such as JPEG stream,
    3 for separate color component output such as YUV/YCbCr/RGB.
  */
  uint8_t plane_count;
  /*! Output image plane info. The number of output planes is specified by plane_count. */
  MLCameraPlaneInfo planes[MLCamera_MaxImagePlanes];
  /*! Supported output format specified by MLCameraOutputFormat. */
  MLCameraOutputFormat format;
} MLCameraOutput;

/*!
  \brief Capture operation type.
*/
typedef enum MLCameraCaptureType {
  /*! To capture an image and save the JPEG-compressed data to a file. */
  MLCameraCaptureType_Image = 0,
  /*! To capture an image and obtain the JPEG-compressed stream. */
  MLCameraCaptureType_ImageRaw,
  /*! To capture a video and save it to a file. */
  MLCameraCaptureType_Video,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraCaptureType_Ensure32Bits = 0x7FFFFFFF
} MLCameraCaptureType;

/*!
  \brief ResultExtras is a structure to encapsulate various indices for a capture result.
*/
typedef struct MLCameraResultExtras {
  /*! An integer to index the request sequence that this result belongs to. */
  int32_t request_id;
  /*! An integer to index this result inside a request sequence, starting from 0. */
  int32_t burst_id;
  /*! A 64bit integer to index the frame number associated with this result. */
  int64_t frame_number;
  /*! The partial result count (index) for this capture result. */
  int32_t partial_result_count;
  /*! VCam exposure timestamp in microseconds (us). */
  uint64_t vcam_timestamp_us;
} MLCameraResultExtras;

/*!
  \brief Device status callbacks to be implemented by client to receive device
  status if callback mechanism is used.
*/
typedef struct MLCameraDeviceStatusCallbacks {
  /*! Camera available. */
  void (*on_device_available)(void *data);
  /*! Camera not available. */
  void (*on_device_unavailable)(void *data);
  /*! Camera opened. */
  void (*on_device_opened)(void *data);
  /*! Camera closed. */
  void (*on_device_closed)(void *data);
  /*! Camera disconnected. */
  void (*on_device_disconnected)(void *data);
  /*! Camera encountered an error. */
  void (*on_device_error)(MLCameraError error, void *data);
  /*! Preview stream is available via output. */
  void (*on_preview_buffer_available)(MLHandle output, void *data);
} MLCameraDeviceStatusCallbacks;

/*!
  \brief Capture callbacks to be implemented by client to receive capture
  status if callback mechanism is used.
*/
typedef struct MLCameraCaptureCallbacks {
  /*! Capture started. */
  void (*on_capture_started)(const MLCameraResultExtras *extra, void *data);
  /*! Capture failed. */
  void (*on_capture_failed)(const MLCameraResultExtras *extra, void *data);
  /*! Captured buffer lost. */
  void (*on_capture_buffer_lost)(const MLCameraResultExtras *extra, void *data);
  /*! Capture is in progress. */
  void (*on_capture_progressed)(MLHandle metadata_handle, const MLCameraResultExtras *extra, void *data);
  /*! Capture completed. */
  void (*on_capture_completed)(MLHandle metadata_handle, const MLCameraResultExtras *extra, void *data);
  /*! Capture is completed. Output stream is available via output. */
  void (*on_image_buffer_available)(const MLCameraOutput *output, void *data);
} MLCameraCaptureCallbacks;

/*!
  \brief Client can implement polling mechanism to retrieve device status
  and use these masks to view device status.
*/
typedef enum MLCameraDeviceStatusFlag {
  MLCameraDeviceStatusFlag_Available     = 1 << 0,
  MLCameraDeviceStatusFlag_Opened        = 1 << 1,
  MLCameraDeviceStatusFlag_Disconnected  = 1 << 2,
  MLCameraDeviceStatusFlag_Error         = 1 << 3,
} MLCameraDeviceStatusFlag;

/*!
  \brief Client can implement polling mechanism to retrieve capture status
  and use these masks to view capture status.
*/
typedef enum MLCameraCaptureStatusFlag {
  MLCameraCaptureStatusFlag_Started      = 1 << 0,
  MLCameraCaptureStatusFlag_Failed       = 1 << 1,
  MLCameraCaptureStatusFlag_BufferLost   = 1 << 2,
  MLCameraCaptureStatusFlag_InProgress   = 1 << 3,
  MLCameraCaptureStatusFlag_Completed    = 1 << 4,
} MLCameraCaptureStatusFlag;

/*!
  \brief Connect to camera device.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraConnect();

/*!
  \brief Disconnect from camera device.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraDisconnect();

/*!
  \brief Prepare for capture.

  This API prepares for capture per specified #MLCameraCaptureType by creating
  a capture request, and a handle to which is returned to the user, who can choose
  to manipulate the request data(metadata) via APIs defined in ml_camera_metadata.h
  before performing the capture.

  Shall be called after MLCameraConnect().

 \param[in] type Capture operation type.
  \return true if operation succeeded and \c false otherwise.
*/
ML_API MLHandle ML_CALL MLCameraPrepareCapture(MLCameraCaptureType type);

/*!
  \brief Set the client-implemented callbacks to convey camera device status.

  Client needs to implement the callbacks defined by #MLCameraDeviceStatusCallbacks.
  The library passes the camera device status to the client via those callbacks.

  Shall be called before MLCameraConnect().

  \param[in] device_status_callbacks Camera device status callbacks.
  \param[in] data User metadata.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraSetDeviceStatusCallbacks(MLCameraDeviceStatusCallbacks *device_status_callbacks, void *data);

 /*!
  \brief Set the client-implemented callbacks to convey capture status.

  Client needs to implement the callbacks defined by #MLCameraCaptureCallbacks.
  The library passes the capture status to the client via those callbacks.

  Shall be called before capture operation for preview/image/video.

  \param[in] capture_callbacks Capture status callbacks.
  \param[in] data User metadata.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraSetCaptureCallbacks(MLCameraCaptureCallbacks *capture_callbacks, void *data);

/*!
  \brief Capture still image.

  The output image will be stored in a compressed format (i.e., jpeg)
  into the file specified by the file path. The library is responsible
  for opening and closing the file.

  \param[in] path File path to store the output image.
  \return \c true if image capture operation started successfully and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraCaptureImage(const char *path);

/*!
  \brief Capture raw image.

  The output is the raw JPEG stream, which is passed to client via
  on_image_buffer_available. Client can also choose to implement polling
  mechanism and obtain the stream by MLCameraPollImageStream().

  \return \c true if image capture operation started successfully and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraCaptureImageRaw();

/*!
  \brief Start video capture.

  The output video will be stored in a compressed format (i.e., mp4)
  into the file specified by the file path. The library is responsible
  for opening and closing the file. The current supported
  video resolution is 1080p.

  MLCameraCaptureVideoStop() needs to be called to stop the capture.

  \param[in] path File path to store the output video.
  \return \c true if video capture operation started successfully and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraCaptureVideoStart(const char *path);

/*!
  \brief Stop video capture.
  \return \c true if video capture operation stopped successfully and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraCaptureVideoStop();

/*!
  \brief Poll camera device status.

  Use #MLCameraDeviceStatusFlag to view specific status bit.
  Call MLCameraGetErrorCode() to obtain the error code if
  #MLCameraDeviceStatusFlag_Error bit is set.

  Note: This API can still be used even if MLCameraSetDeviceStatusCallbacks() has been called.

  \param[out] out_device_status Device status.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraGetDeviceStatus(uint32_t *out_device_status);

/*!
  \brief Poll capture status.

  Use #MLCameraCaptureStatusFlag to view specific status bit.
  Call MLCameraGetErrorCode() to obtain the error code if
  #MLCameraCaptureStatusFlag_Error bit is set.

  Note: This API can still be used even if MLCameraSetCaptureStatusCallbacks() has been called.

  \param[out] out_capture_status Capture status.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraGetCaptureStatus(uint32_t *out_capture_status);

/*!
  \brief Obtain device error code.
  \param[out] out_error_code Device error code.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraGetErrorCode(MLCameraError *out_error_code);

/*!
  \brief Poll preview stream.

  The preview stream and image stream are separate streams. The preview data is
  available upon MLCameraConnect(), and will always be available; whereas the image stream
  is produced when the user captures images.
  The library allocates the buffer and destroys it when disconnecting from the camera.

  Note: This API can still be used even if MLCameraSetDeviceStatusCallbacks() has been called.

  \param[out] out_preview Preview stream.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraGetPreviewStream(MLHandle *out_preview);

/*!
  \brief Poll raw image stream.

  The library allocates the buffer and destroys it when disconnecting from the camera.

  Note: This API can still be used even if MLCameraSetCaptureStatusCallbacks() has been called.

  \param[out] out_image Raw image stream.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraGetImageStream(MLCameraOutput **out_image);

/*!
  \brief Poll capture result extras data.

  The library allocates the buffer and destroys it when disconnecting from the camera.

  Note: This API can still be used even if MLCameraSetCaptureStatusCallbacks() has been called.

  \param[out] out_result_extras Capture result extras data.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraGetCaptureResultExtras(MLCameraResultExtras **out_result_extras);

/*!
  \brief Obtain handle for retrieving camera characteristics.

  This API provides the handle for retrieving camera characteristics via APIs
  defined in ml_camera_metadata.h.

  \return the handle to be used to retrieve camera characteristics.
*/
ML_API MLHandle ML_CALL MLCameraGetCameraCharacteristics();

/*!
  \brief Obtains handle for retrieving capture result metadata

  This API provides the handle for retrieving capture result metadata via APIs
  defined in ml_camera_metadata.h.

  Note: that this handle is also available via callbacks if capture callbacks has been set.

  \return the handle to be used to retrieve capture result metadata.
*/
ML_API MLHandle ML_CALL MLCameraGetResultMetadata();

ML_EXTERN_C_END
