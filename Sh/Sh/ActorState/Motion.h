//!---------------------------------------------------------
//! @file Motion.h
//! @brief Actorの動きの定義をする
//!        Actorのフレンドクラス
//! @author name
//! @date 2019/11/06
//!---------------------------------------------------------


#ifndef SH_MOTION_H
#define SH_MOTION_H

#include "Actor.h"

#include <algorithm>

namespace sh {
class Motion {
public:
    Motion();
    ~Motion();
    Motion(const Motion& rhs) = delete;
    Motion& operator=(const Motion& rhs) = delete;
    Motion(const Motion&& rhs) = delete;
    Motion& operator=(Motion&& rhs) = delete;

    void Initialize(void);

    void Control(sh::Actor& obj);
    void Rotate(sh::Actor& obj, float angle, const sh::Vector2 center);
    void LeftYaw(sh::Actor& obj);
    void RightYaw(sh::Actor& obj);

    void Accel(sh::Actor& obj);
    void Move(sh::Actor& obj);
    void Straight(sh::Actor& obj);
    void Exit(sh::Actor& obj);
    void Tacklle(sh::Actor& obj, const sh::Vector2 target);
    void Translate(sh::Actor& obj,const sh::Vector2 target);
    void Wave(sh::Actor& obj, const float direction);
private:
    float count_;
    float count_limit_;
    float wave_amplitude_;
    float angle_;

    bool set_target_;
    sh::Vector2 target_position_;
    float tacklle_direction_;
};
}
#endif // !SH_MOTION_H