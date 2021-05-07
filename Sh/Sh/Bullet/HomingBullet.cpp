#include "HomingBullet.h"

sh::HomingBullet::HomingBullet() :
    target_enemy_(nullptr),
    search_range_(100.0f) {
    super::type_ = sh::BulletType::Homing;
}

sh::HomingBullet::~HomingBullet() {
}

void sh::HomingBullet::SetTargetEnemy(sh::Actor* enemy) {
    this->target_enemy_ = enemy;
}

sh::Rectangle sh::HomingBullet::GetRectangle(void) const noexcept {
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

int sh::HomingBullet::GetAttackValue(void) const noexcept {
    return this->attack_value_;
}

sh::Circle sh::HomingBullet::GetSearchArea(void) {
    return sh::Circle(
        search_range_,
        position_.x_ + this->GetRectangle().GetWidth() * 0.5f,
        position_.y_ + this->GetRectangle().GetHeight() * 0.5f);
}

bool sh::HomingBullet::Update(void) {
    if (!is_show_) {
        return true;
    } // if

   move_.Zero();
    if (target_enemy_) {
        auto direction = std::atan2(
            target_enemy_->GetPosition().y_ - super::position_.y_,
            target_enemy_->GetPosition().x_ - super::position_.x_);
        super::speed_.x_ = std::cos(direction) * super::speed_limit_.y_;
        super::speed_.y_ = std::sin(direction) * super::speed_limit_.y_;
    } // if
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


    auto pos = position_;
    auto rect = current_animation_.GetRectangle();
    auto radian = std::atan2f(
        speed_.y_,
        speed_.x_);
    auto degree = radian * 180.0f / 3.141592f;
    angle_ = degree - 90.0f;


    super::Cliping();

    return true;
}

bool sh::HomingBullet::Render(void) {
    super::Render();
#ifdef _DEBUG
    auto g = sh::Graphics();
    g.DrawCircle(this->GetSearchArea(), sh::Color(200, 200, 100, 100));
#endif // _DEBUG


    return true;
}

bool sh::HomingBullet::MakeAnimation(void) {
    super::MakeAnimation(sh::BulletColor::BLACK);
    return true;
}