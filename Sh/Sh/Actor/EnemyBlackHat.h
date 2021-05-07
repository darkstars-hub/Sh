//!---------------------------------------------------------
//! @file EnemyBlackHat.h
//! @brief シルクハットを付けているエネミー
//! @author name
//! @date 2019/01/14
//!---------------------------------------------------------


#ifndef SH_ENEMY_BLACK_HAT
#define SH_ENEMY_BLACK_HAT

#include "Enemy.h"

namespace sh {
class EnemyBlackHat final : public sh::Enemy {
    using super = sh::Enemy;
public:
    EnemyBlackHat();
    ~EnemyBlackHat() = default;
    EnemyBlackHat(const EnemyBlackHat& rhs) = delete;
    EnemyBlackHat& operator=(const EnemyBlackHat& rhs) = delete;
    EnemyBlackHat(EnemyBlackHat&& rhs) = delete;
    EnemyBlackHat& operator= (EnemyBlackHat&& rhs) = delete;


    virtual void Move(void) override;
    virtual void SetUp(void) override;
};
}
#endif // !SH_ENEMY_BLACK_HAT