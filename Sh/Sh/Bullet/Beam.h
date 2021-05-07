//!---------------------------------------------------------
//! @file Beam.h
//! @brief Player‚ªBullet‚Ì‚æ‚¤‚ÉŽg‚¤ƒNƒ‰ƒX
//! @author name
//! @date 2019/12/12
//!---------------------------------------------------------

#ifndef SH_BEAM_H
#define SH_BEAM_H

#include <memory>

#include "Bullet.h"
#include "Helper.h"
#include "Texture.h"
#include "Animation.h"
#include "Graphics.h"
#include "Color.h"

namespace sh {
class Beam final : public sh::Bullet {
    using super = sh::Bullet;
private:
    struct BeamPosition {
        sh::Vector2 pos;
        sh::Vector2 move;
    };
public:
    Beam();
    ~Beam();
    Beam(const sh::Beam& rhs) = default;
    Beam& operator=(const sh::Beam& rhs) = default;
    Beam(Beam&& rhs) = default;
    Beam& operator= (Beam&& rhs) = default;

    sh::Rectangle GetRectangle(void) const noexcept override;
    int GetAttackValue(void) const noexcept override;
    std::vector<sh::Beam::BeamPosition>& GetPositions(void);
    bool IsEnable(void) const;

    bool Initialize(void) override;
    bool Update(void) override;
    bool Render(void) override;

    void Fire(const sh::Vector2  position, const float angle, const sh::Vector2  speed);
    bool MakeAnimation(void);
private:
    std::vector<int>indices;
    std::vector<BeamPosition> bpos_;

   //sh::Texture circle_texture_;
};
}
#endif // !SH_BEAM_H