#include "EnemyBlackHat.h"

sh::EnemyBlackHat::EnemyBlackHat() :
super(){
    super::enemy_type_ = sh::EnemyType::BLACK_HAT;
}

void sh::EnemyBlackHat::Move(void) {
    status_.GetMotion()->Tacklle(*this, target_position_);
    
    super::position_ += super::move_;
    move_distance_ += std::abs(super::move_.y_);
}

void sh::EnemyBlackHat::SetUp(void) {
    animation_.MakeAnimation(32.0f, 32.0f, 1, 3);
    status_.Initialize(1);
    status_.MakeWeapons(
        sh::WeaponType::RANDOM_GUN,
        sh::WeaponType::NONE,
        sh::WeaponType::NONE,
        sh::WeaponType::NONE);
    status_.AddUser(*this);
    
    auto weapon = status_.GetWeapon(0);
    weapon->SetShotPower(5);
    weapon->SetShotIntervalMax(1);
    weapon->AddBullet(5);
}

