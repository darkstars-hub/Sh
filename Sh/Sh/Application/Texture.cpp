//!---------------------------------------------------------
//! @file Texture.cpp
//! @brief 画像を読み込み描画するクラス
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#include "Texture.h"

#include "stb/stb_image.h"

sh::Texture::Texture()
    : width_(0),
    height_(0),
    texture_(),
    texture_coordinate_(),
    texture_coordinate_offset_() {
}
sh::Texture::~Texture() {
    _ASSERT_EXPR(!texture_,
                 L"未開放のテクスチャがあります");
}

int sh::Texture::GetWidth(void) const noexcept {
    return width_;
}
int sh::Texture::GetHeight(void) const noexcept {
    return height_;
}

void sh::Texture::Bind(void) {
    ::glBindTexture(GL_TEXTURE_2D, texture_);
}

bool sh::Texture::Load(const char* path) {
    texture_coordinate_.x_ = 0.0;
    texture_coordinate_.y_ = 0.0;
    texture_coordinate_offset_.x_ = 1.0;
    texture_coordinate_offset_.y_ = 1.0;

    stbi_uc* pixels =
        stbi_load(path, &width_, &height_, nullptr, STBI_rgb_alpha);
    ::glGenTextures(1, &texture_);
    ::glBindTexture(GL_TEXTURE_2D, texture_);

    ::glEnable(GL_TEXTURE_2D);
    ::glEnable(GL_BLEND);
    ::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    ::glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    ::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                   width_, height_,
                   0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    ::glTexParameteri(
        GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    ::glTexParameteri(
        GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    ::glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    ::stbi_image_free(pixels);
    return true;
}

bool sh::Texture::Render(const float x, const  float y) {
    ::glEnable(GL_TEXTURE_2D);
    ::glEnable(GL_BLEND);
    ::glBindTexture(GL_TEXTURE_2D, texture_);

    ::glPushMatrix();
    ::glTranslatef(0.0f, 0.0f, 0.0f);
    ::glBegin(GL_POLYGON);

    auto size = sh::Vector2(
        static_cast<float>(width_),
        static_cast<float>(height_));
    auto tex_coord = texture_coordinate_;
    auto offset = texture_coordinate_offset_;

    ::glTexCoord2f(tex_coord.x_,
                   tex_coord.y_);
    ::glVertex2f(x, y + size.y_);

    ::glTexCoord2f(tex_coord.x_ + offset.x_,
                   tex_coord.y_);
    ::glVertex2f(x + size.x_, y + size.y_);

    ::glTexCoord2f(tex_coord.x_ + offset.x_,
                   tex_coord.y_ + offset.y_);
    ::glVertex2f(x + size.x_, y);

    ::glTexCoord2f(tex_coord.x_,
                   tex_coord.y_ + offset.y_);
    ::glVertex2f(x, y);

    ::glEnd();
    ::glPopMatrix();
    ::glDisable(GL_TEXTURE_2D);

    return true;
}

bool sh::Texture::Render(const float x, const float y,
                         const sh::Rectangle render_rect) {
    ::glEnable(GL_TEXTURE_2D);
    ::glEnable(GL_BLEND);
    ::glBindTexture(GL_TEXTURE_2D, texture_);

    ::glPushMatrix();
    ::glTranslatef(0.0f, 0.0f, 0.0f);
    ::glBegin(GL_POLYGON);

    auto size = sh::Vector2(
        render_rect.right_ - render_rect.left_,
        render_rect.bottom_ - render_rect.top_);
    auto tex_coord = sh::Vector2(
        render_rect.left_ / width_,
        render_rect.top_ / height_);
    auto offset = sh::Vector2(
        render_rect.right_ / width_,
        render_rect.bottom_ / height_);

    ::glTexCoord2f(tex_coord.x_,
                   tex_coord.y_);
    ::glVertex2f(x, y + size.y_);
    ::glTexCoord2f(tex_coord.x_ + offset.x_,
                   tex_coord.y_);
    ::glVertex2f(x + size.x_, y + size.y_);
    ::glTexCoord2f(tex_coord.x_ + offset.x_,
                   tex_coord.y_ + offset.y_);
    ::glVertex2f(x + size.x_, y);
    ::glTexCoord2f(tex_coord.x_,
                   tex_coord.y_ + offset.y_);
    ::glVertex2f(x, y);

    ::glEnd();
    ::glPopMatrix();
    ::glDisable(GL_TEXTURE_2D);

    return true;
}

bool sh::Texture::Render(const sh::Vector2 position, const sh::Rectangle render_rect) {
    this->Render(position.x_, position.y_, render_rect);
    return true;
}

bool sh::Texture::Render(const float x, const float y, const float angle) {
    ::glEnable(GL_TEXTURE_2D);
    ::glEnable(GL_BLEND);
    ::glBindTexture(GL_TEXTURE_2D, texture_);

    ::glPushMatrix();
    ::glTranslatef(x, y, 0);
    ::glRotatef(angle, 0.0f, 0.0f, 1.0f);
    ::glBegin(GL_POLYGON);

    auto size = sh::Vector2(
        static_cast<float>(width_),
        static_cast<float>(height_));
    auto tex_coord = texture_coordinate_;
    auto offset = texture_coordinate_offset_;

    ::glTexCoord2f(tex_coord.x_,
                   tex_coord.y_);
    ::glVertex2f(x - x - (size.x_ * 0.5f),
                 y - y + size.y_ - (size.y_ * 0.5f));
    ::glTexCoord2f(tex_coord.x_ + offset.x_, tex_coord.y_);
    ::glVertex2f(x - x + size.x_ - (size.x_ * 0.5f),
                 y - y + size.y_ - (size.y_ * 0.5f));
    ::glTexCoord2f(tex_coord.x_ + offset.x_, tex_coord.y_ + offset.y_);
    ::glVertex2f(x - x + size.x_ - (size.x_ * 0.5f),
                 y - y - (size.y_ * 0.5f));
    ::glTexCoord2f(tex_coord.x_, tex_coord.y_ + offset.y_);
    ::glVertex2f(x - x - (size.x_ * 0.5f),
                 y - y - (size.y_ * 0.5f));

    ::glEnd();
    ::glPopMatrix();
    ::glDisable(GL_TEXTURE_2D);

    return true;
}
bool sh::Texture::Render(const float x, const float y,
                         const float angle,
                         const sh::Rectangle render_rect,
                         const float scale) {
    ::glEnable(GL_TEXTURE_2D);
    ::glEnable(GL_BLEND);
    ::glBindTexture(GL_TEXTURE_2D, texture_);

    ::glPushMatrix();
    ::glTranslatef(x, y, 0.0f);
    ::glRotatef(angle, 0.0f, 0.0f, 1.0f);
    ::glBegin(GL_POLYGON);

    auto size = sh::Vector2(
        (render_rect.right_ - render_rect.left_) * scale,
        (render_rect.bottom_ - render_rect.top_) * scale);
    auto tex_coord = sh::Vector2(
        render_rect.left_ / width_,
        render_rect.top_ / height_);
    auto offset = sh::Vector2(
        render_rect.right_ / width_,
        render_rect.bottom_ / height_);

    ::glTexCoord2f(tex_coord.x_, tex_coord.y_);
    ::glVertex2f(-(size.x_ * 0.5f),
                 +(size.y_ * 0.5f));

    ::glTexCoord2f(offset.x_, tex_coord.y_);
    ::glVertex2f(+(size.x_ * 0.5f),
                 +(size.y_ * 0.5f));

    ::glTexCoord2f(offset.x_, offset.y_);
    ::glVertex2f(+(size.x_ * 0.5f),
                 -(size.y_ * 0.5f));

    ::glTexCoord2f(tex_coord.x_, offset.y_);
    ::glVertex2f(-(size.x_ * 0.5f),
                 -(size.y_ * 0.5f));

    ::glEnd();
    ::glPopMatrix();
    ::glDisable(GL_TEXTURE_2D);

    return true;
}

bool sh::Texture::Render(const sh::Vector2 position, const float angle, const sh::Rectangle render_rect, const float scale) {
    this->Render(position.x_, position.y_,
                 angle, render_rect, scale);
    return true;
}

bool sh::Texture::Release() {
    ::glDeleteTextures(1, &texture_);
    texture_ = NULL;

    return true;
}