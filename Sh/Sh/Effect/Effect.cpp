#include "Effect.h"

sh::Effect::Effect()
    : super(),
    texture_(),
    animation_() {
}
sh::Effect::~Effect() {
}

void sh::Effect::SetTexture(std::shared_ptr<sh::Texture> texture) {
    this->texture_ = texture;
}

sh::Rectangle sh::Effect::GetRectangle(void) const noexcept {
    return sh::Rectangle();
}

bool sh::Effect::Initialize(const sh::EffectType type) {
    this->Initialize();
    this->MakeAnimation(type);
    return true;
}
bool sh::Effect::Initialize(void) {
    is_show_ = false;
    animation_.ResetRectangles();

    return true;
}
bool sh::Effect::Update(void) {
    if (!is_show_) {
        return false;
    } // if
    animation_.Update();
    if (animation_.IsEnd()) {
        this->is_show_ = false;
    } // if
    return true;
}
bool sh::Effect::Render(void) {
    if (!is_show_) {
        return true;
    } // if

    auto pos = position_;
    auto w = animation_.GetRectangle().GetWidth();
    auto h = animation_.GetRectangle().GetHeight();

#if defined (_DEBUG)||(DEBUG)
    {
        //auto g = sh::Graphics<float>();
        //g.DrawRectangle(sh::Rectangle<float>(
        //    pos.x_, pos.y_, pos.x_ + w, pos.y_ + h), sh::Color(0, 0, 255));
    }

#endif // defined(_DEBUG)||(DEBUG)
    if (auto r = texture_.lock()) {
        r->Render(
            pos.x_ + w * 0.5f, pos.y_ + h * 0.5f,
            super::angle_,
            animation_.GetRectangle());
    } // if

    return true;
}
bool sh::Effect::Release() {
    //super::Release();
    return true;
}

void sh::Effect::Start(const sh::Vector2 position) {
    if (!is_show_) {
        animation_.Initialize();

        position_.x_ = position.x_ - animation_.GetRectangle().GetWidth() / 2;
        position_.y_ = position.y_ - animation_.GetRectangle().GetHeight() / 2;
        this->is_show_ = true;
    } // if
}

void sh::Effect::Start(float position_x, float position_y) {
    if (!is_show_) {
        animation_.Initialize();

        position_.x_ = position_x - animation_.GetRectangle().GetWidth() / 2;
        position_.y_ = position_y - animation_.GetRectangle().GetHeight() / 2;
        this->is_show_ = true;
    } // if
}

void sh::Effect::MakeAnimation(const sh::EffectType type) {
    switch (type) {
        case sh::EffectType::DAMAGE:
            animation_.MakeAnimation(120.0f, 120.0f, 1, 5);
            break;
        case sh::EffectType::DEAD:
            animation_.MakeAnimation(120.0f, 120.0f, 1, 8);
            break;
        case sh::EffectType::GAME_START:
            animation_.MakeAnimation(640.0f, 480.0f, 2, 5);
            break;
            /*
        case sh::EffectType::GAME_CLEAR:
            animation_.MakeAnimation(640.0f, 480.0f, 2, 5);
            break;
        case sh::EffectType::GAME_OVER:
            animation_.MakeAnimation(640.0f, 480.0f, 2, 5);
            break;
        case sh::EffectType::GAME_LOGO:
            animation_.MakeAnimation(640.0f, 480.0f, 2, 5);
            break;
            */

        case sh::EffectType::COUNT_MAX:
            break;
        default:
            break;
    } // switch
}
