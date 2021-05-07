//!---------------------------------------------------------
//! @file ResourceManager.h
//! @brief ゲーム内で使うテクスチャの読み込みと解放をする、
//! @author name
//! @date 2019/11/06
//!---------------------------------------------------------


#ifndef SH_RESOURCE_MANAGER_H
#define SH_RESOURCE_MANAGER_H


#include <memory>
#include <array>
#include <unordered_map>

#include "Texture.h"
#include "SoundBuffer.h"

namespace {
constexpr const char* texture_file_names []{
    "../textures/pipo-halloweenchara2016_20.png",
    "../textures/pipo-halloweenchara2016_21.png",
    "../textures/pipo-halloweenchara2016_22.png",
    "../textures/pipo-halloweenchara2016_23.png",

    "../textures/pipo-btleffect003.png",
    "../textures/pipo-btleffect017.png",
    "../textures/frameeffects001m.png",
    

    "../textures/pipo-mapeffect012d.png",
    "../textures/energy.png",
    "../textures/frame.png",
    
    "../textures/balloon.png",
    "../textures/bomb.png",
    "../textures/beam.png",
    "../textures/boomerang.png",

    "../textures/pipo-halloweenchara2016_24.png",
    "../textures/pipo-halloweenchara2016_11.png",
    "../textures/pipo-halloweenchara2016_12.png",
    "../textures/pipo-halloweenchara2016_13.png",
    "../textures/pipo-halloweenchara2016_14.png",
    "../textures/pipo-enemy039.png",
    

    "../textures/stage1.png",
    "../textures/pipo-bg003.png",
    "../textures/pipo-bg005.png",
    "../textures/pipo-bg004.png",

    "../textures/number.png",

    ""
};
constexpr const char* sound_file_names[] = {
    "../sounds/bgm_maoudamashii_fantasy01.ogg",
    "../sounds/bgm_maoudamashii_fantasy02.ogg",
    "../sounds/bgm_maoudamashii_cyber02.ogg",
    "../sounds/bgm_maoudamashii_cyber01.ogg",
    
    
    "../sounds/se_maoudamashii_effect07.ogg",
    "../sounds/se_maoudamashii_battle_gun04.ogg",
    
    ""
};
}

namespace sh {
enum class TextureFileID {
    PLAYER_TEXTURE_WHITE,
    PLAYER_TEXTURE_BLACK,
    PLAYER_TEXTURE_BLUE,
    PLAYER_TEXTURE_PURPLE,

    EFFECT_TEXTURE_DAMAGE,
    EFFECT_TEXTURE_DEAD,
    EFFECT_GAME_START,

    HP_TEXTURE,
    MP_ENERGY_TEXTURE,
    MP_FRAME_TEXTURE,
    
    BULLET_TEXTURE,
    BOMB_TEXTURE,
    BEAM_TEXTURE,
    BOOMERANG_TEXTURE,

    ENEMY_TEXTURE_GHOST_KING,
    ENEMY_TEXTURE_PURPLE_HAT,
    ENEMY_TEXTURE_BLUE_HAT,
    ENEMY_TEXTURE_YELLOW_HAT,
    ENEMY_TEXTURE_BLACK_HAT,
    ENEMY_TEXTURE_SKELETON,


    STAGE_TEXTURE_MORNING,
    STAGE_TEXTURE_NIGHT,
    STAGE_TEXTURE,
    STAGE_BOSS_TEXTURE,
    
    NUMBER_TEXTURE,

    COUNT_MAX,
};
enum class SoundFileID {
    STAGE_01,
    STAGE_02,
    STAGE_03,
    STAGE_BOSS,

    DEAD,
    BULLET_SHOT,

    COUNT_MAX
};

class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager();
    ResourceManager(const ResourceManager& rhs) = delete;
    ResourceManager& operator=(const ResourceManager& rhs) = delete;
    ResourceManager(ResourceManager&& rhs) = delete;
    ResourceManager& operator= (ResourceManager&& rhs) = delete;

    std::shared_ptr<sh::Texture>GetTexture(const TextureFileID id);
    std::shared_ptr<sh::SoundBuffer>GetSoundBuffer(const SoundFileID id);

    bool AllLoaded(void);

    bool Load(void);
    bool LoadTexture(void);
    bool LoadSound(void);
    bool Release(void);

    std::array<bool, static_cast<int>(sh::TextureFileID::COUNT_MAX)> texture_loaded;
    std::array<bool, static_cast<int>(sh::SoundFileID::COUNT_MAX)> sound_loaded;
private:
    std::unordered_map<sh::TextureFileID,
        std::shared_ptr<sh::Texture>> textures_;
    std::unordered_map<sh::SoundFileID,
        std::shared_ptr<sh::SoundBuffer>> sounds_;
};
}
#endif // !SH_RESOURCE_MANAGER_H