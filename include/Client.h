#pragma once

#include <string>
#include "./List.h"

// Estrutura que armazena os ids e índices dos eventos do pacote.
struct PackageStatus {
    int pack_id;
    int registration_index;
    int current_index;

    PackageStatus(int pack_id, int registration) : pack_id(pack_id), registration_index(registration), current_index(registration) {}
};

class Client {
    private:
        std::string name;
        List<PackageStatus> client_pack_list; // Lista que contém as informações dos pacotes que envolvem o cliente.

    public:
        // Construtor padrão.
        Client() : name("undefined_client"), client_pack_list() {}

        // Construtor completo.
        Client(std::string& name) : name(name), client_pack_list() {}

        // Destrutor.
        ~Client() = default;

        // Getters
        std::string getName() const;
        const List<PackageStatus>& getPacks() const;

        // Adiciona um pacote ao cliente.
        void addPack(int pack_id, int registration);

        // Atualiza o index do último evento de um pacote.
        void updatePack(int pack_id, int registration);
};