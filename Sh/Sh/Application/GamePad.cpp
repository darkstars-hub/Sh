//!---------------------------------------------------------
//! @file GamePad.cpp
//! @brief コントローラーで操作するためのクラス
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#include "GamePad.h"

using namespace sh;

static sh::InputState input_state_
[static_cast<int>(sh::GamePadInfo::MAX_KEY_INFO)];
static int info_[] = {
    XINPUT_GAMEPAD_A,
    XINPUT_GAMEPAD_B,
    XINPUT_GAMEPAD_X,
    XINPUT_GAMEPAD_Y,

    XINPUT_GAMEPAD_DPAD_UP,
    XINPUT_GAMEPAD_DPAD_DOWN,
    XINPUT_GAMEPAD_DPAD_LEFT,
    XINPUT_GAMEPAD_DPAD_RIGHT,

    XINPUT_GAMEPAD_LEFT_SHOULDER,
    XINPUT_GAMEPAD_RIGHT_SHOULDER,
    XINPUT_GAMEPAD_LEFT_THUMB,
    XINPUT_GAMEPAD_RIGHT_THUMB,

    XINPUT_GAMEPAD_START,
    XINPUT_GAMEPAD_BACK
};

sh::GamePad::GamePad()
    : state_(),
    is_connected_(false),
    threshold_(32767) {
}
sh::GamePad::~GamePad() {
}

XINPUT_STATE sh::GamePad::GetState(void) const {
    return this->state_;
}
bool sh::GamePad::IsConnected(void) const {
    return this->is_connected_;
}
int sh::GamePad::GetThreshold(void) const {
    return this->threshold_;
}

void sh::GamePad::StateUpdate(void) {
    DWORD result = ::XInputGetState(0, &state_);
    if (result == ERROR_SUCCESS) {
        is_connected_ = true;
    } // if
    else {
        is_connected_ = false;
    } // else

    for (int i = 0; i < static_cast<int>(GamePadInfo::MAX_KEY_INFO); i++) {
        if (state_.Gamepad.wButtons & info_[i]) {
            if (input_state_[i] == InputState::NONE ||
                input_state_[i] == InputState::RELEASE) {
                input_state_[i] = InputState::PRESS;
            } // if
            else {
                input_state_[i] = InputState::REPEAT;
            } // else
        } // if 
        else {
            if (input_state_[i] == InputState::REPEAT ||
                input_state_[i] == InputState::PRESS) {
                input_state_[i] = InputState::RELEASE;
            } // if
            else {
                input_state_[i] = InputState::NONE;
            } // else
        } // else
    } // for
}

bool sh::GamePad::IsPress(const sh::GamePadInfo info) const {
    return (input_state_[static_cast<int>(info)] ==
            InputState::PRESS);
}
bool sh::GamePad::IsRepeat(
    const sh::GamePadInfo info) const {
    return (input_state_[static_cast<int>(info)] ==
            InputState::REPEAT);
}
bool sh::GamePad::IsRelease(
    const sh::GamePadInfo info) const {
    return (input_state_[static_cast<int>(info)] ==
            InputState::RELEASE);
}
bool sh::GamePad::IsActiveLeftTrigger(void) const {
    return this->state_.Gamepad.bLeftTrigger;
}
bool sh::GamePad::IsActiveRightTrigger(void) const {
    return this->state_.Gamepad.bRightTrigger;
}
float sh::GamePad::GetLeftThumbX(void) const {
    return this->state_.Gamepad.sThumbLX;
}
float sh::GamePad::GetLeftThumbY(void) const {
    return this->state_.Gamepad.sThumbLY;
}
float sh::GamePad::GetRightThumbX(void) const {
    return this->state_.Gamepad.sThumbRX;
}
float sh::GamePad::GetRightThumbY(void) const {
    return this->state_.Gamepad.sThumbRY;
}