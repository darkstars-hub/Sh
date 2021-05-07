//!---------------------------------------------------------
//! @file Game.cpp
//! @brief ÉQÅ[ÉÄïîï™ Application::Run(void)ÇÃíÜÇ≈é¿çsÇ≥ÇÍÇÈ
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#include "Game.h"

#include "Application.h"
#include "SystemSound.h"

#include "SceneTitle.h"
#include "SceneSelect.h"
#include "SceneLoad.h"
#include "SceneGame.h"
#include "SceneClear.h"
#include "SceneOver.h"
#include "SceneResult.h"

sh::Game::Game()
    : is_end_(false),
    scene_(),
    camera_(std::make_shared<sh::Camera>()),
    selected_numbers_(){
}
sh::Game::~Game() {
    puts("game destructor");
}

bool sh::Game::IsEnd(void) const noexcept {
    return this->is_end_;
}

void sh::Game::End(void) {
    this->is_end_ = true;
}

bool sh::Game::Initialize(void) {
    sh::SystemSound::Singleton().Load();

    scene_ = std::make_unique<sh::SceneTitle>();
    r = std::make_shared<sh::ResourceManager>();
    //r->Load();
    //r->LoadTexture();
    return true;
}
bool sh::Game::Update(void) {
    // get game pad
    auto game_pad =
        sh::Application::GetInstance().GetGamePad();

    // camera update
    camera_->Update();

    // game scene update
    scene_->Update();

    if (scene_->GetSceneNo() == sh::SCENE_NO::SELECT) {
        auto& s = dynamic_cast<sh::SceneSelect&>(*scene_);
        selected_numbers_ = s.GetSelectNumber();
    } // if
    
    if (this->is_end_) {
        scene_->Release();
        scene_.reset();
        return true;
    } // if

    // change scene
    if (scene_->IsEnd()) {
        std::unique_ptr<sh::Score> score;
        if (scene_->GetSceneNo() == sh::SCENE_NO::GAME){
            score = scene_->GetScore();
        } // if

        auto change_scene = scene_->GetNextScene();
        scene_->Release();
        scene_.reset();

        switch (change_scene) {
            case sh::SCENE_NO::TITLE:
            {
                scene_ = std::make_unique<sh::SceneTitle>();
                break;
            } // case
            case sh::SCENE_NO::SELECT:
            {
                scene_ = std::make_unique<sh::SceneSelect>();
                r->LoadTexture();
                break;
            } // case
            case sh::SCENE_NO::LOAD:
            {
                scene_ = std::make_unique<sh::SceneLoad>(selected_numbers_);
                scene_->AcquireResource(*r);
                scene_->Initialize();
                break;
            } // case
            case sh::SCENE_NO::GAME:
            {
                scene_ = std::make_unique<sh::SceneGame>(selected_numbers_);
                r->LoadSound();
                scene_->AcquireResource(*r);
                scene_->Initialize();
                break;
            } // case
            case sh::SCENE_NO::CLEAR:
            {
                scene_ = std::make_unique<sh::SceneClear>(222);
                scene_->SetScore(std::move(score));
                scene_->Initialize();
                break;
            } // case
            case sh::SCENE_NO::OVER:
            {
                scene_ = std::make_unique<sh::SceneOver>();
                break;
            } // case
            case sh::SCENE_NO::RESULT:
            {
                scene_ = std::make_unique<sh::SceneResult>();
                break;
            } // case
            default:
            {
                break;
            } // default
        } // switch
        
        // reset view point
        camera_->GetViewPoint()->Zero();
    } // if

    return true;
}
bool sh::Game::Render(void) {
    scene_->Render();
    return true;
}
bool sh::Game::Release(void) {
    puts("game release");
    scene_->Release();
    scene_.reset();
    r->Release();
    return true;
}

std::shared_ptr<sh::Camera> sh::Game::GetCamera(void) const {
    return camera_;
}