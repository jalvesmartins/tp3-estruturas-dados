#include "../include/System.h"

class Event;

Event* System::getEvents() {
    return this->events;
}

HashMap<std::string, Client*>& System::getClientHash() {
    return this->client_map;
}

HashMap<int, Package*>& System::getPackageHash() {
    return this->package_map;
}

void System::processRG(Event& event, int index) {
    // Cria novo pacote.
    Package* new_pack = new Package(event.getPackId(), index);
    package_map.insert(event.getPackId(), new_pack);

    // Atualiza ou cria remetente
    Client* sender;
    if (!client_map.contains(event.getSender())) {
        sender = new Client(event.getSender());
        client_map.insert(event.getSender(), sender);
    } else {
        sender = *client_map.getValue(event.getSender());
    }
    sender->addPack(new_pack);

    // Atualiza ou cria destinatário
    Client* recipient;
    if (!client_map.contains(event.getRecipient())) {
        recipient = new Client(event.getRecipient());
        client_map.insert(event.getRecipient(), recipient);
    } else {
        recipient = *client_map.getValue(event.getRecipient());
    }
    recipient->addPack(new_pack);
}

void System::processOtherPackEvent(Event& event, int index) {

    Package** pack = package_map.getValue(event.getPackId());
    (*pack)->addEvent(index);
}

void System::printEvent(Event& event) {
    printf("%07d EV %s %03d", event.getEventTime(), event.getEventType().c_str(), event.getPackId());

    // Imprime apenas as variáveis não nulas.
    if (event.getSender() != "") {
        printf(" %s %s", event.getSender().c_str(), event.getRecipient().c_str());
    }
    if (event.getOriginWarehouse() != -1) {
        printf(" %03d", event.getOriginWarehouse());
    }
    if (event.getDestinationWarehouse() != -1) {
        printf(" %03d", event.getDestinationWarehouse());
    }
    if (event.getNextWarehouse() != -1) {
        printf(" %03d", event.getNextWarehouse());
    }
    printf("\n");
}

