//!---------------------------------------------------------
//! @file StageSelect.h
//! @brief プレイヤー、ステージ選択シーンのステージ選択
//! @author name
//! @date 2019/12/27
//!---------------------------------------------------------


#ifndef SH_STAGE_SELECT_H
//!---------------------------------------------------------
//! @def SH_STAGE_SELECT_H
//! @brief include gurad
//!---------------------------------------------------------
#define SH_STAGE_SELECT_H

#include <memory>

#include "Vector2.h"
#include "Rectangle.h"
#include "Graphics.h"
#include "Texture.h"
#include "Animation.h"
#include "Icon.h"

namespace sh {
class StageSelect {
public:
    StageSelect();
    ~StageSelect() = default;
    StageSelect(const StageSelect& rhs) = delete;
    StageSelect& operator=(const StageSelect& rhs) = delete;
    StageSelect(StageSelect&& rhs) = delete;
    StageSelect& operator= (StageSelect&& rhs) = delete;

    int GetSelectNumber(void);

    void Initialize(void);
    void Update(const sh::Rectangle cursor_rect);
    void Render(const sh::Rectangle cursor_rect);
    void Release(void);
private:
    const float stage_scale_;
    std::shared_ptr<sh::Texture> stage_1_;
    std::shared_ptr<sh::Texture> stage_2_;
    std::shared_ptr<sh::Texture> stage_3_;

    sh::Rectangle stage_rect_1_;
    bool select_1_;
    sh::Rectangle stage_rect_2_;
    bool select_2_;
    sh::Rectangle stage_rect_3_;
    bool select_3_;
};
}
#endif SH_STAGE_SELECT_H