#include "Enemy.h"

sh::Enemy::Enemy() :
    super(),
    texture_(),
    animation_(),
    status_(),
    move_distance_(0.0f),
    exit_point_y_(),
    enemy_type_(sh::EnemyType::NONE),
    move_count_(0),
    attack_count_(0) {
    super::actor_type_ = sh::ActorType::ENEMY;
    super::listener_ = sh::EventMessenger::
        Singleton().CreateListener(sh::ClassID::ENEMY);
    sh::EventMessenger::
        Singleton().AddEventListener(*listener_);
}

sh::Enemy::~Enemy() {
}
void sh::Enemy::SetShow(const bool b) {
    this->is_show_ = b;
}
void sh::Enemy::SetTexture(std::shared_ptr<sh::Texture> texture) {
    this->texture_ = texture;
}
sh::Rectangle sh::Enemy::GetRectangle(void) const noexcept {
    if (!is_show_) {
        return std::move(sh::Rectangle());
    } // if

    auto pos = super::position_;
    auto width = animation_.GetRectangle().GetWidth();
    auto height = animation_.GetRectangle().GetHeight();
    return std::move(sh::Rectangle(
        pos.x_,
        pos.y_,
        pos.x_ + width,
        pos.y_ + height));
}
sh::EnemyType sh::Enemy::GetEnemyType(void) const noexcept {
    return this->enemy_type_;
}
bool sh::Enemy::Initialize(void) {
    super::is_show_ = false;
    position_ = Vector2();
    move_.Zero();
    speed_ = Vector2(3.0f, -3.0f);
    animation_.Initialize();
    move_distance_ = 0.0f;
    exit_point_y_ = static_cast<float>(sh::GenerateRandom(300, 600));
    return true;
};
bool sh::Enemy::Update(void) {
    if (!is_show_) {
        return false;
    } // if

    this->MemberUpdate();

    this->Move();

    this->Attack();

    this->Cliping();

    return true;
};


bool sh::Enemy::Render(void) {
    if (!is_show_) {
        return false;
    } // if

    // プレーヤーが死んでいればプレイヤーのテクスチャは描画しない
#if defined (_DEBUG)
    {
        auto g = sh::Graphics();
//        g.DrawRectangle(this->GetRectangle(),
//                        sh::Color(0, 0, 255, 180));
    }
#endif // defined(_DEBUG)
    if (auto r = texture_.lock()) {
        auto pos = super::position_;
        auto rect = this->animation_.GetRectangle();
        auto width = rect.GetWidth();
        auto height = rect.GetHeight();

        r->Render(pos.x_ + width * 0.5f,
                  pos.y_ + height * 0.5f,
                  super::angle_, rect);
    } // if
    return true;
};
bool sh::Enemy::Release(void) {
    return true;
};
void sh::Enemy::Damage(const int damage_value) {
    auto pos = super::position_;
    auto rect = this->animation_.GetRectangle();
    auto width = rect.GetWidth();
    auto height = rect.GetHeight();

    status_.GetHp()->Damage(damage_value);

    //ダメージエフェクト発生
    sh::EffectEvent* e = new EffectEvent();
    e->destination_id_ = sh::ClassID::EFFECT_MANAGER;
    e->id_ = sh::EventID::DAMAGE;
    e->position_ = Vector2(pos.x_ + width * 0.5f,
                           pos.y_ + height * 0.5f);
    listener_->Send(*e);

    if (status_.GetHp()->GetValue() <= 0) {
        super::is_show_ = false;
    } // else
}
void sh::Enemy::MemberUpdate(void) {
    // メンバ更新
    super::move_.Zero();
    this->animation_.Update();
    status_.Update();
}
void sh::Enemy::Move(void) {
    status_.GetMotion()->Straight(*this);

    super::position_ += super::move_;
    move_distance_ += std::abs(super::move_.y_);
}
void sh::Enemy::Attack(void) {
        // 武器使用
    auto weapon = status_.GetWeapon(0);
    if (weapon->CanShot()) {
        weapon->Fire();
    } // if
}
void sh::Enemy::Cliping(void) {
    // 画面外に出れば見えなくなる
    auto pos = position_;
    auto rect = this->GetRectangle();
    if (position_.x_ <= 0 - rect.GetWidth() ||
        position_.x_ >= sh::kWindowWidth + rect.GetWidth() ||
        position_.y_ <= 0 - rect.GetHeight() ||
        position_.y_ >= sh::kWindowHeight + rect.GetHeight()) {
        is_show_ = false;
    } // ifz
}
void sh::Enemy::AcquireTexture(sh::ResourceManager& container) {
    texture_ = container.GetTexture(sh::TextureFileID::ENEMY_TEXTURE_GHOST_KING);
    status_.Load(container);
}

void sh::Enemy::Start(const Vector2 position) {
    position_ = position;
    super::initial_position_ = position;
    is_show_ = true;
}

void sh::Enemy::SetUp(void) {
    animation_.MakeAnimation(32.0f, 32.0f, 1, 3);
    status_.Initialize(1);
    status_.MakeWeapons(
        sh::WeaponType::NORMAL_GUN,
        sh::WeaponType::NONE,
        sh::WeaponType::NONE,
        sh::WeaponType::NONE);
    status_.AddUser(*this);

    auto weapon = status_.GetWeapon(0);
    weapon->SetShotPower(5);
    weapon->SetShotIntervalMax(60);
    weapon->AddBullet(5);
}