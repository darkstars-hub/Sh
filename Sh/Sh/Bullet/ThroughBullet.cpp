#include "ThroughBullet.h"

sh::ThroughBullet::ThroughBullet() {
    super::type_ = sh::BulletType::Through;
}

sh::ThroughBullet::~ThroughBullet() {
}

void sh::ThroughBullet::SetState(const BulletState state) {
    super::state_ = state;
}

sh::Rectangle sh::ThroughBullet::GetRectangle(void) const noexcept {
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

int sh::ThroughBullet::GetAttackValue(void) const noexcept {
    return this->attack_value_;
}

bool sh::ThroughBullet::Update(void) {
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
            position_ += move_;
            break;
        default:
            break;
    } // switch

    this->Cliping();
    return true;
}

bool sh::ThroughBullet::Render(void) {
    super::Render();
    return true;
}

bool sh::ThroughBullet::MakeAnimation(void) {
    super::MakeAnimation(sh::BulletColor::WHITE);
    return true;
}