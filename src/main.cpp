#include "../include/System.h"

#include <fstream>
#include <iostream>

enum query_type {
    EV,
    CL,
    PC
};

int main (int argc, char* argv[]) {
    // Verificação de segurança.
    if (argc < 2) {
        std::cerr << "ERRO: Nome do arquivo deve ser passado na execução" << std::endl;
        return 1;
    }

    // Cria um stream de entrada a partir do arquivo
    std::ifstream inputFile(argv[1]);

    // Verifica se o arquivo foi aberto com sucesso
    if (!inputFile.is_open()) {
        std::cerr << "ERRO: Não foi possível abrir o arquivo." << std::endl;
        return 1;
    }

    // Cria o sistema.
    System system;

    int event_count = 0;                // Índice do evento.
    int event_time = -1;                // Tempo do evento
    std::string query_type_string;      // Tipo do evento em string, para leitura.
    query_type query;                   // Tipo de consulta.
    std::string event_type;             // Tipo de evento em string, para leitura.
    int pack_id = -1;                   // id do pacote.
    std::string sender;                 // Remetente.
    std::string recipient;              // Destinatário.
    int origin_warehouse = -1;          // Armazém de destino
    int destination_warehouse = -1;     // Armazém de origem.
    int next_warehouse = -1;            // Próxima sessão.

    // Começa o loop de eventos, faz a leitura até que acabem os eventos.
    while (inputFile >> event_time) {

        // Faz a leitura do tipo da consulta.
        inputFile >> query_type_string;

        if (query_type_string == "EV") query = EV;
        else if (query_type_string == "CL") query = CL;
        else if (query_type_string == "PC") query = PC;
        
        switch (query) {

        case EV: {
            
            inputFile >> event_type;

            if (event_type == "RG") {
                // Faz a leitura dos outros atributos.
                inputFile >> pack_id >> sender >> recipient >> origin_warehouse >> destination_warehouse;
                
                // Adiciona o evento na base de dados.
                Event event(event_time, "RG", pack_id, sender, recipient, origin_warehouse, destination_warehouse, -1);
                system.getEvents()[event_count] = event;

                // Processa o evento.
                system.processRG(event, event_count);

            } else if (event_type == "AR") {
                // Faz a leitura dos outros atributos.
                inputFile >> pack_id >> destination_warehouse >> next_warehouse;

                // Adiciona o evento na base de dados.
                Event event(event_time, "AR", pack_id, "", "", -1, destination_warehouse, next_warehouse);
                system.getEvents()[event_count] = event;
                
                // Processa o evento.
                system.processOtherPackEvent(event, event_count);

            } else if (event_type == "RM") {
                // Faz a leitura dos outros atributos.
                inputFile >> pack_id >> destination_warehouse >> next_warehouse;

                // Adiciona o evento na base de dados.
                Event event(event_time, "RM", pack_id, "", "", -1, destination_warehouse, next_warehouse);
                system.getEvents()[event_count] = event;
                
                // Processa o evento.
                system.processOtherPackEvent(event, event_count);
                
            } else if (event_type == "UM") {
                // Faz a leitura dos outros atributos.
                inputFile >> pack_id >> destination_warehouse >> next_warehouse;

                // Adiciona o evento na base de dados.
                Event event(event_time, "UM", pack_id, "", "", -1, destination_warehouse, next_warehouse);
                system.getEvents()[event_count] = event;
                
                // Processa o evento.
                system.processOtherPackEvent(event, event_count);

            } else if (event_type == "TR") {
                // Faz a leitura dos outros atributos.
                inputFile >> pack_id >> destination_warehouse >> next_warehouse;

                // Adiciona o evento na base de dados.
                Event event(event_time, "UM", pack_id, "", "", -1, destination_warehouse, next_warehouse);
                system.getEvents()[event_count] = event;
                
                // Processa o evento.
                system.processOtherPackEvent(event, event_count);

            } else if (event_type == "EN") {
                // Faz a leitura dos outros atributos.
                inputFile >> pack_id >> destination_warehouse;

                // Adiciona o evento na base de dados.
                Event event(event_time, "EN", pack_id, "", "", -1, destination_warehouse, -1);
                system.getEvents()[event_count] = event;
                
                // Processa o evento.
                system.processOtherPackEvent(event, event_count);
            }

            event_count++;

            break;
        }

        case PC: {
            
            break;
        }


        default:
            break;
        }
    }

return 0;
}