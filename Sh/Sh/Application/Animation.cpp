//!---------------------------------------------------------
//! @file Animation.h
//! @brief テクスチャに渡すRectangleクラスのvector
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#include "Animation.h"

sh::Animation::Animation()
    : rectangles_(),
    index_(0),
    rate_(5),
    count_(0) {
}
sh::Animation::~Animation() {
}

void sh::Animation::SetCurrentIndex(int index) {
    this->index_ = index;
}
void sh::Animation::SetRate(int rate) {
    this->rate_ = rate;
}
sh::Rectangle sh::Animation::GetRectangle() const {
    auto it = rectangles_.begin();
    return *(it + index_);
}
int sh::Animation::GetCurrentIndex() const {
    return this->index_;
}
int sh::Animation::GetRate() const {
    return this->rate_;
}
bool sh::Animation::IsEnd() const {
    return index_ == 0 && count_ == 0;
}
void sh::Animation::PushRectangle(sh::Rectangle rectangle) {
    rectangles_.push_back(rectangle);
}

void sh::Animation::ResetRectangles() {
    rectangles_.clear();
}
void sh::Animation::MakeAnimation(const sh::MakeAnime make_animetion) {
    auto a = make_animetion;
    this->MakeAnimation(
        a.width,
        a.height,
        a.column_count,
        a.row_count,
        a.offset);
}
void sh::Animation::MakeAnimation(float width, float height, int column_count, int row_count, sh::Vector2 offset) {
    for (int i = 0; i < column_count; i++) {
        for (int j = 0; j < row_count; j++) {
            PushRectangle(std::move( sh::Rectangle(
                offset.x_ + 0.0f   + width  * j,
                offset.y_ + 0.0f   + height * i,
                offset.x_ + width  + width  * j,
                offset.y_ + height + height * i)));
        } // for
    } // for
}
bool sh::Animation::Initialize() {
    index_ = 0;
    count_ = 0;
    return true;
}
void sh::Animation::Update() {
    count_++;
    if (count_ > rate_) {
        index_++;
        count_ = 0;
    } // if
    if (index_ >= rectangles_.size()) {
        index_ = 0;
    } // if
}