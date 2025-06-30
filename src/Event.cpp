#include "../include/Event.h"

int Event::getEventTime() const {
    return this->event_time;
}

event_type Event::getEventType() const {
    return this->type;
}

int Event::getPackId() const {
    return this->pack_id;
}

std::string Event::getSender() const {
    return this->sender;
}

std::string Event::getRecepient() const {
    return this->recipient;
}

int Event::getOriginWarehouse() const {
    return this->origin_warehouse;
}

int Event::getDestinationWarehouse() const {
    return this->destination_warehouse;
}

int Event::getNextWarehouse() const {
    return this->next_warehouse;
}