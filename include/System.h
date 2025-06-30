#pragma once

#include "./Event.h"
#include "./HashMap.h"
#include "./Client.h"
#include "./Package.h"

#include <string>
#include <fstream>

class System {
    private:
        HashMap<std::string, Client> client_map;
        HashMap<int, Package> package_map;
        Event events[200] = {};

    public:
        System() : client_map(), package_map(), events() {}

        ~System() = default;

        // Getters
        Event* getEvents();

        void processRG(Event& event, int index);

        void processOtherPackEvent(Event& event, int index);

};