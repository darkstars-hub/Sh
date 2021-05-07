#include "Mine.h"

sh::Mine::Mine() {
    super::shot_interval_max_ = 10;
    super::power_ = Vector2(0.0f, 0.0f);
    super::listener_ = sh::EventMessenger::
        Singleton().CreateListener(sh::ClassID::MINE);
    sh::EventMessenger::
        Singleton().AddEventListener(*listener_);
}
sh::Mine::~Mine() {
}

int sh::Mine::GetCost(void) {
    switch (bullet_type_) {
        case sh::BulletType::Bullet:
            return 2;
        case sh::BulletType::Bomb:
            return 5;
        case sh::BulletType::Beam:
        case sh::BulletType::BeamShooting:
            return 3;
        case sh::BulletType::Boomerang:
            return 5;
        case sh::BulletType::Homing:
            return 5;
        case sh::BulletType::Through:
            return 5;
        default:
            break;
    } // switch
    return 0;
}

void sh::Mine::Fire(void) {
    super::AddWait(shot_interval_max_);
    bullet_count_--;

    sh::EventID event_id = sh::EventID::NONE;

    if (user_->GetType() == sh::ActorType::PLAYER) {
        event_id = sh::EventID::SHOT_PLAYER;
        super::SendSoundEvent();
    } // if
    else if (user_->GetType() == sh::ActorType::ENEMY) {
        event_id = sh::EventID::SHOT_ENEMY;
    } // else if

    auto pos = user_->GetPosition();
    auto angle = user_->GetAngle();
    auto speed = sh::Vector2();
    super::SendEvent(event_id, pos, angle, speed);
}
