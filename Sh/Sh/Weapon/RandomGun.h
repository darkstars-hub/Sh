//!---------------------------------------------------------
//! @file RandomGun.h
//! @brief Bullet‚ð‚½‚­‚³‚ñŒ‚‚Â
//! @author name
//! @date 2019/12/02
//!---------------------------------------------------------


#ifndef SH_RANDOM_GUN
#define SH_RANDOM_GUN


#include "Weapon.h"
#include "Bullet.h"

namespace sh {
class RandomGun : public sh::Weapon {
    using super = sh::Weapon;
public:
    RandomGun();
    ~RandomGun();
    RandomGun(const RandomGun& rhs) = delete;
    RandomGun& operator=(const RandomGun& rhs) = delete;
    RandomGun(RandomGun&& rhs) = delete;
    RandomGun& operator= (RandomGun&& rhs) = delete;

    virtual int GetCost(void) override;
    virtual void Fire(void) override;
private:
    float target_angle_p;
    float target_angle_m;
};
}
#endif // !SH_RANDOM_GUN