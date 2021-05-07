#include "PlayerBlue.h"

#include "Application.h"

sh::PlayerBlue::PlayerBlue(int type) :
    super() {
    super::player_type_ = type;
}

sh::PlayerBlue::~PlayerBlue() {
}

bool sh::PlayerBlue::Initialize(void) {
    super::is_show_ = true;
    position_ = Vector2(
        kWindowWidth / 2 - animation_.GetRectangle().GetWidth(),
        100.0f);
    move_.Zero();
    speed_ = Vector2(5.0f, 5.0f);
    animation_.Initialize();
    status_.Initialize(2);
    mp_coefficient_ = 1.0f;

    status_.MakeWeapons(
        sh::WeaponType::NORMAL_GUN,
        sh::WeaponType::THREE_WAY_GUN,
        sh::WeaponType::NORMAL_GUN,
        sh::WeaponType::NORMAL_GUN);
    status_.AddUser(*this);

    status_.GetWeapon(2)->ChangeBulletType(sh::BulletType::Through);
    status_.GetWeapon(3)->ChangeBulletType(sh::BulletType::Beam);
    status_.GetWeapon(0)->SetShotIntervalMax(5);
    status_.GetWeapon(2)->SetShotIntervalMax(10);
    status_.GetWeapon(3)->SetShotIntervalMax(1);
    return true;
}

bool sh::PlayerBlue::Update(void) {
    if (!is_show_) {
        return false;
    } // if

    // メンバ更新
    super::move_.Zero();
    this->animation_.Update();
    status_.Update();


    // 被弾時の無敵判定更新
    damage_interval_--;
    if (damage_interval_ < 0) {
        damage_interval_ = 0;
    } // if

    auto game_pad = sh::Application::
        GetInstance().GetGamePad();
    using Info = sh::GamePadInfo;

    // スティックで移動
    status_.GetMotion()->Control(*this);
    // アクセル
    if ((game_pad->IsRepeat(Info::LEFT_SHOULDER) ||
         game_pad->IsRepeat(Info::RIGHT_SHOULDER)) &&
        !status_.GetMp()->IsOverHeat()) {
        status_.GetMotion()->Accel(*this);
        status_.GetMp()->Use(static_cast<int>
            (2 * mp_coefficient_));
    } // if
    super::position_ += super::move_;

    // 描画角度・弾発射角度増減
    if (game_pad->IsActiveLeftTrigger()) {
        status_.GetMotion()->LeftYaw(*this);
    } // if
    if (game_pad->IsActiveRightTrigger()) {
        status_.GetMotion()->RightYaw(*this);
    } // if


    // 武器使用
    if (game_pad->IsRepeat(Info::BUTTON_A)) {
        auto weapon = status_.GetWeapon(0);
        weapon->AddBullet(20);
        if (weapon->CanShot() && !status_.GetMp()->IsOverHeat()) {
            this->UseWeapon(weapon);
        } // if
    } // if
    else if (game_pad->IsRepeat(Info::BUTTON_B)) {
        auto weapon = status_.GetWeapon(1);
        weapon->AddBullet(20);
        if (weapon->CanShot() && !status_.GetMp()->IsOverHeat()) {
            this->UseWeapon(weapon);
        } // if
    } // if
    else if (game_pad->IsRepeat(Info::BUTTON_X)) {
        auto weapon = status_.GetWeapon(2);
        weapon->AddBullet(20);
        if (weapon->CanShot() && !status_.GetMp()->IsOverHeat()) {
            this->UseWeapon(weapon);
        } // if
    } // else if
    else if (game_pad->IsRepeat(Info::BUTTON_Y)) {
        auto weapon = status_.GetWeapon(3);
        weapon->AddBullet(20);
        if (weapon->CanShot() && !status_.GetMp()->IsOverHeat()) {
            this->UseWeapon(weapon);
        } // if
        weapon->ChangeBulletType(sh::BulletType::BeamShooting);
    } // else if
    else if (game_pad->IsRepeat(Info::BUTTON_Y)) {
        auto weapon = status_.GetWeapon(3);
        weapon->AddBullet(20);
        if (weapon->CanShot() && !status_.GetMp()->IsOverHeat()) {
            this->UseWeapon(weapon);
        } // if
    } // else if
    else if (game_pad->IsRelease(Info::BUTTON_Y)) {
        auto weapon = status_.GetWeapon(3);
        weapon->ChangeBulletType(sh::BulletType::Beam);
    } // else if
    
    return true;
}