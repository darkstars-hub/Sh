#include "Icon.h"

#include "Application.h"
#include "SystemSound.h"

sh::Icon::Icon() :
    position_(),
    anime_width_(1.0f),
    anime_height_(1.0f),
    scale_(1.0f),
    texture_(),
    select_animation_(),
    animation_(),
    rect_(),
    is_select_(false),
    under_cursor_(false) {
}

bool sh::Icon::UnderCursor(void) const noexcept {
    return this->under_cursor_;
}
bool sh::Icon::IsSelect(void) const noexcept {
    return this->is_select_;
}
void sh::Icon::SetSelected(const bool is_selected) {
    this->is_select_ = is_selected;
}

sh::Rectangle sh::Icon::GetRectangle(void) const noexcept {
    return this->rect_;
}

void sh::Icon::Initialize(const sh::Vector2 position, std::shared_ptr< sh::Texture> texture,
                          const float scale) {
    this->position_ = position;
    this->texture_ = texture;
    this->scale_ = scale;

    rect_ = sh::Rectangle(
        position.x_,
        position.y_,
        position.x_ + scale_ * anime_width_,
        position.y_ + scale_ * anime_height_);
}
void sh::Icon::Update(const sh::Rectangle cursor_rect) {
    auto pad = sh::Application::GetInstance().GetGamePad();
    if (pad->IsPress(sh::GamePadInfo::BUTTON_A)) {
        if (this->under_cursor_) {
            if (!this->is_select_) {
                sh::SystemSound::Singleton().PlayDecide();
            } // if
            this->is_select_ = true;
        } // if
    } // if

    if (rect_.CollisionRectangle(cursor_rect)) {
        if (!this->under_cursor_) {
            sh::SystemSound::Singleton().PlaySelect();
        } // if
        this->under_cursor_ = true;
    } // if
    else {
        this->under_cursor_ = false;
    } // else

    if (pad->IsPress(sh::GamePadInfo::BUTTON_B)) {
        this->is_select_ = false;
        sh::SystemSound::Singleton().PlayCancel();
    } // else


    animation_.Update();
    select_animation_.Update();
}
void sh::Icon::Render(void) {
#ifdef _DEBUG
    auto g = sh::Graphics();
    const auto c = is_select_ ? sh::Color(120, 220, 120, 250) : sh::Color(220, 220, 120, 250);
    g.DrawRectangle(rect_, c);
#endif // _DEBUG    

    if (auto tex = texture_.lock()) {
        auto rect = animation_.GetRectangle();
        if (under_cursor_ || is_select_) {
            rect = select_animation_.GetRectangle();
        } // if

        auto width = rect.GetWidth() * scale_;
        auto height = rect.GetHeight() * scale_;
        tex->Render(
            position_.x_ + width * 0.5f,
            position_.y_ + height * 0.5f,
            0.0f, rect,
            scale_);
    } // if
}
void sh::Icon::MakeAnimation(
    const sh::MakeAnime animation,
    const sh::MakeAnime select_animation) {
    animation_.MakeAnimation(animation);
    select_animation_.MakeAnimation(select_animation);

    animation_.SetRate(3);
    select_animation_.SetRate(3);

    this->anime_width_ = animation.width;
    this->anime_height_ = animation.height;
}