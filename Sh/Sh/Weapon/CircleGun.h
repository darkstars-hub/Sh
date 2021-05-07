//!---------------------------------------------------------
//! @file CircleGun.h
//! @brief ‘S•ûˆÊ‚ÉBullet‚ðŒ‚‚Â
//! @author name
//! @date 2019/12/02
//!---------------------------------------------------------


#ifndef SH_CIRCLE_GUN_H
#define SH_CIRCLE_GUN_H


#include "Weapon.h"
#include "Bullet.h"

namespace sh {
class CircleGun : public sh::Weapon {
    using super = sh::Weapon;
public:
    CircleGun();
    ~CircleGun();
    CircleGun(const CircleGun& rhs) = delete;
    CircleGun& operator=(const CircleGun& rhs) = delete;
    CircleGun(CircleGun&& rhs) = delete;
    CircleGun& operator= (CircleGun&& rhs) = delete;

    virtual int GetCost(void) override;
    virtual void Fire(void) override;
};
}
#endif // !SH_CIRCLE_GUN_H