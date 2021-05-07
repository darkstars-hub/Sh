#include "SelectLogo.h"

#include "SystemSound.h"

sh::SelectLogo::SelectLogo() :
    logo_active_(),
    logo_negative_(),
    position_((sh::kWindowWidth * 0.5f - logo_active_.GetWidth()) * 0.5f, -80.0f),
    start_rect_(),
    is_select_(false){
}
sh::Rectangle sh::SelectLogo::GetRectangle(void) const noexcept {
    return this->start_rect_;
}
void sh::SelectLogo::Initialize(void) {
    logo_active_.Load("../textures/select_logo_active.png");
    logo_negative_.Load("../textures/select_logo_negative.png");

    auto offset_x = 120.0f;
    auto offset_y = 120.0f;
    start_rect_ = sh::Rectangle(position_.x_ + offset_x,
                                position_.y_ + offset_y,
                                position_.x_ - offset_x + logo_active_.GetWidth(),
                                position_.y_ - offset_y + logo_active_.GetHeight());

}
void sh::SelectLogo::Update(const sh::Rectangle cursor_rect) {
    auto rect = this->GetRectangle();

    if (rect.CollisionRectangle(cursor_rect)) {
        if (! is_select_) {
            sh::SystemSound::Singleton().PlaySelect();
        } // if
        is_select_ = true;
    } // if
    else {
        is_select_ = false;
    } // else
}
void sh::SelectLogo::Render(const sh::Rectangle cursor_rect) {
    auto rect = this->GetRectangle();

#ifdef _DEBUG
    auto g = sh::Graphics();
    g.DrawRectangle(rect, sh::Color(120, 120, 120, 250));
#endif // _DEBUG

    const auto pos = position_;
    if (rect.CollisionRectangle(cursor_rect)) {
        logo_active_.Render(pos.x_, pos.y_);
    } // if
    else {
        logo_negative_.Render(pos.x_, pos.y_);
    } // else
}
void sh::SelectLogo::Release(void) {
    logo_active_.Release();
    logo_negative_.Release();
}