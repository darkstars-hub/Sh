//!---------------------------------------------------------
//! @file EnemyFactory.cpp
//! @brief Bulletのファクトリークラス
//! @author name
//! @date 2019/11/02
//!---------------------------------------------------------


#include "EnemyFactory.h"

#include "EnemyCrown.h"
#include "EnemyPurpleHat.h"
#include "EnemyBlackHat.h"
#include "EnemyYellowHat.h"
#include "EnemyBlueHat.h"
#include "EnemySkeleton.h"

sh::EnemyFactory::EnemyFactory() :
    king_(nullptr),
    purple_(nullptr),
    blue_(nullptr),
    yellow_(nullptr),
    black_(nullptr),
    skeleton_(nullptr),
    resource_manager_(nullptr) {
}

sh::EnemyFactory::~EnemyFactory() {
}

void sh::EnemyFactory::SetResourceManager(sh::ResourceManager& resource_manager) {
    this->resource_manager_ = &resource_manager;
}

/*
std::shared_ptr<sh::Enemy>
sh::EnemyFactory::Create(const sh::ActorType type) const {
    switch (type) {
        case ActorType::ENEMY_CROWN:
        {
            //auto result = std::make_shared<sh::Enemy>();
            auto result = std::make_shared<sh::EnemyCrown>();
            result->SetTexture(resource_manager_->GetTexture(
                sh::TextureFileID::ENEMY_TEXTURE_GHOST_KING));
            //result->MakeAnimation();
            return std::move(result);
        } // case
        default:
            break;
    } // switch
    return nullptr;
}
*/

sh::Enemy* sh::EnemyFactory::PlaceCreate(const sh::EnemyType type, sh::Enemy* place) const {
    switch (type) {
        case sh::EnemyType::CROWN:
        {
            auto result = new(place) sh::EnemyCrown();
            result->SetTexture(resource_manager_->GetTexture(
                sh::TextureFileID::ENEMY_TEXTURE_GHOST_KING));
            return std::move(result);
        } // case

        case sh::EnemyType::PURPLE_HAT:
        {
            auto result = new(place) sh::EnemyPurpleHat();
            result->SetTexture(resource_manager_->GetTexture(
                sh::TextureFileID::ENEMY_TEXTURE_PURPLE_HAT));
            return std::move(result);
        } // case

        case sh::EnemyType::BLUE_HAT:
        {
            auto result = new(place) sh::EnemyBlueHat();
            result->SetTexture(resource_manager_->GetTexture(
                sh::TextureFileID::ENEMY_TEXTURE_BLUE_HAT));
            return std::move(result);
        } // case

        case sh::EnemyType::YELLOW_HAT:
        {
            auto result = new(place) sh::EnemyYellowHat();
            result->SetTexture(resource_manager_->GetTexture(
                sh::TextureFileID::ENEMY_TEXTURE_YELLOW_HAT));
            return std::move(result);
        } // case

        case sh::EnemyType::BLACK_HAT:
        {
            auto result = new(place) sh::EnemyBlackHat();
            result->SetTexture(resource_manager_->GetTexture(
                sh::TextureFileID::ENEMY_TEXTURE_BLACK_HAT));
            return std::move(result);
        } // case

        case sh::EnemyType::SKELETON:
        {
            auto result = new(place) sh::EnemySkeleton();
            result->SetTexture(resource_manager_->GetTexture(
                sh::TextureFileID::ENEMY_TEXTURE_SKELETON));
            return std::move(result);
        } // case

        default:
            break;
    } // switch

    auto result = new(place) sh::Enemy();
    result->SetTexture(resource_manager_->GetTexture(
        sh::TextureFileID::ENEMY_TEXTURE_GHOST_KING));
    return std::move(result);
}
