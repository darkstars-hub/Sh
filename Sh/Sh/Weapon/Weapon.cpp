#include "Weapon.h"


sh::Weapon::Weapon() :
    user_(nullptr),
    shot_interval_(0),
    shot_interval_max_(0),
    cost_(0),
    power_(),
    listener_(nullptr),
    bullet_type_(sh::BulletType::Bullet),
bullet_count_(0){
}

sh::Weapon::~Weapon() {
}


void sh::Weapon::SetShotPower(const int value) {
    this->power_.x_ = static_cast<float>(value);
    this->power_.y_ = static_cast<float>(value);
}

void sh::Weapon::SetShotIntervalMax(const int value) {
    this->shot_interval_max_ = value;
}

void sh::Weapon::AddUser(Actor& user) {
    this->user_ = &user;
}

sh::BulletType sh::Weapon::GetBulletType(void) const noexcept {
    return this->bullet_type_;
}

bool sh::Weapon::CanShot(void) {
    if (shot_interval_ > 0 || bullet_count_ <= 0) {
        return false;
    } // if
    return true;
}

void sh::Weapon::AddWait(int value) {
    shot_interval_ += value;
}

void sh::Weapon::ResetWait(void) {
    shot_interval_ = 0;
}

void sh::Weapon::AddBullet(int value) {
    this->bullet_count_ += value;
    if (bullet_count_ >= 256) {
        bullet_count_ = 256;
    } // if
}

void sh::Weapon::Update(void) {
    shot_interval_--;
    if (shot_interval_ < 0) {
        shot_interval_ = 0;
    } // if
}

void sh::Weapon::SendSoundEvent(void) {
    sh::Event* e = new Event();
    e->destination_id_ = sh::ClassID::SOUND_MANAGER;
    e->id_ = sh::EventID::SHOT_PLAYER;
    listener_->Send(*e);
}

void sh::Weapon::SendEvent(const sh::EventID id, const sh::Vector2 position, const float angle, const sh::Vector2 speed) {
    sh::ShotEvent* e = new ShotEvent();
    e->destination_id_ = sh::ClassID::BULLET_MANAGER;
    e->id_ = id;
    e->position_ = position;
    e->angle_ = angle;
    e->speed_ = speed;

    sh::ClassID bullet_id = sh::ClassID::BULLET;
    if (bullet_type_ == sh::BulletType::Bomb) {
        bullet_id = sh::ClassID::BOMB;
    } // else if
    else if (bullet_type_ == sh::BulletType::Beam) {
        bullet_id = sh::ClassID::BEAM;
        e->position_ += Vector2(user_->GetRectangle().GetWidth() + 
                                user_->GetRectangle().GetWidth() * 0.5f, // * 1.5f
                                user_->GetRectangle().GetHeight() + 
                                user_->GetRectangle().GetHeight() * 0.5f); // * 1.5f
    } // else if
    else if (bullet_type_ == sh::BulletType::BeamShooting) {
        bullet_id = sh::ClassID::BEAM_SHOOTING;
        e->position_ += Vector2(user_->GetRectangle().GetWidth() + 
                                user_->GetRectangle().GetWidth() * 0.5f, // * 1.5f
                                user_->GetRectangle().GetHeight() + 
                                user_->GetRectangle().GetHeight() * 0.5f); // * 1.5f
    } // else if
    else if (bullet_type_ == sh::BulletType::Homing) {
        bullet_id = sh::ClassID::HOMING;
    } // else if
    else if (bullet_type_ == sh::BulletType::Through) {
        bullet_id = sh::ClassID::THROUGH;
    } // else if
    else if (bullet_type_ == sh::BulletType::Boomerang) {
        bullet_id = sh::ClassID::BOOMERANG;
        e->actor_ = this->user_;
    } // else if

    e->bullet_type_ = bullet_id;
    listener_->Send(*e);
}

void sh::Weapon::ChangeBulletType(const BulletType type) {
    this->bullet_type_ = type;
}