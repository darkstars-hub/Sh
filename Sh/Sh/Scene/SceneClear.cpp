//!---------------------------------------------------------
//! @file SceneClear.cpp
//! @brief ゲームのクリアシーン
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#include "SceneClear.h"

#include "Application.h"

sh::SceneClear::SceneClear(int score)
    : super(),
    resource_manager_(nullptr),
    score_(nullptr),
score_value_(score){
    //this->Initialize();
}
sh::SceneClear::~SceneClear() {
}

sh::SCENE_NO sh::SceneClear::GetSceneNo(void) const noexcept {
    return sh::SCENE_NO::CLEAR;
}

bool sh::SceneClear::Initialize(void) {
    super::texture_->Load(
        "../textures/scene_clear.png");
    super::sound_->Load(
        "../sounds/bgm_maoudamashii_cyber04.ogg");
    sound_->SetLoop(true);
    sound_->SetGain(0.1);
    sound_->Play();

    score_->AddPosition({400.0f,-640.0f});
    return true;
}
bool sh::SceneClear::Update(void) {
    super::ChangeSceneFade(sh::SCENE_NO::TITLE);

    auto pad = sh::Application::GetInstance().GetGamePad();
    if (pad->IsPress(GamePadInfo::BUTTON_START)) {
        is_change_ = true;
        puts("Press clear");
    } // if
    return true;
}
bool sh::SceneClear::Render(void) {
    super::texture_->Render(
        0.0f, 0.0f);
    score_->Render();
    super::RenderFade();
    return true;
}

void sh::SceneClear::AcquireResource(sh::ResourceManager& container) {
    resource_manager_ = &container;
}
void sh::SceneClear::SetScore(std::unique_ptr<sh::Score> score) {
    score_ = std::move(score);
}