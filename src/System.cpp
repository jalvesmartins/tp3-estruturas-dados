#include "../include/System.h"

class Event;

Event* System::getEvents() {
    return this->events;
}

void System::processRG(Event& event, int index) {
    Package new_pack(event.getPackId(), index);
    package_map.insert(event.getPackId(), new_pack);
}

void System::processOtherPackEvent(Event& event, int index) {

    Package* pack = package_map.getValue(event.getPackId());
    pack->addEvent(index);
}

