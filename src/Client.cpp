#include "../include/Client.h"
#include "../include/List.h"

std::string Client::getName() const {
    return this->name;
}

const List<PackageStatus>& Client::getPacks() const {
    return this->client_pack_list;
}

void Client::addPack(int pack_id, int registration) {
    List<PackageStatus>::L_Node* current = this->client_pack_list.getHead();
    PackageStatus pack = PackageStatus(pack_id, registration);
    this->client_pack_list.pushBack(pack);
}

void Client::updatePack(int pack_id, int new_index) {
    List<PackageStatus>::L_Node* current = this->client_pack_list.getHead();

    // Verifica se o pacote já esta na lista.
    while (current != nullptr) {
        if (current->data.pack_id == pack_id) {
            break;
        }
        current = current->next;
    }

    if (current == nullptr) {
        std::cout << "ERRO: PACK INEXISTENTE\n";
        exit(1);
    }

    current->data.current_index = new_index;
}

List<int> Client::getClientEvents() {
    List<int> events;

    List<PackageStatus>::L_Node* current = this->client_pack_list.getHead();

    // Verifica se o pacote já esta na lista.
    while (current != nullptr) {
        events.insertSorted(current->data.registration_index);

        current = current->next;
    }

    current = this->client_pack_list.getHead();

    while (current != nullptr) {
        if (current->data.current_index != current->data.registration_index) {
            events.insertSorted(current->data.current_index);
        }
    }

    return events;
}