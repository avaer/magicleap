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

/*! Handle to a homogenous array of data retrievable via MLDataArrayTryLock(). */
typedef uint64_t MLDataArrayHandle;

/*! Result of a lock operation on a data array via MLDataArrayTryLock(). */
typedef enum MLDataArrayLockResult {
  /*! New data is available. When this data has been processed MLDataArrayUnlock() must be called. */
  MLDataArrayLockResult_New,
  /*! The data has not changed based on the #MLDataArrayDiff passed in.
      The #MLDataArray will not be populated, and there is no need to unlock. */
  MLDataArrayLockResult_Unchanged,
  /*! The data has been locked by another thread. */
  MLDataArrayLockResult_Locked,
  /*! There was an internal error when processing this request. */
  MLDataArrayLockResult_Error,
  /*! Ensure enum is represented as 32 bits. */
  MLDataArrayLockResult_Ensure32Bits = 0x7FFFFFFF
} MLDataArrayLockResult;

/*! Information about the data contained inside of a data array. */
typedef enum MLDataArrayType {
  /*! No data is contained. */
  MLDataArrayType_None,
  /*! Data is XYZ floats. Use the .xyz member of the data array. */
  MLDataArrayType_XYZ,
  /*! Data is an array of handles to other data arrays. Use the .handle member of the data array. */
  MLDataArrayType_Handle,
  /*! Data is an array of uint32_t data. */
  MLDataArrayType_UInt,
  /*! Data is an array of float data. */
  MLDataArrayType_Float,
  /*! Data is in a custom format. Use .custom to get a void* pointer. */
  MLDataArrayType_Custom,
  /*! Ensure enum is represented as 32 bits. */
  MLDataArrayType_Ensure32Bits = 0x7FFFFFFF
} MLDataArrayType;

/*! Internal data blob size for #DataArrayDiff. */
enum {
  MLDataArrayDiff_BlobSize = 32
};

/*!
  \brief In/Out parameter to understand whether the data array has changed since the
  last time it was queried.
*/
typedef struct MLDataArrayDiff {
  /*!
    \brief A blob of data which is used internally to keep track of
    whether changes occurred. This data must be initialized with MLDataArrayInitDiff().
  */
  uint8_t blob[MLDataArrayDiff_BlobSize];
} MLDataArrayDiff;

/*! Maximum number of streams allowed in a data array. */
enum {
  MLDataArray_MaxStreamCount = 8,
};

/*! Index to refer to an invalid stream reference. */
enum {
  MLDataArray_InvalidStreamIndex = 0xFFFFFFFFu,
};

/*! Defines the characteristics (type, size, count) of the block of data of a #MLDataArray. */
typedef struct MLDataArrayStream {
  /*! The type of data held inside of this array. */
  MLDataArrayType type;
  /*! Number of items contained in the data array. */
  uint32_t count;
  /*! Size of each item in this array. */
  uint32_t data_size;
  /*! Reserved field. */
  uint32_t reserved;

  union {
    /*! Data if type is MLDataArrayType_XYZ. */
    MLVec3f *xyz_array;
    /*! Data if type is MLDataArrayType_Handle. */
    MLDataArrayHandle *handle_array;
    /*! Data if type is MLDataArrayType_UInt. */
    uint32_t *uint_array;
    /*! Data if type is MLDataArrayType_Float. */
    float *float_array;
    /*! Data if type is MLDataArrayType_Custom. */
    void *custom_array;
    /*! This ensures that the size of the union remains 8 bytes even on 32-bit platforms. */
    uint64_t ensure_64_bits;
  };
} MLDataArrayStream;

/*! Homogeneous data which can be retrieved via MLDataArrayTryLock(). */
typedef struct MLDataArray {
  /*! When (in nanoseconds) this object has been last updated. */
  uint64_t timestamp;
  /*! Number of items in the streams list. */
  uint32_t stream_count;
  /*! Reserved field. */
  uint32_t reserved;
  /*! Array of stream_count data streams containing the data held in this array. */
  MLDataArrayStream streams[MLDataArray_MaxStreamCount];
} MLDataArray;

/*!
  \brief Initialize the #MLDataArrayDiff struct.
  \param[out] out_diff the #MLDataArrayDiff struct to be initialized.
*/
ML_API void ML_CALL MLDataArrayInitDiff(MLDataArrayDiff *out_diff);

/*!
  \brief Request that a data array is locked for reading.
  \param[in] data_array The handle to the data to query.
  \param[out] out_data Out parameter which contains the data retrieved if successful.
  \param[in,out] in_out_diff Optional in/out parameter to prevent data from being retrieved
                 if it hasn't changed since a previous change.
  \return MLDataArrayLockResult_New if data is available, otherwise an error code.
*/
ML_API MLDataArrayLockResult ML_CALL MLDataArrayTryLock(MLDataArrayHandle data_array, MLDataArray *out_data, MLDataArrayDiff *in_out_diff);

/*!
  \brief Unlock a data array previously locked via MLDataArrayTryLock().

  This function must be called if MLDataArrayTryLock() returned MLDataArrayLockResult_New.
  Data should be locked for as short of a time as possible because it will block
  new data from being updated/processed.

  \param[in] data_array The handle which was used to lock this data.
*/
ML_API void ML_CALL MLDataArrayUnlock(MLDataArrayHandle data_array);

ML_EXTERN_C_END
