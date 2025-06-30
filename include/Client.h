#pragma once

#include <string>
#include "./List.h"

class Client {
    private:
        std::string name;
        List<int> client_pack_list; // Lista que contém os ids dos pacotes ligados ao cliente.

    public:
        // Construtor padrão.
        Client() : name("undefined_client"), client_pack_list() {}

        // Construtor completo.
        Client(std::string& name) : name(name), client_pack_list() {}

        // Destrutor.
        ~Client() = default;

        // Getters
        std::string getName() const;
        const List<int>& getPacks() const;

        // Adiciona um pacote ao cliente.
        void addPack(int pack_id);
};