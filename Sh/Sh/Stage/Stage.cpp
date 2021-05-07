#include "Stage.h"

#include "Application.h"

sh::Stage::Stage()
    : scroll_speed_default_(sh::Vector2(0.0f, -5.0f)),
    scroll_speed_(scroll_speed_default_),
    scroll_(sh::Vector2(0.0f, 0.0f)),
    boss_exist_scroll_(sh::Vector2(0.0f, -13000.0f)),
    boss_exist_(false),
    stage_rotate_(0.0f),
    boss_stage_show_(false),
    boss_stage_position_(-1024.0f, 0.0f),
    boss_stage_show_count_(0),

    texture_(),
    boss_texture_(),
    sound_(nullptr),
    sound_boss_(nullptr),

    enemy_start_(new EnemyStart()),
    enemy_no_(0) {
}

sh::Stage::~Stage() {
    if (sound_) {
        sound_->SetGain(0.0);
    } // if
    if (sound_boss_) {
        sound_boss_->SetGain(0.0);
    } // if
}

void sh::Stage::SetScrollSpeed(const float speed_x, const float speed_y) {
    this->scroll_speed_.x_ = speed_x;
    this->scroll_speed_.y_ = speed_y;
}

sh::Vector2 sh::Stage::GetScroll(void) const noexcept {
    return this->scroll_;
}

bool sh::Stage::Load(sh::ResourceManager& resource_manager, int select) {
    using TexID = sh::TextureFileID;
    using SoundID = sh::SoundFileID;

    switch (select) {
        case 1:
            texture_ = resource_manager.GetTexture(TexID::STAGE_TEXTURE_MORNING);
            sound_ = resource_manager.GetSoundBuffer(SoundID::STAGE_01);
            sound_boss_ = resource_manager.GetSoundBuffer(SoundID::STAGE_BOSS);
            break;
        case 2:
            texture_ = resource_manager.GetTexture(TexID::STAGE_TEXTURE_NIGHT);
            sound_ = resource_manager.GetSoundBuffer(SoundID::STAGE_02);
            sound_boss_ = resource_manager.GetSoundBuffer(SoundID::STAGE_BOSS);
            break;
        case 3:
            texture_ = resource_manager.GetTexture(TexID::STAGE_TEXTURE);
            boss_texture_ = resource_manager.GetTexture(TexID::STAGE_BOSS_TEXTURE);
            sound_ = resource_manager.GetSoundBuffer(SoundID::STAGE_03);
            sound_boss_ = resource_manager.GetSoundBuffer(SoundID::STAGE_BOSS);
            break;
        default:
            break;
    } // switch

    enemy_factory_.SetResourceManager(resource_manager);


    stage_number_ = select;

    std::vector< std::string > data;
    std::ifstream stream;
    switch (select) {
        case 1:
            stream = std::ifstream("../stages/stage1.txt");
            break;
        case 2:
            stream = std::ifstream("../stages/stage2.txt");
            break;
        case 3:
            stream = std::ifstream("../stages/stage3.txt");
            break;
        default:
            break;
    } // switch

    if (!stream.is_open()) {
        throw std::runtime_error("file can not open");
        //return false;
    } // if

    while (!stream.eof()) {
        std::string str;
        std::getline(stream, str);
        data.push_back(str);
    } // for
    stream.close();

    auto convert = [](std::string& str) ->float {
        float result;
        std::from_chars(
            str.data(),
            str.data() + str.size(),
            result);
        return result;
    };


    std::string x_str = "x=";
    std::string scroll_str = "scroll=";
    std::string type_str = "type=";

    int index = 0;
    for (auto str : data) {
        char* ptr;
        ptr = std::strtok(const_cast<char*>(str.c_str()), ";");
        auto work = str;
        auto copy = work;

        std::string check;
        check = std::strtok(const_cast<char*>(str.c_str()), "=");

        if (std::equal(check.begin(), check.end(), "count")) {
            auto count =
                std::strtok(const_cast<char*>(work.c_str()), "count=");

            int result;
            std::from_chars(
                count,
                count + std::strlen(count),
                result);
            enemy_start_->count = result;
            continue;
        } // if
        unsigned int begin;
        unsigned int end;
        std::string code;
        //float result;

        begin = work.find(x_str) + x_str.size();
        end = work.find(",");
        code = std::string(work, begin, end - begin);
        enemy_start_->position_x.push_back(convert(code));

        begin = work.find(scroll_str) + scroll_str.size();
        work = std::string(work, begin, (work.size() - 1));
        end = work.find(",");
        code = std::string(work, 0, end);
        enemy_start_->scroll.push_back(convert(code));

        begin = work.find(type_str) + type_str.size();
        work = std::string(work, begin, (work.size() - 1));
        end = work.find(",");
        code = std::string(work, 0, end);
        enemy_start_->type.push_back(convert(code));

        index++;
    } // for

    return true;
}


bool sh::Stage::Initialize(void) {
    scroll_.Zero();
    enemy_no_ = 0;

    sound_->SetPosition(0);
    sound_->SetLoop(true);
    sound_->SetGain(0.1);

    sound_boss_->SetPosition(0);
    sound_boss_->SetLoop(true);
    sound_boss_->SetGain(0.1);

    sound_->Play();
    return true;
}

bool sh::Stage::Update(sh::Enemy** enemy, int count, Vector2 pos) {
    this->UpdateMember();
    this->ChangeSpeed();
    this->ChangeSound();
    scroll_speed_ = scroll_speed_default_;
    scroll_ += scroll_speed_;

    if (enemy_no_ < enemy_start_->count &&
        scroll_.y_ <= enemy_start_->scroll[enemy_no_]) {

        for (int i = 0; i < count; i++) {
            if (enemy[i]->IsShow()) {
                continue;
            } // if
            switch (enemy_start_->type[enemy_no_]) {
                case 0:
                    enemy[i] = enemy_factory_.PlaceCreate(
                        sh::EnemyType::CROWN, enemy[i]);
                    break;
                case 1:
                    enemy[i] = enemy_factory_.PlaceCreate(
                        sh::EnemyType::PURPLE_HAT, enemy[i]);
                    break;
                case 2:
                    enemy[i] = enemy_factory_.PlaceCreate(
                        sh::EnemyType::BLACK_HAT, enemy[i]);
                    break;
                case 3:
                    enemy[i] = enemy_factory_.PlaceCreate(
                        sh::EnemyType::YELLOW_HAT, enemy[i]);
                    break;
                case 4:
                    enemy[i] = enemy_factory_.PlaceCreate(
                        sh::EnemyType::BLUE_HAT, enemy[i]);
                    break;
                case 5:
                    enemy[i] = enemy_factory_.PlaceCreate(
                        sh::EnemyType::SKELETON, enemy[i]);
                    break;
            } // switch
            enemy[i]->Initialize();
            enemy[i]->SetUp();
            enemy[i]->SetTargetPosition(pos);
            enemy[i]->Start(Vector2(enemy_start_->position_x[enemy_no_],
                                    768.0f));
            break;
        } // for
        enemy_no_++;
    } // if
    return true;
}

bool sh::Stage::Render(void) {
    if (boss_stage_show_) {
        this->RenderBossStage();
    } // if
    else {
        this->RenderStage();
    } // else

    return true;
}

bool sh::Stage::Release(void) {
    sound_->Stop();
    sound_.reset();

    //sound_boss_->Release();
    sound_boss_->Stop();
    sound_boss_.reset();
    return true;
}

bool sh::Stage::IsAllEnemy(void) {
    return enemy_no_ >= enemy_start_->count;
    //return enemy_no_ > enemy_start_->count;
}


void sh::Stage::ChangeSound(void) {
    if (boss_exist_) {
        sound_->SetGain(0.0);
        if (!sound_boss_->IsPlay()) {
            sound_boss_->Play();
        } // if
    } // if
}

void sh::Stage::ChangeSpeed(void) {
    auto pad = sh::Application::GetInstance().GetGamePad();
    auto y = pad->GetRightThumbY() / 32767.0f;
    if (std::abs(y) >= 0.5) {
        if (y <= 0.0f) {
            scroll_speed_.y_ += 1.0f;
        } // if
        else {
            scroll_speed_.y_ -= 1.0f;
        } // else
    } // if
}

void sh::Stage::UpdateMember(void) {
    if (scroll_.y_ <= boss_exist_scroll_.y_) {
        boss_exist_ = true;
    } // if

    if (boss_exist_) {
        boss_stage_position_.x_ += 8.0f;
    } // if

    if (boss_stage_position_.x_ > -sh::kWindowWidth * 0.5f) {
        boss_stage_show_count_++;
        boss_stage_position_.x_ -= 8.0f;
    } // if

    if (boss_stage_show_count_ > 60) {
        boss_stage_show_ = true;

        stage_rotate_ += 1.0f;
    } // if
}

void sh::Stage::RenderBossStage(void) {
    if (auto r = boss_texture_.lock()) {
        float x = kWindowWidth;
        float y = kWindowHeight;
        auto rect = sh::Rectangle(0.0f, 0.0f, (float)r->GetWidth(), (float)r->GetHeight());
        r->Render(0.0f + x * 0.5f,
                  0.0f + y * 0.5f,
                  stage_rotate_,
                  rect,
                  2.0f);
    } // if
}

void sh::Stage::RenderStage(void) {
    if (stage_number_ == 1) {
        if (auto r = texture_.lock()) {
            int height = r->GetHeight();
            int screen_height = sh::kWindowHeight;

            for (float y = ((int)scroll_.y_ % height) - height; 
                 y < screen_height; y += height) {
                r->Render(0.0f, y);
            } // for
        } // if
        return;
    } // if

    if (auto r = texture_.lock()) {

        auto width = r->GetWidth();
        auto height = r->GetHeight();

        for (auto y = (static_cast<int>(scroll_.y_) % height) - height;
             y < kWindowHeight; y += height) {
            for (auto x = (static_cast<int>(scroll_.x_) % width) - width;
                 x < kWindowWidth; x += width) {
                r->Render(static_cast<float>(x), static_cast<float>(y));
            } // for
        } // for
    } // if
    if (!boss_exist_) {
        return;
    } // if

    if (auto r = boss_texture_.lock()) {
        float x = kWindowWidth;
        float y = kWindowHeight;
        auto pos = sh::Vector2();
        auto rect = sh::Rectangle();

        pos = boss_stage_position_;
        rect = sh::Rectangle(
            0.0f,
            0.0f,
            static_cast<float>(r->GetWidth() * 0.5f),
            static_cast<float>(r->GetHeight()));
        r->Render(0.0f + x * 0.5f + pos.x_,
                  0.0f + y * 0.5f + pos.y_,
                  0,
                  rect,
                  2.0f);

        pos.x_ *= -1;
        rect = sh::Rectangle(
            static_cast<float>(r->GetWidth() * 0.5f),
            0.0f,
            static_cast<float>(r->GetWidth()),
            static_cast<float>(r->GetHeight()));
        r->Render(0.0f + x * 0.5f + pos.x_,
                  0.0f + y * 0.5f + pos.y_,
                  0,
                  rect,
                  2.0f);
    } // if
}