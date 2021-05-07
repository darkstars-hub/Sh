//!---------------------------------------------------------
//! @file Scene.cpp
//! @brief 各シーンクラスの基底クラス
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------

#include "Scene.h"

sh::Scene::Scene()
    : next_scene_(SCENE_NO::NONE),
    is_end_(false),
    texture_(std::make_shared<sh::Texture>()),
    sound_(std::make_shared<sh::SoundBuffer>()),
    alpha_(255),
    is_change_(false) {
}
sh::Scene::~Scene() {
    puts("scene destructor");
}

sh::SCENE_NO sh::Scene::GetNextScene(void) const noexcept {
    return next_scene_;
}
bool sh::Scene::Release(void) {
    if (!texture_->Release()) {
        return false;
    } // if
    if (!sound_->Release()) {
        return false;
    } // if
    return true;
}
void sh::Scene::AcquireResource(sh::ResourceManager& container) {
    std::cout << &container << "\n";
}
void sh::Scene::ChangeSceneFade(const SCENE_NO next_scene) {
    this->Fade();
    this->ChangeScene(next_scene);
}
void sh::Scene::RenderFade(void) {
    auto g = sh::Graphics();
    auto rect = sh::Rectangle(0, 0, sh::kWindowWidth, sh::kWindowHeight);
    g.DrawRectangle(
        rect, sh::Color(0, 0, 0, alpha_));
}
void sh::Scene::Fade(void) {
    if (!is_change_ && alpha_ >= 0) {
        alpha_ -= 10;
        if (alpha_ <= 0) {
            alpha_ = 0;
        } // if
    } // if
    if (is_change_) {
        if (alpha_ < 255) {
            alpha_ += 10;
        } // if
        if (alpha_ >= 255) {
            alpha_ = 255;
        } // if
    } // if
}
void sh::Scene::ChangeScene(const SCENE_NO next_scene) {
    if (is_change_ && alpha_ >= 255) {
        this->next_scene_ = next_scene;
        this->is_end_ = true;
    } // if
}
void sh::Scene::SetScore(std::unique_ptr<sh::Score> score) {
    std::cout << score << "\n";
}

std::unique_ptr<sh::Score> sh::Scene::GetScore(void) {
    return std::move(std::unique_ptr<sh::Score>());
}

bool sh::Scene::IsEnd(void) const noexcept {
    return this->is_end_;
}