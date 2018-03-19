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
#include "ml_invoke_async.h"

ML_EXTERN_C_BEGIN

/*!
  \addtogroup Identity
  \brief APIs for the Identity system.

  - The Identity system is for identity.
  @{
*/

/*!
  \brief #MLIdentityAttributeEnum identifies an attribute in a user profile.
  Attributes that were not known at the time the library was built, are marked as
  #MLIdentityAttributeEnum_Unknown
*/
typedef enum MLIdentityAttributeEnum {
  /*! User Id */
  MLIdentityAttributeEnum_UserId,
  /*! Given name. */
  MLIdentityAttributeEnum_GivenName,
  /*! Family name. */
  MLIdentityAttributeEnum_FamilyName,
  /*! Email. */
  MLIdentityAttributeEnum_Email,
  /*! Status. */
  MLIdentityAttributeEnum_Status,
  /*! Terms accepted. */
  MLIdentityAttributeEnum_TermsAccepted,
  /*! Birthday. */
  MLIdentityAttributeEnum_Birthday,
  /*! Company. */
  MLIdentityAttributeEnum_Company,
  /*! Industry. */
  MLIdentityAttributeEnum_Industry,
  /*! Location. */
  MLIdentityAttributeEnum_Location,
  /*! Tagline. */
  MLIdentityAttributeEnum_Tagline,
  /*! Phone number. */
  MLIdentityAttributeEnum_PhoneNumber,
  /*! 2D avatar. */
  MLIdentityAttributeEnum_Avatar2D,
  /*! 3D avatar. */
  MLIdentityAttributeEnum_Avatar3D,
  /*! Is developer. */
  MLIdentityAttributeEnum_IsDeveloper,
  /*! Unknown. */
  MLIdentityAttributeEnum_Unknown,
  /*! Ensure enum is represented as 32 bits. */
  MLIdentityAttributeEnum_Ensure32Bits = 0x7FFFFFFF
} MLIdentityAttributeEnum;

/*!
  \brief #MLIdentityAttribute represents an attribute of a user's profile
  (for instance: name, address, email). Each attribute has a name (represented by key and value).
*/
typedef struct MLIdentityAttribute {
  MLIdentityAttributeEnum enum_value;
  const char *name;
  const char *value;
  bool is_requested;
  bool is_granted;
} MLIdentityAttribute;

/*!
  \brief #MLIdentityProfile represents a set of attribute of a user's profile.
*/
typedef struct MLIdentityProfile {
  /*! attribute_count is the number of #MLIdentityAttribute structures pointed
      to by attribute_ptrs. */
  uint32_t attribute_count;
  /*! attribute_ptrs is an array of #MLIdentityAttributes containing user profile
      information */
  MLIdentityAttribute *const *attribute_ptrs;
} MLIdentityProfile;

/*!
  \brief #MLIdentityError is the return type of some of the Identity functions.
*/
typedef enum MLIdentityError {
  /*! The call returned with no error and returned a pointer to a #MLIdentityProfile. */
  MLIdentityError_Ok,
  /*! The local service is not running, or it cannot be accessed. */
  MLIdentityError_FailedToConnectToLocalService,
  /*!
    \brief The service failed to access the cloud service.
    Either there is no IP connection or the cloud service is not available.
  */
  MLIdentityError_FailedToConnectToCloudService,
  /*!
    \brief The user does not have the required privileges to use the requesting service
    or the refresh token used by the service is invalid.
  */
  MLIdentityError_CloudAuthentication,
  /*!
    \brief Signature verification failed on the information returned by the cloud or a
    parsing error occurred.
  */
  MLIdentityError_InvalidInformationFromCloud,
  /*! A pointer passed to a function was 0 or did not conform with other usage requirements. */
  MLIdentityError_InvalidArgument,
  /*! A polling function returned false because the asynchronous operation has not completed. */
  MLIdentityError_AsyncOperationNotComplete,
  /*! An error not described by other values occurred. */
  MLIdentityError_OtherError,
  /*! The operation failed because the user is not logged in to the cloud. */
  MLIdentityError_NotLoggedIn,
  /*! The user's credentials have expired. */
  MLIdentityError_ExpiredCredentials,
  /*! Failed to retrieve attributes of the user's profile. */
  MLIdentityError_FailedToGetUserProfile,
  /*! The cloud rejected the operation because the user is not authorized to execute it. */
  MLIdentityError_Unauthorized,
  /*! The device failed to authenticate the server. */
  MLIdentityError_CertificateError,
  /*! The cloud rejected the operation. */
  MLIdentityError_RejectedByCloud,
  /*! The user is already logged in. */
  MLIdentityError_AlreadyLoggedIn,
  /*! The cloud does not support modification of an attribute value. */
  MLIdentityError_ModifyIsNotSupported,
  /*! The device is not connected to a network. */
  MLIdentityError_NetworkError,
  /*! Ensure enum is represented as 32 bits. */
  MLIdentityError_Ensure32Bits = 0x7FFFFFFF
} MLIdentityError;

/*!
  \brief MLIdentityGetAttributeNames() is a blocking function that access the cloud and
  returns a #MLIdentityProfile structure containing all of the attributes that are available
  for the Audience of the calling service. It does not request access to them from the user.

  The library deduces the Audience being requested from the name of the calling service.
  This method does not request access to the values of the attributes from the user and does
  not return the values of these attributes. Only the names are provided.
  In order to request access for the attributes values and to receive them, set the
  is_requested field of each required attribute in the profile that is returned and call
  one of the methods: MLIdentityRequestAttributeValues() or MLIdentityRequestAttributeValuesAsync().

  \param[out] out_profile
  \parblock
  A pointer to a #MLIdentityProfile pointer that is allocated by the library.
  In each attribute of the returned profile the name field will point to the name of the
  attribute, the value field will point to an empty string and the is_requested and is_granted
  flags will both be \c false.

  The returned profile structure must not be modified by the caller except to set the
  is_requested field. (See MLIdentityRequestAttributeValues())
  The returned profile must be released when no longer needed by calling MLIdentityReleaseUserProfile().
  \endparblock
  \return #MLIdentityError: See description above.
*/

ML_API MLIdentityError ML_CALL MLIdentityGetAttributeNames(MLIdentityProfile **out_profile);

/*!
  \brief MLIdentityGetKnownAttributeNames() returns a #MLIdentityProfile structure containing
  attributes of a user's profile whose names are specified in the attributeNames array.

  Each element of the attributeNames array may only be one of the values specified above.
  This method does not access the cloud to discover which attribute names are actually
  available for the calling service, does not request access to the values of these
  attributes for the service by the user, and does not return the values of these attributes.
  In order to request access for the attributes and to receive their values, pass the profile
  that is returned by MLIdentityGetKnownAttributeNames() to one of the methods:
  MLIdentityRequestAttributeValues() or MLIdentityRequestAttributeValuesAsync().

  \param[in] enum_values is an array of distinct #MLIdentityAttributeEnum values that
             are not equal #to MLIdentityAttributeEnum_Unknown.
  \param[in] enum_value_count is the number of elements in the #MLIdentityAttributeEnum array.
  \param[out] out_profile
  \parblock
  A pointer to #MLIdentityProfile pointer which will be allocated by the library.
  The returned profile will contain an array of #MLIdentityAttribute structures such that the
  enumValue of each attribute is contained in enum_values.

  If the attribute specified by any of the enum_values is not available a corresponding
  MLIdentityAttribute will not appear in the #MLIdentityProfile.
  Not available in this context means that the user profile does not contain the attribute,
  not that the caller does not have permission to access its value.

  All attributes in the returned profile will have their is_requested field set to true and
  their is_granted field to false. The values of the attributes will point to empty strings.
  The returned profile must be released using #MLIdentityReleaseUserProfile when no longer needed.
  \endparblock
  \return #MLIdentityError: See description above.
*/
ML_API MLIdentityError ML_CALL MLIdentityGetKnownAttributeNames(const MLIdentityAttributeEnum *enum_values, uint32_t enum_value_count, MLIdentityProfile **out_profile);

/*!
  \brief MLIdentityGetAttributeNamesAsync() invokes the MLIdentityGetAttributeNames()
  function asynchronously (in a different thread).

  Note: This pointer will be freed by the library before returning from the first (and last)
  call to MLIdentityGetAttributeNamesWait(), after the asynchronous call completed.

  \return A pointer to an #MLInvokeFuture which provides the means to poll for completion and
          to retrieve the profile returned by MLIdentityGetAttributeNames().
*/
ML_API MLInvokeFuture *ML_CALL MLIdentityGetAttributeNamesAsync();

/*!
  \brief Having made a call to MLIdentityGetAttributeNamesAsync(), the user can call
  MLIdentityGetAttributeNamesWait() to detect whether the asynchronous call completed and if
  so, to retrieve the profile in out_profile.

  The call to MLIdentityGetAttributeNamesWait() blocks until either msec_timeout msec elapses or the asynchronous function completes.

  Note:
  1. To poll without blocking use msec_timeout = 0.
  2. After the function returns \c true, future is freed by the library and must not be used again in
     a call to MLIdentityGetAttributeNamesWait().

  \param[in,out] future The pointer returned by the MLIdentityGetAttributeNamesAsync() function.
  \param[in] msec_timeout The timeout in milliseconds.
  \param[out] out_ret_val The location in memory where the return value of
              MLIdentityGetAttributeNames() will be copied, if the asynchronous call completed,
              or #MLIdentityError_AsyncOperationNotComplete if not.
  \param[out] out_profile The location in memory where the pointer to the profile structure allocated by
              the library will be copied, if the asynchronous call completed, or 0 (null) if not.
  \return If the timeout elapsed before the asynchronous call completed, MLIdentityGetAttributeNamesWait()
          will return \c false and out_profile will be set to 0 (null). If the asynchronous
          call completed before the timeout elapsed, the function will return \c true and
          out_profile will be set to the address of the #MLIdentityProfile structure allocated
          by the library. The returned profile must be released when no longer needed by
          calling MLIdentityReleaseUserProfile().
*/
ML_API bool ML_CALL MLIdentityGetAttributeNamesWait(MLInvokeFuture *future, uint32_t msec_timeout, MLIdentityError *out_ret_val, MLIdentityProfile **out_profile);

/*!
  \brief MLIdentityRequestAttributeValues() is a blocking function that accesses the cloud
  and requests permission from the user in order to fill the attribute values that are marked as
  requested in the #MLIdentityProfile pointed to by the profile argument.

  Note: If any (even all) of the attributes passed in have is_requested set to false this will not
  cause the function to return an error.
  If any (even all) of the attributes passed in are no longer available for the user, this
  will not cause the function to return an error.

  \param[in,out] profile
  \parblock
  A pointer to the #MLIdentityProfile that was allocated by the library in which
  (none, ) one or more of the attributes have had their is_requested field set to true.
  Attributes for which the is_requested field is true, that are still available in the cloud and
  which the user has approved to make available for the calling service will have their
  values filled.
  The is_granted field will be set by the library to true in those attributes that were filled
  and false in the others.
  \endparblock
  \return #MLIdentityError: See description above.
*/
ML_API MLIdentityError ML_CALL MLIdentityRequestAttributeValues(MLIdentityProfile *profile);

/*!
  \brief MLIdentityRequestAttributeValuesAsync() invokes the
  MLIdentityRequestAttributeValues() function in a different thread.

  \param[in,out] profile
  \parblock
  A pointer to the #MLIdentityProfile that was allocated by the library in which
  (none, ) one or more of the attributes have had their is_requested field set to true.

  Attributes for which the is_requested field is true, that are still available in the cloud and
  which the user has approved to make available for the calling service will have their
  values filled.

  The is_granted field will be set by the library to \c true in those attributes that were filled
  and \c false in the others.

  profile must not be released (using MLIdentityReleaseUserProfile()) until
  MLIdentityRequestAttributeValuesWait() returns \c true, because it will be written to asynchronously.
  \parblock
  \return A pointer to an #MLInvokeFuture which provides the means to poll for completion
          and to retrieve the return value and profile returned by MLIdentityRequestAttributeValues().
          This pointer will be freed by the library before returning from the first (and last) call
          to MLIdentityRequestAttributeValuesWait() after the asynchronous call completed.
*/
ML_API MLInvokeFuture *ML_CALL MLIdentityRequestAttributeValuesAsync(MLIdentityProfile *profile);

/*!
  \brief Having made a call to MLIdentityRequestAttributeValuesAsync(), the user can call
  MLIdentityRequestAttributeValuesWait() to detect whether the asynchronous call completed
  and if so, to retrieve the result in out_ret_val.

  The call to MLIdentityRequestAttributeValuesWait() blocks until either msec_timeout msec elapses or the
  asynchronous function completes.

  Note:
  1. To poll without blocking use msec_timeout = 0.
  2. After the function returns true, future is freed by the library and must not be used again in
     consecutive calls to MLIdentityRequestAttributeValuesWait().

  \param[in,out] future The pointer returned by the MLIdentityRequestAttributeValuesAsync() function.
  \param[in] msec_timeout The timeout in milliseconds.
  \param[out] out_ret_val The location in memory where the result of the asynchronous call will be copied,
              if it completed, or #MLIdentityError_AsyncOperationNotComplete if not.
              This location is allocated by the user.
  \return If the timeout elapsed before the asynchronous call completed,
          MLIdentityRequestAttributeValuesWait() will return \c false and out_ret_val will be set to
          #MLIdentityError_Ok. If the asynchronous call completed before the timeout elapsed,
          the function will return \c true and out_ret_val will be assigned with the return value of the
          MLIdentityRequestAttributeValues() call.
*/
ML_API bool ML_CALL MLIdentityRequestAttributeValuesWait(MLInvokeFuture *future, uint32_t msec_timeout, MLIdentityError *out_ret_val);

/*!
  \brief MLIdentityModifyAttributeValues() is a blocking function that accesses the cloud
  and requests permission from the user to modify the attribute values that are marked as
  requested in the #MLIdentityProfile pointed to by the profile argument.

  Note: If any (even all) of the attributes passed in have is_requested set to false this will not
  cause the function to return an error.
  If any (even all) of the attributes passed in are no longer available for the user, this
  will not cause the function to return an error.

  \param[in,out] profile
  \parblock
  A pointer to the #MLIdentityProfile that was allocated by the library in which
  (none, ) one or more of the attributes have had their is_requested field set to true.

  Attributes for which the is_requested field is \c true, that are still available in the cloud and
  which the user has approved for modification by the calling service will have their
  values modified.

  The is_granted field will be set by the library to \c true in those attributes that were modified
  and \c false in the others.
  \endparblock
  \return #MLIdentityError: See description above.
*/
ML_API MLIdentityError ML_CALL MLIdentityModifyAttributeValues(MLIdentityProfile *profile);

/*!
  \brief MLIdentityModifyAttributeValuesAsync() invokes the
  MLIdentityModifyAttributeValues() function in a different thread.

  \param[in,out] profile
  \parblock
  A pointer to the #MLIdentityProfile that was allocated by the library in which
  (none, ) one or more of the attributes have had their is_requested field set to \c true.

  Attributes for which the is_requested field is \c true, that are still available in the cloud and
  which the user has approved to make available for the calling service will have their
  values modified.

  The is_granted field will be set by the library to \c true in those attributes that were modified
  and false in the others.
  profile must not be released (using MLIdentityReleaseUserProfile()) until
  MLIdentityModifyAttributeValuesWait() returns \c true, because it will be written to
  asynchronously.
  \endparblock
  \return A pointer to an #MLInvokeFuture which provides the means to poll for completion and
  to retrieve the return value and profile returned by MLIdentityModifyAttributeValues().
  This pointer will be freed by the library before returning from the first (and last) call to
  MLIdentityModifyAttributeValuesWait() after the asynchronous call completed.
*/
ML_API MLInvokeFuture *ML_CALL MLIdentityModifyAttributeValuesAsync(MLIdentityProfile *profile);

/*!
  \brief Having made a call to MLIdentityModifyAttributeValuesAsync(), the user can call
  MLIdentityModifyAttributeValuesWait() to detect whether the asynchronous call completed
  and if so, to retrieve the result in out_ret_val.

  The call to MLIdentityModifyAttributeValuesWait() blocks until either msec_timeout msec elapses or the
  asynchronous function completes.

  Note:
  1. To poll without blocking use msec_timeout = 0.
  2. After the function returns true, future is freed by the library and must not be used again in
     consecutive calls to MLIdentityModifyAttributeValuesWait.

  \param[in,out] future The pointer returned by the MLIdentityModifyAttributeValuesAsync() function.
  \param[in] msec_timeout The timeout in milliseconds.
  \param[out] out_ret_val The location in memory where the result of the asynchronous call will be copied,
              if it completed, or #MLIdentityError_AsyncOperationNotComplete if not.
              This location is allocated by the user.
  \return If the timeout elapsed before the asynchronous call completed,
          MLIdentityModifyAttributeValuesWait() will return \c false and out_ret_val will be set to
          #MLIdentityError_Ok. If the asynchronous call completed before the timeout elapsed,
          the function will return \c true and out_ret_val will be assigned with the return value
          of the MLIdentityModifyAttributeValues() call.
*/
ML_API bool ML_CALL MLIdentityModifyAttributeValuesWait(MLInvokeFuture *future, uint32_t msec_timeout, MLIdentityError *out_ret_val);

/*!
  \brief MLIdentityReleaseUserProfile() releases all resources associated with the
  #MLIdentityProfile stucture that was returned by the library.
  \param[in] profile A pointer to a library allocated structure received using one of:
             MLIdentityGetAttributeNames(), MLIdentityGetAttributeNamesWait() or
             MLIdentityGetKnownAttributeNames().
*/
ML_API void ML_CALL MLIdentityReleaseUserProfile(MLIdentityProfile *profile);

/*! @} */

ML_EXTERN_C_END
