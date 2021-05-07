#ifndef SH_EVENT_H
#define SH_EVENT_H

#include "Helper.h"
#include "Vector2.h"
#include "Object.h"

namespace sh {
enum class EventID {
    NONE,
    SHOT_PLAYER,
    SHOT_ENEMY,
    DAMAGE,
    DEAD,
    GAME_START,
    GAME_CLEAR,
    GAME_OVER,
};
//!Å@Åuà∂êÊÅv
enum class ClassID {
    NONE,
    PLAYER,
    ENEMY,
    NORMAL_GUN,
    THREE_WAY_GUN,
    CIRCLE_GUN,
    RANDOM_GUN,
    MINE,
    SCENE_GAME,
    BULLET_MANAGER,
    SOUND_MANAGER,
    EFFECT_MANAGER,
    BULLET,
    BOMB,
    BEAM,
    BEAM_SHOOTING,
    HOMING,
    THROUGH,
    BOOMERANG,
};

//struct
class Event {
public:
    Event();
    virtual ~Event();
    //sh::ClassID source_id_;

    //! sh::ClassID
    sh::ClassID destination_id_;
    //! sh::EventID
    sh::EventID id_;
};

class ShotEvent : public Event {
public:
    ShotEvent();
    ~ShotEvent();
    sh::Vector2 position_;
    float angle_;
    sh::Vector2 speed_;
    sh::ClassID bullet_type_;
    sh::Object* actor_;
};
class EffectEvent : public Event {
public:
    EffectEvent();
    ~EffectEvent();
    sh::Vector2 position_;
};
}
#endif // !SH_EVENT_H