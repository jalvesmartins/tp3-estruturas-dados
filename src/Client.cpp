#include "../include/Client.h"

std::string Client::getName() const {
    return this->name;
}

const List<int>& Client::getPacks() const {
    return this->client_pack_list;
}