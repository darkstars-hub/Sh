//!---------------------------------------------------------
//! @file Mine.h
//! @brief BulletÇê›íuÇ∑ÇÈ
//! @author name
//! @date 2019/12/03
//!---------------------------------------------------------


#ifndef SH_MINE_H
#define SH_MINE_H


#include "Weapon.h"
#include "Bullet.h"

namespace sh {
class Mine : public sh::Weapon {
    using super = sh::Weapon;
public:
    Mine();
    ~Mine();
    Mine(const Mine& rhs) = delete;
    Mine& operator=(const Mine& rhs) = delete;
    Mine(Mine&& rhs) = delete;
    Mine& operator= (Mine&& rhs) = delete;

    virtual int GetCost(void) override;
    virtual void Fire(void) override;
};
}
#endif // !SH_MINE_H