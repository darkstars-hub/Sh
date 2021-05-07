//!---------------------------------------------------------
//! @file SceneGame.cpp
//! @brief 実際のゲームシーン
//! ステージやアクターが作られて動く
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#include "SceneGame.h"

#include "Application.h"

#include "PlayerWhite.h"
#include "PlayerBlack.h"
#include "PlayerBlue.h"
#include "PlayerPurple.h"
#include "HomingBullet.h"

sh::SceneGame::SceneGame(sh::GameStart select)
    : super(),
    resource_manager_(nullptr),
    stage_(std::make_unique<sh::Stage>()),
    player_(nullptr),
    enemys_(),
    score_(std::make_unique<sh::Score>()),
    game_effect_show_(false),
    game_effect_count_(0),
    game_effect_count_max_(60),
    select_stage_(select.select_stage) {
    switch (select.select_chara) {
        case 1:
            player_ = std::make_shared<sh::PlayerWhite>(select.select_chara);
            break;
        case 2:
            player_ = std::make_shared<sh::PlayerBlack>(select.select_chara);
            break;
        case 3:
            player_ = std::make_shared<sh::PlayerBlue>(select.select_chara);
            break;
        case 4:
            player_ = std::make_shared<sh::PlayerPurple>(select.select_chara);
            break;
        default:
            break;
    } // switch

    listener_ = sh::EventMessenger::Singleton().CreateListener(sh::ClassID::SCENE_GAME);
    sh::EventMessenger::Singleton().AddEventListener(*listener_);

    for (auto& enemy : enemys_) {
        enemy = new sh::Enemy();
    } // for
}

sh::SceneGame::~SceneGame() {
}

sh::SCENE_NO sh::SceneGame::GetSceneNo(void) const noexcept {
    return sh::SCENE_NO::GAME;
}

bool sh::SceneGame::Initialize(void) {
    score_->Initialize(*resource_manager_);
    sound_manager_.SetResourceManager(*resource_manager_);
    effect_manager_.Load(*resource_manager_);

    bullet_manager_.SetUpBulletFactory(*resource_manager_);

        // ステージの初期化処理
    if (!stage_->Load(*resource_manager_, select_stage_)) {
        std::cerr << "failed to load stage" << std::endl;
        TRACE;
        return false;
    } // if
    if (!stage_->Initialize()) {
        std::cerr << "failed to initialize stage" << std::endl;
        TRACE;
        return false;
    } // if


    // プレイヤーの初期化処理
    player_->AcquireTexture(*resource_manager_);
    if (!player_->Initialize()) {
        std::cerr << "failed to initialize player" << std::endl;
        TRACE;
        return false;
    } // if


    sh::EffectEvent* e = new EffectEvent();
    e->destination_id_ = sh::ClassID::EFFECT_MANAGER;
    e->id_ = sh::EventID::GAME_START;
    //e->id_ = sh::EventID::GAME_OVER;
    e->position_ = Vector2(sh::kWindowWidth * 0.5f,
                           sh::kWindowHeight * 0.5f);
    listener_->Send(*e);
    game_effect_show_ = true;

    return true;
}
bool sh::SceneGame::Update(void) {
    super::Fade();
    sh::EventMessenger::Singleton().Send();
    sh::EventMessenger::Singleton().ClearMessage();
    auto pad = sh::Application::GetInstance().GetGamePad();

    this->GameEnd();

    effect_manager_.Update();
    sound_manager_.Update();
    if (game_effect_count_ > game_effect_count_max_) {
        game_effect_count_ = 0;
        game_effect_show_ = false;
    } // if
    if (game_effect_show_) {
        game_effect_count_++;
        return true;
    } // if

    score_->Update();

    stage_->Update(enemys_.data(), enemy_count_, player_->GetPosition());
    player_->Update();
    // エネミーの更新
    auto player_pos = player_->GetPosition();
    for (int i = 0; i < enemy_count_; i++) {
        enemys_[i]->SetTargetPosition(player_pos);
        enemys_[i]->Update();
    } // for
    bullet_manager_.Update();


    //プレイヤーとエネミーの衝突判定
    auto player_rect = player_->GetRectangle();
    for (auto& enemy : enemys_) {
        if (!enemy->IsShow()) {
            continue;
        } // if

        if (enemy->GetRectangle().
            CollisionRectangle(player_rect)) {
            player_->Damage(1);
        } // if
    } // for

    // プレーヤーの弾とエネミーの衝突判定
    for (auto& enemy : enemys_) {
        if (!enemy->IsShow()) {
            continue;
        } // if

        auto enemy_rect = enemy->GetRectangle();
        for (auto& bullet : bullet_manager_.GetPlayerBullets()) {
            if (!bullet->IsShow()) {
                continue;
            } // if

            if (bullet->GetType() == sh::BulletType::BeamShooting ||
                bullet->GetType() == sh::BulletType::Beam) {
                auto beam =
                    std::dynamic_pointer_cast<sh::Beam>(bullet);
                auto positions = beam->GetPositions();

                if (!beam->IsEnable()) {
                    continue;
                } // if

                for (auto& bpos : positions) {
                    if (sh::Rectangle(
                        bpos.pos.x_ - 16,
                        bpos.pos.y_ - 16,
                        bpos.pos.x_ + 16,
                        bpos.pos.y_ + 16).
                        CollisionRectangle(enemy_rect)) {
                        enemy->Damage(bullet->GetAttackValue());
                    } // if
                } // for
                continue;
            } // if

            if (bullet->GetRectangle().
                CollisionRectangle(enemy_rect)) {
                enemy->Damage(bullet->GetAttackValue());
                bullet->SetState(sh::BulletState::HIT);
                if (bullet->GetType() == sh::BulletType::Boomerang) {
                    bullet->SetShow(false);
                } // if

                if (!enemy->IsShow()) {
                    score_->AddScore(10 *
                                     static_cast <int>(enemy->GetEnemyType()));
                } // if
                break;
            } // if
        } // for
    } // for

    // 追尾弾用
    auto bullets = bullet_manager_.GetPlayerBullets();
    for (auto& bullet : bullets) {
        if (!bullet->IsShow() ||
            bullet->GetType() != sh::BulletType::Homing) {
            continue;
        } // if
        for (auto& enemy : enemys_) {
            auto& homing = dynamic_cast<sh::HomingBullet&>(*bullet);
            homing.SetTargetEnemy(nullptr);
            if (enemy->GetRectangle().CollisionCircle(homing.GetSearchArea())) {
                homing.SetTargetEnemy(enemy);
                break;
            } // if
        } // for
    } // for


    // プレーヤーの弾とエネミーの衝突判定 (ブーメラン用)
    for (auto& bullet : bullet_manager_.GetPlayerBullets()) {
        if (bullet->GetType() != sh::BulletType::Boomerang) {
            continue;
        } // if
        if (bullet->GetState() == sh::BulletState::HIT &&
            bullet->GetRectangle().CollisionRectangle(player_rect)) {
            bullet->SetShow(false);
            //break;
        } // if
    } // for

    // エネミーの弾とプレーヤーの衝突判定
    for (auto& bullet : bullet_manager_.GetEnemyBullets()) {
        if (!bullet->IsShow()) {
            continue;
        } // if
        if (bullet->GetState() == sh::BulletState::HIT) {
            continue;
        } // if
        auto rect = bullet->GetRectangle();

        // バリアと弾の衝突
        if (player_->IsEquipmentBarrier()) {
            auto purple = std::dynamic_pointer_cast<sh::PlayerPurple>(player_);
            if (rect.CollisionCircle(purple->GetBarrierCircle())) {
                bullet->SetState(sh::BulletState::HIT);
                //break;
                continue;
            } // if
        } // if

        if (rect.CollisionRectangle(player_rect)) {
            player_->Damage(bullet->GetAttackValue());
            bullet->SetState(sh::BulletState::HIT);
            break;
        } // if
    } // for




    /*
        // デバッグ用画面遷移
    if (pad->IsPress(GamePadInfo::BUTTON_START)) {
        super::next_scene_ = sh::SCENE_NO::CLEAR;
        super::is_end_ = true;
        puts("Press game");
        is_change_ = true;

    } // if
    if (pad->IsPress(GamePadInfo::BUTTON_BACK)) {
        super::next_scene_ = sh::SCENE_NO::OVER;
        super::is_end_ = true;
        puts("Press game");
        is_change_ = true;
    } // if
    */

    return true;
}
bool sh::SceneGame::Render(void) {
    stage_->Render();
    effect_manager_.Render();

    if (player_->GetPlayerType() == 4) {
        auto purple =
            std::dynamic_pointer_cast<sh::PlayerPurple>(player_);
        purple->BarrierRender();
    } // if

    bullet_manager_.Render();
    player_->Render();
    for (auto& enemy : enemys_) {
        enemy->Render();
    } // for


    score_->Render();
    super::RenderFade();
    return true;
}

bool sh::SceneGame::Release(void) {
    super::Release();
    //resource_manager_->Release();
    for (auto& enemy : enemys_) {
        delete enemy;
        enemy = nullptr;
    } // for
    stage_->Release();
    return true;
}

void sh::SceneGame::AcquireResource(sh::ResourceManager& container) {
    resource_manager_ = &container;
}

std::unique_ptr<sh::Score> sh::SceneGame::GetScore(void) {
    return std::move(score_);
}

void sh::SceneGame::GameEnd(void) {
    if (!player_->IsShow()) {
        game_effect_count_++;

        if (game_effect_count_ > game_effect_count_max_ / 2) {
            game_effect_count_ = 0;

            is_change_ = true;
            super::ChangeScene(sh::SCENE_NO::OVER);
        } // if
    } // if

    if (select_stage_ == 3) {
        if (effect_manager_.IsEndEffectEnd()) {
            game_effect_count_++;

            if (game_effect_count_ > game_effect_count_max_ / 2) {
                game_effect_count_ = 0;

                is_change_ = true;
                super::ChangeScene(sh::SCENE_NO::CLEAR);
            } // if
        } // if
    } // if
    else {
        if (stage_->IsAllEnemy()) {
            for (auto& enemy : enemys_) {
                if (enemy->IsShow()) {
                    return;
                } // if
            } // for

            game_effect_count_++;

            if (game_effect_count_ > game_effect_count_max_) {
                game_effect_count_ = 0;

                is_change_ = true;
                super::ChangeScene(sh::SCENE_NO::CLEAR);
            } // if
        } // if
    } // else

}