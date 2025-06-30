#pragma once

#include <functional>
#include <stdexcept>

// Estrutura de um nó na lista encadeada de um bucket.
template <typename Key, typename Value>
struct Node {
    Key key;
    Value value;
    Node* next;

    Node(const Key& key, const Value& value) : key(key), value(value), next(nullptr) {}
};

// Mapa de hash genérico com encadeamento separado.
template <typename Key, typename Value>
class HashMap {
    private:
        static const int DEFAULT_CAPACITY = 16;
        static constexpr float DEFAULT_LOAD_FACTOR = 0.75f;

        Node<Key, Value>** table;     // Ponteiro para o array de buckets.
        int capacity;                // Número de buckets.
        int count;                   // Número de elementos armazenados.
        float max_load_factor;       // Taxa máxima de ocupação do bucket.
        
    public:
        // Construtor padrão.
        HashMap() {
            capacity = DEFAULT_CAPACITY;
            count = 0;
            max_load_factor = DEFAULT_LOAD_FACTOR;

            // Inicializa todos os elementos com nullptr.
            table = new Node<Key, Value>*[capacity];
            for (int i = 0; i < capacity; i++) {
                table[i] = nullptr;
            }
        }

        // Construtor com capacidade inicial personalizada.
        HashMap(int initial_capacity) {
            capacity = initial_capacity;
            count = 0;
            max_load_factor = DEFAULT_LOAD_FACTOR;

            table = new Node<Key, Value>*[capacity];
            for (int i = 0; i < capacity; i++) {
                table[i] = nullptr;
            }
        }

        // Destrutor.
        ~HashMap() {
            clearTable();
            delete[] table;
        }

        std::hash<Key> hash_function;

        // Calcula o índice de bucket usando std::hash.
        int getBucketIndex(const Key& key) const {
            return hash_function(key) % capacity;
        }

        // Reorganiza a tabela se o fator de carga for excedido.
        void rehash() {
            int old_capacity = capacity;
            capacity *= 2;

            Node<Key, Value>** old_table = table;
            table = new Node<Key, Value>*[capacity];
            for (int i = 0; i < capacity; i++) {
                table[i] = nullptr;
            }

            count = 0;
            for (int i = 0; i < old_capacity; i++) {
                Node<Key, Value>* node = old_table[i];
                while (node != nullptr) {
                    insert(node->key, node->value);  // reusa insert para reinsere
                    Node<Key, Value>* temp = node;
                    node = node->next;
                    delete temp;
                }
            }

            delete[] old_table;
        }

        // Libera toda a memória alocada.
        void clearTable() {
            for (int i = 0; i < capacity; i++) {
                Node<Key, Value>* node = table[i];
                while (node != nullptr) {
                    Node<Key, Value>* temp = node;
                    node = node->next;
                    delete temp;
                }
                table[i] = nullptr;
            }
            count = 0;
        }

        // Insere ou atualiza um par (chave, valor).
        void insert(const Key& key, const Value& value) {
            int index = getBucketIndex(key);
            Node<Key, Value>* node = table[index];

            while (node != nullptr) {
                if (node->key == key) {
                    node->value = value;  // Atualiza
                    return;
                }
                node = node->next;
            }

            // Insere no início da lista
            Node<Key, Value>* new_node = new Node<Key, Value>(key, value);
            new_node->next = table[index];
            table[index] = new_node;
            count++;

            if ((float)count / capacity > max_load_factor) {
                rehash();
            }
        }

        // Acessa o valor de uma chave (exceção se não existir).
        Value* getValue(const Key& key) {
            int index = getBucketIndex(key);
            Node<Key, Value>* node = table[index];

            while (node != nullptr) {
                if (node->key == key) {
                    return node->value;
                }
                node = node->next;
            }
            
            std::cout << "ERRO: Valor não encontrado no hash";
            return nullptr;
        }

        // Verifica se a chave está presente.
        bool contains(const Key& key) const {
            int index = getBucketIndex(key);
            Node<Key, Value>* node = table[index];

            while (node != nullptr) {
                if (node->key == key) return true;
                node = node->next;
            }

            return false;
        }

        // Retorna o número de elementos.
        int getSize() const {
            return count;
        }

        // Verifica se está vazio.
        bool isEmpty() const {
            return count == 0;
        }
};
