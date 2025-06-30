#include "../include/Client.h"
#include "../include/List.h"

std::string Client::getName() const {
    return this->name;
}

const List<int>& Client::getPacks() const {
    return this->client_pack_list;
}

void Client::addPack(int pack_id) {
    List<int>::L_Node* current = this->client_pack_list.getHead();

    // Verifica se o pacote já esta na lista.
    while (current != nullptr) {
        if (current->data == pack_id) {
            return;
        }

        current = current->next;
    }

    this->client_pack_list.pushBack(pack_id);
}