#pragma once

#include "./Event.h"
#include "./HashMap.h"
#include "./Client.h"
#include "./Package.h"

#include <string>
#include <fstream>
#include <cstdio>

class System {
    private:
        HashMap<std::string, Client*> client_map;
        HashMap<int, Package*> package_map;
        Event events[200] = {};

    public:
        System() : client_map(), package_map(), events() {}

        ~System() {
            client_map.deleteAllValues();
            package_map.deleteAllValues();

        };

        // Getters
        Event* getEvents();
        HashMap<std::string, Client*>& getClientHash();
        HashMap<int, Package*>& getPackageHash();

        // Processa o registro de um pacote.
        void processRG(Event& event, int index);
        
        // Processa os outros eventos de um pacote.
        void processOtherPackEvent(Event& event, int index);

        // Imprime um evento.
        void printEvent(Event& event);
};