//!---------------------------------------------------------
//! @file EnemyCrown.h
//! @brief 王冠を付けているエネミー
//! @author name
//! @date 2019/01/14
//!---------------------------------------------------------


#ifndef SH_ENEMY_CROWN
#define SH_ENEMY_CROWN

#include "Enemy.h"

namespace sh {
class EnemyCrown final : public sh::Enemy {
    using super = sh::Enemy;
public:
    EnemyCrown();
    ~EnemyCrown() = default;
    EnemyCrown(const EnemyCrown& rhs) = delete;
    EnemyCrown& operator=(const EnemyCrown& rhs) = delete;
    EnemyCrown(EnemyCrown&& rhs) = delete;
    EnemyCrown& operator= (EnemyCrown&& rhs) = delete;

    /*
    virtual void Move(void) override;
    virtual void SetUp(void) override;
    */
};
}
#endif // !SH_ENEMY_CROWN