#include "../include/Client.h"
#include "../include/List.h"
#include "../include/Package.h"

std::string Client::getName() const {
    return this->name;
}

const List<Package*>& Client::getPacks() const {
    return this->client_pack_list;
}

void Client::addPack(Package* pack) {
    this->client_pack_list.pushBack(pack);
}

// Retorna os eventos de um cliente de forma ordenada.
List<int> Client::getClientEvents() {
    List<int> events;

    List<Package*>::L_Node* current = this->client_pack_list.getHead();

    // Os dois loops são usados para evitar o pior caso de complexidade n², inserindo primeiro os índices menores, em O(1), e depois os maiores.
    while (current != nullptr) {
        events.insertSorted(current->data->getEvents().getFrontData()); 
        current = current->next;
    }

    current = this->client_pack_list.getHead();

    while (current != nullptr) {
        if (current->data->getEvents().getFrontData() != current->data->getEvents().getBackData()) {
            events.insertSorted(current->data->getEvents().getBackData());
        }
    }

    return events;
}