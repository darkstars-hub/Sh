//!---------------------------------------------------------
//! @file SoundManager.h
//! @brief ‰¹‚ğƒQ[ƒ€“à‚Å–Â‚ç‚·‚È‚ç‚±‚ÌƒNƒ‰ƒX‚ÖˆË—Š‚·‚é
//! @author name
//! @date 2019/11/06
//!---------------------------------------------------------


#ifndef SH_SOUND_MANAGER_H
#define SH_SOUND_MANAGER_H


#include <vector>

#include "ResourceManager.h"
#include "EventListener.h"

namespace sh {
class SoundManager {
public:
    SoundManager();
    ~SoundManager();
    SoundManager(const SoundManager& rhs) = delete;
    SoundManager& operator=(const SoundManager& rhs) = delete;
    SoundManager(SoundManager&& rhs) = delete;
    SoundManager& operator= (SoundManager&& rhs) = delete;

    void SetResourceManager(sh::ResourceManager& resource_container);
    bool Update(void);
private:
    sh::ResourceManager* resource_manager_;
    sh::EventListener* listener_;
};
}
#endif // !SH_SOUND_MANAGER_H