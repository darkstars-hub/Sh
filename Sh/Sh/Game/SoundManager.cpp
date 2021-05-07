#include "SoundManager.h"

#include "EventMessenger.h"

sh::SoundManager::SoundManager() :
    resource_manager_(nullptr),
    listener_(sh::EventMessenger::
              Singleton().CreateListener(sh::ClassID::SOUND_MANAGER)) {
    sh::EventMessenger::
        Singleton().AddEventListener(*listener_);
}

sh::SoundManager::~SoundManager() {
}

void sh::SoundManager::SetResourceManager(sh::ResourceManager& resource_container) {
    this->resource_manager_ = &resource_container;
}

bool sh::SoundManager::Update(void) {
   
    for (auto event : listener_->events_) {
        switch (event->id_) {
            case sh::EventID::SHOT_PLAYER:
            {
                auto sound = resource_manager_->GetSoundBuffer(sh::SoundFileID::BULLET_SHOT);
                sound->SetGain(0.1);
                if (!sound->IsPlay()) {
                    sound->Play();
                } // if
                break;
            } // case
            case sh::EventID::SHOT_ENEMY:
                break;
            default:
                break;
        } // switch
    } // for
    listener_->ResetEvents();

    return true;
}
