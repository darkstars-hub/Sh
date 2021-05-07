#include "NormalGun.h"

sh::NormalGun::NormalGun() {
    super::shot_interval_max_ = 3;
    super::power_ = Vector2(10.0f, 10.0f);
    super::listener_ = sh::EventMessenger::
        Singleton().CreateListener(sh::ClassID::NORMAL_GUN);
    sh::EventMessenger::
        Singleton().AddEventListener(*listener_);
}

sh::NormalGun::~NormalGun() {
}


int sh::NormalGun::GetCost(void) {
    switch (bullet_type_) {
        case sh::BulletType::Bullet:
            return 2;
        case sh::BulletType::Beam:
        case sh::BulletType::BeamShooting:
            return 3;
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

void sh::NormalGun::Fire(void) {
    super::AddWait(shot_interval_max_);
    bullet_count_--;

    Vector2 pos;
    float angle;
    Vector2 bullet_speed;
    sh::EventID event_id = sh::EventID::NONE;

    if (user_->GetType() == sh::ActorType::PLAYER) {
        event_id = sh::EventID::SHOT_PLAYER;

        pos = user_->GetPosition();
        angle = user_->GetAngle();
        float direction = kPi * (angle + 90) / 180.0f;
        bullet_speed = sh::Vector2(
            std::cosf(direction) * super::power_.x_,
            std::sinf(direction) * super::power_.y_);

        super::SendSoundEvent();
    } // if

    else if (user_->GetType() == sh::ActorType::ENEMY) {
        event_id = sh::EventID::SHOT_ENEMY;

        float x = user_->GetPosition().x_ +
            user_->GetRectangle().GetWidth() * 0.5f;
        float y = user_->GetPosition().y_ +
            user_->GetRectangle().GetHeight();

        auto direction = Vector2(
            user_->GetTargetPosition().x_ - x,
            user_->GetTargetPosition().y_ - y);

        float distance = std::sqrtf(
            direction.x_ * direction.x_ +
            direction.y_ * direction.y_);
        if (distance <= 0.0f) {
            return;
        } // if
        direction.x_ /= distance;
        direction.y_ /= distance;

        pos = user_->GetPosition();
        bullet_speed = sh::Vector2(direction.x_ * super::power_.x_,
                                   direction.y_ * super::power_.y_);

        auto radian = std::atan2f(
            bullet_speed.y_,
            bullet_speed.x_);
        auto degree = radian * 180.0f / 3.141592f;
        angle = degree - 90.0f;
    } // else if

    super::SendEvent(
        event_id,
        user_->GetPosition(),
        user_->GetAngle(),
        bullet_speed);
}