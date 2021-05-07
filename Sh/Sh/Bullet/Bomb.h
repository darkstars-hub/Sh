//!---------------------------------------------------------
//! @file Bomb.h
//! @brief PlayerがBulletのように使うクラス
//!        ボムは移動しない
//! @author name
//! @date 2019/11/13
//!---------------------------------------------------------

#ifndef SH_BOMB_H
#define SH_BOMB_H

#include <memory>

#include "Bullet.h"
#include "Helper.h"
#include "Texture.h"
#include "Animation.h"
#include "Graphics.h"
#include "Color.h"

namespace sh {
class Bomb : public sh::Bullet {
    using super = sh::Bullet;
public:
    Bomb();
    ~Bomb();
    Bomb(const sh::Bomb& rhs) = default;
    Bomb& operator=(const sh::Bomb & rhs) = default;
    Bomb(Bomb && rhs) = default;
    Bomb& operator= (Bomb && rhs) = default;

    sh::Rectangle GetRectangle(void) const noexcept override;
    int GetAttackValue(void) const noexcept override;
    
    bool Update(void) override;
    bool Render(void) override;

    bool MakeAnimation(void);
private:
};
}
#endif // !SH_BOMB_H