/** @file */
#ifndef SEM_3_PROJECT_LINKED_LIST_H
#define SEM_3_PROJECT_LINKED_LIST_H
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
/**
 *  @brief A template List class.
 *  It takes T type data. It has a structure Node which contains object of that class. The class includes also shared pointers to the first and the last element of the list and integer value representing size.
 */
template <typename T>
class List {
public:
/**
 *  @brief A node structure.
 *  Structure responsible for objects of class List. It has data stored inside and points to both previous and next node with respectively weak and shared pointers.
 */
    struct Node {
        T element_content;
        std::shared_ptr<Node> next;
        std::weak_ptr<Node> previous;
/** @brief A one argument node constructor.
 * Creates an object with content being the input value and sets value of the pointer to the next object as null pointer.
 * @param value Content of the new node.
 */
        Node(T value) : element_content(value), next(nullptr) {};
    };

    int size = 0;
    std::shared_ptr<Node> head = nullptr;
    std::shared_ptr<Node> tail = nullptr;

/** @brief A one argument list constructor.
 * Creates an object with content being the input value while allocating the memory for it. Sets value of the pointer to the next object as null pointer.
 * @param node_content Content of the new node.
 */
    List(T node_content) {
        head = std::make_shared<Node>(node_content);
        this->head->next = nullptr;
    }
/** @brief Default constructor.
 * Creates an object of class list.
 */
    List() {};

//copy constructor
/** @brief Copy constructor.
 * Creates an object of class list by copying elements from a list provided.
 * @param node1 The list that is being copied.
 */
    List(const List &node1) {
        auto current_head = node1.head;
        if (current_head == nullptr)
            return;

        head = std::make_shared<Node>(current_head->element_content);
        auto current = head;
        current_head = current_head->next;
        size = node1.size;
        while (current_head != nullptr) {
            current->
                    next = std::make_shared<Node>(current_head->element_content);
            current->next->
                    previous = current;

            current = current->next;
            current_head = current_head->next;

        }
    }
/** @brief Moves constructor.
 * Creates an object of class list by moving elements from a list provided.
 * @param node1 The list that is being moved.
 */
//move constructor
    List(List &&node1) {
        size = node1.size;
        head = std::move(node1.head);
        tail = std::move(node1.tail);
        node1.size = 0;
    }
    /**
     * @brief Copy assignment operator overloading.
     * @param node1 Another List object that is being copied.
     * @return The reference to the current List object.
     */
    //assignment operator
    List &operator=(List &node1) {
        head.reset();
        tail.reset();
        auto current_head = node1.head;
        if (current_head != nullptr) {
            head = std::make_shared<Node>(current_head->element_content);
            auto current = head;
            current_head = current_head->next;

            while (current_head != nullptr) {
                current->next = std::make_shared<Node>(current_head->element_content);
                current->next->previous = current;

                current = current->next;
                current_head = current_head->next;
            }
        }
        size = node1.size;
        return *this;
    }
    /**
     * @brief Move assignment operator overloading.
     * @param obj1 Another List object about to be moved.
     * @return The reference to the current List object.
     */
    //move operator
    List &operator=(List &&obj1)
    noexcept {
        head = std::move(obj1.head);
        size = obj1.size;
        obj1.size = 0;
        tail = std::move(obj1.tail);
        return *this;
    }

//adding an element after an element
    /**
     * @brief Insert method.
     * A method that adds another node element to the list after a certain node.
     * @param previous_node The node after which a new one is inserted.
     * @param new_content The data stored inside the just inserted node.
     */
    void add_element(std::shared_ptr<Node> previous_node, T new_content) {
        if (previous_node == nullptr) {
            std::cout << "Previous node cannot be null" << std::endl;
        }
        if (previous_node->next != nullptr) {
            auto copy_node = previous_node->next;
            previous_node->next = std::make_shared<Node>(new_content);
            previous_node->next->previous = previous_node;
            previous_node->next->next = copy_node;
            copy_node->previous = previous_node->next;
        } else {
            previous_node->next = std::make_shared<Node>(new_content);
            previous_node->next->previous = previous_node;
            tail = previous_node->next;
        }
        size = size + 1;
    }
    /**
     * @brief Pushback.
     * A method that adds another element at the end of the list.
     * @param new_content The data stored in element that is being added.
     */
    void pushback(T new_content) {
        auto current = head;
        if (current == nullptr) {
            head = std::make_shared<Node>(new_content);
            size = size + 1;
        } else {
            while (current != nullptr) {
                if (current->next == nullptr) {
                    current->next = std::make_shared<Node>(new_content);
                    current->next->previous = current;
                    tail = current;
                    size++;
                    return;
                }
                current = current->next;
            }
        }
    }

//searching for an element
    /**
     * @brief Searching.
     * A method that searches through the list in order to find a certain value. When it is found the method returns 1, otherwise it returns 0.
     * @param search_node The content of the node that is searched for inside the list.
     * @return Boolean value, true if the value is found, 0 otherwise.
     */
    bool search(T search_node) {
        auto current = head;
        while (current->next != nullptr) {
            if (current->element_content == search_node) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

//sorting
    /**
     * @brief Sorting.
     * A method that sorts the list using bubble sort.
     */
    void sort() {
        auto current = head;
        auto last = tail;
        if (head == NULL) {
            std::cout << "Cannot sort an empty list" << std::endl;
        }
        for (int i = 0; i < size; i++) {
            current = head;
            while (current->next != last) {
                if (current->element_content > current->next->element_content) {
                    current->next->previous = current->previous;
                    if (current != head)
                        current->previous.lock()->next = current->next;
                    if (current->next->next) {
                        current->next->next->previous = current;
                    }

                    std::shared_ptr<Node> tmp = current->next;
                    current->previous = current->next;
                    current->next = current->next->next;
                    current->previous.lock()->next = current;
                    if (current == head) {
                        head = current->previous.lock();
                    }
                } else {
                    current = current->next;
                }
            }
        }
    }

//display
    /**
     * @brief Display.
     * A method that displays content of each node and content of the nodes it is pointing at.
     */
    void display() {
        auto cur = head;
        while (cur != nullptr) {
            std::cout << cur->element_content << std::endl;
            if (cur->next != nullptr) {
                std::cout << "Next:   " << cur->next->element_content << std::endl;
            } else { std::cout << "next is nullptr" << std::endl; }
            if (cur->previous.lock() != nullptr) {
                std::cout << "Previous:   " << cur->previous.lock()->element_content << std::endl;
            } else { std::cout << "previous is nullptr" << std::endl; }
            cur = cur->next;
        }
    }
    /**
     * @brief Display values.
     * A method that displays lists as only the content of certain nodes.
     */
    void display_val() {
        auto cur = head;
        while (cur != nullptr) {
            std::cout << cur->element_content << std::endl;
            cur = cur->next;
        }
    }

//serialization
    /**
     * @brief Serialization.
     * A method that serializes the whole list. It takes the content of all nodes into stringstream and writes it into the provided file.
     * @param file_name The name/path to the file the serialized content will be written to.
     */
    void serialization(const std::string &file_name) {

        std::ofstream out_file(file_name, std::ios::out | std::ios::trunc);
        if (out_file) {
            std::string content;
            auto node_1 = head;
            while (node_1 != nullptr) {
                std::stringstream ss;
                if (node_1->next != nullptr) {
                    ss << node_1->element_content;
                    out_file << ss.str() << std::endl;
                    node_1 = node_1->next;
                }
                else {
                    ss << node_1->element_content;
                    out_file << ss.str();
                    node_1 = node_1->next;
                }
            }
            out_file.close();
        }
    }
//deserialization
    /**
     * @brief Deserialization.
     * A method that deserializes the whole list. From the file provided it takes the content line by line and then inserts each one to a list using method pushback.
     * @param file_name The name/path to the file which stores the content about to be inserted to the list.
     */
    void deserialization(const std::string &file_name) {
        std::ifstream input_file(file_name, std::ios::in);
        if (input_file) {
            while (input_file.eof() == 0) {
                std::stringstream ss;
                T temp;
                std::string in_data;
                std::getline(input_file, in_data);
                ss << in_data;
                ss >> temp;
                pushback(temp);
            }
            input_file.close();
        }
    }
};

#endif //SEM_3_PROJECT_LINKED_LIST_H
