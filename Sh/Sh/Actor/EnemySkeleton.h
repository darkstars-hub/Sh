//!---------------------------------------------------------
//! @file EnemySkeleton.h
//! @brief 骸骨エネミー　ボス
//! @author name
//! @date 2019/01/18
//!---------------------------------------------------------


#ifndef SH_ENEMY_SKELETON
#define SH_ENEMY_SKELETON

#include "Enemy.h"

namespace {
constexpr float destination_positions[10]{
    512.0f, 584.0f,
    712.0f, 384.0f,
    612.0f, 184.0f,
    412.0f, 184.0f,
    312.0f, 384.0f
};
}

namespace sh {
class EnemySkeleton final : public sh::Enemy {
    using super = sh::Enemy;
public:
    EnemySkeleton();
    ~EnemySkeleton() = default;
    EnemySkeleton(const EnemySkeleton& rhs) = delete;
    EnemySkeleton& operator=(const EnemySkeleton& rhs) = delete;
    EnemySkeleton(EnemySkeleton&& rhs) = delete;
    EnemySkeleton& operator= (EnemySkeleton&& rhs) = delete;

    virtual sh::Rectangle GetRectangle(void) const noexcept override;

    virtual bool Render(void) override;
    
    virtual void SetUp(void) override;
    virtual void Move(void) override;
    virtual void Attack(void) override;
    virtual void Damage(const int damage_value)override;
};
}
#endif // !SH_ENEMY_SKELETON