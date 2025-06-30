#pragma once

#include <iostream>

// Lista encadeada usando template.
template<typename T>
class List {
    private:
        // Nó da lista.
        struct L_Node {
            T data; // Dado em si.
            L_Node* next; // Ponteiro para o próximo nó.
            L_Node(T& data_ref) : data(data_ref), next(nullptr) {} // Construtor.
        };

        L_Node* head; // Nó "cabeça" da lista.
        L_Node* tail; // Nó "rabo" da lista.
        int size;     // Tamanho da lista.

    public:
        // Construtor padrão
        List() : head(nullptr), tail(nullptr) {}

        // Destrutor.
        ~List() { 
            while (!isEmpty()) {
                popFront();
            }
        }

        // Construtor de cópia.
        List(const List<T>& other) {
            // Inicializa a lista como vazia.
            head = nullptr;
            tail = nullptr;
            size = 0;

            // Criamos um ponteiro temporário para percorrer a lista 'other'
            L_Node* current_other = other.head;

            // Percorremos a lista 'other' do início ao fim.
            while (current_other != nullptr) {
                // Para cada nó na lista original, pegamos seu dado e o adicionamos ao final da *nossa* nova lista.
                this->pushBack(current_other->data);

                // Avançamos para o próximo nó na lista original.
                current_other = current_other->next;
            }
        }

        // Adiciona um nó na frente da lista.
        void pushFront(T& data) {
            L_Node* new_node = new L_Node(data);
            if (isEmpty()) {
                head = new_node;
                tail = new_node;
            } else {
                new_node->next = head;
                head = new_node;
            }
            this->size++;
        }

        // Adiciona um nó ao fim da lista.
        void pushBack(T& data) {
            L_Node* new_node = new L_Node(data);

            if (isEmpty()) {
                head = new_node;
                tail = new_node;

            } else {
                tail->next = new_node;
                tail = new_node;
            }

            this->size++;
        }

        // Retira um nó do início da lista.
        T popFront() {
            if (isEmpty()) {
                std::cerr << "ERRO: Tentativa de pop_front() em uma lista vazia." << std::endl;
                exit(1);
            }

            L_Node* temp_node = head;
            T value = head->data;

            if (head == tail) {
                head = nullptr;
                tail = nullptr;

            } else {
                head = head->next;
            }

            delete temp_node;
            this->size--;
            return value;
        }

        // Retira um nó do fim da lista.
        T popBack() {
            if (isEmpty()) {
                std::cerr << "ERRO: Tentativa de pop_back() em uma lista vazia." << std::endl;
                exit(1);
            }

            L_Node* temp_node = tail;
            T value = tail->data;

            if (head == tail) {
                head = nullptr;
                tail = nullptr;

            } else {
                L_Node* current = head;

                while (current->next != tail) {
                    current = current->next;
                }

                tail = current;
                tail->next = nullptr;
            }

            delete temp_node;
            this->size--;
            return value;
        }

        // Retorna o endereço do primeiro elemento.
        T& front() {
            if (isEmpty()) {
                std::cerr << "ERRO: Tentativa de front() em uma lista vazia." << std::endl;
                exit(1);
            }
            return head->data;
        }

        // Retorna o endereço do último elemento.
        T& back() {
            if (isEmpty()) {
                std::cerr << "ERRO: Tentativa de back() em uma lista vazia." << std::endl;
                exit(1);
            }
            return tail->data;
        }

        L_Node* getHead() {
            return this->head;
        }

        // Retorna o load do primeiro elemento.
        T& getFrontData() {
            if (isEmpty()) {
                std::cerr << "ERRO: Tentativa de getFrontData() em uma lista vazia." << std::endl;
                exit(1);
            }
            return this->head->data;
        }

        // Verifica se a lista está vazia.
        bool isEmpty() const {
            return head == nullptr;
        }

        // Overload do operador =. Copia uma lista para a outra.
        List<T>& operator=(const List<T>& other) {
            // Proteção contra auto-atribuição.
            if (this == &other) {
                return *this;
            }

            // Limpa a lista atual para não vazar memória
            while (!isEmpty()) {
                popFront();
            }

            // Copia os elementos da outra lista (mesma lógica do construtor de cópia)
            L_Node* current_other = other.head;
            while (current_other != nullptr) {
                this->pushBack(current_other->data);
                current_other = current_other->next;
            }

            return *this;
        }
};