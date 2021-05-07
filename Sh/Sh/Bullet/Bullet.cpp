#include "Bullet.h"

sh::Bullet::Bullet()
    : super(),
    state_(BulletState::NONE),
    speed_limit_(sh::Vector2(0.0f, 5.0f)),
    texture_(nullptr),
    current_animation_(),
    move_animation_(),
    hit_animation_(),
    attack_value_(1),
    type_(sh::BulletType::Bullet),
    rect_offset_(5.0f) {
    super::speed_ = speed_limit_;
}
sh::Bullet::~Bullet() {
}

void sh::Bullet::SetShow(const bool is_show) {
    this->is_show_ = is_show;
}

void sh::Bullet::SetState(const BulletState state) {
    this->state_ = state;
    switch (state_) {
        case sh::BulletState::NONE:
            break;
        case sh::BulletState::MOVE:
            current_animation_ = move_animation_;
            break;
        case sh::BulletState::HIT:
            current_animation_ = hit_animation_;
            break;
        case sh::BulletState::COUNT:
            break;
        default:
            break;
    } // switch
}

void sh::Bullet::SetTexture(std::shared_ptr<sh::Texture> texture) {
    this->texture_ = texture;
}


sh::Rectangle sh::Bullet::GetRectangle(void) const noexcept {
    if (this->state_ == sh::BulletState::HIT) {
        return std::move(sh::Rectangle());
    } // if

    auto pos = position_;
    auto width = current_animation_.GetRectangle().GetWidth();
    auto height = current_animation_.GetRectangle().GetHeight();

    return std::move(sh::Rectangle(
        pos.x_ + rect_offset_,
        pos.y_ + rect_offset_,
        pos.x_ - rect_offset_ + width,
        pos.y_ - rect_offset_ + height));
}

int sh::Bullet::GetAttackValue(void) const noexcept {
    return this->attack_value_;
}

sh::BulletType sh::Bullet::GetType(void) const noexcept {
    return this->type_;
}

sh::BulletState sh::Bullet::GetState(void) const noexcept {
    return this->state_;
}

bool sh::Bullet::Initialize(void) {
    super::position_.Zero();
    super::speed_ = speed_limit_;
    super::angle_ = 0.0f;
    state_ = BulletState::MOVE;
    current_animation_ = move_animation_;
    current_animation_.Initialize();
    is_show_ = false;

    return true;
}

bool sh::Bullet::Update(void) {
    if (!is_show_) {
        return true;
    } // if

   //move_.Zero();
    move_ = speed_;
    current_animation_.Update();

    switch (state_) {
        case BulletState::MOVE:
            position_ += move_;
            break;
        case BulletState::HIT:
            // 衝突アニメーションが終われば更新・描画されなくなる
            if (current_animation_.IsEnd()) {
                is_show_ = false;
                return true;
            } // if
            break;
        default:
            break;
    } // switch

    this->Cliping();
    return true;
}
bool sh::Bullet::Render(void) {
    if (!is_show_) {
        return true;
    } // if

#if defined (_DEBUG)||(DEBUG)
    {
        auto g = sh::Graphics();
        //g.DrawRectangle(this->GetRectangle(),
          //              sh::Color(0, 0, 255, 255));
    }
#endif // defined(_DEBUG)||(DEBUG)

    //if (auto r = texture_.lock()) {
    auto pos = position_;
    auto rect = current_animation_.GetRectangle();
    auto width = rect.GetWidth();
    auto height = rect.GetHeight();

    //r->Render(
    texture_->Render(
        pos.x_ + width * 0.5f,
        pos.y_ + height * 0.5f,
        angle_,
        rect);
//} // if


    return true;
}

bool sh::Bullet::Release(void) {
    return true;
}

void sh::Bullet::Fire(const sh::Vector2 position, const float angle, const sh::Vector2 speed) {
        // 既に発射していれば処理しない
    this->is_show_ = true;

    // アニメーションを発射中のものに変更
    this->state_ = BulletState::MOVE;
    this->current_animation_ = move_animation_;
    this->current_animation_.Initialize();


    // 描画位置設定
    super::position_ = position;
    super::angle_ = angle;
    super::speed_ = speed;
}

bool sh::Bullet::MakeAnimation(sh::BulletColor color) {
    // 発射中のアニメーション設定
    move_animation_.MakeAnimation(
        32.0f, 32.0f, 1, 3,
        { 0.0f,
        32.0f * static_cast<float>(color) });
    hit_animation_.MakeAnimation(
        32.0f, 32.0f, 1, 3,
        { 0.0f + 96.0f,
        32.0f * static_cast<float>(color) });
    return true;
}

void sh::Bullet::Cliping(void) {
    auto pos = position_;
    auto rect = current_animation_.GetRectangle();
    // 画面外に出れば見えなくなる
    if (pos.x_ <= 0 - rect.GetWidth() ||
        pos.x_ >= sh::kWindowWidth + rect.GetWidth() ||
        pos.y_ <= 0 - rect.GetHeight() ||
        pos.y_ >= sh::kWindowHeight + rect.GetHeight()) {
        is_show_ = false;
    } // if
}
