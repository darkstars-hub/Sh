//!---------------------------------------------------------
//! @file EventMessenger.h
//! @brief EventListener‚©‚çEvent‚ğó‚¯æ‚é
//!        “o˜^‚µ‚½EventListener‚ÖEvent‚ğ‘—‚é
//!        Event*‚ÌŠÇ—‚ÍŠë‚È‚Á‚©‚µ‚¢‚Ì‚Å’ˆÓ‚·‚é‚±‚Æ
//! @author name
//! @date 2019/12/09
//!---------------------------------------------------------


#ifndef SH_EVENT_MESSENGER_H
#define SH_EVENT_MESSENGER_H

#include <vector>

#include "Event.h"
#include "EventListener.h"


namespace sh {
class EventMessenger {
public:
    EventMessenger();
    ~EventMessenger();

    static EventMessenger& Singleton(void);

    sh::EventListener* CreateListener(sh::ClassID id);
    void AddEventListener(sh::EventListener& listener);
    void ClearMessage(void);
    void Send(void);
    void Receive(sh::Event& e);

    std::vector<sh::EventListener*> listeners_;
    std::vector<sh::Event*> events_;
private:
};
}
#endif // !SH_EVENT_MESSENGER_H