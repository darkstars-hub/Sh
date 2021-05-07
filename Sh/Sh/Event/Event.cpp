#include "Event.h"

sh::Event::Event() :
    destination_id_(sh::ClassID::NONE),
    id_(sh::EventID::NONE) {
}

sh::Event::~Event() {
}

sh::ShotEvent::ShotEvent() :
    position_(),
    angle_(),
    speed_(),
    bullet_type_(sh::ClassID::BULLET) {
}

sh::ShotEvent::~ShotEvent() {
}

sh::EffectEvent::EffectEvent() :
    position_() {
}

sh::EffectEvent::~EffectEvent() {
}
