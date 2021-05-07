#ifndef SH_BULLET_MANAGER_H
#define SH_BULLET_MANAGER_H

#include <vector>
#include <memory>

#include "Helper.h"
#include "Bullet.h"
#include "BulletFactory.h"
#include "EventListener.h"
#include "ResourceManager.h"

#include "Beam.h"

namespace sh {
class BulletManager {
public:
    BulletManager();
    ~BulletManager();
    BulletManager(const sh::BulletManager& rhs) = default;
    BulletManager& operator=(const sh::BulletManager& rhs) = default;
    BulletManager(BulletManager&& rhs) = default;
    BulletManager& operator= (BulletManager&& rhs) = default;

    void SetUpBulletFactory(sh::ResourceManager& resource_manager);

    std::vector<std::shared_ptr<sh::Bullet>>& GetEnemyBullets(void);
    std::vector<std::shared_ptr<sh::Bullet>>& GetPlayerBullets(void);

    bool Update(void);
    bool Render(void);
    bool Release(void);
private:
    std::vector< std::shared_ptr<sh::Beam>> beam_pointers_;
    sh::BulletFactory bullet_factory_;
    
     //! ”­ŽË‚µ‚½Œã‚ÌBullet‚Ì”z—ñ
    std::vector<std::shared_ptr<sh::Bullet>> player_bullets_;
    std::vector<std::shared_ptr<sh::Bullet>> enemy_bullets_;
    
    sh::EventListener* listener_;

    void PickupEvent(ShotEvent& e,sh::Vector2& pos, float& angle,
                     sh::Vector2& speed, sh::BulletType& type);
};
}
#endif // !SH_BULLET_MANAGER_H