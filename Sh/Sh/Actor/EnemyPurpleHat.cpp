#include "EnemyPurpleHat.h"

sh::EnemyPurpleHat::EnemyPurpleHat() :
super(){
    super::enemy_type_ = sh::EnemyType::PURPLE_HAT;
    //super::actor_type_ = sh::ActorType::ENEMY_;
}

void sh::EnemyPurpleHat::Move(void) {
                // スティックで移動
    //status_.GetMotion()->Straight(*this);
    //status_.GetMotion()->Translate(*this, target_position_);
    //status_.GetMotion()->Tacklle(*this, target_position_);
    if (move_distance_ > exit_point_y_) {
        status_.GetMotion()->Exit(*this);
    } // if
    else {
        status_.GetMotion()->Wave(*this, 180.0f);
    } // else


    super::position_ += super::move_;
    move_distance_ += std::abs(super::move_.y_);
}

void sh::EnemyPurpleHat::SetUp(void) {
    animation_.MakeAnimation(32.0f, 32.0f, 1, 3);
    status_.Initialize(1);
    status_.MakeWeapons(
        sh::WeaponType::THREE_WAY_GUN,
        sh::WeaponType::NONE,
        sh::WeaponType::NONE,
        sh::WeaponType::NONE);
    status_.AddUser(*this);

    auto weapon = status_.GetWeapon(0);
    weapon->SetShotPower(5);
    weapon->SetShotIntervalMax(60);
    weapon->AddBullet(9);
}