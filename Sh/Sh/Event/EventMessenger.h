//!---------------------------------------------------------
//! @file EventMessenger.h
//! @brief EventListenerからEventを受け取る
//!        登録したEventListenerへEventを送る
//!        Event*の管理は危なっかしいので注意すること
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