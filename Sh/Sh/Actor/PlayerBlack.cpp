#include "PlayerBlack.h"

sh::PlayerBlack::PlayerBlack(int type) :
    super() {
    super::player_type_ = type;
}

sh::PlayerBlack::~PlayerBlack() {
}

bool sh::PlayerBlack::Initialize(void) {
    super::is_show_ = true;
    position_ = Vector2(
        kWindowWidth / 2 - animation_.GetRectangle().GetWidth(),
        100.0f);
    move_.Zero();
    speed_ = Vector2(7.0f, 7.0f);
    animation_.Initialize();
    status_.Initialize(5);
    mp_coefficient_ = 1.0f;

    status_.MakeWeapons(
        sh::WeaponType::NORMAL_GUN,
        sh::WeaponType::THREE_WAY_GUN,
        sh::WeaponType::NORMAL_GUN,
        sh::WeaponType::MINE);
    status_.AddUser(*this);

    status_.GetWeapon(2)->ChangeBulletType(sh::BulletType::Homing);
    status_.GetWeapon(3)->ChangeBulletType(sh::BulletType::Bomb);
    status_.GetWeapon(0)->SetShotIntervalMax(5);
    status_.GetWeapon(2)->SetShotIntervalMax(10);
    status_.GetWeapon(3)->SetShotIntervalMax(10);

    return true;
}