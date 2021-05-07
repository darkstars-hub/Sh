//!---------------------------------------------------------
//! @file Actor.h
//! @brief äÓíÍÉNÉâÉX
//! åpè≥êÊ Player, Enemy
//! @author name
//! @date 2019/11/06
//!---------------------------------------------------------


#ifndef SH_ACTOR_H
#define SH_ACTOR_H

#include <memory>

#include "Object.h"
#include "Helper.h"
#include "Rectangle.h"
#include "Animation.h"
#include "ResourceManager.h"
#include "EventListener.h"
#include "EventMessenger.h"


namespace sh {
enum class ActorType {
    NONE,
    PLAYER,
    ENEMY,
    COUNT_MAX
    /*
    ENEMY_CROWN,
    ENEMY_PURPLE_HAT,
    ENEMY_BLUE_HAT,
    ENEMY_YELLOW_HAT,
    ENEMY_BLACK_HAT,
    ENEMY_SKELETON,
    */

};
class Motion;
class Actor : public sh::Object {
    using super = sh::Object;
public:
    friend Motion;

    Actor();
    virtual ~Actor();
    Actor(const Actor& rhs) = default;
    Actor& operator=(const Actor& rhs) = default;
    Actor(Actor&& rhs) = default;
    Actor& operator= (Actor&& rhs) = default;

    void SetTargetPosition(const sh::Vector2 position);
    virtual sh::ActorType GetType(void) const noexcept;
    virtual sh::Vector2 GetTargetPosition(void) const noexcept;
    virtual sh::Rectangle GetRectangle(void) const noexcept = 0;

    virtual bool Initialize(void) = 0;
    virtual bool Update(void) = 0;
    virtual bool Render(void) = 0;
    virtual bool Release(void) = 0;

    virtual void AcquireTexture(sh::ResourceManager& container) = 0;
    virtual void Damage(const int damage_value) = 0;
protected:
    ActorType   actor_type_;
    sh::Vector2 speed_limit_;
    sh::Vector2 target_position_;
    sh::Vector2 initial_position_;
    sh::EventListener* listener_;
};
}
#endif // !SH_ACTOR_H