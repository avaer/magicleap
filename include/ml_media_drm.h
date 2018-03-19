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
  \addtogroup MediaPlayer
  @{
*/

typedef const char *MLMediaDRMProperty;

/*!
  \brief String property name: identifies the maker of the DRM engine plugin.
*/
extern MLMediaDRMProperty MLMediaDRMProperty_Vendor;

/*!
  \brief String property name: identifies the version of the DRM engine plugin.
*/
extern MLMediaDRMProperty MLMediaDRMProperty_Version;

/*!
  \brief String property name: describes the DRM engine plugin.
*/
extern MLMediaDRMProperty MLMediaDRMProperty_Description;

/*!
  \brief String property name: a comma-separated list of cipher and mac algorithms
  supported by #CryptoSession. The list may be empty if the DRM engine
  plugin does not support #CryptoSession operations.
*/
extern MLMediaDRMProperty MLMediaDRMProperty_Algorithms;

/*!
  \brief Byte array property name: the device unique identifier is established during
  device provisioning and provides a means of uniquely identifying each device.
*/
extern MLMediaDRMProperty MLMediaDRMProperty_DeviceUniqueID;

/*!
  \brief Data type containing byte array buffer and the size.
*/
typedef struct MLMediaDRMByteArray {
  uint8_t *ptr;
  size_t length;
} MLMediaDRMByteArray;

/*!
  \brief Data type containing list of byte array buffers and the size.
*/
typedef struct MLMediaDRMByteArrayList {
  MLMediaDRMByteArray *ptr;
  size_t length;
} MLMediaDRMByteArrayList;

/*!
  \brief Data type containing {key, value} pair.
*/
typedef struct MLMediaDRMKeyValue {
  const char *key;
  const char *value;
} MLMediaDRMKeyValue;

/*!
  \brief Data type containing array of {key, value} pair.
*/
typedef struct MLMediaDRMKeyValueArray {
  MLMediaDRMKeyValue *ptr;
  size_t length;
  size_t index;
} MLMediaDRMKeyValueArray;

typedef enum MLMediaDRMKeyType {
  /*!
    \brief This key request type specifies that the keys will be for online use, they will
    not be saved to the device for subsequent use when the device is not connected to a network.
  */
  MLMediaDRMKeyType_Streaming    = 1,
  /*!
    \brief This key request type specifies that the keys will be for offline use, they
    will be saved to the device for use when the device is not connected to a network.
  */
  MLMediaDRMKeyType_Offline      = 2,
  /*! This key request type specifies that previously saved offline keys should be released. */
  MLMediaDRMKeyType_Release      = 3,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaDRMKeyType_Ensure32Bits = 0x7FFFFFFF
} MLMediaDRMKeyType;

typedef enum MLMediaDRMEventType {
  /*!
    \brief This event type indicates that the app needs to request
    a certificate from the provisioning server.
    The request message data is obtained using MLMediaDRMGetProvisionRequest().
  */
  MLMediaDRMEventType_ProvisionRequired = 1,
  /*!
    \brief This event type indicates that the app needs to request keys from a license server.
    The request message data is obtained using MLMediaDRMGetKeyRequest().
  */
  MLMediaDRMEventType_KeyRequired       = 2,
  /*!
    \brief This event type indicates that the licensed usage duration for keys in a session has expired.
    The keys are no longer valid.
  */
  MLMediaDRMEventType_KeyExpired        = 3,
  /*!
    \brief This event may indicate some specific vendor-defined condition,
    see your DRM provider documentation for details.
  */
  MLMediaDRMEventType_VendorDefined     = 4,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaDRMEventType_Ensure32Bits      = 0x7FFFFFFF
} MLMediaDRMEventType;

typedef enum MLMediaDRMErrorCode {
  /*! Not an error. */
  MLMediaDRMErrorCode_OK                           = 0,
  /*!
    \brief Error Code when an operation on a #MediaDRM handle is attempted
    and the device does not have a certificate.
    The app should obtain and install a certificate using the #MediaDRM
    provisioning methods then retry the operation.
  */
  MLMediaDRMErrorCode_NotProvisioned               = 1,
  /*! Error code if the MediaDRM operation fails when the required resources are in use. */
  MLMediaDRMErrorCode_ResourceBusy                 = 2,
  /*! Error code if the key response from the server indicates that the server has rejected the request. */
  MLMediaDRMErrorCode_DeniedByServer               = 3,
  /*! Error code for undefined type. */
  MLMediaDRMErrorCode_Unknown                      = 4,
  /*! Error code for Device License Revoked. */
  MLMediaDRMErrorCode_DeviceRevoked                = 5,
  /*! Error code for insufficient output protection. */
  MLMediaDRMErrorCode_InsufficientOutputProtection = 6,
  /*! Error code for no DRM license. */
  MLMediaDRMErrorCode_NoLicense                    = 7,
  /*! Error code for DRM license expired. */
  MLMediaDRMErrorCode_LicenseExpired               = 8,
  /*! Error code for DRM session not expired. */
  MLMediaDRMErrorCode_SessionNotOpened             = 9,
  /*! Error code for DRM can not handle the operation. */
  MLMediaDRMErrorCode_CantHandle                   = 10,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaDRMErrorCode_Ensure32Bits                 = 0x7FFFFFFF
} MLMediaDRMErrorCode;

/*!
  \brief Data type that encapsulates Key Request input arguments.
*/
typedef struct MLMediaDRMKeyRequestInputParam {
  /*!
    \brief init_data The container-specific data, its meaning is interpreted based on the
    mime-type provided in the mime_type parameter.
    It could contain, for example, the content ID, key ID or other data obtained
    from the content metadata that is required in generating the key request.
  */
  MLMediaDRMByteArray *init_data;
  /*! mime_type The mime type of the content. */
  char *mime_type;
  /*!
    \brief key_type The type of the request.
    The request may be to acquire keys for streaming or offline content,
    or to release previously acquired keys, which are identified by a key_set_id.
  */
  MLMediaDRMKeyType key_type;
  /*!
    \brief optional_params Optional parameters included in the key request message to allow a client
    application to provide additional message parameters to the server.
  */
  MLMediaDRMKeyValueArray *optional_params;
} MLMediaDRMKeyRequestInputParam;

/*!
  \brief Data type that encapsulates either of the following along with an URL:

  For Key Request Message: an opaque key request byte array
  that should be delivered to the license server.

  For Provision Request Message: an opaque provision request byte array
  that should be delivered to the provisioning server.
*/
typedef struct MLMediaDRMRequestMessage {
  /*! request The opaque request byte array. */
  MLMediaDRMByteArray request;
  /*! default_URL The recommended URL to deliver the request to. */
  char *default_URL;
} MLMediaDRMRequestMessage;

/*!
  \brief Data type that encapsulates algorithm, key_set_id and IV for Encryption/Decryption.
*/
typedef struct MLMediaDRMCryptoInputParam {
  /*!
    \brief algorithm The cipher mode used for the crypto operation.
    "AES/CBC/NoPadding" is the only supported algorithm now.
  */
  char *algorithm;
  /*! key_set_id The identifier for the key to be used. */
  MLMediaDRMByteArray *key_set_id;
  /*! iv The initial vector used for the crypto operation. */
  MLMediaDRMByteArray *iv;
} MLMediaDRMCryptoInputParam;

/*!
  \brief Data type that encapsulates algorithm, key_set_id for HMAC based Sign/Verify.
*/
typedef struct MLMediaDRMHMACInputParam {
  /*!
    \brief algorithm The MAC algorithm used for the MAC-HASH operation.
    "HmacSHA256" is the only supported algorithm now.
  */
  char *algorithm;
  /*! key_set_id The identifier for the key to be used. */
  MLMediaDRMByteArray *key_set_id;
} MLMediaDRMHMACInputParam;

/*!
  \brief Data type that encapsulates algorithm, wrapped_key for RSA operation.
*/
typedef struct MLMediaDRMRSAInputParam {
  /*!
    \brief algorithm The MAC algorithm used for padding/signing.
    "HmacSHA256" is the only supported algorithm now.
  */
  char *algorithm;
  /*! wrapped_rsa_key The wrapped RSA key to be used. */
  MLMediaDRMByteArray *wrapped_rsa_key;
} MLMediaDRMRSAInputParam;

/*!
  \brief #MediaDRM event listener callback function - user of ml_media_drm.h should implement this.
  \param[in] session_id DRM session id associated with the event.
  \param[in] event_type Type of Media DRM event, as described above.
  \param[in] extra Secondary error code.
  \param[in] data Optional data that may be associated with the event.
*/
typedef void (*MLMediaDRMEventListener)(const MLMediaDRMByteArray *session_id, MLMediaDRMEventType event_type, int extra, const MLMediaDRMByteArray *data);

/*!
  \brief Allocate byte array buffer.
  \param[in] size Maximum size of the desirable byte array to be allocated.
  \param[out] out_array Pointer to byte array buffer that needs to be allocated.
              To free/release, call MLMediaDRMByteArrayRelease().
  \return \c true or \c false based on whether the allocation is successful or not.
*/
ML_API bool ML_CALL MLMediaDRMByteArrayAllocate(size_t size, MLMediaDRMByteArray *out_array);

/*!
  \brief Allocate and Copy to byte array buffer.
  \param[in] copy_from Buffer from which copy into byte array.
  \param[in] size Number of bytes to be copied.
  \param[out] out_array Pointer to byte array buffer that needs to be allocated and copied to.
              To free/release, call MLMediaDRMByteArrayRelease().
  \return \c true or \c false based on whether the copy operation is successful or not.
*/
ML_API bool ML_CALL MLMediaDRMByteArrayAllocAndCopy(const uint8_t *copy_from, size_t size, MLMediaDRMByteArray *out_array);

/*!
  \brief Allocate array of {key, value} pairs.
  \param[in] size Maximum size of the desirable array of {key, value} pair to be allocated.
  \param[out] out_array Pointer to array of {key, value} pair that needs to be allocated.
              To free/release, call MLMediaDRMKeyValueArrayRelease().
  \return \c true or \c false based on whether the allocation is successful or not.
*/
ML_API bool ML_CALL MLMediaDRMKeyValueArrayAllocate(size_t size, MLMediaDRMKeyValueArray *out_array);

/*!
  \brief Create a #MediaDRM instance from a UUID.
  \param[in] uuid The universal unique ID of the crypto scheme. uuid must be 16 bytes.
  \return A handle to the created MediaDRM. If there is an error during
          creation, it will return #ML_INVALID_HANDLE.
*/
ML_API MLHandle ML_CALL MLMediaDRMCreate(MLUUID uuid);

/*!
  \brief Release the #MediaDRM instance.
  \param[in] media_drm #MLHandle to the #MediaDRM.
  \return \c true if #MediaDRM object was successfully released.
*/
ML_API bool ML_CALL MLMediaDRMRelease(MLHandle media_drm);

/*!
  \brief Release byte array buffer.
  \param array Byte array buffer that needs to be released.
  \return \c true or \c false based on whether the release operation is successful or not.
*/
ML_API bool ML_CALL MLMediaDRMByteArrayRelease(MLMediaDRMByteArray *array);

/*!
  \brief Release list of byte array buffer.
  \param array List of byte array buffer that needs to be released.
  \return \c true or \c false based on whether the release operation is successful or not.
*/
ML_API bool ML_CALL MLMediaDRMByteArrayListRelease(MLMediaDRMByteArrayList *array);

/*!
  \brief Release {key, value} pair array.
  \param array {key, value} pair array that needs to be released.
  \return \c true or \c false based on whether the release operation is successful or not.
*/
ML_API bool ML_CALL MLMediaDRMKeyValueArrayRelease(MLMediaDRMKeyValueArray *array);

/*!
  \brief Release Request Message.
  \param request Pointer to Request Message that needs to be released.
  \return \c true or \c false based on whether the release operation is successful or not.
*/
ML_API bool ML_CALL MLMediaDRMRequestMessageRelease(MLMediaDRMRequestMessage *request);

/*!
  \brief Add a {key, value} pair to the array of {key, value} pairs.
  \param[in] pair The source {key, value} pair that needs to be added.
  \param[out] out_array Pointer to array of {key, value} pair to which the pair needs to be added to.
  \return \c true or \c false based on whether the add operation is successful or not.
*/
ML_API bool ML_CALL MLMediaDRMKeyValueArrayAdd(const MLMediaDRMKeyValue *pair, MLMediaDRMKeyValueArray *out_array);

/*!
  \brief Query if the given scheme identified by its UUID is supported on this device.
  And whether the drm plugin is able to handle the media container format.
  \param[in] uuid Identifies the universal unique ID of the crypto scheme. uuid must be 16 bytes.
  \param[in] mime_type The MIME type of the media container, e.g. "video/mp4".
             If mime_type is not known or required, it can be provided as NULL.
  \return \c true or \c false based on the given crypto scheme is supported or not.
*/
ML_API bool ML_CALL MLMediaDRMIsCryptoSchemeSupported(MLUUID uuid, const char *mime_type);

/*!
  \brief Register a callback to be invoked when an event occurs.
  \param[in] media_drm #MLHandle to the #MediaDRM.
  \param[in] listener is the callback that will be invoked on event.
  \return \c true if the call is successful, \c false otherwise.
*/
ML_API bool ML_CALL MLMediaDRMSetOnEventListener(MLHandle media_drm, MLMediaDRMEventListener listener);

/*!
  \brief Opens a new session. A session ID is returned.
  \param[in] media_drm #MLHandle to the #MediaDRM.
  \param[out] out_session_id ID of the session created/opened.
              This byte array will be released when MLMediaDRMCloseSession() is called.
  \param[out] out_error_code Pointer to store the error code.
              If NULL is passed, no error code is returned.
  \return \c true on success, \c false otherwise.
*/
ML_API bool ML_CALL MLMediaDRMOpenSession(MLHandle media_drm, MLMediaDRMByteArray *out_session_id, MLMediaDRMErrorCode *out_error_code);

/*!
  \brief Closes a session on the #MediaDRM object that was previously opened with openSession().
  \param[in] media_drm #MLHandle to the #MediaDRM.
  \param[in] session_id The session ID for the DRM session, which will be released on return.
  \return \c true on success, \c false otherwise.
*/
ML_API bool ML_CALL MLMediaDRMCloseSession(MLHandle media_drm, MLMediaDRMByteArray *session_id);

/*!
  \brief A key request/response exchange occurs between the app and a license server
  to obtain or release keys used to decrypt encrypted content.

  MLMediaDRMGetKeyRequest() is used to obtain an opaque key request byte array
  that is delivered to the license server.
  The opaque key request byte array is returned in out_key_request.request
  The recommended URL to deliver the key request to is returned in out_key_request.default_URL.

  After the app has received the key request response from the server,
  it should deliver to the response to the DRM engine plugin using the method
  provideKeyResponse().

  \param[in] media_drm #MLHandle to the #MediaDRM.
  \param[in] session_id The session ID for the DRM session.
  \param[in] key_request_param Placeholder for needed arguments for generating a key request message.
  \param[out] out_key_request Upon successful return, contains key request message.
              To free/release this, call MLMediaDRMRequestMessageRelease().
  \return \c true on success, \c false otherwise.
*/
ML_API bool ML_CALL MLMediaDRMGetKeyRequest(MLHandle media_drm, const MLMediaDRMByteArray *session_id, const MLMediaDRMKeyRequestInputParam *key_request_param, MLMediaDRMRequestMessage *out_key_request);

/*!
  \brief A key response is received from the license server by the app, then it is
  provided to the DRM engine plugin using provideKeyResponse().

  When the response is for an offline key request, a key_set_id is returned that can be
  used to later restore the keys to a new session with restoreKeys().
  When the response is for a streaming or release request, a null key_set_id is returned.

  \param[in] media_drm #MLHandle to the #MediaDRM.
  \param[in] session_id The session ID for the DRM session.
  \param[in] response The opaque response from the server.
  \param[out] out_key_set_id Upon successful return, contains the key identifier.
              To free/release this buffer, call MLMediaDRMByteArrayRelease().
  \return \c true on success, \c false otherwise.
*/
ML_API bool ML_CALL MLMediaDRMProvideKeyResponse(MLHandle media_drm, const MLMediaDRMByteArray *session_id, const MLMediaDRMByteArray *response, MLMediaDRMByteArray *out_key_set_id);

/*!
  \brief Restore persisted offline keys into a new session. key_set_id identifies the
  keys to load, obtained from a prior call to provideKeyResponse().
  \param[in] media_drm #MLHandle to the #MediaDRM.
  \param[in] session_id The session ID for the DRM session.
  \param[in] key_set_id The saved key set to restore.
  \return \c true on success, \c false otherwise.
*/
ML_API bool ML_CALL MLMediaDRMRestoreKeys(MLHandle media_drm, const MLMediaDRMByteArray *session_id, const MLMediaDRMByteArray *key_set_id);

/*!
  \brief Remove the current keys from a session.
  \param[in] media_drm #MLHandle to the #MediaDRM.
  \param[in] key_set_id The keys to remove, which will be released on success.
  \return \c true on success, \c false otherwise.
*/
ML_API bool ML_CALL MLMediaDRMRemoveKeys(MLHandle media_drm, MLMediaDRMByteArray *key_set_id);

/*!
  \brief Request an informative description of the key status for the session.

  The status is in the form of {key, value} pairs. Since DRM license policies vary by vendor,
  the specific status field names are determined by each DRM vendor. Refer to your
  DRM provider documentation for definitions of the field names for a particular DRM engine plugin.

  \param[in] media_drm #MLHandle to the #MediaDRM.
  \param[in] session_id The session ID for the DRM session.
  \param[out] out_info_map The Key-Value pair place-holder for the key status.
              To release/free this call MLMediaDRMKeyValueArrayRelease().
  \return \c true on success, \c false otherwise.
*/
ML_API bool ML_CALL MLMediaDRMQueryKeyStatus(MLHandle media_drm, const MLMediaDRMByteArray *session_id, MLMediaDRMKeyValueArray *out_info_map);

/*!
  \brief A provision request/response exchange occurs between the app and a provisioning
  server to retrieve a device certificate.

  If provisioning is required, the #EVENT_PROVISION_REQUIRED event will be sent to the event handler.
  MLMediaDRMGetProvisionRequest() is used to obtain the opaque provision request byte array that
  should be delivered to the provisioning server.

  \param[in] media_drm #MLHandle to the #MediaDRM.
  \param[in] cert_type The device certificate type, which can be "none" or "X.509".
  \param[out] out_provision_request Upon successful return, contains provision request message.
              To free/release this, call MLMediaDRMRequestMessageRelease().
  \return \c true on success, \c false otherwise.
*/
ML_API bool ML_CALL MLMediaDRMGetProvisionRequest(MLHandle media_drm, const char *cert_type, MLMediaDRMRequestMessage *out_provision_request);

/*!
  \brief After a provision response is received by the app, it is provided to the DRM
  engine plugin using this method.

  \param[in] media_drm #MLHandle to the #MediaDRM.
  \param[in] response The opaque provisioning response byte array to provide to the DRM engine plugin.
  \param[out] out_certificate The device certificate upon sucessful return.
              To release/free this call MLMediaDRMByteArrayRelease().
  \param[out] out_wrapped_key The wrapped device key upon sucessful return.
              To release/free this call MLMediaDRMByteArrayRelease().
  \return \c true on success, \c false otherwise.
*/
ML_API bool ML_CALL MLMediaDRMProvideProvisionResponse(MLHandle media_drm, const MLMediaDRMByteArray *response, MLMediaDRMByteArray *out_certificate, MLMediaDRMByteArray *out_wrapped_key);

/*!
  \brief Secure Stop:

  A means of enforcing limits on the number of concurrent streams per subscriber
  across devices is provided via #SecureStop. This is achieved by securely
  monitoring the lifetime of sessions.

  Information from the server related to the current playback session is written
  to persistent storage on the device when each #MediaCrypto object is created.

  In the normal case, playback will be completed, the session destroyed and the
  Secure Stops will be queried. The app queries secure stops and forwards the
  secure stop message to the server which verifies the signature and notifies the
  server side database that the session destruction has been confirmed.

  The persisted record on the client is only removed after positive confirmation that the server
  received the message using releaseSecureStops().
*/

/*!
  \brief Access all secure stops.
  \param[in] media_drm #MLHandle to the #MediaDRM.
  \param[out] out_secure_stops List of all the secure stops upon successful return.
              To free/release call MLMediaDRMByteArrayListRelease().
  \return \c true on success, \c false otherwise.
*/
ML_API bool ML_CALL MLMediaDRMGetSecureStops(MLHandle media_drm, MLMediaDRMByteArrayList *out_secure_stops);

/*!
  \brief Access secure stop by secure stop ID.
  \param[in] media_drm #MLHandle to the #MediaDRM.
  \param[in] ss_id The ID for the DRM securestop session.
  \param[out] out_secure_stop The secure stop upon successful return.
              To free/release call MLMediaDRMByteArrayRelease().
  \return \c true on success, \c false otherwise.
*/
ML_API bool ML_CALL MLMediaDRMGetSecureStop(MLHandle media_drm, const MLMediaDRMByteArray *ss_id, MLMediaDRMByteArray *out_secure_stop);

/*!
  \brief Process the SecureStop server response message. After authenticating
  the message, remove the SecureStops identified in the response.
  \param[in] media_drm #MLHandle to the #MediaDRM.
  \param[in] secure_stop The server response indicating which secure stops to release.
  \return \c true on success, \c false otherwise.
*/
ML_API bool ML_CALL MLMediaDRMReleaseSecureStops(MLHandle media_drm, const MLMediaDRMByteArray *secure_stop);

/*!
  \brief Remove all the SecureStops.
  \param[in] media_drm #MLHandle to the #MediaDRM.
  \return \c true on success, \c false otherwise.
*/
ML_API bool ML_CALL MLMediaDRMReleaseAllSecureStops(MLHandle media_drm);

/*!
  \brief Read a DRM engine plugin String property value, given the property name.
  \param[in] media_drm #MLHandle to the #MediaDRM.
  \param[in] property_name The property to query. Standard property names are:
             - MLMediaDRMProperty_Vendor
             - MLMediaDRMProperty_Version
             - MLMediaDRMProperty_Description
             - MLMediaDRMProperty_Algorithms
  \param[out] out_property_value The property value upon successful return.
              Ownership is passed, call free(*out_property_value) to free it.
  \return \c true on success, \c false otherwise.
*/
ML_API bool ML_CALL MLMediaDRMGetPropertyString(MLHandle media_drm, MLMediaDRMProperty property_name, char **out_property_value);

/*!
  \brief Read a DRM engine plugin byte array property value, given the property name.
  \param[in] media_drm #MLHandle to the #MediaDRM.
  \param[in] property_name The property to query. Standard property names are:
             - MLMediaDRMProperty_DeviceUniqueID
  \param[out] out_property_value The property value upon successful return.
              To release/free call MLMediaDRMByteArrayRelease().
  \return \c true on success, \c false otherwise.
*/
ML_API bool ML_CALL MLMediaDRMGetPropertyByteArray(MLHandle media_drm, MLMediaDRMProperty property_name, MLMediaDRMByteArray *out_property_value);

/*!
  \brief Set a DRM engine plugin String property value.
  \param[in] media_drm #MLHandle to the #MediaDRM.
  \param[in] property_name The property to query. Standard property names are:
             - MLMediaDRMProperty_Vendor
             - MLMediaDRMProperty_Version
             - MLMediaDRMProperty_Description
             - MLMediaDRMProperty_Algorithms
  \param[in] property_value The value of the corresponding property.
  \return \c true on success, \c false otherwise.
*/
ML_API bool ML_CALL MLMediaDRMSetPropertyString(MLHandle media_drm, MLMediaDRMProperty property_name, const char *property_value);

/*!
  \brief Set a DRM engine plugin byte array property value.
  \param[in] media_drm #MLHandle to the #MediaDRM.
  \param[in] property_name The property to query. Standard property names are:
             - MLMediaDRMProperty_DeviceUniqueID
  \param[in] property_value The value of the corresponding property.
  \return \c true on success, \c false otherwise.
*/
ML_API bool ML_CALL MLMediaDRMSetPropertyByteArray(MLHandle media_drm, MLMediaDRMProperty property_name, const MLMediaDRMByteArray *property_value);

/*!
  \brief Encrypt the data referenced by input using algorithm if specified,
  and write the encrypted result into output.

  The key to use is identified by the 16 byte keyId. The key must have been loaded into
  the session using provideKeyResponse().

  \param[in] media_drm #MLHandle to the #MediaDRM.
  \param[in] session_id The session ID for the DRM session.
  \param[in] crypto_key_param Pointer to the structure that contains
             needed crypto arguments for encryption operation.
  \param[in] input The data that needs to be encrypted.
  \param[out] out_output The encrypted input upon successful return.
              To free/release this buffer, call MLMediaDRMByteArrayRelease().
  \return \c true on success, \c false otherwise.
*/
ML_API bool ML_CALL MLMediaDRMEncrypt(MLHandle media_drm, const MLMediaDRMByteArray *session_id, const MLMediaDRMCryptoInputParam *crypto_key_param, const MLMediaDRMByteArray *input, MLMediaDRMByteArray *out_output);

/*!
  \brief Decrypt the data referenced by input using algorithm if specified,
  and write the encrypted result into output.

  The key to use is identified by the 16 byte keyId. The key must have been loaded into
  the session using provideKeyResponse().

  \param[in] media_drm #MLHandle to the #MediaDRM.
  \param[in] session_id The session ID for the DRM session.
  \param[in] crypto_key_param Pointer to the structure that contains
             needed crypto arguments for decryption operation.
  \param[in] input The data that needs to be decrypted.
  \param[out] out_output The decrypted input upon successful return.
              To free/release this buffer, call MLMediaDRMByteArrayRelease().
  \return \c true on success, \c false otherwise.
*/
ML_API bool ML_CALL MLMediaDRMDecrypt(MLHandle media_drm, const MLMediaDRMByteArray *session_id, const MLMediaDRMCryptoInputParam *crypto_key_param, const MLMediaDRMByteArray *input, MLMediaDRMByteArray *out_output);

/*!
  \brief Generate a signature using the specified algorithm (if provided) over the message data
  and store the signature.

  The key to use is identified by the 16 byte keyId.
  The key must have been loaded into the session using provideKeyResponse().

  \param[in] media_drm #MLHandle to the #MediaDRM.
  \param[in] session_id The session ID for the DRM session.
  \param[in] hmac_key_param Pointer to the structure that contains
             needed crypto arguments for HMAC operation.
  \param[in] message The data that needs to be signed.
  \param[out] out_signature The signature of the input message upon success.
              To free/release this buffer, call MLMediaDRMByteArrayRelease().
  \return \c true on success, \c false otherwise.
*/
ML_API bool ML_CALL MLMediaDRMSign(MLHandle media_drm, const MLMediaDRMByteArray *session_id, const MLMediaDRMHMACInputParam *hmac_key_param, const MLMediaDRMByteArray *message, MLMediaDRMByteArray *out_signature);

/*!
  \brief Perform a signature verification using the specified algorithm (if specified)
  over the message data referenced by the message parameter.

  The key must have been loaded into the session using provideKeyResponse().

  \param[in] media_drm #MLHandle to the #MediaDRM.
  \param[in] session_id The session ID for the DRM session.
  \param[in] hmac_key_param Pointer to the structure that contains
             needed crypto arguments for HMAC operation.
  \param[in] message The data for which signature needs to be verified.
  \param[in] signature The signature of the input message.
  \param[out] out_match pointer to bool, which would return "true" if the signature matches,
              "false" otherwise.
  \return \c true on success, \c false otherwise.
*/
ML_API bool ML_CALL MLMediaDRMVerify(MLHandle media_drm, const MLMediaDRMByteArray *session_id, const MLMediaDRMHMACInputParam *hmac_key_param, const MLMediaDRMByteArray *message, const MLMediaDRMByteArray *signature, bool *out_match);

/*!
  \brief Generate a signature using the specified RSA Key and algorithm.
  \param[in] media_drm #MLHandle to the #MediaDRM.
  \param[in] session_id The session ID for the DRM session.
  \param[in] rsa_key_param Pointer to the structure that contains
             needed key arguments for this RSA operation.
  \param[in] message The data that needs to be signed.
  \param[out] out_signature The signature of the input message upon success.
              To free/release this buffer, call MLMediaDRMByteArrayRelease().
  \return \c true on success, \c false otherwise.
*/
ML_API bool ML_CALL MLMediaDRMSignRSA(MLHandle media_drm, const MLMediaDRMByteArray *session_id, const MLMediaDRMRSAInputParam *rsa_key_param, const MLMediaDRMByteArray *message, MLMediaDRMByteArray *out_signature);

/*! @} */

ML_EXTERN_C_END
