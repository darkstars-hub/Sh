#include "HitPoint.h"

sh::HitPoint::HitPoint() :
    value_(0),
    texture_(),
    animation_(std::make_unique<sh::Animation>()) {
}

sh::HitPoint::~HitPoint() {
    animation_->ResetRectangles();
}

void sh::HitPoint::SetTexture(const std::shared_ptr<sh::Texture> texture) {
    this->texture_ = texture;
    this->MakeAnimation();
}


bool sh::HitPoint::Initialize(int init_value) {
    this->value_ = init_value;
    return true;
}

bool sh::HitPoint::Update(void) {
    animation_->Update();
    return true;
}

bool sh::HitPoint::Render(float x, float y) const {
    auto w = animation_->GetRectangle().GetWidth();
    auto h = animation_->GetRectangle().GetHeight();
    
    if (auto r = texture_.lock()) {
        r->Render(
            x + w * 0.5f,
            y + h * 0.5f,
            0.0f,
            animation_->GetRectangle());
    } // if

    return true;
}

int sh::HitPoint::GetValue(void) const noexcept {
    return this->value_;
}

bool sh::HitPoint::Damage(const int damage_value) {
    this->value_ -= damage_value;
    return true;
}

void sh::HitPoint::MakeAnimation(void) {
    // アニメーション設定
    animation_->MakeAnimation(120.0f, 120.0f, 1, 5);
}