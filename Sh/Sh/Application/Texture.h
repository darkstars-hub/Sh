//!---------------------------------------------------------
//! @file Texture.h
//! @brief âÊëúÇì«Ç›çûÇ›ï`âÊÇ∑ÇÈÉNÉâÉX
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#ifndef SH_TEXTURE_H
//!---------------------------------------------------------
//! @def SH_TEXTURE_H
//! @brief include gurad
//!---------------------------------------------------------
#define SH_TEXTURE_H

#include <iostream>

#include "GLFW/glfw3.h"
#if defined(APIENTRY)
#undef APIENTRY
#endif // defined(APIENTRY)

#define STB_IMAGE_IMPLEMENTATION


#include "Helper.h"
#include "Vector2.h"
#include "Rectangle.h"
#include "Color.h"

namespace sh {
class Texture {
public:
    Texture();
    ~Texture();
    Texture(const Texture& rhs) = default;
    Texture& operator=(const Texture& rhs) = default;
    Texture(Texture&& rhs) = default;
    Texture& operator= (Texture&& rhs) = default;

    int GetWidth(void) const noexcept;
    int GetHeight(void) const noexcept;

    void Bind(void);

    bool Load(const char* path);
    bool Render(const float x, const  float y);
    
    bool Render(const float x, const  float y, const sh::Rectangle render_rect);
    bool Render(const sh::Vector2 position, const sh::Rectangle render_rect);

    bool Render(const float x, const  float y, const float angle);
    
    bool Render(const float x, const  float y, const float angle,
                const sh::Rectangle render_rect, const float scale = 1.0f);
    bool Render(const sh::Vector2 position, const float angle,
                const sh::Rectangle render_rect, const float scale = 1.0f);
    bool Release(void);
private:
    int width_;
    int height_;
    GLuint texture_;
    sh::Vector2 texture_coordinate_;
    sh::Vector2 texture_coordinate_offset_;
};
}
#endif // !SH_TEXTURE_H