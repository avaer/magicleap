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
  \brief This header provides forward declarations for types used for invoking a user-
  supplied blocking method on a different thread and for managing its completion.
*/

/*!
  \brief #MLInvokeParams represents a user defined type.
  A user-supplied blocking method accepts a pointer to this type as its single argument.
*/
typedef struct MLInvokeParams MLInvokeParams;

/*!
  \brief #MLInvokeResult represents a user defined type.
  A user-supplied blocking method returns a pointer to this type.
*/
typedef struct MLInvokeResult MLInvokeResult;

/*!
  \brief #MLInvokeMethod is the type of a user-supplied method that will be called asynchronously.
*/
typedef MLInvokeResult *(*MLInvokeMethod)(MLInvokeParams *);

/*!
  \brief #MLInvokerContext represents a user defined type.
  A pointer to this type is supplied by the user to the AsyncWithCallback() method and is then
  passed to the user-supplied callback method when the asynchronous operation completes.
*/
typedef struct MLInvokerContext MLInvokerContext;

/*!
  \brief #MLCallbackMethod is the type of the user-supplied completion callback.
*/
typedef void(*MLCallbackMethod)(MLInvokerContext *, MLInvokeResult *);

/*!
  \brief #MLInvokeFuture represents a type which is opaque (incomplete) to users of this library.
  A pointer to an #MLInvokeFuture is returned by the Async function.
  Users pass it to the Wait function to determine if the asynchronous method has
  completed and to retrieve the result if it has.
*/
typedef struct MLInvokeFuture MLInvokeFuture;

ML_EXTERN_C_END
