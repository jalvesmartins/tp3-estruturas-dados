#pragma once

#include "./List.h"

class Package {
    private:
        int pack_id;
        List<int> events;

    public:
        // Constutor padrão.
        Package() : pack_id(-1), events() {}

        // Construtor completo.
        Package(int pack_id, int event_position) : pack_id(pack_id) {
            this->events.pushBack(event_position);
        }

        // Destrutor.
        ~Package() = default;

        // Getters
        int getId() const;
        List<int>& getEvents();
};