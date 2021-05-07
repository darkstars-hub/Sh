#include "EventMessenger.h"

sh::EventMessenger::EventMessenger() :
    listeners_() {
}

sh::EventMessenger::~EventMessenger() {
}

sh::EventMessenger& sh::EventMessenger::Singleton(void) {
    static sh::EventMessenger object;
    return object;
}

void sh::EventMessenger::AddEventListener(sh::EventListener& listener) {
    listeners_.push_back(&listener);
}

sh::EventListener* sh::EventMessenger::CreateListener(sh::ClassID id) {
    return new sh::EventListener(id);
}

#include <iostream>
void sh::EventMessenger::Send(void) {
   // std::cout << "size = " <<  listeners_.size() << "\n";
   // std::cout << "event size = " << events_.size() << "\n";

    for (auto listener : listeners_) {
     //   std::cout << "id = " << (int)listener->class_id_ << "\n";
        for (auto e : events_) {
       //     std::cout << "destination = " << (int)(e->destination_id_) << "\n";
       //     std::cout << "event id = " << (int)(e->id_) << "\n";
            if (listener->class_id_ == e->destination_id_) {
                listener->Receive(*e);
            } // if
        } // for
    } // for
}

void sh::EventMessenger::Receive(sh::Event& e) {
    events_.push_back(&e);
}

void sh::EventMessenger::ClearMessage(void) {
    events_.clear();
}