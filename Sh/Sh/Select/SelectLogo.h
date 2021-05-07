//!---------------------------------------------------------
//! @file SelectLogo.h
//! @brief プレイヤー、ステージ選択シーンのスタートボタン
//! @author name
//! @date 2019/12/27
//!---------------------------------------------------------


#ifndef SH_SELECT_LOGO_H
//!---------------------------------------------------------
//! @def SH_SELECT_LOGO_H
//! @brief include gurad
//!---------------------------------------------------------
#define SH_SELECT_LOGO_H


#include "Vector2.h"
#include "Rectangle.h"
#include "Graphics.h"
#include "Texture.h"
#include "Icon.h"

namespace sh {
class SelectLogo {
public:
    SelectLogo();
    ~SelectLogo() = default;
    SelectLogo(const SelectLogo& rhs) = delete;
    SelectLogo& operator=(const SelectLogo& rhs) = delete;
    SelectLogo(SelectLogo&& rhs) = delete;
    SelectLogo& operator= (SelectLogo&& rhs) = delete;

    sh::Rectangle GetRectangle(void) const noexcept;

    void Initialize(void);
    void Update(const sh::Rectangle cursor_rect);
    void Render(const sh::Rectangle cursor_rect);
    void Release(void);
private:
    sh::Texture logo_active_;
    sh::Texture logo_negative_;

    const sh::Vector2 position_;
    sh::Rectangle start_rect_;

    bool is_select_;
};
}
#endif SH_SELECT_LOGO_H