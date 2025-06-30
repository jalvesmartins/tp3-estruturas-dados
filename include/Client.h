#pragma once

#include <string>
#include "./List.h"

class Client {
    private:
        std::string name;
        List<Package*> client_pack_list; // Lista que contém ponteiros dos pacotes que envolvem o cliente.

    public:
        // Construtor padrão.
        Client() : name("undefined_client"), client_pack_list() {}

        // Construtor completo.
        Client(std::string& name) : name(name), client_pack_list() {}

        // Destrutor.
        ~Client() = default;

        // Getters
        std::string getName() const;
        const List<Package*>& getPacks() const;

        // Adiciona um pacote ao cliente.
        void addPack(Package* pack);

        // Retorna uma lista com todos os índices de eventos;
        List<int> getClientEvents();
};