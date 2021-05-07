//!---------------------------------------------------------
//! @file EffectManager.h
//! @brief 生成された各Effect登録し更新、描画する <- レンダラー
//! メンバが多くなってきた
//! @author name
//! @date 2019/11/06
//!---------------------------------------------------------


#ifndef SH_EFFECT_MANAGER_H
#define SH_EFFECT_MANAGER_H

#include <deque>
#include <unordered_map>
#include <memory>
#include <optional>

#include "ResourceManager.h"
#include "Effect.h"
#include "Vector2.h"
#include "EventListener.h"
#include "EventMessenger.h"

namespace sh {
class EffectManager {
public:
    EffectManager();
    ~EffectManager();
    EffectManager(const EffectManager& rhs) = delete;
    EffectManager& operator=(const EffectManager& rhs) = delete;
    EffectManager(EffectManager&& rhs) = delete;
    EffectManager& operator= (EffectManager&& rhs) = delete;

    void Start(const float x, const float y, const sh::EffectType type);
    void Start(const Vector2 position, const sh::EffectType type);
    bool IsEndEffectEnd(void) const;
    //std::optional<sh::Effect> GetEndEffect(void);

    bool Load(sh::ResourceManager& resource_manager);
    bool Update(void);
    bool Render(void);
private:
    std::deque<sh::Effect> effects_;
    std::optional<sh::Effect>end_effect_;
    int end_effect_count_;

    std::unordered_map<sh::EffectType,
        std::shared_ptr<sh::Texture>> textures_;
    sh::EventListener* listener_;
};
}
#endif // !SH_EFFECT_MANAGER_H