//!---------------------------------------------------------
//! @file Camera.cpp
//! @brief ゲーム内の視点位置を持つクラス
//!  Gameクラスのメンバとなる
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#include "Camera.h"

#include "Application.h"


sh::Camera::Camera()
    : view_point_(sh::Vector2(0.0f, 0.0f)) {
}
sh::Camera::~Camera() {
}

sh::Vector2* sh::Camera::GetViewPoint(void) {
    return &view_point_;
}

float sh::Camera::GetWindowTop(void) const noexcept {
    auto height = sh::kWindowHeight * 0.5f;
    return view_point_.y_ + height;
}
float sh::Camera::GetWindowBottom(void) const noexcept {
    auto height = sh::kWindowHeight * 0.5f;
    return view_point_.y_ - height;
}
float sh::Camera::GetWindowRight(void) const noexcept {
    auto width = sh::kWindowWidth * 0.5f;
    return view_point_.x_ + width;
}
float sh::Camera::GetWindowLeft(void) const noexcept {
    auto width = sh::kWindowWidth * 0.5f;
    return view_point_.x_ - width;
}

void sh::Camera::Update(void) {
    auto game_pad =
        sh::Application::GetInstance().GetGamePad();

    auto x = 
        game_pad->GetRightThumbX() / game_pad->GetThreshold();
    auto y = 
        game_pad->GetRightThumbY() / game_pad->GetThreshold();

    if (std::fabs(x) < 0.5f) {
        x = 0.0f;
    } // if
    if (std::fabs(y) < 0.5f) {
        y = 0.0f;
    } // if

//    view_point_.x_ += x;
//    view_point_.y_ += y;
    
    ::glOrtho(
        0.0 + static_cast<double>(view_point_.x_),
        sh::kWindowWidth + static_cast<double>(view_point_.x_),
        0.0 + static_cast<double>(view_point_.y_),
        sh::kWindowHeight + static_cast<double>(view_point_.y_),
        -1.0,
        1.0);
}