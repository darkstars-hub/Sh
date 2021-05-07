#include "Beam.h"


sh::Beam::Beam() :
    super(),
    bpos_()
//    circle_texture_()
{
    is_show_ = false;
    super::type_ = sh::BulletType::Beam;
}
sh::Beam::~Beam() {
    //texture_->Release();
    //circle_texture_.Release();
}

sh::Rectangle sh::Beam::GetRectangle(void) const noexcept {
    return sh::Rectangle();
}
int sh::Beam::GetAttackValue(void) const noexcept {
    return super::attack_value_;
}

std::vector<sh::Beam::BeamPosition>& sh::Beam::GetPositions(void) {
    // TODO: return ステートメントをここに挿入します
    return bpos_;
}
bool sh::Beam::IsEnable(void) const {
    if (bpos_.size() > 2) {
        return true;
    } // if
    return false;
}

bool sh::Beam::Initialize(void) {
    //circle_texture_.Load("../textures/beam_circle.png");
    return true;
}

bool sh::Beam::Update(void) {
    if (!super::is_show_) {
        return true;
    } // if


    auto size = super::current_animation_.GetRectangle().GetWidth();
    bpos_.erase(std::remove_if(bpos_.begin(), bpos_.end(),
                               [=](BeamPosition& b) {
        return
            b.pos.x_ < 0 - size ||
            b.pos.x_ > kWindowWidth + size ||
            b.pos.y_ < 0 - size ||
            b.pos.y_ > kWindowHeight + size;
    }), bpos_.end());

    super::current_animation_.Update();

    //super::move_ = super::speed_;
    //super::position_ += super::move_;

    for (auto& b : bpos_) {
        b.pos += b.move;
    } // for


    //std::cout << "size = " << bpos_.size() << "\n";
    //DEBUG_PRINT("size = %d \n", bpos_.size());

    return true;
}

bool sh::Beam::Render(void) {
    if (!super::is_show_) {
        return true;
    } // if

    if (bpos_.size() < 2) {
        return true;
    } // if

    /*
    {
        auto pos = (bpos_.end() - 1)->pos;
        pos.y_ += circle_texture_.GetHeight() * 0.125f;
        circle_texture_.Render(pos.x_, pos.y_,angle_);
    }
    */

    using namespace std;
    auto rect = super::current_animation_.GetRectangle();
    auto half_width = rect.GetWidth() * 0.25f;
    auto half_height = rect.GetHeight() * 0.25f;
    auto            vertical = 90.0f;

    float increment_size = 1.0f / bpos_.size();
    float tex_coord_increments = increment_size;
    for (auto it = ++bpos_.begin(); it != bpos_.end() - 1; ++it) {
        auto pos_previous = (it - 1)->pos;
        auto pos_current = (it)->pos;
        auto pos_next = (it + 1)->pos;

        // ひとつ前の点から現在の点まで
        auto radian = atan2(pos_previous.y_ - pos_current.y_,
                            pos_previous.x_ - pos_current.x_);
        auto degree = ToDegree(radian);
        auto degree_left = degree - vertical;
        auto degree_right = degree + vertical;
        auto left = sh::Vector2(pos_current.x_ + cosf(ToRadian(degree_left)) * half_width,
                                pos_current.y_ + sinf(ToRadian(degree_left)) * half_height);
        auto right = sh::Vector2(pos_current.x_ + cosf(ToRadian(degree_right)) * half_width,
                                 pos_current.y_ + sinf(ToRadian(degree_right)) * half_height);


        // 現在前の点から次の点まで
        auto next_radian = atan2(pos_current.y_ - pos_next.y_,
                                 pos_current.x_ - pos_next.x_);
        auto next_degree = ToDegree(next_radian);
        auto next_degree_left = next_degree - vertical;
        auto next_degree_right = next_degree + vertical;
        auto next_left = sh::Vector2(pos_next.x_ + cosf(ToRadian(next_degree_left)) * half_width,
                                     pos_next.y_ + sinf(ToRadian(next_degree_left)) * half_height);
        auto next_right = sh::Vector2(pos_next.x_ + cosf(ToRadian(next_degree_right)) * half_width,
                                      pos_next.y_ + sinf(ToRadian(next_degree_right)) * half_height);


        auto tex_width = texture_->GetWidth();
        auto tex_height = texture_->GetHeight();

        auto index = std::distance(it, bpos_.end());
        index++;

        auto tex_coord = sh::Vector2(
            rect.left_ / tex_width,
            rect.top_ / tex_height + tex_coord_increments);
        auto offset = sh::Vector2(
            rect.right_ / tex_width,
            rect.top_ / tex_height + tex_coord_increments + increment_size);
        tex_coord_increments += increment_size;

        // 描画
        texture_->Bind();
        ::glEnable(GL_TEXTURE_2D);
        ::glEnable(GL_BLEND);
        ::glBegin(GL_TRIANGLE_STRIP);

        ::glPushMatrix();
        ::glTranslatef(pos_current.x_, pos_current.y_, 0.0f);
        ::glRotatef(super::angle_, 0.0f, 0.0f, 1.0f);

        // 0
        ::glTexCoord2f(tex_coord.x_, tex_coord.y_);
        ::glVertex2f(left.x_,
                     left.y_);
        // 1
        ::glTexCoord2f(offset.x_, tex_coord.y_);
        ::glVertex2f(right.x_,
                     right.y_);
        // 3
        ::glTexCoord2f(tex_coord.x_, offset.y_);
        ::glVertex2f(next_left.x_,
                     next_left.y_);
        // 3
        ::glTexCoord2f(tex_coord.x_, offset.y_);
        ::glVertex2f(next_left.x_,
                     next_left.y_);
        // 1
        ::glTexCoord2f(offset.x_, tex_coord.y_);
        ::glVertex2f(right.x_,
                     right.y_);
        // 2
        ::glTexCoord2f(offset.x_, offset.y_);
        ::glVertex2f(next_right.x_,
                     next_right.y_);

        ::glEnd();
        ::glPopMatrix();
        ::glDisable(GL_TEXTURE_2D);
    } // for

    return true;
}

void sh::Beam::Fire(const sh::Vector2 position, const float angle, const sh::Vector2 speed) {
    super::is_show_ = true;
    super::position_ = position;
    super::angle_ = angle;
    super::speed_ = speed;

    float s = 30.0f;

    float direction = kPi * (angle + 90) / 180.0f;
    Vector2 bullet_speed = sh::Vector2(
        std::cosf(direction) * s,
        std::sinf(direction) * s);
    bpos_.push_back({ position, bullet_speed });
}

bool sh::Beam::MakeAnimation(void) {
    super::current_animation_.MakeAnimation(128.0f, 128.0f, 1, 8);
    super::current_animation_.SetRate(1);
    return true;
}