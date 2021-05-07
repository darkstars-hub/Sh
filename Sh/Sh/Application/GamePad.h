//!---------------------------------------------------------
//! @file GamePad.h
//! @brief コントローラーで操作するためのクラス
//! @author name
//! @date 2019/10/29
//!---------------------------------------------------------


#ifndef SH_GAME_PAD_H
//!---------------------------------------------------------
//! @def SH_GAME_PAD_H
//! @brief include gurad
//!---------------------------------------------------------
#define SH_GAME_PAD_H

#include <Windows.h>
#if defined(max)
#undef max
#endif // defined(max)
#if defined(min)
#undef min
#endif // defined(min)
#include "xinput/Xinput.h"


namespace sh {

//!---------------------------------------------------------
//! @enum class InputState
//! @brief defined in GamePad.h
//!---------------------------------------------------------
enum class InputState {
    NONE,
    PRESS,
    REPEAT,
    RELEASE
};

//!---------------------------------------------------------
//! @enum class GamePadInfo
//! @brief defined in GamePad.h
//!---------------------------------------------------------
enum class GamePadInfo {
    BUTTON_A,
    BUTTON_B,
    BUTTON_X,
    BUTTON_Y,
    DPAD_UP,
    DPAD_DOWN,
    DPAD_LEFT,
    DPAD_RIGHT,
    LEFT_SHOULDER,
    RIGHT_SHOULDER,
    LEFT_THUMB,
    RIGHT_THUMB,
    BUTTON_START,
    BUTTON_BACK,
    MAX_KEY_INFO,
};
class GamePad {
public:
    GamePad();
    ~GamePad();
    GamePad(const GamePad& rhs) = delete;
    GamePad& operator=(const GamePad& rhs) = delete;
    GamePad(GamePad&& rhs) = delete;
    GamePad& operator= (GamePad&& rhs) = delete;

    int GetThreshold(void) const;
    XINPUT_STATE GetState(void) const;
    bool IsConnected(void) const;

    void StateUpdate(void);
    bool IsPress(const sh::GamePadInfo info) const;
    bool IsRepeat(const sh::GamePadInfo info) const;
    bool IsRelease(const sh::GamePadInfo info) const;
    bool IsActiveLeftTrigger(void) const;
    bool IsActiveRightTrigger(void) const;
    float GetLeftThumbX(void) const;
    float GetLeftThumbY(void) const;
    float GetRightThumbX(void) const;
    float GetRightThumbY(void) const;
private:
    XINPUT_STATE state_;
    bool is_connected_;
    const int threshold_;
};
}
#endif // !SH_GAME_PAD_H