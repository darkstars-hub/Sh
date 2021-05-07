//!---------------------------------------------------------
//! @file EnemyFactory.h
//! @brief Actorのファクトリークラス
//! @author name
//! @date 2019/11/02
//!---------------------------------------------------------

#ifndef SH_ACTOR_FACTORY_H
//!---------------------------------------------------------
//! @def SH_ACTOR_FACTORY_H
//! @brief include gurad
//!---------------------------------------------------------
#define SH_ACTOR_FACTORY_H

#include <memory>

#include "Actor.h"
#include "Enemy.h"
#include "Helper.h"
#include "Texture.h"
#include "ResourceManager.h"

namespace sh {
class EnemyFactory {
public:
    EnemyFactory();
    ~EnemyFactory();
    EnemyFactory(const EnemyFactory& rhs) = delete;
    EnemyFactory(EnemyFactory&& rhs) = delete;
    EnemyFactory& operator=(const EnemyFactory& rhs) = delete;
    EnemyFactory& operator=(EnemyFactory&& rhs) = delete;

    void SetResourceManager(sh::ResourceManager& resource_manager);
    //std::shared_ptr<sh::Enemy> Create(const sh::ActorType type) const;
    sh::Enemy* PlaceCreate(const sh::EnemyType type, sh::Enemy* place) const;
private:
    std::shared_ptr<sh::Texture> king_;
    std::shared_ptr<sh::Texture> purple_;
    std::shared_ptr<sh::Texture> blue_;
    std::shared_ptr<sh::Texture> yellow_;
    std::shared_ptr<sh::Texture> black_;
    std::shared_ptr<sh::Texture> skeleton_;
 //std::array <  std::shared_ptr<sh::Texture>, sh::EnemyType::COUNT_MAX>
    sh::ResourceManager* resource_manager_;
};
}
#endif // !SH_ACTOR_FACTORY_H