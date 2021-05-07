#ifndef SH_EFFECT_H
#define SH_EFFECT_H

#include <memory>
#include <vector>

#include "Object.h"
#include "Helper.h"
#include "Animation.h"
#include "Texture.h"

namespace sh {
enum class EffectType {
    DAMAGE,
    DEAD,
    GAME_START,
//    GAME_CLEAR,
//    GAME_OVER,

//    GAME_LOGO,
    COUNT_MAX,
};
class Effect final : public sh::Object {
    using super = sh::Object;
public:
    Effect();
    ~Effect();
    Effect(const Effect& rhs) = default;
    Effect& operator=(const Effect& rhs) = default;
    Effect(Effect&& rhs)  = default;
    Effect& operator= (Effect&& rhs)  = default;

    //virtual bool IsShow(void) const noexcept;
    void SetTexture(std::shared_ptr<sh::Texture> texture);

    bool Initialize(const sh::EffectType type);
    bool Initialize(void)override;
    bool Update(void)    override;
    bool Render(void)    override;
    bool Release(void)   override;
    
    void Start(const sh::Vector2 position);
    void Start(const float position_x, const float position_y);
    void MakeAnimation(const sh::EffectType type);
private:
    std::weak_ptr<sh::Texture> texture_;
    //std::unique_ptr<sh::Animation> animation_;
    sh::Animation animation_;

    sh::Rectangle GetRectangle(void) const noexcept override;
};
}
#endif // !SH_EFFECT_H