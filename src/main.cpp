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

    // Começa o loop de eventos, faz a leitura até que acabem os eventos.
    while (inputFile >> event_time) {
        std::string query_type_string;  // Tipo do evento em string, para leitura.
        query_type query;                   // Tipo de consulta.

        // Faz a leitura do tipo da consulta.
        inputFile >> query_type_string;

        if (query_type_string == "EV") query = EV;
        else if (query_type_string == "CL") query = CL;
        else if (query_type_string == "PC") query = PC;
        
        switch (query) {

        case EV: {
            std::string event_type;
            int pack_id = -1;
            std::string sender, recipient;
            int origin_warehouse = -1;
            int destination_warehouse = -1;
            int next_warehouse = -1;

            // Faz a leitura do tipo do evento.
            inputFile >> event_type;

            if (event_type == "RG") {
                inputFile >> pack_id >> sender >> recipient >> origin_warehouse >> destination_warehouse;
                Event event(event_time, "RG", pack_id, sender, recipient, origin_warehouse, destination_warehouse, -1);
                system.getEvents()[event_count] = event;
                system.processRG(event, event_count);
                event_count++;

            } else if (event_type == "EN") {
                inputFile >> pack_id >> destination_warehouse;
                Event event(event_time, "EN", pack_id, "", "", -1, destination_warehouse, -1);
                system.getEvents()[event_count] = event;
                system.processOtherPackEvent(event, event_count);
                event_count++;

            } else if (event_type == "AR" || event_type == "RM" || event_type == "UR" || event_type == "TR") {
                inputFile >> pack_id >> destination_warehouse >> next_warehouse;
                Event event(event_time, event_type, pack_id, "", "", -1, destination_warehouse, next_warehouse);
                system.getEvents()[event_count] = event;
                system.processOtherPackEvent(event, event_count);
                event_count++;
            }

            break;
        }

        case PC: {
            int pack_id = -1;   // id do pacote.

            // Encontra o pacote lido.
            inputFile >> pack_id;
            Package** pack = system.getPackageHash().getValue(pack_id);
            
            List<int> event_list = (**pack).getEvents();

            printf("%06d PC %03d\n%d\n", event_time, pack_id, event_list.getSize());

            while (!event_list.isEmpty()) {
                system.printEvent(system.getEvents()[event_list.popFront()]);
            }

            event_count++;

            break;
        }

        case CL: {
            // Encontra o cliente lido.
            std::string client_name;
            inputFile >> client_name;
            Client** client = system.getClientHash().getValue(client_name);

            if (client == nullptr || *client == nullptr) {
                printf("%06d CL %s\n0\n", event_time, client_name.c_str());
                event_count++;
                break;
            } else {
            
            List<int> event_list = (**client).getClientEvents();

            printf("%06d CL %s\n%d\n", event_time, client_name.c_str(), event_list.getSize());

            while (!event_list.isEmpty()) {
                system.printEvent(system.getEvents()[event_list.popFront()]);
            }

            event_count++;
            }

            break;
        }

        default:
            break;
        }
    }

return 0;
}