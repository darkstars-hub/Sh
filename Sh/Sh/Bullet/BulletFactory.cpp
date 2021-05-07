//!---------------------------------------------------------
//! @file BulletFactory.cpp
//! @brief Bulletのファクトリークラス
//! @author name
//! @date 2019/11/02
//!---------------------------------------------------------


#include "BulletFactory.h"

sh::BulletFactory::BulletFactory() :
    texture_(nullptr),
    bomb_texture_(nullptr),
    beam_texture_(nullptr),
    boomerang_texture_(nullptr){
}

sh::BulletFactory::~BulletFactory() {
}

void sh::BulletFactory::SetTexture(sh::ResourceManager& resource_manager) {
    this->texture_ = resource_manager.GetTexture(
        sh::TextureFileID::BULLET_TEXTURE);
    this->bomb_texture_ = resource_manager.GetTexture(
        sh::TextureFileID::BOMB_TEXTURE);
    this->beam_texture_ = resource_manager.GetTexture(
        sh::TextureFileID::BEAM_TEXTURE);
    this->boomerang_texture_ = resource_manager.GetTexture(
        sh::TextureFileID::BOOMERANG_TEXTURE);
}

std::shared_ptr<sh::Bullet> sh::BulletFactory::Create(
    const sh::BulletColor color,
    const sh::BulletType type) const {

    switch (type) {
        case BulletType::Bullet:
        {
            auto result = std::make_shared<sh::Bullet>();
            result->SetTexture(texture_);
            result->MakeAnimation(color);
            return std::move(result);
        } // case 
        case BulletType::Bomb:
        {
            auto result = std::make_unique<sh::Bomb>();
            result->SetTexture(bomb_texture_);
            result->MakeAnimation();
            return std::move(result);
        } // case
        case BulletType::Beam:
        {
            auto result = std::make_unique<sh::Beam>();
            result->SetTexture(beam_texture_);
            result->MakeAnimation();
            return std::move(result);
        } // case
        case BulletType::BeamShooting:
        {
            auto result = std::make_unique<sh::Beam>();
            result->SetTexture(beam_texture_);
            result->MakeAnimation();
            return std::move(result);
        } // case
        case BulletType::Homing:
        {
            auto result = std::make_shared<sh::HomingBullet>();
            result->SetTexture(texture_);
            result->MakeAnimation();
            return std::move(result);
        } // case 
        case BulletType::Through:
        {
            auto result = std::make_shared<sh::ThroughBullet>();
            result->SetTexture(texture_);
            result->MakeAnimation();
            return std::move(result);
        } // case 
        case BulletType::Boomerang:
        {
            auto result = std::make_shared<sh::Boomerang>();
            result->SetTexture(boomerang_texture_);
            result->MakeAnimation();
            return std::move(result);
        } // case 
        default:
            break;
    } // switch
    return nullptr;
}