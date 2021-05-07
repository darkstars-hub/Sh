//!---------------------------------------------------------
//! @file SceneTitle.cpp
//! @brief ゲームのタイトルシーン
//! Gameのstd::unique_ptr<sh::Scene>の
//! インスタンスはこれで生成される
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#include "SceneTitle.h"

#include "Application.h"

sh::SceneTitle::SceneTitle()
    : super(),
    signal_count_(0),
    signal_count_max_(30) {
    this->Initialize();
}
sh::SceneTitle::~SceneTitle() {
}

sh::SCENE_NO sh::SceneTitle::GetSceneNo(void) const noexcept {
    return sh::SCENE_NO::TITLE;
}

bool sh::SceneTitle::Initialize() {
    super::texture_->Load("../textures/scene_title.png");
    super::sound_->Load("../sounds/bgm_maoudamashii_cyber07.ogg");

    sound_->SetLoop(true);
    sound_->SetGain(0.1);

    sound_->Play();

    return true;
}
bool sh::SceneTitle::Update(void) {
    super::ChangeSceneFade(sh::SCENE_NO::SELECT);
    auto pad = sh::Application::GetInstance().GetGamePad();
    if (pad->IsPress(GamePadInfo::BUTTON_BACK)) {
        sh::Application::GetInstance().GetGame()->End();
        return true;
    } // if
    if (!is_change_) {
        if (pad->IsPress(GamePadInfo::BUTTON_START)) {
            sh::SystemSound::Singleton().PlaySelect();
            is_change_ = true;
        } // if
    } // if
    
    signal_count_++;
    if (signal_count_ > signal_count_max_) {
        signal_count_ = 0;
    } // if

    return true;
}
bool sh::SceneTitle::Render(void) {
    super::texture_->Render(0.0f, 0.0f);

    if (signal_count_ < signal_count_max_ * 0.5f) {
        auto g = sh::Graphics();
        g.DrawRectangle(
            sh::Rectangle(180.0f, 100.0f, 850.0f, 200.0f),
            sh::Color(60, 60, 60, 60));
    } // if

    super::RenderFade();

    return true;
}