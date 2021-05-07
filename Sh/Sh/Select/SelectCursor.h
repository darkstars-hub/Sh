//!---------------------------------------------------------
//! @file SelectCursor.h
//! @brief プレイヤー、ステージ選択シーンのカーソル
//! @author name
//! @date 2019/12/27
//!---------------------------------------------------------


#ifndef SH_SELECT_CURSOR_H
//!---------------------------------------------------------
//! @def SH_SELECT_CURSOR_H
//! @brief include gurad
//!---------------------------------------------------------
#define SH_SELECT_CURSOR_H


#include "Vector2.h"
#include "Rectangle.h"
#include "Graphics.h"
#include "Texture.h"
#include "Animation.h"

namespace sh {
class SelectCursor {
public:
    SelectCursor();
    ~SelectCursor() = default;
    SelectCursor(const SelectCursor& rhs) = delete;
    SelectCursor& operator=(const SelectCursor& rhs) = delete;
    SelectCursor(SelectCursor&& rhs) = delete;
    SelectCursor& operator= (SelectCursor&& rhs) = delete;

    sh::Rectangle GetRectangle(void) const noexcept;
    bool OnStartLogo(void) const noexcept;
    void SetOnStartLogo(const bool b);

    void Initialize(void);
    void Update(void);
    void Render(void);
    void Release(void);
private:
    sh::Texture texture_;
    sh::Vector2 cursor_position_;
    bool on_texture_;
    float icon_size_;
    sh::Rectangle cursor_rect_;
    sh::Animation animation_;

    void MoveCursor(void);
    void Cliping(void);
};
}
#endif SH_SELECT_CURSOR_H