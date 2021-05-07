//!---------------------------------------------------------
//! @file ThroughBullet.h
//! @brief Player‚ªBullet‚Ì‚æ‚¤‚ÉŽg‚¤ƒNƒ‰ƒX
//!        Enemy‚ðŠÑ’Ê‚·‚é
//! @author name
//! @date 2020/01/06
//!---------------------------------------------------------

#ifndef SH_THROUGH_BULLET_H
#define SH_THROUGH_BULLET_H

#include <memory>

#include "Bullet.h"
#include "Helper.h"
#include "Circle.h"
#include "Graphics.h"
#include "Color.h"

namespace sh {
class ThroughBullet : public sh::Bullet {
    using super = sh::Bullet;
public:
    ThroughBullet();
    ~ThroughBullet();
    ThroughBullet(const sh::ThroughBullet& rhs) = default;
    ThroughBullet& operator=(const sh::ThroughBullet& rhs) = default;
    ThroughBullet(ThroughBullet&& rhs) = default;
    ThroughBullet& operator= (ThroughBullet&& rhs) = default;

    virtual void SetState(const BulletState state) override;
    sh::Rectangle GetRectangle(void) const noexcept override;
    int GetAttackValue(void) const noexcept override;
    
    bool Update(void) override;
    bool Render(void) override;

    bool MakeAnimation(void);
private:
};
}
#endif // !SH_THROUGH_BULLET_H