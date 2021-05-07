#include "ActorState.h"

sh::ActorState::ActorState() :
    motion_(),
    weapons_(),
    hp_(std::make_shared<sh::HitPoint>()),
    mp_(std::make_shared<sh::WeaponEnergy>()) {
}

std::shared_ptr<sh::Weapon> sh::ActorState::GetWeapon(int botton) {
    return weapons_.at(botton);
}

sh::Motion* sh::ActorState::GetMotion(void) {
    return &this->motion_;
}

std::shared_ptr<sh::HitPoint> sh::ActorState::GetHp(void) {
    return this->hp_;
}

std::shared_ptr<sh::WeaponEnergy> sh::ActorState::GetMp(void) {
    return this->mp_;
}

void sh::ActorState::AddUser(sh::Actor& user) {
    for (auto& weapon : weapons_) {
        if (weapon) {
            weapon->AddUser(user);
        } // if
    } // for
}

void sh::ActorState::MakeWeapons(const WeaponType a, const WeaponType b, const WeaponType x, const WeaponType y) {
    std::vector<sh::WeaponType> types = { a, b, x, y };
    using Type = sh::WeaponType;
    std::shared_ptr<sh::Weapon> weapon = nullptr;
    for (unsigned int i = 0; i < types.size(); i++) {
        if (types.at(i) == sh::WeaponType::NONE) {
            continue;
        } // if

        switch (types.at(i)) {
            case Type::NORMAL_GUN:
                weapon = std::make_shared<sh::NormalGun>();
                break;
            case Type::THREE_WAY_GUN:
                weapon = std::make_shared<sh::ThreeWayGun>();
                break;
            case Type::CIRCLE_GUN:
                weapon = std::make_shared<sh::CircleGun>();
                break;
            case Type::RANDOM_GUN:
                weapon = std::make_shared<sh::RandomGun>();
                break;
            case Type::MINE:
                weapon = std::make_shared<sh::Mine>();
                break;
            default:
                break;
        } // switch
        weapons_.at(i) = std::move(weapon);
    } // for
}

void sh::ActorState::Load(sh::ResourceManager& container) {
    {
        std::shared_ptr<sh::Texture> texture;
        texture = container.GetTexture(sh::TextureFileID::HP_TEXTURE);
        hp_->SetTexture(texture);
    }
    {
        std::shared_ptr<sh::Texture> texture;
        texture = container.GetTexture(sh::TextureFileID::MP_FRAME_TEXTURE);
        mp_->SetFrameTexture(texture);
    }
    {
        std::shared_ptr<sh::Texture> texture;
        texture = container.GetTexture(sh::TextureFileID::MP_ENERGY_TEXTURE);
        mp_->SetEnegryTexture(texture);
    }
}

void sh::ActorState::Initialize(int hp) {
    hp_->Initialize(hp);
    mp_->Initialize();
    motion_.Initialize();
}

void sh::ActorState::Update(void){
    for (auto weapon : weapons_) {
        if (!weapon) {
            continue;
        } // if
        weapon->Update();
    } // for

    hp_->Update();
    mp_->Update();
}
void sh::ActorState::Render(void) {
    mp_->Render();
    for (int i = 0; i < hp_->GetValue(); i++) {
        hp_->Render(900.0f, 0.0f + i * 120.0f);
    } // for
}