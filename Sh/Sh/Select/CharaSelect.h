//!---------------------------------------------------------
//! @file CharaSelect.h
//! @brief プレイヤー、ステージ選択シーンのプレイヤー選択
//! @author name
//! @date 2019/12/27
//!---------------------------------------------------------


#ifndef SH_CHARA_SELECT_H
//!---------------------------------------------------------
//! @def SH_CHARA_SELECT_H
//! @brief include gurad
//!---------------------------------------------------------
#define SH_CHARA_SELECT_H


#include "Vector2.h"
#include "Rectangle.h"
#include "Graphics.h"
#include "Texture.h"
#include "Animation.h"
#include "Icon.h"
#include "ResourceManager.h"

namespace sh {
class CharaSelect {
public:
    CharaSelect();
    ~CharaSelect() = default;
    CharaSelect(const CharaSelect& rhs) = delete;
    CharaSelect& operator=(const CharaSelect& rhs) = delete;
    CharaSelect(CharaSelect&& rhs) = delete;
    CharaSelect& operator= (CharaSelect&& rhs) = delete;

    int GetSelectNumber(void);

    void Initialize(sh::ResourceManager& resource_manager);
    void Initialize(void);
    void Update(const sh::Rectangle cursor_rect);
    void Render(void);
    void Release(void);
private:
    sh::ResourceManager* resource_manager_;

    float icon_size_;
    const float player_scale_;
    std::shared_ptr<sh::Texture> player_white_;
    std::shared_ptr<sh::Texture> player_black_;
    std::shared_ptr<sh::Texture> player_blue_;
    std::shared_ptr<sh::Texture> player_purple_;
    
    sh::Icon white_icon_;
    sh::Icon black_icon_;
    sh::Icon blue_icon_;
    sh::Icon purple_icon_;
};
}
#endif SH_CHARA_SELECT_H