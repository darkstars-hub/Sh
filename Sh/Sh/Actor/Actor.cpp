#include "Actor.h"

sh::Actor::Actor() :
    super(),
    actor_type_(sh::ActorType::NONE),
    speed_limit_(),
    target_position_(),
    initial_position_(),
    listener_(nullptr){
}

sh::Actor::~Actor() {
}


void sh::Actor::SetTargetPosition(const sh::Vector2 position) {
    this->target_position_ = position;
}

sh::ActorType sh::Actor::GetType(void) const noexcept {
    return this->actor_type_;
}

sh::Vector2 sh::Actor::GetTargetPosition(void) const noexcept {
    return this->target_position_;
}