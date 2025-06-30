#include "../include/Package.h"

int Package::getId() const {
    return this->pack_id;
}

const List<int>& Package::getEvents() const {
    return this->events;
}

void Package::addEvent(int event_position) {
    this->events.pushBack(event_position);
}