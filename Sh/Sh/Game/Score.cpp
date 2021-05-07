#include "Score.h"

sh::Score::Score() :
    texture_(),
    score_(0),
    count_score_(0),
    is_counted_(false),
    number_rectangles_(),
position_(){
}

sh::Score::~Score() {
}

void sh::Score::AddScore(const int score) {
    score_ += score;
}

void sh::Score::AddPosition(const sh::Vector2 position) {
    this->position_ += position;
}

bool sh::Score::Initialize(sh::ResourceManager& r) {
    this->texture_ = r.GetTexture(
        sh::TextureFileID::NUMBER_TEXTURE);

            // Še”Žš‚Ì•\Ž¦‹éŒ`
    for (auto it = number_rectangles_.begin(); it != number_rectangles_.end(); ++it) {
        auto index = std::distance(number_rectangles_.begin(), it);
        *(it) = sh::Rectangle(
            0.0f + 64.0f * index,
            0.0f,
            64.0f + 64.0f * index,
            64.0f);
    } // for
    return true;
}


bool sh::Score::Update(void) {
    //score_ += 10;
    is_counted_ = false;

    if (score_ > count_score_) {
        count_score_++;
        is_counted_ = true;
    } // if
    return true;
}
bool sh::Score::Render(void) {
    const auto score = count_score_;

    const auto place10000 = (score / 10000) % 10;
    const auto place1000 = (score / 1000) % 10;
    const auto place100 = (score / 100) % 10;
    const auto place10 = (score / 10) % 10;
    const auto place1 = (score / 1) % 10;

    const auto width = number_rectangles_.begin()->GetWidth();
    const auto height = number_rectangles_.begin()->GetHeight();

    /*const*/ auto offset = is_counted_ ?
        sh::Vector2(
           static_cast<float>(sh::GenerateRandom(-3, 3)),
           static_cast<float>(sh::GenerateRandom(-3, 3)))
        : sh::Vector2();

    offset += position_;
    
    if (auto r = texture_.lock()) {
        r->Render(width * 0 + 32.0f + offset.x_,
                  sh::kWindowHeight - height + offset.y_,
                  1.0f,
                  number_rectangles_.at(place10000));
        r->Render(width * 1 + 32.0f + offset.x_,
                  sh::kWindowHeight - height + offset.y_,
                  1.0f,
                  number_rectangles_.at(place1000));
        r->Render(width * 2 + 32.0f + offset.x_,
                  sh::kWindowHeight - height + offset.y_,
                  1.0f,
                  number_rectangles_.at(place100));
        r->Render(width * 3 + 32.0f + offset.x_,
                  sh::kWindowHeight - height + offset.y_,
                  1.0f,
                  number_rectangles_.at(place10));
        r->Render(width * 4 + 32.0f + offset.x_,
                  sh::kWindowHeight - height + offset.y_,
                  1.0f,
                  number_rectangles_.at(place1));
    } // if
    return true;
}
