//!---------------------------------------------------------
//! @file Boomerang.h
//! @brief Player‚ªBullet‚Ì‚æ‚¤‚ÉŽg‚¤ƒNƒ‰ƒX
//!        ˆê’è‹——£“®‚¢‚½Œã–ß‚Á‚Ä‚­‚é
//! @author name
//! @date 2020/01/06
//!---------------------------------------------------------

#ifndef SH_BOOMERANG_H
#define SH_BOOMERANG_H

#include <memory>

#include "Bullet.h"
#include "Helper.h"
#include "Circle.h"
#include "Graphics.h"
#include "Color.h"
#include "Actor.h"

namespace sh {
class Boomerang : public sh::Bullet {
    using super = sh::Bullet;
public:
    Boomerang();
    ~Boomerang();
    Boomerang(const sh::Boomerang& rhs) = default;
    Boomerang& operator=(const sh::Boomerang& rhs) = default;
    Boomerang(Boomerang&& rhs) = default;
    Boomerang& operator= (Boomerang&& rhs) = default;

    void SetUser(sh::Actor* user);
    sh::Rectangle GetRectangle(void) const noexcept override;
    int GetAttackValue(void) const noexcept override;
    
    bool Update(void) override;
    bool Render(void) override;

    bool MakeAnimation(void);
private:
    sh::Actor* user_;
    const float moved_distance_limit_;
    sh::Vector2 moved_distance_;
};
}
#endif // !SH_BOOMERANG_H