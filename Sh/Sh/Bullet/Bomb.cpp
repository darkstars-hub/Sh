#include "Bomb.h"

sh::Bomb::Bomb() :
    super() {
    super::type_ = sh::BulletType::Bomb;
}

sh::Bomb::~Bomb() {
}

sh::Rectangle sh::Bomb::GetRectangle(void) const noexcept {
    if (!is_show_) {
    //if (!is_show_ || state_ != BulletState::HIT) {
        return sh::Rectangle();
    } // if

    auto pos = super::position_;
    auto width = current_animation_.GetRectangle().GetWidth();
    auto height = current_animation_.GetRectangle().GetHeight();
    return std::move(sh::Rectangle(
        pos.x_, pos.y_,
        pos.x_ + width, pos.y_ + height));
}

int sh::Bomb::GetAttackValue(void) const noexcept {
    return this->attack_value_;
}



bool sh::Bomb::Update(void) {
    if (!is_show_) {
        return true;
    } // if
    current_animation_.Update();
    
    //! ボムは移動しない こともない
    move_ = speed_;   

    switch (state_) {
        case BulletState::MOVE:
            position_ += move_;
            if (current_animation_.IsEnd()) {
                current_animation_ = hit_animation_;
                state_ = BulletState::HIT;
            } // if
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

    super::Cliping();
    return true;
}

bool sh::Bomb::Render(void) {
    super::Render();
    return true;
}

/*
void sh::Bomb::Fire(const sh::Vector2<float> position, const float angle) {
    is_show_ = true;
    state_ = BulletState::MOVE;
    current_animation_ = move_animation_;
    current_animation_.Initialize();
    position_ = position;
    angle_ = angle;
}
*/

bool sh::Bomb::MakeAnimation(void) {
    if (!texture_) {
        return false;
    } // if
    // アニメーション作成
    move_animation_.MakeAnimation(
        32.0f, 32.0f, 1, 6,
        { 0.0f,
        0.0f });
    hit_animation_.MakeAnimation(
        32.0f, 32.0f, 1, 6,
        { 0.0f,
        160.0f });
    return true;
}