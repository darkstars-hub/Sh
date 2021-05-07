//!---------------------------------------------------------
//! @file ThreeWayGun.h
//! @brief Bullet‚ð3”­Œ‚‚Â
//! @author name
//! @date 2019/11/06
//!---------------------------------------------------------


#ifndef SH_THREE_WAY_GUN_H
#define SH_THREE_WAY_GUN_H


#include "Weapon.h"
#include "Bullet.h"


namespace sh {
class ThreeWayGun : public sh::Weapon {
    using super = sh::Weapon;
public:
    ThreeWayGun();
    ~ThreeWayGun();
    ThreeWayGun(const ThreeWayGun& rhs) = delete;
    ThreeWayGun& operator=(const ThreeWayGun& rhs) = delete;
    ThreeWayGun(ThreeWayGun&& rhs) = delete;
    ThreeWayGun& operator= (ThreeWayGun&& rhs) = delete;

    virtual int GetCost(void) override;
    virtual void Fire(void) override;
};
}
#endif // !SH_THREE_WAY_GUN_H