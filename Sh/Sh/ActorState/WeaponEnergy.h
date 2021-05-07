//!---------------------------------------------------------
//! @file WeaponEnergy.h
//! @brief Player‚ª•Ší(Barrier)‚ğg‚¤‚ÉÁ”ï‚·‚é
//!        •`‰æˆÊ’u‚ÍŒÅ’è
//! @author name
//! @date 2019/11/18
//!---------------------------------------------------------

#ifndef SH_WEAPON_ENERGY_H
#define SH_WEAPON_ENERGY_H

#include <memory>

#include "Helper.h"
#include "Texture.h"

namespace sh {
class WeaponEnergy {
public:
    WeaponEnergy();
    ~WeaponEnergy();
    WeaponEnergy(const WeaponEnergy& rhs) = delete;
    WeaponEnergy(WeaponEnergy&& rhs) = delete;

    void SetFrameTexture(const std::shared_ptr<sh::Texture> texture);
    void SetEnegryTexture(const std::shared_ptr<sh::Texture> texture);

    bool Initialize(void);
    bool Update(void);
    bool Render(void);

    int GetValue(void) const noexcept;
    bool IsOverHeat(void) const noexcept;
    void Use(const int cost);
private:
    int value_;
    int limit_max_;
    bool overheat_;
    int overheat_time_;
    const int overheat_time_limit_max_;
    std::weak_ptr<sh::Texture> energy_texture_;
    std::weak_ptr<sh::Texture> frame_texture_;
};
}
#endif // !SH_WEAPON_ENERGY_H