#include "Motion.h"

#include "Application.h"

sh::Motion::Motion()
    :count_(0.0f),
    count_limit_(360.0f),
    wave_amplitude_(10.0f),
    angle_(0.0f),
    set_target_(false),
    target_position_(),
    tacklle_direction_(0.0f) {
}

sh::Motion::~Motion() {
}

void sh::Motion::Initialize(void) {
    //count_ = 0;
    //count_limit_ = 0;
    //wave_amplitude_ = 0;
    angle_ = static_cast<float>(
        sh::GenerateRandom(15, 30));
    set_target_ = false;
    target_position_ = sh::Vector2();
    tacklle_direction_ = 0.0f;
}

void sh::Motion::Control(sh::Actor& obj) {
    auto game_pad = sh::Application::GetInstance().GetGamePad();

    auto x =
        game_pad->GetLeftThumbX() / game_pad->GetThreshold();
    auto y =
        game_pad->GetLeftThumbY() / game_pad->GetThreshold();

    // ‚¿‚á‚ñ‚Æ“|‚³‚È‚¢‚Æ“®‚©‚È‚¢
    if (std::fabs(x) <= 0.3f) {
        x = 0.0f;
    } // if
    if (std::fabs(y) <= 0.3f) {
        y = 0.0f;
    } // if

    // ˆÚ“®
    obj.move_.x_ += x * obj.speed_.x_;
    obj.move_.y_ += y * obj.speed_.y_;

    // ŽÎ‚ßˆÚ“®•â³
    if (std::abs(obj.move_.x_) > 0 && std::abs(obj.move_.y_) > 0) {
        auto r = std::sqrt(obj.move_.x_ * obj.move_.x_ + obj.move_.y_ * obj.move_.y_);
        obj.move_.x_ = obj.move_.x_ * obj.move_.x_ / r * obj.move_.x_ / std::abs(obj.move_.x_);
        obj.move_.y_ = obj.move_.y_ * obj.move_.y_ / r * obj.move_.y_ / std::abs(obj.move_.y_);
    } // if
}
void sh::Motion::Rotate(sh::Actor& obj, float angle, const sh::Vector2 center) {
    float rad = kPi * angle / 180.0f;
    auto pos = obj.position_;

    float axis_x = pos.x_ - center.x_;
    float axis_y = pos.y_ - center.y_;

    float translate_x = (axis_x)*std::cos(rad) - (axis_y)*std::sin(rad);
    float translate_y = (axis_x)*std::sin(rad) + (axis_y)*std::cos(rad);

    pos = Vector2(
        center.x_ + translate_x,
        center.y_ + translate_y);

    obj.position_ = pos;
}


void sh::Motion::LeftYaw(sh::Actor& obj) {
    obj.angle_++;
    if (obj.angle_ >= 360) {
        obj.angle_ = 0;
    } // if
}
void sh::Motion::RightYaw(sh::Actor& obj) {
    obj.angle_--;
    if (obj.angle_ <= 0) {
        obj.angle_ = 360;
    } // if
}

void sh::Motion::Accel(sh::Actor& obj) {
    // ‰Á‘¬
    obj.move_.x_ *= 2;
    obj.move_.y_ *= 2;
}

void sh::Motion::Move(sh::Actor& obj) {
    obj.move_ = obj.speed_;
}

void sh::Motion::Straight(sh::Actor& obj) {
    obj.move_.y_ = obj.speed_.y_;
}

void sh::Motion::Exit(sh::Actor& obj) {
    if (obj.initial_position_.x_ > sh::kWindowWidth * 0.5f) {
        obj.move_.x_ = obj.speed_.x_;
    } // if
    else {
        obj.move_.x_ = -obj.speed_.x_;
    } // else
}

void sh::Motion::Translate(sh::Actor& obj, const sh::Vector2 target) {
    auto direction = std::atan2(
        target.y_ - obj.position_.y_,
        target.x_ - obj.position_.x_);
    obj.speed_.x_ = std::cos(direction) * 3;
    obj.speed_.y_ = std::sin(direction) * 3;

    obj.move_ = obj.speed_;
}

void sh::Motion::Wave(sh::Actor& obj, const float direction) {
    obj.move_.x_ = std::cosf(count_ * sh::kPi / 180.0f) * wave_amplitude_;
    obj.move_.y_ = 5;
    auto angle = direction;

    if (obj.initial_position_.x_ > sh::kWindowWidth * 0.5f) {
        angle *= -1;
        if (angle_ > 0) {
            angle_ *= -1;
        } // if
    } // if

    sh::Rotate(obj.move_.x_, obj.move_.y_, 
               angle + angle_, 
               0, 0);

    count_ += 10;
    if (count_ > count_limit_) {
        count_ = 0.0f;
    } // if
}

void sh::Motion::Tacklle(sh::Actor& obj, const sh::Vector2 target) {
    if (!set_target_) {
        set_target_ = true;
        target_position_ = target;

        tacklle_direction_ = std::atan2(
            target_position_.y_ - obj.position_.y_,
            target_position_.x_ - obj.position_.x_);
    } // if

    obj.speed_.x_ = std::cos(tacklle_direction_) * 7;
    obj.speed_.y_ = std::sin(tacklle_direction_) * 7;

    obj.move_ = obj.speed_;
}