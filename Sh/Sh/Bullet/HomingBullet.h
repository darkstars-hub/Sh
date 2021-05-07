//!---------------------------------------------------------
//! @file HomingBullet.h
//! @brief Player‚ªBullet‚Ì‚æ‚¤‚ÉŽg‚¤ƒNƒ‰ƒX
//!        Enemy‚ð’Ç‚¢‚©‚¯‚é
//! @author name
//! @date 2020/01/06
//!---------------------------------------------------------

#ifndef SH_HOMING_BULLET_H
#define SH_HOMING_BULLET_H

#include <memory>

#include "Bullet.h"
#include "Helper.h"
#include "Circle.h"
#include "Graphics.h"
#include "Color.h"

namespace sh {
class HomingBullet : public sh::Bullet {
    using super = sh::Bullet;
public:
    HomingBullet();
    ~HomingBullet();
    HomingBullet(const sh::HomingBullet& rhs) = default;
    HomingBullet& operator=(const sh::HomingBullet& rhs) = default;
    HomingBullet(HomingBullet&& rhs) = default;
    HomingBullet& operator= (HomingBullet&& rhs) = default;

    void SetTargetEnemy(sh::Actor* enemy);
    sh::Rectangle GetRectangle(void) const noexcept override;
    int GetAttackValue(void) const noexcept override;
    sh::Circle GetSearchArea(void);

    bool Update(void) override;
    bool Render(void) override;

    bool MakeAnimation(void);
private:
    sh::Actor* target_enemy_;
    float search_range_;
};
}
#endif // !SH_HOMING_BULLET_H