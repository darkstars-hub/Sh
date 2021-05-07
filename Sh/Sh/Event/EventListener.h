#ifndef SH_EVENT_LISTENER_H
#define SH_EVENT_LISTENER_H


#include <memory>
#include <vector>

#include "Event.h"

namespace sh {
class EventListener {
public:
    EventListener(sh::ClassID id);
    ~EventListener();
    EventListener(const EventListener& rhs) = default;
    EventListener& operator=(const EventListener& rhs) = default;
    EventListener(EventListener&& rhs) = default;
    EventListener& operator=(const EventListener&& rhs) = delete;
    
    void Send(sh::Event& e);
    void Receive(sh::Event& e);
    void ResetEvents(void);

    sh::ClassID class_id_;
    std::vector<sh::Event*> events_;
private:
};
}
#endif // !SH_EVENT_LISTENER_H