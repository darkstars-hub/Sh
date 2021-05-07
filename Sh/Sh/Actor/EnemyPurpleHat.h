//!---------------------------------------------------------
//! @file EnemyPurpleHat.h
//! @brief 紫の防止を付けているエネミー
//! @author name
//! @date 2019/01/14
//!---------------------------------------------------------


#ifndef SH_ENEMY_PURPLE_HAT
#define SH_ENEMY_PURPLE_HAT

#include "Enemy.h"

namespace sh {
class EnemyPurpleHat final : public sh::Enemy {
    using super = sh::Enemy;
public:
    EnemyPurpleHat();
    ~EnemyPurpleHat() = default;
    EnemyPurpleHat(const EnemyPurpleHat& rhs) = delete;
    EnemyPurpleHat& operator=(const EnemyPurpleHat& rhs) = delete;
    EnemyPurpleHat(EnemyPurpleHat&& rhs) = delete;
    EnemyPurpleHat& operator= (EnemyPurpleHat&& rhs) = delete;

    virtual void Move(void) override;
    virtual void SetUp(void) override;
};
}
#endif // !SH_ENEMY_PURPLE_HAT