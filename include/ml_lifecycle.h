// %BANNER_BEGIN%
//---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
//
// Copyright (c) 2017 Magic Leap, Inc. (COMPANY) All Rights Reserved.
// Magic Leap, Inc. Confidential and Proprietary
//
// NOTICE:  All information contained herein is, and remains the property
// of COMPANY. The intellectual and technical concepts contained herein
// are proprietary to COMPANY and may be covered by U.S. and Foreign
// Patents, patents in process, and are protected by trade secret or
// copyright law.  Dissemination of this information or reproduction of
// this material is strictly forbidden unless prior written permission is
// obtained from COMPANY.  Access to the source code contained herein is
// hereby forbidden to anyone except current COMPANY employees, managers
// or contractors who have executed Confidentiality and Non-disclosure
// agreements explicitly covering such access.
//
// The copyright notice above does not evidence any actual or intended
// publication or disclosure  of  this source code, which includes
// information that is confidential and/or proprietary, and is a trade
// secret, of  COMPANY.   ANY REPRODUCTION, MODIFICATION, DISTRIBUTION,
// PUBLIC  PERFORMANCE, OR PUBLIC DISPLAY OF OR THROUGH USE  OF THIS
// SOURCE CODE  WITHOUT THE EXPRESS WRITTEN CONSENT OF COMPANY IS
// STRICTLY PROHIBITED, AND IN VIOLATION OF APPLICABLE LAWS AND
// INTERNATIONAL TREATIES.  THE RECEIPT OR POSSESSION OF  THIS SOURCE
// CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS
// TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE,
// USE, OR SELL ANYTHING THAT IT  MAY DESCRIBE, IN WHOLE OR IN PART.
//
// %COPYRIGHT_END%
// ---------------------------------------------------------------------
// %BANNER_END%

#pragma once

#include "ml_api.h"
#include "ml_fileinfo.h"

ML_EXTERN_C_BEGIN

typedef enum MLLifecycleErrorCode {
  /*! Failure. */
  MLLifecycleErrorCode_Failure = -1,
  /*! Success. */
  MLLifecycleErrorCode_Success = 0,
  /*! Ensure enum is represented as 32 bits. */
  MLLifecycleErrorCode_Ensure32Bits = 0x7FFFFFF
} MLLifecycleErrorCode;

typedef struct MLLifecycleCallbacks {
  /*!
    \brief This callback is called when the application is being stopped by the system.

    The system expects the application to gracefully terminate when this function is called.

    If the application does not terminate after a pre-defined timeout,
    it will be terminated by the system.

    If this function is not registered, the default behavior is to terminate
    with an exit status 1.

    NOTE: The termination of the app's process is not yet
    enforced. This note will be removed once it is in place.

    \param Pointer to the application context passed during initialization with a call to
           MLLifecycleInit(). This parameter is NULL if NULL was passed to MLLifecycleInit().
  */
  void (*on_stop)(void *);
  /*!
    \brief This callback is called when the application is being
    paused/suspended by the system.

    The application process is suspended after a pre-defined timeout. Applications should
    ensure any temporary data is flushed to disk for resumption later.

    \param Pointer to the application context passed during initialization by a call to
           MLLifecycleInit(). This parameter is NULL if NULL was passed to MLLifecycleInit().
  */
  void (*on_pause)(void *);
  /*!
    \brief This callback is called when the application is being
    resumed after being suspended.

    The application can restore its state in the function call to resume normal execution.

    \param Pointer to the application context passed during initialization to call to
           MLLifecycleInit(). This parameter is NULL if NULL was passed to MLLifecycleInit().
  */
  void (*on_resume)(void *);
  /*!
    \brief This callback is called when the application is being
    asked to free up cached resources by the system.

    This might happen when the system is running low on resources
    and requires to retain resources for other use cases.

    \param Pointer to the application context passed during initialization to call to
           MLLifecycleInit(). This parameter is NULL if NULL was passed to MLLifecycleInit().
  */
  void (*on_unload_resources)(void *);
  /*!
    \brief This callback is called when the application has received
    new init args.

    The application can obtain the init args by calling MLLifecycleGetInitArgList().

    \param Pointer to the application context passed during initialization to call to
           MLLifecycleInit(). This parameter is NULL if NULL was passed to MLLifecycleInit().
  */
  void (*on_new_initarg)(void *);
} MLLifecycleCallbacks;

/*! This structure should be explicitly freed by calling MLLifecycleFreeSelfInfo(). */
typedef struct MLLifecycleSelfInfo {
  /*!
    \brief Path to the writable dir of the application. This path is valid when the
    user is logged in and using the device, i.e the device is unlocked. This path
    is not available when device is locked.
   */
  const char *writable_dir_path;
  /*! Path to the application package dir. */
  const char *package_dir_path;
  /*! Package name of the application. */
  const char *package_name;
  /*! Component name of the application. */
  const char *component_name;
  /*! Path to the application tmp dir. */
  const char *tmp_dir_path;
  /*! \brief Visible name of the application */
  const char *visible_name;

  /*!
    \brief Path to the writable dir of the application available when device is
    locked. This path is valid when the user has logged in once and the device
    is locked. An application that needs to write data when running in the
    background e.g. a music app should use this path.  The same application can
    continue using this path when the device is unlocked afterwards. Therefore
    this path is always available to an application.
   */
  const char *writable_dir_path_locked_and_unlocked;
} MLLifecycleSelfInfo;

/*!
  \brief Opaque structure containing array of init args and other fields.

  An app can have multiple initial argument objects accumulated if it has been triggered multiple
  times and the app hasn't retrieved its InitArgs. These objects are stored in
  #MLLifecycleInitArgList which the app can retrieve.

  Note: The platform does not keep a copy of the InitArgs once they have been retrieved by the app.

  The accessible fields in this structure are:
  InitArg Array length - Can be obtained by calling MLLifecycleGetInitArgListLength().
  InitArg Array        - Can be obtained by calling MLLifecycleGetInitArgByIndex().
*/
typedef struct MLLifecycleInitArgList MLLifecycleInitArgList;

/*!
  \brief Opaque structure containing array of file infos and other fields.

  The accessible fields in this structure are:
  URI                    - Can be obtained by calling MLLifecycleGetInitArgUri().
  File Info Array length - Can be obtained by calling MLLifecycleGetFileInfoListLength().
  File Info Array        - Can be obtained by calling MLLifecycleGetFileInfoByIndex().
*/
typedef struct MLLifecycleInitArg MLLifecycleInitArg;

/*!
  \brief Initialize the lifecycle service interface.
  \param[in] callbacks Pointer to an #MLLifecycleCallbacks structure
  \param[out] context Pointer to the application context that the application wants a
              reference to during callbacks. This parameter is optional and the user can pass a
              NULL if not using it.
  \return Returns an #MLLifecycleErrorCode.
*/
ML_API MLLifecycleErrorCode ML_CALL MLLifecycleInit(const MLLifecycleCallbacks *callbacks, void *context);

/*!
  \brief Retrieve the process specific information for the application.

  The function returns a pointer to the #MLLifecycleSelfInfo structure. The
  user needs to explicitly free this structure by calling
  MLLifecycleFreeSelfInfo().

  \return Returns a pointer to #MLLifecycleSelfInfo structure on success and NULL on failure.
*/
ML_API MLLifecycleSelfInfo *ML_CALL MLLifecycleGetSelfInfo();

/*!
  \brief Free the #MLLifecycleSelfInfo struct that is allocated by MLLifecycleGetSelfInfo().

  The pointer to the #MLLifecycleSelfInfo struct will point to NULL after this call.

  \param[in] info Pointer to #MLLifecycleSelfInfo struct pointer.
*/
ML_API void ML_CALL MLLifecycleFreeSelfInfo(MLLifecycleSelfInfo **info);

/*!
  \brief Retrieve the initial arguments or "init args" for the application.

  The function returns a pointer to the #MLLifecycleInitArgList structure. The
  user needs to explicitly free this structure by calling
  MLLifecycleFreeInitArgList() function.

  The platform does not store the initial argument objects once the app has retrieved them.
  Subsequent calls to this API can return an empty list if there are no new init args available.

  \return Returns a pointer to #MLLifecycleInitArgList structure on success and NULL on failure.
*/
ML_API MLLifecycleInitArgList *ML_CALL MLLifecycleGetInitArgList();

/*!
  \brief Retrieve the length of the init arg array.

  This function can return length of 0 which implies there are no init
  args available.

  \param[in] init_arg_list Pointer to #MLLifecycleInitArgList struct.
  \return Returns length of #MLLifecycleInitArg array on success and -1 on failure.
*/
ML_API int64_t ML_CALL MLLifecycleGetInitArgListLength(const MLLifecycleInitArgList *init_arg_list);

/*!
  \brief Retrieve the #MLLifecycleInitArg structure from MLLifecycleInitArgList() for given index.

  Note: The caller should not free the pointer returned.
  The memory will be released in the call to MLLifecycleFreeInitArgList().

  \param[in] init_arg_list Pointer to #MLLifecycleInitArgList struct.
  \param[in] index of the #MLLifecycleInitArg array.
  \return Returns a pointer to #MLLifecycleInitArg structure on success and NULL on failure.
*/
ML_API const MLLifecycleInitArg *ML_CALL MLLifecycleGetInitArgByIndex(const MLLifecycleInitArgList *init_arg_list, int64_t index);

/*!
  \brief Retrieve the URI of the given MLLifecycleInitArg().

  This returned URI can be of the pattern <schema://> where schema can be
  http, ftp etc.

  Note: This field is typically used to pass URIs that the app can handle.
  However, it can be any string that the app developer wants.

  \param[in] init_arg Pointer to #MLLifecycleInitArg struct which was obtained by
             calling MLLifecycleGetInitArg().
  \return Returns a pointer to URI of the given #MLLifecycleInitArg on success and
          NULL on failure to get a URI.
          The caller should not free the pointer returned.
          The memory will be released in the call to MLLifecycleFreeInitArgList().
*/
ML_API const char *ML_CALL MLLifecycleGetInitArgUri(const MLLifecycleInitArg *init_arg);

/*!
  \brief Retrieve length of the #MLFileInfo array in the given #MLLifecycleInitArg.

  This function can return length of 0 which implies there is no file info
  available.

  \param[in] init_arg Pointer to #MLLifecycleInitArg array.
  \return Returns length of #MLLifecycleInitArg array on success and -1 on failure.
*/
ML_API int64_t ML_CALL MLLifecycleGetFileInfoListLength(const MLLifecycleInitArg *init_arg);

/*!
  \brief Retrieve the #MLFileInfo structure from #MLLifecycleInitArg for given index.
  \param[in] init_arg Pointer to #MLLifecycleInitArg struct.
  \param[in] index of the #MLFileInfo array.
  \return Returns a pointer to #MLFileInfo structure on success and
          NULL on failure to find valid #MLFileInfo at the index.
          The caller should not free the pointer returned.
          The memory will be released in the call to MLLifecycleFreeInitArgList().
*/
ML_API const MLFileInfo *ML_CALL MLLifecycleGetFileInfoByIndex(const MLLifecycleInitArg *init_arg, int64_t index);

/*!
  \brief Free the #MLLifecycleInitArgList, #MLLifecycleInitArg and #MLFileInfo structures
  that are allocated by MLLifecycleGetInitArgList().

  The pointer to the #MLLifecycleInitArgList struct will point to NULL after this
  call.

  \param[in] Pointer to #MLLifecycleInitArgList struct pointer.
  \return \c true or \c false if freeing #MLLifecycleInitArgList was successful or not.
*/
ML_API bool ML_CALL MLLifecycleFreeInitArgList(MLLifecycleInitArgList **init_arg_list);

/*!
  \brief This function should be called by applications to indicate that they are
  done with their initialization sequences and ready for the user.

  Initialization checklist:
  Create graphics client connection with MLGraphicsCreateClient().

  \param[out] Pointer to #MLLifecycleErrorCode that has the error code.
  \return Returns \c true on success, \c false otherwise.
*/
ML_API bool ML_CALL MLLifecycleSetReadyIndication(MLLifecycleErrorCode *out_error_code);

/*! \brief Attempts to accelerate the thread indicated by tid (Lumin OS support is required).

    \param[in] tid Thread ID as returned by gettid()
    \return: True if thread acceleration is supported, false otherwise
*/
ML_API bool ML_CALL MLLifecycleThreadAccelerate(int32_t tid);

/*! \brief Attempts to set the scheduler and priority for the specified thread (requires Lumin OS support).

    \param[in] tid Thread ID as returned by gettid()
    \param[in] policy SCHED_NORMAL, SCHED_FIFO, SCHED_RR, SCHED_BATCH or SCHED_IDLE
    \param[in] priority from minimal to maximal allowed
    \return: True if thread setscheduler is supported, false otherwise
*/
ML_API bool ML_CALL MLLifecycleThreadSetScheduler(int32_t tid, int32_t policy, int32_t priority);


ML_EXTERN_C_END
