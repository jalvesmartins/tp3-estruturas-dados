#pragma once

#include <string>

enum event_type {
    RG,
    AR,
    RM,
    UM,
    TR,
    EN,
    N
};

class Event {
    private:
        int event_time;
        event_type type;
        int pack_id;
        std::string sender;
        std::string recipient;
        int origin_warehouse;
        int destination_warehouse;
        int next_warehouse;

    public:
        // Construtor padrão
        Event() : event_time(0), type(N), pack_id(-1), sender(""), recipient(""), origin_warehouse(-1), destination_warehouse(-1), next_warehouse(-1) {}

        // Construtor completo
        Event(int event_time, event_type type, int pack_id, const std::string& sender, const std::string& recipient, int origin_warehouse, int destination_warehouse, int next_warehouse) :
        event_time(event_time), type(type), pack_id(pack_id), sender(sender), recipient(recipient), origin_warehouse(origin_warehouse),
        destination_warehouse(destination_warehouse), next_warehouse(next_warehouse) {}
        
        // Destrutor padrão
        ~Event() = default;

        // Getters
        int getEventTime() const;
        event_type getEventType() const;
        int getPackId() const;
        std::string getSender() const;
        std::string getRecipient() const;
        int getOriginWarehouse() const;
        int getDestinationWarehouse() const;
        int getNextWarehouse() const;

        //
};