//!---------------------------------------------------------
//! @file NormalGun.h
//! @brief BulletÇíºê¸èÛÇ…åÇÇ¬
//! @author name
//! @date 2019/11/06
//!---------------------------------------------------------


#ifndef SH_NORMAL_GUN_H
#define SH_NORMAL_GUN_H


#include "Weapon.h"
#include "Bullet.h"


namespace sh {
class NormalGun : public sh::Weapon {
    using super = sh::Weapon;
public:
    NormalGun();
    ~NormalGun();
    NormalGun(const NormalGun& rhs) = delete;
    NormalGun& operator=(const NormalGun& rhs) = delete;
    NormalGun(NormalGun&& rhs) = delete;
    NormalGun& operator= (NormalGun&& rhs) = delete;

    virtual int GetCost(void) override;
    virtual void Fire(void) override;
private:
};
}
#endif // !SH_NORMAL_GUN_H