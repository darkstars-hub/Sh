#include "Boomerang.h"

sh::Boomerang::Boomerang() :
    user_(nullptr),
    moved_distance_limit_(300.0f),
    moved_distance_() {
    type_ = sh::BulletType::Boomerang;
    rect_offset_ = 7.0f;
}

sh::Boomerang::~Boomerang() {
}

void sh::Boomerang::SetUser(sh::Actor* user) {
    this->user_ = user;
}

sh::Rectangle sh::Boomerang::GetRectangle(void) const noexcept {
    
    auto pos = position_;
    auto width = current_animation_.GetRectangle().GetWidth();
    auto height = current_animation_.GetRectangle().GetHeight();

    return sh::Rectangle(
        pos.x_ + rect_offset_, 
        pos.y_ + rect_offset_,
        pos.x_ - rect_offset_ + width,
        pos.y_ - rect_offset_ + height);
}

int sh::Boomerang::GetAttackValue(void) const noexcept {
    return this->attack_value_;
}

bool sh::Boomerang::Update(void) {
    if (!is_show_) {
        return true;
    } // if


    moved_distance_.x_ += std::abs(move_.x_);
    moved_distance_.y_ += std::abs(move_.y_);
    if (moved_distance_limit_ * moved_distance_limit_ <
        moved_distance_.x_ * moved_distance_.x_ +
        moved_distance_.y_ * moved_distance_.y_) {

        auto direction = std::atan2(
            user_->GetPosition().y_ - super::position_.y_,
            user_->GetPosition().x_ - super::position_.x_);
        super::move_.x_ = std::cos(direction) * super::speed_limit_.y_;
        super::move_.y_ = std::sin(direction) * super::speed_limit_.y_;

        super::angle_ += 15.0f;
        if (super::angle_ >= 360.0f) {
            super::angle_ = 0.0f;
        } // if
        super::state_ = BulletState::HIT;
    } // if
    else {
        super::move_ = super::speed_;
        super::angle_ -= 15.0f;
        if (super::angle_ <= 0.0f) {
            super::angle_ = 360.0f;
        } // if
    } // else
    super::current_animation_.Update();

    switch (state_) {
        case BulletState::MOVE:
            position_ += move_;
            break;
        case BulletState::HIT:
            position_ += move_;
            break;
        default:
            break;
    } // switch

    this->Cliping();
    return true;
}

bool sh::Boomerang::Render(void) {
    super::Render();
    return true;
}

bool sh::Boomerang::MakeAnimation(void) {
        // 発射中のアニメーション設定
    move_animation_.MakeAnimation(
        32.0f, 32.0f, 1, 5);
    hit_animation_.MakeAnimation(
        0.0f, 0.0f, 1, 1);
    return true;
}