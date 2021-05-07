#include "BulletManager.h"

#include "EventMessenger.h"

sh::BulletManager::BulletManager() :
    player_bullets_(),
    enemy_bullets_(),
    bullet_factory_(),
    listener_(nullptr),
    beam_pointers_() {

    listener_ = sh::EventMessenger::
        Singleton().CreateListener(sh::ClassID::BULLET_MANAGER);
    sh::EventMessenger::
        Singleton().AddEventListener(*listener_);

}

sh::BulletManager::~BulletManager() {
}

void sh::BulletManager::SetUpBulletFactory(sh::ResourceManager& resource_manager) {
    bullet_factory_.SetTexture(resource_manager);
    //beam_pointer_ = bullet_factory_.Create(sh::BulletColor::BLUE, sh::BulletType::Beam);
}

bool sh::BulletManager::Update(void) {
    for (auto event : listener_->events_) {
        switch (event->id_) {
            case sh::EventID::SHOT_PLAYER:
            {
                ShotEvent* e =
                    dynamic_cast<sh::ShotEvent*>(event);
                sh::Vector2 pos, bullet_speed; float angle; sh::BulletType type;
                this->PickupEvent(*e, pos, angle, bullet_speed, type);

                if (type == sh::BulletType::BeamShooting) {
                    (*(beam_pointers_.end() - 1))->Fire(pos, angle, bullet_speed);
                    continue;
                } // if

                auto bullet = bullet_factory_.Create(
                    sh::BulletColor::GREEN, type);
                if (type == sh::BulletType::Beam) {
                    beam_pointers_.push_back(
                        std::dynamic_pointer_cast<sh::Beam>(bullet));
                } // if
                else if (type == sh::BulletType::Boomerang) {
                    auto& boomerang = dynamic_cast<sh::Boomerang&>(*bullet);
                    auto& actor = dynamic_cast<sh::Actor&>(*e->actor_);
                    boomerang.SetUser(&actor);
                } // if

                bullet->Initialize();
                bullet->Fire(pos, angle, bullet_speed);
                player_bullets_.push_back(std::move(bullet));
                break;
            } // case
            case sh::EventID::SHOT_ENEMY:
            {
                ShotEvent* e =
                    dynamic_cast<sh::ShotEvent*>(event);
                sh::Vector2 pos, bullet_speed; float angle; sh::BulletType type;
                this->PickupEvent(*e, pos, angle, bullet_speed, type);

                auto bullet = bullet_factory_.Create(
                    static_cast<sh::BulletColor>(
                        sh::GenerateRandom(0, static_cast<int>(
                            sh::BulletColor::COUNT))), type);
                bullet->Initialize();
                bullet->Fire(pos, angle, bullet_speed);
                enemy_bullets_.push_back(std::move(bullet));
                break;
            } // case
            break;
            default:
                break;
        } // switch
    } // for
    listener_->ResetEvents();


    player_bullets_.erase(std::remove_if(
        player_bullets_.begin(), player_bullets_.end(),
        [](std::shared_ptr < sh::Bullet> bullet) { return !bullet->IsShow(); }),
        player_bullets_.end());
    enemy_bullets_.erase(std::remove_if(
        enemy_bullets_.begin(), enemy_bullets_.end(),
        [](std::shared_ptr < sh::Bullet> bullet) { return !bullet->IsShow(); }),
        enemy_bullets_.end());



    for (auto& bullet : player_bullets_) {
        bullet->Update();
    } // for
    for (auto& bullet : enemy_bullets_) {
        bullet->Update();
    } // for

    /*
    std::cout << enemy_bullets_.size() << "\n";
    char buf[256];
    ::sprintf_s(buf, "bullet size = %d \n", enemy_bullets_.size());
    const char* str = buf;
    wchar_t buffer[256];
    size_t len = 0;
    ::setlocale(LC_ALL, "japanese");
    ::mbstowcs_s(&len, buffer, 256, str, _TRUNCATE);
    ::OutputDebugString(buffer);
    */
    return true;
}

bool sh::BulletManager::Render(void) {
    for (auto& bullet : player_bullets_) {
        bullet->Render();
    } // for
    for (auto& bullet : enemy_bullets_) {
        bullet->Render();
    } // for

    return true;
}

bool sh::BulletManager::Release(void) {
    player_bullets_.clear();
    enemy_bullets_.clear();
    return true;
}

void sh::BulletManager::PickupEvent(
    ShotEvent& e, sh::Vector2& pos, float& angle,
    sh::Vector2& speed, sh::BulletType& type) {

    pos = e.position_;
    angle = e.angle_;
    speed = e.speed_;
    type = BulletType::Bullet;
    if (e.bullet_type_ == sh::ClassID::BOMB) {
        type = BulletType::Bomb;
    } // if
    else if (e.bullet_type_ == sh::ClassID::BEAM) {
        type = BulletType::Beam;
    } // else if
    else if (e.bullet_type_ == sh::ClassID::BEAM_SHOOTING) {
        type = BulletType::BeamShooting;
    } // else if
    else if (e.bullet_type_ == sh::ClassID::HOMING) {
        type = BulletType::Homing;
    } // else if
    else if (e.bullet_type_ == sh::ClassID::THROUGH) {
        type = BulletType::Through;
    } // else if
    else if (e.bullet_type_ == sh::ClassID::BOOMERANG) {
        type = BulletType::Boomerang;
    } // else if
}


std::vector<std::shared_ptr<sh::Bullet>>&
sh::BulletManager::GetEnemyBullets(void) {
    return enemy_bullets_;
}
std::vector<std::shared_ptr<sh::Bullet>>&
sh::BulletManager::GetPlayerBullets(void) {
    return player_bullets_;
}