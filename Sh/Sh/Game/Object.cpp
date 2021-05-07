#include "Object.h"


sh::Object::Object() :
    position_(),
    move_(),
    speed_(),
    angle_(0.0f),
    is_show_(false){
}

sh::Object::~Object() {
}

void sh::Object::SetPosition(const sh::Vector2 position) {
    this->position_ = position;
}

void sh::Object::SetMove(const sh::Vector2 move) {
    this->move_ = move;
}

void sh::Object::SetSpeed(const sh::Vector2 speed) {
    this->speed_ = speed;
}

sh::Vector2 sh::Object::GetPosition(void) const noexcept {
    return this->position_;
}

sh::Vector2 sh::Object::GetMove(void) const noexcept {
    return this->move_;
}

sh::Vector2 sh::Object::GetSpeed(void) const noexcept {
    return this->speed_;
}
float sh::Object::GetAngle(void) const noexcept {
    return this->angle_;
}

bool sh::Object::IsShow(void) const noexcept {
    return this->is_show_;
}