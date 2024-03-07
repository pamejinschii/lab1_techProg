#include <iostream>
#include <functional> // Для std::function -)

struct Node {
    int data;
    Node* next;

    Node(int data) : data(data), next(nullptr) {}
};

class LinkedList {
public:
    Node* head;

    LinkedList() : head(nullptr) {}

    // Добавление в начало 
    void addFirst(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    // Добавление в конец 
    void addLast(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // Добавление по индексу
    void addAt(int index, int value) {
        if (index == 0) {
            addFirst(value);
            return;
        }
        Node* newNode = new Node(value);
        Node* current = head;
        for (int i = 0; i < index - 1 && current != nullptr; ++i) {
            current = current->next;
        }
        if (current == nullptr) {
            std::cout << "Index out of bounds" << std::endl;
            delete newNode;
            return;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    // Удаление первого 
    void deleteFirst() {
        if (head == nullptr) return;
        Node* toDelete = head;
        head = head->next;
        delete toDelete;
    }

    // Удаление последнего 
    void deleteLast() {
        if (head == nullptr) return;
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return;
        }
        Node* current = head;
        while (current->next->next != nullptr) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }

    // Удаление по индексу
    void deleteAt(int index) {
        if (head == nullptr) return;
        if (index == 0) {
            deleteFirst();
            return;
        }
        Node* current = head;
        for (int i = 0; i < index - 1 && current->next != nullptr; ++i) {
            current = current->next;
        }
        if (current->next == nullptr) {
            std::cout << "индекс вышел за рамки!" << std::endl;
            return;
        }
        Node* toDelete = current->next;
        current->next = current->next->next;
        delete toDelete;
    }

    // Обновление значения по индексу
    void updateAt(int index, int newValue) {
        Node* current = head;
        for (int i = 0; i < index && current != nullptr; ++i) {
            current = current->next;
        }
        if (current == nullptr) {
            std::cout << "индекс вышел за рамки" << std::endl;
            return;
        }
        current->data = newValue;
    }

    // Поиск элемента по индексу
    Node* findAt(int index) {
        Node* current = head;
        for (int i = 0; i < index && current != nullptr; ++i) {
            current = current->next;
        }
        if (current == nullptr) {
            std::cout << "Index out of bounds" << std::endl;
            return nullptr;
        }
        return current;
    }

    // Поиск элемента по фильтру
    Node* findByFilter(const std::function<bool(int)>& filter) {
        Node* current = head;
        while (current != nullptr) {
            if (filter(current->data)) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
};

int main() {
    LinkedList list;
    // Пример 
    list.addLast(1);
    list.addLast(2);
    list.addFirst(0);
    list.addAt(2, 1); 
    list.updateAt(1, 4); // Обновить значение 
    list.deleteAt(2); // Удалить элемент по позиции

    // Поиск элемента по условию
    Node* found = list.findByFilter([](int value) { return value == 4; });
    if (found != nullptr) {
        std::cout << "Found: " << found->data << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    return 0;
}