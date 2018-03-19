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
  @{
*/

/*! The credentials that can be used to for a user to access a particular service (Audience). */
typedef struct MLTokenAgentCredentials {
  /*! Null terminated string allocated and released by the library. */
  const char *access_key_id;
  /*! Null terminated string allocated and released by the library. */
  const char *secret_key;
  /*! Null terminated string allocated and released by the library. */
  const char *session_token;
} MLTokenAgentCredentials;

/*! Contains tokens that are used to read and modify the user profile. */
typedef struct MLTokenAgentTokens {
  /*! The id_token contains information from the user profile.
      It is a null terminated string that is allocated and released by the library. */
  const char *id_token;
  /*! The access_token is the token that can be used to modify attributes of the user profile.
      It is a null terminated string that is allocated and released by the library. */
  const char *access_token;
} MLTokenAgentTokens;

/*!
  \brief Represents the credentials and tokens of the User-Audience pair
  that is associated with the calling service.
*/
typedef struct MLTokenAgentClientCredentials {
  /*!
    The credentials that can be used to access a particular service (Audience).*/
    MLTokenAgentCredentials credentials;
  /*! The tokens that can be used to manage the user profile for a particular Audience. */
    MLTokenAgentTokens tokens;
} MLTokenAgentClientCredentials;

/*!
  \brief The return value type of some of the #MLTokenAgent functions.
*/
typedef enum MLTokenAgentError {
  /*! The function returned with no error.*/
  MLTokenAgentError_Ok,
  /*! The local binder service was not found.*/
  MLTokenAgentError_FailedToConnectToLocalService,
  /*! The local binder service is running but has not been registered by the login service.*/
  MLTokenAgentError_ServiceNotStarted,
  /*! The local binder service failed to connect to the cloud service.*/
  MLTokenAgentError_FailedToConnectToCloud,
  /*! The cloud service rejected the request due to inappropriate credentials.*/
  MLTokenAgentError_CloudAuthentication,
  /*! The local server failed to log in with the cloud.*/
  MLTokenAgentError_FailedToLogin,
  /*! An attempt to complete the login was begun without starting the login.*/
  MLTokenAgentError_LoginNotBegun,
  /*! The operation was rejected because the local server was not logged in with the cloud. */
  MLTokenAgentError_NotLoggedIn,
  /*! The login request failed because the local server is already logged in with the cloud. */
  MLTokenAgentError_AlreadyLoggedIn,
  /*! The login request request failed because a login is already in progress. */
  MLTokenAgentError_LoginInProgress,
  /*! Having completed the login process with the cloud successfully, the service failed to
      start the local identity service. */
  MLTokenAgentError_FailedToStartIdentityService,
  /*! The operation failed due to an invalid argument being passed in. */
  MLTokenAgentError_InvalidArgument,
  /*! A polling function returned false because the asynchronous operation has not completed */
  MLTokenAgentError_AsyncOperationNotComplete,
  /*! An error not described by other values occurred. */
  MLTokenAgentError_OtherError,
  /*! The serial number of the device is not recognized by the cloud so login failed. */
  MLTokenAgentError_DeviceNotRegistered,
  /*! The device is not yet connected to the cloud so login failed. */
  MLTokenAgentError_DeviceNotConnected,
  /*! The device is not connected to a network. */
  MLTokenAgentError_NetworkError,
  /*! The user is not registered on the website. */
  MLTokenAgentError_UserIsNotRegistered,
  /*! The user's credentials have expired. */
  MLTokenAgentError_ExpiredCredentials,
  /*! The cloud rejected the operation because the user is not authorized to execute it. */
  MLTokenAgentError_Unauthorized,
  /*! The device failed to authenticate the server. */
  MLTokenAgentError_CertificateError,
  /*! The cloud rejected the operation. */
  MLTokenAgentError_RejectedByCloud,
  /*! The user must accept the terms of use on the website. */
  MLTokenAgentError_UserMustAcceptTerms,
  /*! The user's account has been locked and can only be unlocked on the website. */
  MLTokenAgentError_AccountLocked,
  /*! Ensure enum is represented as 32 bits. */
  MLTokenAgentError_Ensure32Bits = 0x7FFFFFFF
} MLTokenAgentError;

/*!
  \brief MLTokenAgentGetClientCredentials() is a blocking function that accesses the cloud and
  returns a pointer to an #MLTokenAgentClientCredentials structure containing the users credentials and
  tokens for a particular service (Audience).

  The library deduces the Audience being requested from the name of the calling service.

  \param[out] out_credentials is a pointer to a #MLTokenAgentClientCredentials pointer which was allocated
              with all its fields by the library. It must only be released
              using MLTokenAgentReleaseClientCredentials().
  \return #MLTokenAgentError: See description above.
*/
ML_API MLTokenAgentError ML_CALL MLTokenAgentGetClientCredentials(const MLTokenAgentClientCredentials **out_credentials);

/*!
  \brief MLTokenAgentGetClientCredentialsAsync() invokes the MLTokenAgentGetClientCredentials()
  function asynchronously (in a different thread).
  \return A pointer to an #MLInvokeFuture which provides the means to poll for completion and
          to retrieve the credentials returned by MLTokenAgentGetClientCredentials().
          This pointer will be freed by the library before returning from the first (and last)
          call to MLTokenAgentGetClientCredentialsWait(), after the asynchronous call completed.
*/
ML_API MLInvokeFuture *ML_CALL MLTokenAgentGetClientCredentialsAsync();

/*!
  \brief Having made a call to MLTokenAgentGetClientCredentialsAsync(), the user can call
  MLTokenAgentGetClientCredentialsWait() to detect whether the asynchronous call completed and if
  so, to retrieve the credentials in /p out_credentials.

  The call to MLTokenAgentGetClientCredentialsWait() blocks until either
  msec_timeout msec elapses or the asynchronous function completes.

  Note:
  1. To poll without blocking use msec_timeout = 0.
  2. After the function returns true, future is freed by the library and must not be used again in
     a call to MLTokenAgentGetClientCredentialsWait().

  \param[in] future The pointer returned by the MLTokenAgentGetClientCredentialsAsync() function.
  \param[in] msec_timeout The timeout in milliseconds.
  \param[out] out_ret_val The location in memory where the return value of #MLTokenAgentClientCredentials
              will be copied, if the asynchronous call completed, or
              #MLTokenAgentError_AsyncOperationNotComplete if not.
  \param[out] out_credentials The location in memory where the pointer to the credentials
              structure allocated by the library will be copied, if the asynchronous call completed,
              or 0 (null) if not.
  \return If the timeout elapsed before the asynchronous call completed,
          MLTokenAgentGetClientCredentialsWait() will return \c false and out_credentials
          will be set to 0 (null). If the asynchronous call completed before the timeout elapsed,
          the function will return \c true and out_credentials will be set to the address of the
          #MLTokenAgentClientCredentials structure allocated by the library.
          The returned credentials must be released when no longer needed by calling
          MLTokenAgentReleaseClientCredentials().
*/
ML_API bool ML_CALL MLTokenAgentGetClientCredentialsWait(MLInvokeFuture *future, uint32_t msec_timeout, MLTokenAgentError *out_ret_val, const MLTokenAgentClientCredentials **out_credentials);

/*!
  \brief MLTokenAgentReleaseClientCredentials() releases all resources associated with the
  #MLTokenAgentClientCredentials structure that was returned by the library.
  \param[in] credentials a pointer to a library allocated structure received using one of:
              MLTokenAgentGetClientCredentials() or MLTokenAgentGetClientCredentialsWait().
*/
ML_API void ML_CALL MLTokenAgentReleaseClientCredentials(const MLTokenAgentClientCredentials *credentials);

/*! @} */

ML_EXTERN_C_END
