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
// agreements explicitly covering such access.configure
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
#include "ml_camera_metadata_tags.h"

ML_EXTERN_C_BEGIN

/*!
  \brief This header file contains APIs for getting/setting camera
         characteristic/request/result metadata.
*/

/*!
  \brief Rational data type.
*/
typedef struct MLCameraMetadataRational {
  int32_t numerator;
  int32_t denominator;
} MLCameraMetadataRational;

/*!
  \brief Get color correction aberration modes.
  \param[in] handle Camera characteristic metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data Array of aberration modes.
              The Library allocates and maintains the lifetime of the output data.
  \param[out] out_count Number of output data elements.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetColorCorrectionAvailableAberrationModes(MLHandle handle, MLCameraMetadataColorCorrectionAberrationMode **out_data, size_t *out_count);

/*!
  \brief Get AE modes.
  \param[in] handle Camera characteristic metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data Array of AE modes.
              The Library allocates and maintains the lifetime of the output data.
  \param[out] out_count Number of output data elements.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetControlAEAvailableModes(MLHandle handle, MLCameraMetadataControlAEMode **out_data, size_t *out_count);

/*!
  \brief Get AE compensation range.
  \param[in] handle Camera characteristic metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data Array of min (1st) and max (2nd) of AE compensation.
              The Library allocates and maintains the lifetime of the output data.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetControlAECompensationRange(MLHandle handle, int32_t (**out_data)[2]);

/*!
  \brief Get AE compensation step.
  \param[in] handle Camera characteristic metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data AE compensation step.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetControlAECompensationStep(MLHandle handle, MLCameraMetadataRational *out_data);

/*!
  \brief Get AE lock.
  \param[in] handle Camera characteristic metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data AE lock.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetControlAELockAvailable(MLHandle handle, MLCameraMetadataControlAELockAvailable *out_data);

/*!
  \brief Get AWB modes.
  \param[in] handle Camera characteristic metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data Array of AWB modes.
              The Library allocates and maintains the lifetime of the output data.
  \param[out] out_count Number of output data elements.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetControlAWBAvailableModes(MLHandle handle, MLCameraMetadataControlAWBMode **out_data, size_t *out_count);

/*!
  \brief Get AWB lock.
  \param[in] handle Camera characteristic metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data AWB lock.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetControlAWBLockAvailable(MLHandle handle, MLCameraMetadataControlAWBLockAvailable *out_data);

/*!
  \brief Get scaler processed sizes list
  \param[in] handle Camera characteristic metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data List of [width, height] pairs.
              The Library allocates and maintains the lifetime of the output data.
  \param[out] out_count Number of output data elements.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetScalerProcessedSizes(MLHandle handle, int32_t **out_data, size_t *out_count);

/*!
  \brief Get scaler available max digital zoom.
  \param[in] handle Camera characteristic metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data Max digital zoom.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetScalerAvailableMaxDigitalZoom(MLHandle handle, float *out_data);

/*!
  \brief Get scaler available stream configrations.
  \param[in] handle Camera characteristic metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data List of stream configuration settings.
              Each element is consisted of [format, width, height, #MLCameraMetadataScalerAvailableStreamConfigurations].
              The Library allocates and maintains the lifetime of the output data.
  \param[out] out_count Number of output data elements.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetScalerAvailableStreamConfigurations(MLHandle handle, int32_t **out_data, size_t *out_count);

/*!
  \brief Get sensor info active array sizes.
  \param[in] handle Camera characteristic metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data Active array size [left, top, right, bottom].
              The Library allocates and maintains the lifetime of the output data.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetSensorInfoActiveArraySize(MLHandle handle, int32_t (**out_data)[4]);

/*!
  \brief Get sensor info sensitivity range.
  \param[in] handle Camera characteristic metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data Sensor info sensitivity range[min, max].
              The Library allocates and maintains the lifetime of the output data.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetSensorInfoSensitivityRange(MLHandle handle, int32_t (**out_data)[2]);

/*!
  \brief Get sensor info exposure time range.
  \param[in] handle Camera characteristic metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data Sensor info exposure time range[min, max] in microseconds.
              The Library allocates and maintains the lifetime of the output data.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetSensorInfoExposureTimeRange(MLHandle handle, int64_t (**out_data)[2]);

/*!
  \brief Get sensor orientation degree.
  \param[in] handle Camera characteristic metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data Sensor orientation degree.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetSensorOrientation(MLHandle handle, int32_t *out_data);

/*!
  \brief Set sensor info exposure time range. Only max time will be set currently.
  \param[in] handle Camera characteristic metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] data Sensor info exposure time range[min, max] in microseconds.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataSetSensorInfoExposureTimeRange(MLHandle handle, const int64_t data[2]);

/*!
  \brief Get color correction mode.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data Color correction mode.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetColorCorrectionModeRequestMetadata(MLHandle handle, MLCameraMetadataColorCorrectionMode *out_data);

/*!
\brief Get color correction transform.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data 3x3 color correction transform.
              The Library allocates and maintains the lifetime of the output data.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetColorCorrectionTransformRequestMetadata(MLHandle handle, MLCameraMetadataRational (**out_data)[3][3]);

/*!
  \brief Get color correction gains.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data Color correction gains.
              The Library allocates and maintains the lifetime of the output data.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetColorCorrectionGainsRequestMetadata(MLHandle handle, float (**out_data)[4]);

/*!
  \brief Get color correction aberration.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data Color correction aberration.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetColorCorrectionAberrationModeRequestMetadata(MLHandle handle, MLCameraMetadataColorCorrectionAberrationMode *out_data);

/*!
  \brief Get AE antibanding mode.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data AE antibanding mode.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetControlAEAntibandingModeRequestMetadata(MLHandle handle, MLCameraMetadataControlAEAntibandingMode *out_data);

/*!
  \brief Get AE exposure compensation.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data Exposure compensation value.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetControlAEExposureCompensationRequestMetadata(MLHandle handle, int32_t *out_data);

/*!
  \brief Get AE lock.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data AE Lock.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetControlAELockRequestMetadata(MLHandle handle, MLCameraMetadataControlAELock *out_data);

/*!
  \brief Get AE mode.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data AE Lock.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetControlAEModeRequestMetadata(MLHandle handle, MLCameraMetadataControlAEMode *out_data);

/*!
  \brief Get AE target FPS range.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data AE target FPS range.
              The Library allocates and maintains the lifetime of the output data.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetControlAETargetFPSRangeRequestMetadata(MLHandle handle, int32_t (**out_data)[2]);

/*!
  \brief Get AWB lock.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data AWB Lock.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetControlAWBLockRequestMetadata(MLHandle handle, MLCameraMetadataControlAWBLock *out_data);

/*!
  \brief Get AWB mode.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data AWB mode.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetControlAWBModeRequestMetadata(MLHandle handle, MLCameraMetadataControlAWBMode *out_data);

/*!
  \brief Get sensor exposure time.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data Sensor exposure time.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetSensorExposureTimeRequestMetadata(MLHandle handle, int64_t *out_data);

/*!
  \brief Get sensor sensitivity.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data Sensor sensitivity.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetSensorSensitivityRequestMetadata(MLHandle handle, int32_t *out_data);

/*!
  \brief Get scaler crop region.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data Cropped region [left, top, right, bottom].
              The Library allocates and maintains the lifetime of the output data.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetScalerCropRegionRequestMetadata(MLHandle handle, int32_t (**out_data)[4]);

/*!
  \brief Set color correction mode.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] data Color correction mode.
              Null pointer will clear the data.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataSetColorCorrectionMode(MLHandle handle, const MLCameraMetadataColorCorrectionMode *data);

/*!
  \brief Set color correction transform.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] data 3x3 color correction transform.
              Null pointer will clear the data.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataSetColorCorrectionTransform(MLHandle handle, const MLCameraMetadataRational (*data)[3][3]);

/*!
  \brief Set color correction gains.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] data Color correction gains.
              Null pointer will clear the data.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataSetColorCorrectionGains(MLHandle handle, const float data[4]);

/*!
  \brief Set color correction aberration.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] data Color correction aberration.
              Null pointer will clear the data.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataSetColorCorrectionAberrationMode(MLHandle handle, const MLCameraMetadataColorCorrectionAberrationMode *data);

/*!
  \brief Set AE antiband mode.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] data AE antibanding mode.
              Null pointer will clear the data.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataSetControlAEAntibandingMode(MLHandle handle, const MLCameraMetadataControlAEAntibandingMode *data);

/*!
  \brief Set AE exposure compensation.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] data Exposure compensation value.
              Null pointer will clear the data.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataSetControlAEExposureCompensation(MLHandle handle, const int32_t *data);

/*!
  \brief Set AE lock.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] data AE Lock.
              Null pointer will clear the data.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataSetControlAELock(MLHandle handle, const MLCameraMetadataControlAELock *data);

/*!
  \brief Set AE mode.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] data AE Mode.
              Null pointer will clear the data.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataSetControlAEMode(MLHandle handle, const MLCameraMetadataControlAEMode *data);

/*!
  \brief Set AE target FPS range.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] data AE target FPS range.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataSetControlAETargetFPSRange(MLHandle handle, const int32_t data[2]);

/*!
  \brief Set AWB lock.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] data AWB Lock.
              Null pointer will clear the data.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataSetControlAWBLock(MLHandle handle, const MLCameraMetadataControlAWBLock *data);

/*!
  \brief Set AWB mode.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] data AWB mode.
              Null pointer will clear the data.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataSetControlAWBMode(MLHandle handle, const MLCameraMetadataControlAWBMode *data);

/*!
  \brief Set sensor exposure time.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] data Sensor exposure time.
              Null pointer will clear the data.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataSetSensorExposureTime(MLHandle handle, const int64_t *data);

/*!
  \brief Set sensor sensitivity.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] data Sensor sensitivity.
              Null pointer will clear the data.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataSetSensorSensitivity(MLHandle handle, const int32_t *data);

/*!
  \brief Set scaler crop region.
  \param[in] handle Camera request metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] data Cropped region [left, top, right, bottom].
              Null pointer will clear the data.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataSetScalerCropRegion(MLHandle handle, const int32_t data[4]);

/*!
  \brief Get color correction.
  \param[in] handle Camera result metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data Color correction mode.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetColorCorrectionModeResultMetadata(MLHandle handle, MLCameraMetadataColorCorrectionMode *out_data);

/*!
  \brief Get color correction transform.
  \param[in] handle Camera result metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data 3x3 color correction transform matrix.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetColorCorrectionTransformResultMetadata(MLHandle handle, MLCameraMetadataRational (**out_data)[3][3]);

/*!
  \brief Get color correction aberration.
  \param[in] handle Camera result metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data Color correction aberration mode.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetColorCorrectionAberrationModeResultMetadata(MLHandle handle, MLCameraMetadataColorCorrectionAberrationMode *out_data);

/*!
  \brief Get color correction gains.
  \param[in] handle Camera result metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data Color correction gains.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetColorCorrectionGainsResultMetadata(MLHandle handle, float (**out_data)[4]);

/*!
  \brief Get AE antibanding mode.
  \param[in] handle Camera result metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data AE antibanding mode.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetControlAEAntibandingModeResultMetadata(MLHandle handle, MLCameraMetadataControlAEAntibandingMode *out_data);

/*!
  \brief Get AE exposure compensation.
  \param[in] handle Camera result metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data AE exposure compensation.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetControlAEExposureCompensationResultMetadata(MLHandle handle, int32_t *out_data);

/*!
  \brief Get AE lock.
  \param[in] handle Camera result metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data AE lock.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetControlAELockResultMetadata(MLHandle handle, MLCameraMetadataControlAELock *out_data);

/*!
  \brief Get AE mode.
  \param[in] handle Camera result metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data AE control mode.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetControlAEModeResultMetadata(MLHandle handle, MLCameraMetadataControlAEMode *out_data);

/*!
  \brief Get AE target FPS range.
  \param[in] handle Camera result metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data AE target FPS range.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetControlAETargetFPSRangeResultMetadata(MLHandle handle, int32_t (**out_data)[2]);

/*!
  \brief Get AE state.
  \param[in] handle Camera result metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data AE state.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetControlAEStateResultMetadata(MLHandle handle, MLCameraMetadataControlAEState *out_data);

/*!
  \brief Get AWB lock.
  \param[in] handle Camera result metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data AWB Lock.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetControlAWBLockResultMetadata(MLHandle handle, MLCameraMetadataControlAWBLockAvailable *out_data);

/*!
  \brief Get AWB state.
  \param[in] handle Camera result metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data AWB state.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetControlAWBStateResultMetadata(MLHandle handle, MLCameraMetadataControlAWBState *out_data);

/*!
  \brief Get sensor exposure time.
  \param[in] handle Camera result metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data Sensor exposure time.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetSensorExposureTimeResultMetadata(MLHandle handle, int64_t *out_data);

/*!
  \brief Get sensor sensitivity.
  \param[in] handle Camera result metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data Sensor sensitivity.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetSensorSensitivityResultMetadata(MLHandle handle, int32_t *out_data);

/*!
  \brief Get frame captured timestamp.
  \param[in] handle Camera result metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data Timestamp in nanoseconds when captured.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetSensorTimestampResultMetadata(MLHandle handle, int64_t *out_data);

/*!
  \brief Get scaler crop region.
  \param[in] handle Camera result metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data Cropped region [left, top, right, bottom].
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetScalerCropRegionResultMetadata(MLHandle handle, int32_t (**out_data)[4]);

/*!
  \brief Get sensor frame duration.
  \param[in] handle Camera result metadata handle acquired from
             #MLCameraGetCameraCharacteristics.
  \param[out] out_data Sensor frame duration.
  \return \c true if operation succeeded and \c false otherwise.
*/
ML_API bool ML_CALL MLCameraMetadataGetSensorFrameDurationResultMetadata(MLHandle handle, int64_t *out_data);

ML_EXTERN_C_END
