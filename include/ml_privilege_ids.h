// %BANNER_BEGIN%
// ---------------------------------------------------------------------
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
// --------------------------------------------------------------------*/
// %BANNER_END%

#pragma once

typedef enum MLPrivilegeID {
    MLPrivilegeID_Invalid = 0,
    MLPrivilegeID_TestReality = 9001,
    MLPrivilegeID_TestSensitive = 9002,
    MLPrivilegeID_TestAutogranted = 9003,
    MLPrivilegeID_AddressBookRead = 1,
    MLPrivilegeID_AddressBookWrite = 2,
    MLPrivilegeID_AudioRecognizer = 13,
    MLPrivilegeID_AudioRender = 14,
    MLPrivilegeID_AudioSettings = 16,
    MLPrivilegeID_BatteryInfo = 18,
    MLPrivilegeID_CalendarRead = 23,
    MLPrivilegeID_CalendarWrite = 24,
    MLPrivilegeID_CameraCapture = 26,
    MLPrivilegeID_DenseMap = 33,
    MLPrivilegeID_EmailSend = 35,
    MLPrivilegeID_Eyetrack = 36,
    MLPrivilegeID_Headpose = 41,
    MLPrivilegeID_InAppPurchase = 42,
    MLPrivilegeID_Location = 47,
    MLPrivilegeID_AudioCaptureMic = 49,
    MLPrivilegeID_MMPlayback = 50,
    MLPrivilegeID_DrmCertificates = 51,
    MLPrivilegeID_Occlusion = 52,
    MLPrivilegeID_ScreenCapture = 67,
    MLPrivilegeID_Internet = 96,
    MLPrivilegeID_GraphicsClient = 97,
    MLPrivilegeID_AudioCaptureMixed = 100,
    MLPrivilegeID_IdentityRead = 113,
    MLPrivilegeID_IdentityModify = 114,
    MLPrivilegeID_BackgroundDownload = 120,
    MLPrivilegeID_BackgroundUpload = 121,
    MLPrivilegeID_MediaDrm = 129,
    MLPrivilegeID_Media = 130,
    MLPrivilegeID_MediaMetadata = 140,
    MLPrivilegeID_PowerInfo = 150,
    MLPrivilegeID_AudioCaptureVirtual = 156,
    MLPrivilegeID_CalibrationRigModelRead = 168,
    MLPrivilegeID_NetworkServer = 170,
    MLPrivilegeID_LocalAreaNetwork = 171,
    MLPrivilegeID_Input = 172,
    MLPrivilegeID_VoiceInput = 173,
    MLPrivilegeID_ConnectBackgroundMusicService = 192,
    MLPrivilegeID_RegisterBackgroundMusicService = 193,
    MLPrivilegeID_NormalNotificationsUsage = 208,
    MLPrivilegeID_MusicService = 218,
    MLPrivilegeID_Ensure32Bits = 0x7FFFFFFF,
} MLPrivilegeID;
