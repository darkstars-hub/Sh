#include "EnemySkeleton.h"

sh::EnemySkeleton::EnemySkeleton() :
    super() {
    super::enemy_type_ = sh::EnemyType::SKELETON;

    move_count_ = 0;
    attack_count_ = 0;

    auto it_begin = destinations_.begin();
    auto it_end = destinations_.end();
    for (auto it = it_begin; it < it_end; ++it) {
        auto index = std::distance(it_begin, it);
        it->position.x_ = destination_positions[index * 2];
        it->position.y_ = destination_positions[index * 2 + 1];
        //it->is_set = false;

        if ((it + 1) != it_end) {
            it->next = &(*(it + 1));
        } // if
        else {
            it->next = &(*(it_begin));
        } // else

    } // for
    current_position_ = (*it_begin);
}

sh::Rectangle sh::EnemySkeleton::GetRectangle(void) const noexcept {
    if (!is_show_) {
        return std::move(sh::Rectangle());
    } // if

    // メンバに置けない
    auto collition_offset = sh::Vector2(-15.0f, -15.0f);
    auto size = sh::Vector2(64.0f, 64.0f);

    auto pos =
        super::position_ + collition_offset;
    return std::move(sh::Rectangle(
        pos.x_,
        pos.y_,
        pos.x_ + size.x_,
        pos.y_ + size.y_));
}

bool sh::EnemySkeleton::Render(void) {
    if (!is_show_) {
        return false;
    } // if


    if (auto r = texture_.lock()) {
        auto pos = super::position_;
        auto rect = this->animation_.GetRectangle();
        auto width = rect.GetWidth();
        auto height = rect.GetHeight();

        r->Render(pos.x_ + width * 0.5f,
                  pos.y_ + height * 0.5f,
                  super::angle_);
    } // if

#if defined (_DEBUG)
    {
        auto g = sh::Graphics();
//        g.DrawRectangle(this->GetRectangle(),
//                        sh::Color(0, 0, 255, 180));
    }
#endif // defined(_DEBUG)

    return true;
}

void sh::EnemySkeleton::SetUp(void) {
    animation_.MakeAnimation(32.0f, 32.0f, 1, 1);
    status_.Initialize(100);
    //status_.Initialize(1);
    status_.MakeWeapons(
        sh::WeaponType::THREE_WAY_GUN,
        sh::WeaponType::CIRCLE_GUN,
        sh::WeaponType::MINE,
        sh::WeaponType::RANDOM_GUN);
    status_.AddUser(*this);

    {
        auto weapon = status_.GetWeapon(0);
        weapon->SetShotPower(5);
        weapon->SetShotIntervalMax(30);
    }

    {
        auto weapon = status_.GetWeapon(1);
        weapon->SetShotPower(8);
        weapon->SetShotIntervalMax(70);
    }

    {
        auto weapon = status_.GetWeapon(2);
        weapon->SetShotIntervalMax(60);
        weapon->ChangeBulletType(sh::BulletType::Bomb);
    }

    {
        auto weapon = status_.GetWeapon(3);
        weapon->SetShotPower(3);
        weapon->SetShotIntervalMax(0);
    }

}

void sh::EnemySkeleton::Move(void) {
    // ピンチになったらいろいろ動く
    if (status_.GetHp()->GetValue() < 500) {
        auto dest = current_position_.position;

        float size = 30.0f;
        auto pos = super::position_;
        if (!sh::Circle(size, pos.x_, pos.y_).
            CollisionCircle(sh::Circle(size, dest.x_, dest.y_))) {
            status_.GetMotion()->Translate(*this, dest);
        } // if
        else {
            move_count_++;
        } // else

        if (move_count_ > 120) {
            move_count_ = 0;
            auto& dests = destinations_;
            //current_position_ = *current_position_.next;
            current_position_ = dests.at(
                sh::GenerateRandom(0, dests.size() - 1));
            //current_position_.next->is_set = true;
        } // if
    } // if
    else {
        status_.GetMotion()->Translate(
            *this, (*destinations_.begin()).position);
    } // else
    super::position_ += super::move_;
}

void sh::EnemySkeleton::Attack(void) {
    // 武器使用
    {
        auto weapon = status_.GetWeapon(0);
        weapon->AddBullet(20);
        if (weapon->CanShot()) {
            weapon->Fire();
        } // if
    }

    {
        auto weapon = status_.GetWeapon(1);
        weapon->AddBullet(20);
        if (weapon->CanShot()) {
            weapon->Fire();
        } // if
    }

    if (status_.GetHp()->GetValue() < 500) {
        {
            auto weapon = status_.GetWeapon(2);
            weapon->AddBullet(20);
            if (weapon->CanShot()) {
                weapon->Fire();
            } // if
        }

        {
            auto weapon = status_.GetWeapon(3);
            if (weapon->CanShot()) {
                weapon->Fire();
            } // if
            attack_count_++;

            if (attack_count_ > 300) {
                attack_count_ = 0;
                weapon->AddBullet(90);
            } // if
        }
    } // if
}

void sh::EnemySkeleton::Damage(const int damage_value) {
    auto pos = super::position_;
    auto rect = this->animation_.GetRectangle();
    auto width = rect.GetWidth();
    auto height = rect.GetHeight();

    status_.GetHp()->Damage(damage_value);

    //ダメージエフェクト発生
    {
        sh::EffectEvent* e = new EffectEvent();
        e->destination_id_ = sh::ClassID::EFFECT_MANAGER;
        e->id_ = sh::EventID::DAMAGE;
        e->position_ = Vector2(pos.x_ + width * 0.5f,
                               pos.y_ + height * 0.5f);
        listener_->Send(*e);
    }
    
    if (status_.GetHp()->GetValue() <= 0) {
        super::is_show_ = false;
        {
            sh::EffectEvent* e = new EffectEvent();
            e->destination_id_ = sh::ClassID::EFFECT_MANAGER;
            e->id_ = sh::EventID::DEAD;
            e->position_ = Vector2(pos.x_ + width * 0.5f,
                                   pos.y_ + height * 0.5f);
            listener_->Send(*e);
        }
    } // else
}