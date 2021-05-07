//!---------------------------------------------------------
//! @file Icon.h
//! @brief アイコン、今は２種類のアニメーション
//!        座標は固定とする
//! @author name
//! @date 2019/12/30
//!---------------------------------------------------------


#ifndef SH_ICON_H
//!---------------------------------------------------------
//! @def SH_ICON_H
//! @brief include gurad
//!---------------------------------------------------------
#define SH_ICON_H

#include <memory>

#include "Vector2.h"
#include "Rectangle.h"
#include "Graphics.h"
#include "Texture.h"
#include "Animation.h"

namespace sh {
class Icon {
public:
    Icon();
    ~Icon() = default;
    Icon(const Icon& rhs) = delete;
    Icon& operator=(const Icon& rhs) = delete;
    Icon(Icon&& rhs) = delete;
    Icon& operator= (Icon&& rhs) = delete;

    bool UnderCursor(void) const noexcept;
    bool IsSelect(void) const noexcept;
    void SetSelected(const bool is_selected);

    sh::Rectangle GetRectangle(void) const noexcept;

    //! MakeAnimationを呼び出してから
    void Initialize(const sh::Vector2 position, std::shared_ptr <sh::Texture> texture,
                    const float scale);
    void Update(const sh::Rectangle cursor_rect);
    void Render(void);

    void MakeAnimation(const sh::MakeAnime animation,
                       const sh::MakeAnime select_animation);
private:
    sh::Vector2 position_;
    float anime_width_;
    float anime_height_;
    float     scale_;
    std::weak_ptr< sh::Texture >    texture_;
    sh::Animation   select_animation_;
    sh::Animation   animation_;
    sh::Rectangle   rect_;

    bool            is_select_;
    bool            under_cursor_;
};
}
#endif SH_ICON_H