#include "PlayerPurple.h"

#include "Application.h"

sh::PlayerPurple::PlayerPurple(int type) :
    super(),
    barrier_texture_(),
    use_barrier_(false){
    super::player_type_ = type;
}

sh::PlayerPurple::~PlayerPurple() {
    barrier_texture_.Release();
}

sh::Circle sh::PlayerPurple::GetBarrierCircle(void) {
    if (! use_barrier_) {
        return std::move(sh::Circle());
    } // if

    float width = static_cast<float>
        (barrier_texture_.GetWidth());
    float height = static_cast<float>
        (barrier_texture_.GetHeight());
    float size = animation_.GetRectangle().GetWidth() * 0.5f;
    float radius = width;
    /*
    barrier_texture_.Render(
        position_.x_ + width * 0.5f - size,
        position_.y_ + height * 0.5f - size,
        (float)sh::GenerateRandom(0, 360),
        { 0.0f,0.0f,width,height },
        2.0f
    );
    */

    auto circle = sh::Circle(
        radius + 5,
        position_.x_ + width * 0.5f - size,
        position_.y_ + height * 0.5f - size);
    return std::move( circle);
}

bool sh::PlayerPurple::IsEquipmentBarrier(void) {
    return true;
}

bool sh::PlayerPurple::Initialize(void) {
    super::is_show_ = true;
    position_ = Vector2(
        kWindowWidth / 2 - animation_.GetRectangle().GetWidth(),
        100.0f);
    move_.Zero();
    speed_ = Vector2(3.0f, 3.0f);
    animation_.Initialize();
    status_.Initialize(2);
    mp_coefficient_ = 0.7f;

    status_.MakeWeapons(
        sh::WeaponType::NORMAL_GUN,
        sh::WeaponType::THREE_WAY_GUN,
        sh::WeaponType::RANDOM_GUN,
        sh::WeaponType::NORMAL_GUN);
    status_.AddUser(*this);

    status_.GetWeapon(2)->SetShotIntervalMax(3);

    barrier_texture_.Load("../textures/beam_circle.png");
    return true;
}

bool sh::PlayerPurple::Update(void) {
    if (!is_show_) {
        return false;
    } // if

    // メンバ更新
    super::move_.Zero();
    this->animation_.Update();
    status_.Update();
    use_barrier_ = false;


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
        /*
        auto weapon = status_.GetWeapon(3);
        weapon->AddBullet(20);
        if (weapon->CanShot() && !status_.GetMp()->IsOverHeat()) {
            this->UseWeapon(weapon);
        } // if
        */
        if (!status_.GetMp()->IsOverHeat()) {
            status_.GetMp()->Use(static_cast<int>
                //(0 * mp_coefficient_));
                (3 * mp_coefficient_));
            use_barrier_ = true;
        } // if
    } // else if

    for (int i = 0, n = 3; i < n; i++) {
        if (game_pad->IsRelease(static_cast<Info>(i))) {
            for (int j = 0; j < n; j++) {
                auto weapon = status_.GetWeapon(j);
                if (weapon->GetBulletType() == sh::BulletType::BeamShooting) {
                    weapon->ChangeBulletType(sh::BulletType::Beam);
                } // if
            } // for
        } // if
    } // for


    return true;
}


void sh::PlayerPurple::BarrierRender(void) {
    if (is_show_ && use_barrier_) {
        float width = static_cast<float>
            (barrier_texture_.GetWidth());
        float height = static_cast<float>
            (barrier_texture_.GetHeight());
        float size = animation_.GetRectangle().GetWidth() * 0.5f;

        barrier_texture_.Render(
            position_.x_ + width * 0.5f - size,
            position_.y_ + height * 0.5f - size,
            (float)sh::GenerateRandom(0, 360),
            { 0.0f,0.0f,width,height },
            2.0f
        );
    } // if
#ifdef _DEBUG
    auto g = sh::Graphics();
    g.DrawCircle(this->GetBarrierCircle(),
                 sh::Color(300, 300, 300, 300));
#endif // _DEBUG

}
