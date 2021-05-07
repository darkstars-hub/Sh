//!---------------------------------------------------------
//! @file EnemyYellowHat.h
//! @brief 卵を付けているエネミー
//! @author name
//! @date 2019/01/14
//!---------------------------------------------------------


#ifndef SH_ENEMY_YELLOW_HAT
#define SH_ENEMY_YELLOW_HAT

#include "Enemy.h"

namespace sh {
class EnemyYellowHat final : public sh::Enemy {
    using super = sh::Enemy;
public:
    EnemyYellowHat();
    ~EnemyYellowHat() = default;
    EnemyYellowHat(const EnemyYellowHat& rhs) = delete;
    EnemyYellowHat& operator=(const EnemyYellowHat& rhs) = delete;
    EnemyYellowHat(EnemyYellowHat&& rhs) = delete;
    EnemyYellowHat& operator= (EnemyYellowHat&& rhs) = delete;

    virtual void Move(void) override;
    virtual void SetUp(void) override;
};
}
#endif // !SH_ENEMY_YELLOW_HAT