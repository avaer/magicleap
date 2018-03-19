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
#include "ml_privilege_ids.h"

ML_EXTERN_C_BEGIN

/*!
  \brief Start the privilege-checking system. This function should be called
  before any privilege-checking functions are called.
  \return \c true or \c false, whether or not the system started up properly.
*/
ML_API bool ML_CALL MLPrivilegesInit();

/*!
  \brief Shut down and clean all resources used by the privilege-checking
  system.

  This function should be called prior to exiting the program if a call to MLPrivilegesInit() was made.
*/
ML_API void ML_CALL MLPrivilegesDestroy();

/*!
  \brief Check whether the application has the specified privileges.

  This does not solicit consent from the end-user.

  \param[in] privilege_id The privilege to check.
  \return \c true if the privilege is granted, else \c false.
*/
ML_API bool ML_CALL MLPrivilegesCheckPrivilege(MLPrivilegeID privilege_id);

/*!
  \brief Request the specified privileges. This may possibly solicit consent from the end-user.
  \param[in] privilege_id The privilege to request.
  \return \c true if the privilege is granted, else \c false.
*/
ML_API bool ML_CALL MLPrivilegesRequestPrivilege(MLPrivilegeID privilege_id);

ML_EXTERN_C_END
