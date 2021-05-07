#ifndef SH_STAGE_H
#define SH_STAGE_H

#include <fstream>
#include <string>
#include <charconv>
#include <vector>
#include <memory>

#include "Helper.h"
#include "Texture.h"
#include "Enemy.h"
#include "EnemyFactory.h"
#include "Stage1.h"
#include "ResourceManager.h"


struct EnemyStart {
    int count;
    std::vector<float> position_x;
    std::vector<float> scroll;
    std::vector<int  > type;
};

namespace sh {
class Stage {
public:
    Stage();
    ~Stage();
    Stage(const Stage& rhs) = delete;
    Stage& operator=(const Stage& rhs) = delete;
    Stage(Stage&& rhs) = delete;
    Stage& operator= (Stage&& rhs) = delete;


    void SetScrollSpeed(const float speed_x, const float speed_y);
    sh::Vector2 GetScroll(void) const noexcept;

    bool Load(sh::ResourceManager& resource_manager, int select);
    //bool Initialize(EnemyStart* start);
    bool Initialize(void);

    bool Update(sh::Enemy** enemy, int count, Vector2 pos);
    bool Render(void);
    bool Release(void);

    bool IsAllEnemy(void);
    void ChangeSound(void);
private:
    sh::EnemyFactory enemy_factory_;
    const sh::Vector2 scroll_speed_default_;
    sh::Vector2 scroll_speed_;
    sh::Vector2 scroll_;
    const sh::Vector2 boss_exist_scroll_;
    bool boss_exist_;
    float stage_rotate_;
    bool boss_stage_show_;
    sh::Vector2 boss_stage_position_;
    int boss_stage_show_count_;
    int stage_number_;

    std::weak_ptr<sh::Texture> texture_;
    std::weak_ptr<sh::Texture> boss_texture_;
    std::shared_ptr<sh::SoundBuffer> sound_;
    std::shared_ptr<sh::SoundBuffer> sound_boss_;

    EnemyStart* enemy_start_;
    int enemy_no_;

    void ChangeSpeed(void);
    void UpdateMember(void);
    void RenderBossStage(void);
    void RenderStage(void);
};
}
#endif // !SH_STAGE_H