//
// circular_linked_list.hpp
// Description: A circular linked list implementation
// Created: 3/3/2025
//

#pragma once

#include <concepts>
#include <iostream>

/**
 * @brief A concept defining a generic iterable container
 *
 * @tparam C 	The container type
 */
template<typename C>
concept __Container = requires(C container) {
	// All containers require certain type aliases to meet the Container named requirement
	typename C::value_type;
	typename C::reference;
	typename C::const_reference;
	typename C::allocator_type;
	typename C::iterator;
	typename C::const_iterator;
	typename C::difference_type;
	typename C::size_type;

	// All STL containers are iterable and wrap member functions which return certain
	// underlying types
	{ container.get_allocator() }	-> std::same_as<typename C::allocator_type>;
	{ container.begin() } 			-> std::same_as<typename C::iterator>;
	{ container.end() } 			-> std::same_as<typename C::iterator>;
	{ container.cbegin() } 			-> std::same_as<typename C::const_iterator>;
	{ container.cend() } 			-> std::same_as<typename C::const_iterator>;
};

/**
 * @brief A linked list node
 *
 * @tparam 	T 	The type of data stored in the node
 */
template<typename T>
struct Node {
	T data;
	Node* next;
};

/**
 * @brief A circular linked list implementation
 *
 * @tparam T 	The contianer's underlying type
 */
template <class T>
class CircularLinkedList {
	public:
		using value_type = T;
		using node_type  = Node<value_type>*;

	private:
		node_type head;

	public:
		CircularLinkedList():
			head(nullptr)
		{}

		template<__Container Container>
		explicit CircularLinkedList(const Container& container):
			CircularLinkedList()
		{
			for (const auto& value : container) {
				node_type current = head;
				int position = 1;

				if (current == nullptr) {
					insertAtEnd(value);
					continue;
				}

				do {
					if (value->priority <= current->data->priority) {
						break;
					}
					current = current->next;
					position++;
				} while (current != head);

				insertAtPosition(value, position);
			}
		}

		~CircularLinkedList() {
			if (head != nullptr) {
				node_type current = head; // Start at the head
				node_type nextNode; // The next node
				do {
					nextNode = current->next;
					delete current; // Delete the current node
					current = nextNode;
				} while (current != head); // Stop when you reach the head
				head = nullptr; // Set head to nullptr after deletion
			}

			delete head;
		}

		node_type getHead() const {
			return head;
		}

		bool isEmpty() const {
			return head == nullptr;
		}

		// insertion member functions

		/**
		 * @brief Insert a node at the end of the list
		 * @param data The data to insert
		 */
		void insertAtEnd(value_type data) {
			node_type newNode = new Node<T>; // Create a new node
			newNode->data = data;
			newNode->next = head; // The last node points to the head

			if (head == nullptr) { // If the list is empty
				head = newNode;
				head->next = head;
			} else {
				node_type current = head; // Start at the head

				while (current->next != head) { // Find the last node
					current = current->next;
				}
				current->next = newNode; // The last node points to the new node
				newNode->next = head; // The new node points to the head
			}
		}

		/**
		 * @brief Insert a node at the front of the list
		 * @param data The data to insert
		 */
		void insertAtFront(value_type data) {
			node_type newNode = new Node<T>; // Create a new node
			newNode->data = data;
			newNode->next = head; // The new node points to the head

			if (head == nullptr) { // If the list is empty
				head = newNode;
				head->next = head;
			} else {
				node_type current = head; // Start at the head

				while (current->next != head) { // Find the last node
					current = current->next;
				}
				current->next = newNode; // The last node points to the new node
				head = newNode; // The new node is the new head
			}
		}

		/**
		 * @brief Insert a node at a specific position in the list
		 * @param data The data to insert
		 * @param position The position to insert the data
		 */
		void insertAtPosition(value_type data, int position) {
			node_type newNode = new Node<T>; // Create a new node
			newNode->data = data;

			if (position <= 1 || head == nullptr) {
				insertAtFront(data);
			} else {
				node_type current = head; // Start at the head

				for (int i = 1;
						 i < position - 1 && current->next != head; // If you've reached the position or the end of the list
						 i++) { // Find the node before the position
					current = current->next;
				}
				newNode->next = current->next; // The new node points to the next node
				current->next = newNode; // The current node points to the new node
			}
		}

		// deletion member functions

		/**
		 * @brief Delete the last node in the list
		 */
		void deleteAtEnd() {
			if (head == nullptr) return; // If the list is empty
			if (head->next == head) { // If there is only one node
				delete head;
				head = nullptr;
			} else {
				node_type current = head; // Start at the head
				node_type previous = nullptr;

				while (current->next != head) { // Find the last node
					previous = current;
					current = current->next;
				}
				previous->next = head; // The previous node points to the head
				delete current; // Delete the last node
			}
		}

		/**
		 * @brief Delete the first node in the list
		 */
		void deleteAtFront() {
			if (head == nullptr) return; // If the list is empty
			if (head->next == nullptr) { // If there is only one node
				delete head;
				head = nullptr;
			} else {
				node_type current = head; // Start at the head

				while (current->next != head) { // Find the last node
					current = current->next;
				}
				node_type currentHead = head;
				current->next = head->next;
				head = head->next;
				delete currentHead; // Delete the head
			}
		}

		/**
		 * @brief Delete a node at a specific position in the list
		 * @param position The position to delete the node
		 */
		void deleteAtPosition(int position) {
			if (head == nullptr) return; // If the list is empty
			if (position <= 1) {
				deleteAtFront();
			} else {
				node_type current = head;

				for (int i = 1;
					i < position - 1 && current->next != head; // If you've reached the position or the end of the list
					i++) { // Find the node before the position
					current = current->next;
				}
				node_type nodeToDelete = current->next; // The node to delete
				current->next = nodeToDelete->next; // The current node points to the next node
				delete nodeToDelete; // Delete the node
			}
		}

		/**
		 * @brief Delete a node with a specific value in the list
		 * @param data The data to delete
		 */
		void deleteByValue(value_type data) {
			if (head == nullptr) return; // If the list is empty
			if (head->data == data) {
				deleteAtFront();
			} else {
				node_type current = head;
				node_type previous = nullptr;

				while (current->next != head && current->data != data) { // Find the node with the data
					previous = current;
					current = current->next;
				}
				if (current->data == data) { // If the node with the data is found
					previous->next = current->next;
					delete current; // Delete the node
				}
			}
		}

		// display and search member functions

		/**
		 * @brief Display the list
		 */
		void display() {
			if (head == nullptr || head->data == nullptr) return;
			node_type current = head; // Start at the head

			do {
				std::cout << current->data << " ";
				current = current->next;
			} while (current != head);
			std::cout << std::endl;
		}

		/**
		 * @brief Search for a node with a specific value in the list
		 * @param data The data to search
		 * @return true if the data is found, false otherwise
		 */
		bool search(value_type data) {
			if (head == nullptr) return false;
			node_type current = head; // Start at the head

			do {
				if (current->data == data) return true;
				current = current->next;
			} while (current != head);
			return false;
		}
};