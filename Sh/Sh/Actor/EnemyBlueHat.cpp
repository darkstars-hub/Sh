#include "EnemyBlueHat.h"

sh::EnemyBlueHat::EnemyBlueHat() :
super(){
    super::enemy_type_ = sh::EnemyType::BLUE_HAT;
    //super::actor_type_ = sh::ActorType::ENEMY_;
}

void sh::EnemyBlueHat::Move(void) {
    status_.GetMotion()->Translate(*this, target_position_);

    super::position_ += super::move_;
    move_distance_ += std::abs(super::move_.y_);
}

void sh::EnemyBlueHat::SetUp(void) {
    animation_.MakeAnimation(32.0f, 32.0f, 1, 3);
    status_.Initialize(1);
    status_.MakeWeapons(
        sh::WeaponType::CIRCLE_GUN,
        sh::WeaponType::NONE,
        sh::WeaponType::NONE,
        sh::WeaponType::NONE);
    status_.AddUser(*this);

    auto weapon = status_.GetWeapon(0);
    weapon->SetShotPower(5);
    weapon->ChangeBulletType(sh::BulletType::Bomb);
    weapon->SetShotIntervalMax(60);
    weapon->AddBullet(5);
}