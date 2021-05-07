#include "PlayerWhite.h"

sh::PlayerWhite::PlayerWhite(int type) :
    super() {
    super::player_type_ = type;
}

sh::PlayerWhite::~PlayerWhite() {
}

bool sh::PlayerWhite::Initialize(void) {
    super::is_show_ = true;
    position_ = Vector2(
        kWindowWidth / 2 - animation_.GetRectangle().GetWidth(),
        100.0f);
    move_.Zero();
    speed_ = Vector2(5.0f, 5.0f);
    animation_.Initialize();
    status_.Initialize(3);
    mp_coefficient_ = 1.0f;

    status_.MakeWeapons(
        sh::WeaponType::NORMAL_GUN,
        sh::WeaponType::THREE_WAY_GUN,
        sh::WeaponType::CIRCLE_GUN,
        sh::WeaponType::NORMAL_GUN);
    status_.AddUser(*this);

    status_.GetWeapon(3)->ChangeBulletType(sh::BulletType::Boomerang);
    status_.GetWeapon(0)->SetShotIntervalMax(5);
    status_.GetWeapon(3)->SetShotIntervalMax(10);
    return true;
}