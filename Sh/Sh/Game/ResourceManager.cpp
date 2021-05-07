#include "ResourceManager.h"

sh::ResourceManager::ResourceManager() :
    textures_(),
    sounds_(),
    texture_loaded(),
    sound_loaded() {
    std::fill(texture_loaded.begin(), texture_loaded.end(), false);
    std::fill(sound_loaded.begin(), sound_loaded.end(), false);
}

sh::ResourceManager::~ResourceManager() {
}

std::shared_ptr<sh::Texture>
sh::ResourceManager::GetTexture(const TextureFileID id) {
    return this->textures_.at(id);
}

std::shared_ptr<sh::SoundBuffer>
sh::ResourceManager::GetSoundBuffer(const SoundFileID id) {
    return this->sounds_.at(id);
}

bool sh::ResourceManager::AllLoaded(void) {
    for (auto is_load : texture_loaded) {
        if (!is_load) {
            return false;
        } // if
    } // for
    for (auto is_load : sound_loaded) {
        if (!is_load) {
            return false;
        } // if
    } // for
    return true;
}

bool sh::ResourceManager::Load(void) {
    if (this->AllLoaded()) {
        return true;
    } // if

    if (!this->LoadTexture()) {
        return false;
    } // if
    if (!this->LoadSound()) {
        return false;
    } // if

    return true;
}

bool sh::ResourceManager::LoadTexture(void) {
    for (int i = 0, n = static_cast<int>(sh::TextureFileID::COUNT_MAX);
         i < n; i++) {

        if (texture_loaded[i] == true) {
            continue;
        } // if

        auto texture = std::make_shared<sh::Texture>();
        if (!texture->Load(texture_file_names[i])) {
            std::cerr << "failed to load texture" << std::endl;
            TRACE;
            return false;
        } // if
        texture_loaded[i] = true;
        auto id = static_cast<sh::TextureFileID>(i);
        textures_.emplace(id, texture);
    } // for

    return true;
}

bool sh::ResourceManager::LoadSound(void) {
    for (int i = 0, n = static_cast<int>(sh::SoundFileID::COUNT_MAX);
         i < n; i++) {

        if (sound_loaded[i] == true) {
            continue;
        } // if

        auto sound = std::make_shared<sh::SoundBuffer>();
        if (!sound->Load(sound_file_names[i])) {
            std::cerr << "failed to load sounf buffer" << std::endl;
            TRACE;
            return false;
        } // if
        sound_loaded[i] = true;

        auto id = static_cast<sh::SoundFileID>(i);
        sounds_.emplace(id, sound);
    } // for

    return true;
}

bool sh::ResourceManager::Release(void) {
    /*
    for (int i = 0, n = static_cast<int>(sh::TextureFileID::COUNT_MAX);
         i < n; i++) {
        auto id = static_cast<sh::TextureFileID>(i);
        textures_.at(id)->Release();
    } // for
    */

    for (auto tex : textures_) {
        tex.second->Release();
    } // for
    for (auto sound: sounds_) {
        sound.second->Release();
    } // for


    /*
    puts("");
    for (int i = 0, n = static_cast<int>(sh::SoundFileID::COUNT_MAX);
         i < n; i++) {
        auto id = static_cast<sh::SoundFileID>(i);
        sounds_.at(id)->Release();
    } // for
    */
    return true;
}