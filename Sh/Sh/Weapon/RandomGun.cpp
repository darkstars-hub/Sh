//!---------------------------------------------------------
//! @file RandomGun.h
//! @brief Bullet‚ð‚½‚­‚³‚ñŒ‚‚Â
//! @author name
//! @date 2019/12/02
//!---------------------------------------------------------


#include "RandomGun.h"

sh::RandomGun::RandomGun() :
    target_angle_p(2.0f),
    target_angle_m(-2.0f) {
    super::shot_interval_max_ = 5;
    super::power_ = Vector2(3.0f, 3.0f);
    super::listener_ = sh::EventMessenger::
        Singleton().CreateListener(sh::ClassID::NORMAL_GUN);
    sh::EventMessenger::
        Singleton().AddEventListener(*listener_);
}

sh::RandomGun::~RandomGun() {
}

int sh::RandomGun::GetCost(void) {
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

void sh::RandomGun::Fire(void) {
    super::AddWait(shot_interval_max_);
    int shot_count = 5;
    bullet_count_ -= shot_count;

    sh::EventID event_id = sh::EventID::NONE;

    if (user_->GetType() == sh::ActorType::PLAYER) {
        event_id = sh::EventID::SHOT_PLAYER;
        super::SendSoundEvent();
    } // if
    else if (user_->GetType() == sh::ActorType::ENEMY) {
        event_id = sh::EventID::SHOT_ENEMY;
    } // else if

    float ad = target_angle_p;
    float sd = target_angle_m;
    target_angle_p += 11.0f;
    target_angle_m -= 11.0f;

    auto pos = user_->GetPosition();

    sh::Vector2 shot_speed;
    float radian;
    float degree;
    for (int i = 0; i < shot_count; i++) {
        {
            shot_speed = sh::Vector2(
                std::cosf(sh::ToRadian(ad)) * power_.x_,
                std::sinf(sh::ToRadian(ad)) * power_.y_);

            radian = std::atan2f(
                shot_speed.y_,
                shot_speed.x_);
            degree = radian * 180.0f / 3.141592f;
            super::SendEvent(event_id, pos, (degree - 90.0f), shot_speed);
        }
        {
            shot_speed = sh::Vector2(
                std::cos(sh::ToRadian(sd)) * power_.x_,
                std::sin(sh::ToRadian(sd)) * power_.y_);

            radian = std::atan2f(
                shot_speed.y_,
                shot_speed.x_);
            degree = radian * 180.0f / 3.141592f;
            super::SendEvent(event_id, pos, (degree - 90.0f), shot_speed);
        }
        ad += 360.0f / shot_count;
        sd -= 360.0f / shot_count;
    } // for
}