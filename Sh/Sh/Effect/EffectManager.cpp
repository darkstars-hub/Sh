#include "EffectManager.h"

sh::EffectManager::EffectManager() :
    effects_(),
    end_effect_(std::nullopt),
    end_effect_count_(0),
    textures_(),
    listener_(sh::EventMessenger::
              Singleton().CreateListener(sh::ClassID::EFFECT_MANAGER)) {
    sh::EventMessenger::
        Singleton().AddEventListener(*listener_);
}

sh::EffectManager::~EffectManager() {
}


void sh::EffectManager::Start(const float x, const float y, const  sh::EffectType type) {
    auto effect = sh::Effect();
    effect.SetTexture(textures_.at(type));
    effect.Initialize();
    effect.MakeAnimation(type);
    effect.Start(x, y);
    effects_.push_back(std::move(effect));
}

void sh::EffectManager::Start(const Vector2 position, const sh::EffectType type) {
    this->Start(position.x_, position.y_, type);
}

bool sh::EffectManager::IsEndEffectEnd(void) const {
    if (end_effect_count_ >= 150) {
        return true;
    } // if
    return false;;
}

/*
//std::optional<std::shared_ptr<
  //  sh::Effect>>  sh::EffectManager::GetEndEffect(void) {
std::optional<sh::Effect> sh::EffectManager::GetEndEffect(void) {
    return std::move(end_effect_);
}
*/

bool sh::EffectManager::Load(sh::ResourceManager& resource_manager) {
    using Type = sh::EffectType;
    using ID = sh::TextureFileID;

    // Effectに使用テクスチャをセット
    textures_.emplace(
        Type::DAMAGE,
        resource_manager.GetTexture(ID::EFFECT_TEXTURE_DAMAGE));

    textures_.emplace(
        Type::DEAD,
        resource_manager.GetTexture(ID::EFFECT_TEXTURE_DEAD));

    textures_.emplace(
        Type::GAME_START,
        resource_manager.GetTexture(ID::EFFECT_GAME_START));

    /*
    textures_.emplace(
        Type::GAME_CLEAR,
        resource_manager.GetTexture(ID::EFFECT_GAME_CLEAR));

    textures_.emplace(
        Type::GAME_OVER,
        resource_manager.GetTexture(ID::EFFECT_GAME_OVER));
    */

    return true;
}

bool sh::EffectManager::Update(void) {
    for (auto event : listener_->events_) {
        EffectEvent* e =
            dynamic_cast<sh::EffectEvent*>(event);
        auto pos = e->position_;
        switch (event->id_) {
            case sh::EventID::DAMAGE:
                this->Start(pos, sh::EffectType::DAMAGE);
                break;
            case sh::EventID::DEAD:
                this->Start(pos, sh::EffectType::DEAD);
                end_effect_ = std::make_optional<sh::Effect>(
                    *(effects_.end() - 1));
                break;
            case sh::EventID::GAME_START:
                this->Start(pos, sh::EffectType::GAME_START);
                break;
        /*
            case sh::EventID::GAME_CLEAR:
                this->Start(pos, sh::EffectType::GAME_CLEAR);
                break;
            case sh::EventID::GAME_OVER:
                this->Start(pos, sh::EffectType::GAME_OVER);
                break;
        */

            default:
                break;
        } // switch
    } // for
    listener_->ResetEvents();

    if (end_effect_.has_value() &&
        end_effect_count_ < 120) {
        end_effect_count_++;
        int r = 100;
        auto p = end_effect_->GetPosition();
        auto pos = sh::Vector2(
            p.x_ + sh::GenerateRandom(-r, r),
            p.y_ + sh::GenerateRandom(-r, r));
        pos += sh::Vector2(64.0f, 64.0f);
        this->Start(pos, sh::EffectType::DAMAGE);
    } // if
    if (end_effect_.has_value() &&
        end_effect_count_ == 120) {
        end_effect_count_++;

        auto pos = end_effect_->GetPosition();
        pos += sh::Vector2(64.0f, 64.0f);
        this->Start(pos, sh::EffectType::DEAD);
        end_effect_ = std::make_optional<sh::Effect>(
            *(effects_.end() - 1));
    } // if
    else if (end_effect_.has_value() &&
             end_effect_count_ > 120) {
        end_effect_count_++;
    } // else if


    effects_.erase(std::remove_if(
        effects_.begin(), effects_.end(),
        [](sh::Effect& effect) { return !effect.IsShow(); }),
        effects_.end());

    for (auto& effect : effects_) {
        effect.Update();
    } // for


    return true;
}

bool sh::EffectManager::Render(void) {
    for (auto it = effects_.begin(); it != effects_.end(); ++it) {
        if (!it->IsShow()) {
            continue;
        } // if
        it->Render();
    } // for
    return true;
}