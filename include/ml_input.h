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
#include "ml_keycodes.h"

ML_EXTERN_C_BEGIN

/*!
  \addtogroup Input
  \brief APIs for the Input system.

  - The Input system is for input.
  @{
*/

enum {
  /*! Maximum recognized number of input controllers. */
  MLInput_MaxControllers = 2,

  /*! Maximum recognized number of controller touchpad touches. */
  MLInput_MaxControllerTouchpadTouches = 2
};

/*!
 \brief Touchpad gesture state.
*/
typedef enum MLInputControllerTouchpadGestureState {
  MLInputControllerTouchpadGestureState_End,
  MLInputControllerTouchpadGestureState_Continue,
  MLInputControllerTouchpadGestureState_Start,
  MLInputControllerTouchpadGestureState_Ensure32Bits = 0x7FFFFFFF
} MLInputControllerTouchpadGestureState;

/*!
 \brief Recognized touchpad gesture types.
*/
typedef enum MLInputControllerTouchpadGestureType {
  MLInputControllerTouchpadGestureType_None,
  MLInputControllerTouchpadGestureType_Tap,
  MLInputControllerTouchpadGestureType_ForceTapDown,
  MLInputControllerTouchpadGestureType_ForceTapUp,
  MLInputControllerTouchpadGestureType_ForceDwell,
  MLInputControllerTouchpadGestureType_SecondForceDown,
  MLInputControllerTouchpadGestureType_LongHold,
  MLInputControllerTouchpadGestureType_RadialScroll,
  MLInputControllerTouchpadGestureType_Swipe,
  MLInputControllerTouchpadGestureType_Scroll,
  MLInputControllerTouchpadGestureType_Pinch,
  MLInputControllerTouchpadGestureType_Count,
  MLInputControllerTouchpadGestureType_Ensure32Bits = 0x7FFFFFFF
} MLInputControllerTouchpadGestureType;

/*
 \brief Direction of touchpad gesture.
*/
typedef enum MLInputControllerTouchpadGestureDirection {
  MLInputControllerTouchpadGestureDirection_None,
  MLInputControllerTouchpadGestureDirection_Up,
  MLInputControllerTouchpadGestureDirection_Down,
  MLInputControllerTouchpadGestureDirection_Left,
  MLInputControllerTouchpadGestureDirection_Right,
  MLInputControllerTouchpadGestureDirection_In,
  MLInputControllerTouchpadGestureDirection_Out,
  MLInputControllerTouchpadGestureDirection_Clockwise,
  MLInputControllerTouchpadGestureDirection_CounterClockwise,
  MLInputControllerTouchpadGestureDirection_Count,
  MLInputControllerTouchpadGestureDirection_Ensure32Bits = 0x7FFFFFFF
} MLInputControllerTouchpadGestureDirection;

/*!
 \brief Information about a recognized touchpad gesture.
*/
typedef struct MLInputControllerTouchpadGesture {
  /*! Gesture position (x,y) and force (z).
      Position is in the [-1.0,1.0] range and force is in the [0.0,1.0] range.
  */
  MLVec3f pos_and_force;

  /*! Type of gesture. */
  MLInputControllerTouchpadGestureType type;

  /*! Direction of gesture */
  MLInputControllerTouchpadGestureDirection direction;

  /*! Speed of gesture. Note that this takes on different meanings depending
      on the gesture type being performed:
      - For radial gestures, this will be the angular speed around the axis.
      - For pinch gestures, this will be the speed at which the distance
        between fingers is changing. The touchpad is defined as having extents
        of [-1.0,1.0] so touchpad distance has a range of [0.0,2.0]; this value
        will be in touchpad distance per second. */
  float speed;

  /*! For radial gestures, this is the absolute value of the angle. For scroll
      and pinch gestures, this is the absolute distance traveled in touchpad
      distance. The touchpad is defined as having extents of [-1.0,1.0] so
      this distance has a range of [0.0,2.0]. */
  float distance;

  /*! Distance between the two fingers performing the gestures in touchpad
      distance. The touchpad is defined as having extents of [-1.0,1.0] so
      this distance has a range of [0.0,2.0]. */
  float finger_gap;

  /*! For radial gestures, this is the radius of the gesture. The touchpad
      is defined as having extents of [-1.0,1.0] so this radius has a range
      of [0.0,2.0]. */
  float radius;

  /*! Angle from the center of the touchpad to the finger. */
  float angle;
} MLInputControllerTouchpadGesture;

/*!
 \brief Types of input controllers recognized by Magic Leap platform.
*/
typedef enum MLInputControllerType {
  MLInputControllerType_None,
  MLInputControllerType_Device,
  MLInputControllerType_MobileApp,
  MLInputControllerType_Ensure32Bits = 0x7FFFFFFF
} MLInputControllerType;

/*!
 \brief Degrees-of-freedom mode of input controller.
*/
typedef enum MLInputControllerDof {
  MLInputControllerDof_None,
  MLInputControllerDof_3,
  MLInputControllerDof_6,
  MLInputControllerDof_Ensure32Bits = 0x7FFFFFFF
} MLInputControllerDof;

/*!
 \brief Buttons on input controllers (Magic Leap device and Mobile Companion App).
*/
typedef enum MLInputControllerButton {
  MLInputControllerButton_None,
  MLInputControllerButton_Move,
  MLInputControllerButton_App,
  MLInputControllerButton_Bumper,
  MLInputControllerButton_HomeTap,
  MLInputControllerButton_Count,
  MLInputControllerButton_Ensure32Bits = 0x7FFFFFFF
} MLInputControllerButton;

/*!
\brief A structure containing callbacks for input controller events. The final
       parameter to all the callbacks is a void *, which will point to whatever
       payload data the user provides in MLInputSetControllerCallbacks.
       Individual callbacks which are not required by the client can be NULL.
*/
typedef struct MLInputControllerCallbacks {
  /*! This callback will be invoked whenever a detected touchpad gesture begins. */
  void (*on_touchpad_gesture_start)(uint8_t controller_id, const MLInputControllerTouchpadGesture *touchpad_gesture, void *data);

  /*! This callback will be invoked as a detected touchpad gesture continues. */
  void (*on_touchpad_gesture_continue)(uint8_t controller_id, const MLInputControllerTouchpadGesture *touchpad_gesture, void *data);

  /*! This callback will be invoked whenever a detected touchpad gesture ends. */
  void (*on_touchpad_gesture_end)(uint8_t controller_id, const MLInputControllerTouchpadGesture *touchpad_gesture, void *data);

  /*! This callback will be invoked whenever a button press is detected. */
  void (*on_button_down)(uint8_t controller_id, MLInputControllerButton button, void *data);

  /*! This callback will be invoked whenever a button release is detected. */
  void (*on_button_up)(uint8_t controller_id, MLInputControllerButton button, void *data);

  /*! This callback will be invoked when a controller is connected. */
  void (*on_connect)(uint8_t controller_id, void *data);

  /*! This callback will be invoked when a controller is disconnected. */
  void (*on_disconnect)(uint8_t controller_id, void *data);
} MLInputControllerCallbacks;

/*!
 \brief A structure containing information about the current state of an input controller.
*/
typedef struct MLInputControllerState {
  /*! 6DoF position and orientation of the controller. */
  MLQuaternionf orientation;
  MLVec3f position;

  /*! Current touch position (x,y) and force (z).
      Position is in the [-1.0,1.0] range and force is in the [0.0,1.0] range.
  */
  MLVec3f touch_pos_and_force[MLInput_MaxControllerTouchpadTouches];

  /*! Normalized trigger value [0.0,1.0]. */
  float trigger_normalized;

  /*! Button states. */
  bool button_state[MLInputControllerButton_Count];

  /*! Is touch active. */
  bool is_touch_active[MLInput_MaxControllerTouchpadTouches];

  /*! If this controller is connected. */
  bool is_connected;

  /*! Current touchpad gesture. */
  MLInputControllerTouchpadGesture touchpad_gesture;

  /*! Current touchpad gesture state. */
  MLInputControllerTouchpadGestureState touchpad_gesture_state;

  /*! Type of this controller. */
  MLInputControllerType type;

  /*! Current degrees of freedom mode of the controller. */
  MLInputControllerDof dof;

  /*! Hardware index of this controller. If it is a physical controller this
      will be either 0 or 1. If it is MLMA it will be 0xFF. */
  uint8_t hardware_index;
} MLInputControllerState;

/*!
\brief Feedback patterns for LED target.
*/
typedef enum MLInputControllerFeedbackPatternLED
{
  MLInputControllerFeedbackPatternLED_Clock1,
  MLInputControllerFeedbackPatternLED_Clock2,
  MLInputControllerFeedbackPatternLED_Clock3,
  MLInputControllerFeedbackPatternLED_Clock4,
  MLInputControllerFeedbackPatternLED_Clock5,
  MLInputControllerFeedbackPatternLED_Clock6,
  MLInputControllerFeedbackPatternLED_Clock7,
  MLInputControllerFeedbackPatternLED_Clock8,
  MLInputControllerFeedbackPatternLED_Clock9,
  MLInputControllerFeedbackPatternLED_Clock10,
  MLInputControllerFeedbackPatternLED_Clock11,
  MLInputControllerFeedbackPatternLED_Clock12,
  MLInputControllerFeedbackPatternLED_Clock1And7,
  MLInputControllerFeedbackPatternLED_Clock2And8,
  MLInputControllerFeedbackPatternLED_Clock3And9,
  MLInputControllerFeedbackPatternLED_Clock4And10,
  MLInputControllerFeedbackPatternLED_Clock5And11,
  MLInputControllerFeedbackPatternLED_Clock6And12,
  MLInputControllerFeedbackPatternLED_Ensure32Bits = 0x7FFFFFFF,
} MLInputControllerFeedbackPatternLED;

/*!
\brief Feedback effects for LED target.
*/
typedef enum MLInputControllerFeedbackEffectLED
{
  MLInputControllerFeedbackEffectLED_RotateCW,
  MLInputControllerFeedbackEffectLED_RotateCCW,
  MLInputControllerFeedbackEffectLED_Pulse,
  MLInputControllerFeedbackEffectLED_PaintCW,
  MLInputControllerFeedbackEffectLED_PaintCCW,
  MLInputControllerFeedbackEffectLED_Blink,
  MLInputControllerFeedbackEffectLED_Ensure32Bits = 0x7FFFFFFF
} MLInputControllerFeedbackEffectLED;

/*!
\brief Feedback colors for LED target.
*/
typedef enum MLInputControllerFeedbackColorLED
{
  MLInputControllerFeedbackColorLED_Red0,
  MLInputControllerFeedbackColorLED_Red1,
  MLInputControllerFeedbackColorLED_Red2,
  MLInputControllerFeedbackColorLED_Orange0,
  MLInputControllerFeedbackColorLED_Orange1,
  MLInputControllerFeedbackColorLED_Orange2,
  MLInputControllerFeedbackColorLED_Yellow0,
  MLInputControllerFeedbackColorLED_Yellow1,
  MLInputControllerFeedbackColorLED_Yellow2,
  MLInputControllerFeedbackColorLED_Pink0,
  MLInputControllerFeedbackColorLED_Pink1,
  MLInputControllerFeedbackColorLED_Pink2,
  MLInputControllerFeedbackColorLED_Purple0,
  MLInputControllerFeedbackColorLED_Purple1,
  MLInputControllerFeedbackColorLED_Purple2,
  MLInputControllerFeedbackColorLED_Ensure32Bits = 0x7FFFFFFF
} MLInputControllerFeedbackColorLED;

/*!
\brief Feedback effect speed for LED target.
*/
typedef enum MLInputControllerFeedbackEffectSpeedLED
{
  MLInputControllerFeedbackEffectSpeedLED_Slow,
  MLInputControllerFeedbackEffectSpeedLED_Medium,
  MLInputControllerFeedbackEffectSpeedLED_Fast,
  MLInputControllerFeedbackEffectSpeedLED_Ensure32Bits = 0x7FFFFFFF
} MLInputControllerFeedbackEffectSpeedLED;

/*!
\brief Feedback patterns for vibration, which can be applied to touchpad and body.
*/
typedef enum MLInputControllerFeedbackPatternVibe
{
  MLInputControllerFeedbackPatternVibe_Click,
  MLInputControllerFeedbackPatternVibe_Bump,
  MLInputControllerFeedbackPatternVibe_DoubleClick,
  MLInputControllerFeedbackPatternVibe_Buzz,
  MLInputControllerFeedbackPatternVibe_Tick,
  MLInputControllerFeedbackPatternVibe_ForceDown,
  MLInputControllerFeedbackPatternVibe_ForceUp,
  MLInputControllerFeedbackPatternVibe_ForceDwell,
  MLInputControllerFeedbackPatternVibe_SecondForceDown,
  MLInputControllerFeedbackPatternVibe_Ensure32Bits = 0x7FFFFFFF,
} MLInputControllerFeedbackPatternVibe;

/*!
\brief Discrete intensity of feedback.
*/
typedef enum MLInputControllerFeedbackIntensity
{
  MLInputControllerFeedbackIntensity_Low,
  MLInputControllerFeedbackIntensity_Medium,
  MLInputControllerFeedbackIntensity_High,
  MLInputControllerFeedbackIntensity_Ensure32Bits = 0x7FFFFFFF,
} MLInputControllerFeedbackIntensity;

/*!
\brief A structure containing callbacks for input keyboard events. The final
       parameter to all the callbacks is a void *, which will point to whatever
       payload data the user provides in MLInputSetKeyboardCallbacks. Individual
       callbacks which are not required by the client can be NULL.
*/
typedef struct MLInputKeyboardCallbacks {
  /*! This callback will be invoked whenever a printable char is typed on the keyboard. */
  void (*on_char)(uint32_t char_utf32, void *data);

  /*! This callback will be invoked whenever any key is pressed. */
  void (*on_key_down)(MLKeyCode key_code, uint32_t modifier_mask, void *data);

  /*! This callback will be invoked whenever any key is released. */
  void (*on_key_up)(MLKeyCode key_code, uint32_t modifier_mask, void *data);
} MLInputKeyboardCallbacks;

/*!
 \brief A structure containing information about the current keyboard state. Note that
        all connected keyboards will be muxed together into one state.
*/
typedef struct MLInputKeyboardState {
  /*! Current state of keys: true if currently pressed, false otherwise. */
  bool key_state[MLKEYCODE_COUNT];

  /*! Currently active modifier keys. */
  uint32_t modifier_mask;
} MLInputKeyboardState;

/*!
  \brief Desired configuration of the input system.
*/
typedef struct MLInputConfiguration {
  /*! Desired degrees-of-freedom mode of each controller. */
  MLInputControllerDof dof[MLInput_MaxControllers];
} MLInputConfiguration;

/*!
  \brief    Create an input tracker.
  \param    config #MLInputConfiguration specifying desired configuration. Pass NULL
            for default configuration.
  \returns  A handle to the created input tracker. If there is an error during
            creation, it will return #ML_INVALID_HANDLE.
*/
ML_API MLHandle ML_CALL MLInputCreate(const MLInputConfiguration *config);

/*!
  \brief    Sets the callbacks for controller input events.
  \param    handle Handle to the input tracker.
  \param    callbacks Pointer to #MLInputControllerCallbacks structure (can be NULL).
  \param    user_data Pointer to user payload data; this will be the first argument
            passed to all the callback functions (can be NULL).
*/
ML_API void ML_CALL MLInputSetControllerCallbacks(MLHandle handle, const MLInputControllerCallbacks *controller_callbacks, void *user_data);

/*!
  \brief    Return current state of all possible input controllers.
  \param    handle Handle to the input tracker.
  \param    out_state Array, of at least size #MLInput_MaxControllers, of
            #MLInputControllerState structures that will be populated.
  \returns  true if the data has been populated, false otherwise.
*/
ML_API bool ML_CALL MLInputGetControllerState(MLHandle handle, MLInputControllerState out_state[MLInput_MaxControllers]);

/*!
  \brief    Starts a vibe feedback pattern on the specified controller.
  \param    handle Handle to the input tracker.
  \param    controller_id ID of the input controller.
  \param    vibe_pattern Element of #MLInputControllerFeedbackPatternVibe type specifying pattern to start.
  \param    intensity Element of #MLInputControllerFeedbackIntensity type specifying intensity.
*/
ML_API bool ML_CALL MLInputStartControllerFeedbackPatternVibe(MLHandle handle, uint8_t controller_id, MLInputControllerFeedbackPatternVibe pattern, MLInputControllerFeedbackIntensity intensity);

/*!
  \brief    Starts a LED feedback pattern on the specified controller.
  \param    handle Handle to the input tracker.
  \param    controller_id ID of the input controller.
  \param    pattern Element of #MLInputControllerFeedbackPatternLED type specifying pattern to start.
  \param    color Element of #MLInputControllerFeedbackColorLED type specifying color.
  \param    duration Duration in milliseconds.
*/
ML_API bool ML_CALL MLInputStartControllerFeedbackPatternLED(MLHandle handle, uint8_t controller_id, MLInputControllerFeedbackPatternLED pattern, MLInputControllerFeedbackColorLED color, uint32_t duration);

/*!
  \brief    Starts a LED feedback effect using the specified pattern on the specified controller.
  \param    handle Handle to the input tracker.
  \param    controller_id ID of the input controller.
  \param    effect Element of #MLInputControllerFeedbackEffectLED type specifying effect to start.
  \param    speed Element of #MLInputControllerFeedbackEffectSpeedLED type specifying speed.
  \param    pattern Element of #MLInputControllerFeedbackPatternLED type specifying pattern to use.
  \param    color Element of #MLInputControllerFeedbackColorLED type specifying color.
  \param    duration Duration in milliseconds.
*/
ML_API bool ML_CALL MLInputStartControllerFeedbackPatternEffectLED(MLHandle handle, uint8_t controller_id, MLInputControllerFeedbackEffectLED effect, MLInputControllerFeedbackEffectSpeedLED speed, MLInputControllerFeedbackPatternLED pattern, MLInputControllerFeedbackColorLED color, uint32_t duration);

/*!
  \brief    Sets the callbacks for keyboard input events.
  \param    handle Handle to the input tracker.
  \param    callbacks Pointer to #MLInputKeyboardCallbacks structure (can be NULL).
  \param    user_data Pointer to user payload data; this will be the first argument
            passed to all the callback functions (can be NULL).
*/
ML_API void ML_CALL MLInputSetKeyboardCallbacks(MLHandle handle, const MLInputKeyboardCallbacks *keyboard_callbacks, void *user_data);

/*!
  \brief    Return current state of keyboard keys (down=true).
  \param    handle Handle to the input tracker.
  \param    out_state Pointer to #MLInputKeyboardState structure that will receive data.
  \returns  true if the data has been populated, false otherwise.
*/
ML_API bool ML_CALL MLInputGetKeyboardState(MLHandle handle, MLInputKeyboardState *out_state);

/*!
  \brief    Destroy an input tracker.
  \param    handle #MLHandle to the input tracker to destroy.
  \returns  true if it successfully destroyed the tracker.
*/
ML_API bool ML_CALL MLInputDestroy(MLHandle handle);

/*! @} */

ML_EXTERN_C_END
