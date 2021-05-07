//!---------------------------------------------------------
//! @file BulletFactory.h
//! @brief Bulletのファクトリークラス
//! @author name
//! @date 2019/11/02
//!---------------------------------------------------------

#ifndef SH_BULLET_FACTORY_H
//!---------------------------------------------------------
//! @def SH_BULLET_FACTORY_H
//! @brief include gurad
//!---------------------------------------------------------
#define SH_BULLET_FACTORY_H

#include <memory>

#include "Bullet.h"
#include "Bomb.h"
#include "Beam.h"
#include "HomingBullet.h"
#include "ThroughBullet.h"
#include "Boomerang.h"
#include "Helper.h"
#include "Texture.h"
#include "ResourceManager.h"

namespace sh {
class BulletFactory {
public:
    BulletFactory();
    ~BulletFactory();
    BulletFactory(const BulletFactory& rhs) = delete;
    BulletFactory(BulletFactory&& rhs) = delete;
    BulletFactory& operator=(const BulletFactory& rhs) = delete;
    BulletFactory& operator=(BulletFactory&& rhs) = delete;

    void SetTexture(sh::ResourceManager& resource_manager);
    std::shared_ptr<sh::Bullet> Create(
        const sh::BulletColor color = sh::BulletColor::RED,
        const sh::BulletType type = sh::BulletType::Bullet) const;
    std::shared_ptr<sh::Texture> texture_;
    std::shared_ptr<sh::Texture> bomb_texture_;
    std::shared_ptr<sh::Texture> beam_texture_;
    std::shared_ptr<sh::Texture> boomerang_texture_;
private:
};
}
#endif // !SH_BULLET_FACTORY_H