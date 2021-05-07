//!---------------------------------------------------------
//! @file EnemyBlueHat.h
//! @brief 青い帽子を付けているエネミー
//! @author name
//! @date 2019/01/14
//!---------------------------------------------------------


#ifndef SH_ENEMY_BLUE_HAT
#define SH_ENEMY_BLUE_HAT

#include "Enemy.h"

namespace sh {
class EnemyBlueHat final : public sh::Enemy {
    using super = sh::Enemy;
public:
    EnemyBlueHat();
    ~EnemyBlueHat() = default;
    EnemyBlueHat(const EnemyBlueHat& rhs) = delete;
    EnemyBlueHat& operator=(const EnemyBlueHat& rhs) = delete;
    EnemyBlueHat(EnemyBlueHat&& rhs) = delete;
    EnemyBlueHat& operator= (EnemyBlueHat&& rhs) = delete;

    virtual void Move(void) override;
    virtual void SetUp(void) override;
};
}
#endif // !SH_ENEMY_BLUE_HAT