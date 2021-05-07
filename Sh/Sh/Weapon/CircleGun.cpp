//!---------------------------------------------------------
//! @file CircleGun.h
//! @brief ‘S•ûˆÊ‚ÉBullet‚ðŒ‚‚Â
//! @author name
//! @date 2019/12/02
//!---------------------------------------------------------


#include "CircleGun.h"


sh::CircleGun::CircleGun() {
    super::shot_interval_max_ = 90;
    super::power_ = Vector2(3.0f, 3.0f);
    super::listener_ = sh::EventMessenger::
        Singleton().CreateListener(sh::ClassID::CIRCLE_GUN);
    sh::EventMessenger::
        Singleton().AddEventListener(*listener_);
}

sh::CircleGun::~CircleGun() {
}

int sh::CircleGun::GetCost(void) {
    switch (bullet_type_) {
        case sh::BulletType::Bullet:
            return 15;
        case sh::BulletType::Bomb:
            return 15;
        case sh::BulletType::Beam:
        case sh::BulletType::BeamShooting:
            return 15;
        case sh::BulletType::Boomerang:
            return 15;
        case sh::BulletType::Homing:
            return 15;
        case sh::BulletType::Through:
            return 15;
        default:
            break;
    } // switch
    return 0;
}

void sh::CircleGun::Fire(void) {
    super::AddWait(shot_interval_max_);
    int shot_count = 12;
    bullet_count_ -= shot_count;

    sh::EventID event_id = sh::EventID::NONE;

    if (user_->GetType() == sh::ActorType::PLAYER) {
        event_id = sh::EventID::SHOT_PLAYER;
        super::SendSoundEvent();
    } // if
    else if (user_->GetType() == sh::ActorType::ENEMY) {
        event_id = sh::EventID::SHOT_ENEMY;
    } // else if

    float degree = 0.0f;
    for (int i = 0; i < shot_count; i++) {
        auto to_radian = [](float degree) {
            return degree * (3.141592f / 180.0f);
        };

        auto shot_speed = sh::Vector2(
            std::cos(to_radian(degree)) * super::power_.x_,
            std::sin(to_radian(degree)) * super::power_.y_);

        degree += 360.0f / shot_count;

        
        super::SendEvent(event_id, user_->GetPosition(), (degree - 90.0f), shot_speed);
    } // for
}