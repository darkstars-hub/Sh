#include "Player.h"

#include "Application.h"

sh::Player::Player() :
    super(),
    texture_(),
    animation_(),
    damage_interval_max_(60),
    damage_interval_(0),
    mp_coefficient_(1.0f),
    player_type_(0)
{

    super::actor_type_ = sh::ActorType::PLAYER;
    super::listener_ = sh::EventMessenger::
        Singleton().CreateListener(sh::ClassID::PLAYER);
    sh::EventMessenger::
        Singleton().AddEventListener(*listener_);
}

sh::Player::~Player() {
}
int sh::Player::GetPlayerType(void) const noexcept {
    return this->player_type_;
}
sh::Rectangle sh::Player::GetRectangle(void) const noexcept {
    if (!is_show_) {
        return std::move(sh::Rectangle());
    } // if

    auto size = 120.0f;
    auto player_rect = this->animation_.GetRectangle();
    auto pos = sh::Vector2(super::position_.x_ - size * 0.5f + player_rect.GetWidth() * 0.5f,
                           super::position_.y_ - size * 0.5f + player_rect.GetWidth() * 0.5f + 5);
    return std::move(sh::Rectangle(
        pos.x_ + size * 0.5f - 4,
        pos.y_ + size * 0.5f - 4,
        pos.x_ + size * 0.5f + 4,
        pos.y_ + size * 0.5f + 4));
}
bool sh::Player::Initialize(void) {
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
};
bool sh::Player::Update(void) {
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
};


bool sh::Player::Render(void) {
    if (!is_show_) {
        return false;
    } // if

    status_.Render();

    // プレーヤーが死んでいればプレイヤーのテクスチャは描画しない
#if defined (_DEBUG)
    {
        auto g = sh::Graphics();
//        g.DrawRectangle(this->GetRectangle(),
//                        sh::Color(0, 0, 255, 180));
    }
#endif // defined(_DEBUG)
    if (damage_interval_ % 2 == 0) {
        if (auto r = texture_.lock()) {
            auto pos = super::position_;
            auto rect = this->animation_.GetRectangle();
            auto width = rect.GetWidth();
            auto height = rect.GetHeight();

            r->Render(pos.x_ + width * 0.5f,
                      pos.y_ + height * 0.5f,
                      super::angle_, rect);
        } // if
#if defined (_DEBUG)
        {
            auto g = sh::Graphics();

            auto size = 120.0f;
            auto player_rect = this->animation_.GetRectangle();
            auto pos = sh::Vector2(super::position_.x_ - size * 0.5f + player_rect.GetWidth() * 0.5f,
                                   super::position_.y_ - size * 0.5f + player_rect.GetWidth() * 0.5f + 5);

            auto rect = sh::Rectangle(
                pos.x_ + size * 0.5f - 4, 
                pos.y_ + size * 0.5f - 4,
                pos.x_ + size * 0.5f + 4 , 
                pos.y_ + size * 0.5f + 4);
            g.DrawRectangle(rect,
                            sh::Color(255, 0, 255, 180));
        }
#endif // defined(_DEBUG)
        if (auto r = core_.lock()) {
            auto size = 120.0f;
            auto player_rect = this->animation_.GetRectangle();
            auto rect = sh::Rectangle(0.0f, 0.0f, size, size);
            auto pos = sh::Vector2(super::position_.x_ - size * 0.5f + player_rect.GetWidth() * 0.5f,
                                   super::position_.y_ - size * 0.5f + player_rect.GetWidth() * 0.5f + 5);

            auto p = sh::Vector2(super::position_.x_ - size * 0.5f + player_rect.GetWidth() * 0.5f,
                                 super::position_.y_ - size * 0.5f + player_rect.GetWidth() * 0.5f);
            sh::Rotate(pos, angle_, p);
            
            r->Render(pos.x_ + size * 0.5f,
                      pos.y_ + size * 0.5f,
                      //super::angle_, rect, 1.0f);
                      super::angle_ , rect, 0.125f);
        } // if
    } // if
    return true;
};
bool sh::Player::Release(void) {
    return true;
};
void sh::Player::Damage(const int damage_value) {
    auto pos = super::position_;
    auto rect = this->animation_.GetRectangle();
    auto width = rect.GetWidth();
    auto height = rect.GetHeight();

    if (damage_interval_ == 0) {
        damage_interval_ = damage_interval_max_;
        status_.GetHp()->Damage(damage_value);

        //ダメージエフェクト発生
        sh::EffectEvent* e = new EffectEvent();
        e->destination_id_ = sh::ClassID::EFFECT_MANAGER;
        e->id_ = sh::EventID::DAMAGE;
        e->position_ = Vector2(pos.x_ + width * 0.5f,
                               pos.y_ + height * 0.5f);
        listener_->Send(*e);
    } // if

    // 死亡エフェクト発生
    if (status_.GetHp()->GetValue() <= 0) {
        super::is_show_ = false;
        sh::EffectEvent* e = new EffectEvent();
        e->destination_id_ = sh::ClassID::EFFECT_MANAGER;
        e->id_ = sh::EventID::DEAD;
        e->position_ = Vector2(pos.x_ + width * 0.5f,
                               pos.y_ + height * 0.5f);
        listener_->Send(*e);
    } // else
}

void sh::Player::AcquireTexture(sh::ResourceManager& container) {
    switch (player_type_) {
        case 1:
            texture_ = container.GetTexture(sh::TextureFileID::PLAYER_TEXTURE_WHITE);
            break;
        case 2:
            texture_ = container.GetTexture(sh::TextureFileID::PLAYER_TEXTURE_BLACK);
            break;
        case 3:
            texture_ = container.GetTexture(sh::TextureFileID::PLAYER_TEXTURE_BLUE);
            break;
        case 4:
            texture_ = container.GetTexture(sh::TextureFileID::PLAYER_TEXTURE_PURPLE);
            break;
        default:
            break;
    } // switch

    core_ = container.GetTexture(sh::TextureFileID::HP_TEXTURE);
    animation_.MakeAnimation(32.0f, 32.0f, 1, 3);
    status_.Load(container);
}

bool sh::Player::IsEquipmentBarrier(void) {
    return false;
}

void sh::Player::UseWeapon(std::shared_ptr < sh::Weapon> weapon) {
    status_.GetMp()->Use(static_cast<int>
        (weapon->GetCost() * mp_coefficient_));
    weapon->Fire();

    if (weapon->GetBulletType() == sh::BulletType::Beam) {
        weapon->ChangeBulletType(sh::BulletType::BeamShooting);
    } // if
}