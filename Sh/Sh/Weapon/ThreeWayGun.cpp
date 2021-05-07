#include "ThreeWayGun.h"

sh::ThreeWayGun::ThreeWayGun() {
    super::shot_interval_max_ = 30;
    super::power_ = Vector2(3.0f, 3.0f);
    super::listener_ = sh::EventMessenger::
        Singleton().CreateListener(sh::ClassID::THREE_WAY_GUN);
    sh::EventMessenger::
        Singleton().AddEventListener(*listener_);
}

sh::ThreeWayGun::~ThreeWayGun() {
}

int sh::ThreeWayGun::GetCost(void) {
    switch (bullet_type_) {
        case sh::BulletType::Bullet:
            return 10;
        case sh::BulletType::Beam:
        case sh::BulletType::BeamShooting:
            return 10;
        case sh::BulletType::Boomerang:
            return 10;
        case sh::BulletType::Homing:
            return 10;
        case sh::BulletType::Through:
            return 10;
        default:
            break;
    } // switch
    return 0;
}

void sh::ThreeWayGun::Fire(void) {
    super::AddWait(shot_interval_max_);
    int shot_count = 3;
    bullet_count_ -= shot_count;

    sh::EventID event_id = sh::EventID::NONE;
    
    if (user_->GetType() == sh::ActorType::PLAYER) {
        event_id = sh::EventID::SHOT_PLAYER;
        super::SendSoundEvent();
    } // if
    else if (user_->GetType() == sh::ActorType::ENEMY) {
        event_id = sh::EventID::SHOT_ENEMY;
    } // else if



    auto pos = user_->GetPosition();
    float direction = 0.0f;
    if (event_id == sh::EventID::SHOT_PLAYER) {
         direction = kPi * (user_->GetAngle() + 90) / 180.0f;
    } // if
    else if(event_id == sh::EventID::SHOT_ENEMY){
        auto rect = user_->GetRectangle();
        float shot_x = pos.x_ + rect.GetWidth() * 0.5f;
        float shot_y = pos.y_ + rect.GetHeight();
        direction = std::atan2f(user_->GetTargetPosition().y_ - shot_y,
                                      user_->GetTargetPosition().x_ - shot_x);
    } // else if

    auto to_radian = [](float degree) {
        return degree * (3.141592f / 180.0f);
    };
    float ad = to_radian(-15.0f * (shot_count * 0.5f - 0.5f));

    for (int i = 0; i < shot_count; i++) {
        auto shot_speed = sh::Vector2(
            std::cosf(direction + ad) * super::power_.x_,
            std::sinf(direction + ad) * super::power_.y_);

        auto radian = std::atan2f(
            shot_speed.y_,+
            shot_speed.x_);
        auto degree = radian * 180.0f / 3.141592f;

        ad += to_radian(20.0f);

        super::SendEvent(
            event_id, 
            pos, 
            (degree - 90.0f), 
            shot_speed);
    } // for
}