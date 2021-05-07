//!---------------------------------------------------------
//! @file Object.cpp
//! @brief äÓíÍÉNÉâÉX
//! åpè≥êÊ Actor, Bullet, Effect
//! @author name
//! @date 2019/11/06
//!---------------------------------------------------------


#ifndef SH_OBJECT_H
#define SH_OBJECT_H


#include "Helper.h"
#include "Vector2.h"
#include "Rectangle.h"


namespace sh {
class Object {
public:
    Object();
    virtual ~Object();
    Object(const Object& rhs) = default;
    Object& operator=(const Object& rhs) = default;
    Object(Object&& rhs) noexcept = default;
    Object& operator= (Object&& rhs) noexcept = default;

    virtual void SetPosition(const sh::Vector2 position);
    virtual void SetMove(const sh::Vector2 move);
    virtual void SetSpeed(const sh::Vector2 speed);
    virtual sh::Vector2 GetPosition(void) const noexcept;
    virtual sh::Vector2 GetMove(void) const noexcept;
    virtual sh::Vector2 GetSpeed(void) const noexcept;
    virtual float GetAngle(void) const noexcept;
    virtual bool IsShow(void) const noexcept;
    virtual sh::Rectangle  GetRectangle(void) const noexcept = 0;

    virtual bool Initialize(void) = 0;
    virtual bool Update(void) = 0;
    virtual bool Render(void) = 0;
    virtual bool Release(void) = 0;
protected:
    sh::Vector2  position_;
    sh::Vector2  move_;
    sh::Vector2  speed_;
    float        angle_;
    bool         is_show_;
};
}
#endif // !SH_OBJECT_H