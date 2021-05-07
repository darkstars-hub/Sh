#include "SelectCursor.h"

#include "Application.h"

sh::SelectCursor::SelectCursor() :
    texture_(),
    icon_size_(32.0f),
    cursor_position_(600.0f, 600.0f),
    on_texture_(false),
    cursor_rect_(),
    animation_() {
}

sh::Rectangle sh::SelectCursor::GetRectangle(void) const noexcept {
    return this->cursor_rect_;
}

bool sh::SelectCursor::OnStartLogo(void) const noexcept {
    return this->on_texture_;
}

void sh::SelectCursor::SetOnStartLogo(const bool b) {
    this->on_texture_ = b;
}

void sh::SelectCursor::Initialize(void) {
    texture_.Load("../textures/pipo-halloweenchara2016_20.png");
    animation_.MakeAnimation(icon_size_, icon_size_, 1, 3);
}
void sh::SelectCursor::Update(void) {
    animation_.Update();
    this->MoveCursor();
    this->Cliping();
}
void sh::SelectCursor::Render(void) {
    auto g = sh::Graphics();
#ifdef _DEBUG
    g.DrawRectangle(cursor_rect_, Color(0, 255, 0, 255));
#endif // _DEBUG

    const auto rect = on_texture_ ?
        animation_.GetRectangle() :
        sh::Rectangle(0.0f, 0.0f, 32.0f, 32.0f);

    texture_.Render(cursor_position_, 0.0f, rect);
}
void sh::SelectCursor::Release(void) {
    texture_.Release();
}

void sh::SelectCursor::MoveCursor(void) {
    auto pad = sh::Application::GetInstance().GetGamePad();

    auto x =
        pad->GetLeftThumbX() / pad->GetThreshold();
    auto y =
        pad->GetLeftThumbY() / pad->GetThreshold();

    // ‚¿‚á‚ñ‚Æ“|‚³‚È‚¢‚Æ“®‚©‚È‚¢
    if (std::fabs(x) <= 0.3f) {
        x = 0.0f;
    } // if
    if (std::fabs(y) <= 0.3f) {
        y = 0.0f;
    } // if

    // ˆÚ“®
    cursor_position_.x_ += x * 10.0f;
    cursor_position_.y_ += y * 10.0f;

    this->Cliping();

    cursor_rect_ = sh::Rectangle(
        cursor_position_.x_ - icon_size_ * 0.5f,
        cursor_position_.y_ - icon_size_ * 0.5f,
        cursor_position_.x_ + icon_size_ * 0.5f,
        cursor_position_.y_ + icon_size_ * 0.5f);
}

void sh::SelectCursor::Cliping(void) {

    if (cursor_position_.x_ < 0.0f) {
        cursor_position_.x_ = 0.0f;
    } // if
    else if (cursor_position_.x_ > sh::kWindowWidth - icon_size_) {
        cursor_position_.x_ = sh::kWindowWidth - icon_size_;
    } // else if
    if (cursor_position_.y_ < 0.0f) {
        cursor_position_.y_ = 0.0f;
    } // if
    else if (cursor_position_.y_ > sh::kWindowHeight - icon_size_) {
        cursor_position_.y_ = sh::kWindowHeight - icon_size_;
    } // else if
}