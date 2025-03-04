// 
// circularLinkedList.hpp
// Description: A circular linked list implementation
// Created: 3/3/2025
//

#pragma once

#ifndef CIRCULARLINKEDLIST_HPP
#define CIRCULARLINKEDLIST_HPP

#include "types.hpp"
#include <iostream>

/**
 * @brief A circular linked list implementation
 */
template <typename T>
class CircularLinkedList {
  private:
    struct Node { 
      T data; 
      Node* next; 
    };

    Node* head;
  
  public:
    CircularLinkedList() { head = nullptr; }
    ~CircularLinkedList() {
      if (head != nullptr) {
        Node* current = head; // Start at the head
        Node* nextNode; // The next node
        do {
            nextNode = current->next;
            delete current; // Delete the current node
            current = nextNode;
        } while (current != head); // Stop when you reach the head
        head = nullptr; // Set head to nullptr after deletion
      }

      delete head; // Delete the last node
    }

    // insertion member functions

    /**
     * @brief Insert a node at the end of the list
     * @param data The data to insert
     */
    void insertAtEnd(T data) {
      Node* newNode = new Node; // Create a new node
      newNode->data = data;
      newNode->next = head; // The last node points to the head

      if (head == nullptr) { // If the list is empty
        head = newNode;
        head->next = head;
      } else {
        Node* current = head; // Start at the head

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
    void insertAtFront(T data) {
      Node* newNode = new Node; // Create a new node
      newNode->data = data;
      newNode->next = head; // The new node points to the head

      if (head == nullptr) { // If the list is empty
        head = newNode;
        head->next = head;
      } else {
        Node* current = head; // Start at the head

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
    void insertAtPosition(T data, int position) {
      Node* newNode = new Node; // Create a new node
      newNode->data = data;

      if (position <= 1 || head == nullptr) {
        insertAtFront(data);
      } else {
        Node* current = head; // Start at the head
        
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
        Node* current = head; // Start at the head
        Node* previous = nullptr;

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
        Node* current = head; // Start at the head

        while (current->next != head) { // Find the last node
          current = current->next;
        }
        Node* currentHead = head;
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
        Node* current = head;

        for (int i = 1;
          i < position - 1 && current->next != head; // If you've reached the position or the end of the list
          i++) { // Find the node before the position
          current = current->next;
        }
        Node* nodeToDelete = current->next; // The node to delete
        current->next = nodeToDelete->next; // The current node points to the next node
        delete nodeToDelete; // Delete the node
      }
    }

    /**
     * @brief Delete a node with a specific value in the list
     * @param data The data to delete
     */
    void deleteByValue(T data) {
      if (head == nullptr) return; // If the list is empty
      if (head->data == data) {
        deleteAtFront();
      } else {
        Node* current = head;
        Node* previous = nullptr;

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
      if (head == nullptr) return;
      Node* current = head; // Start at the head

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
    bool search(T data) {
      if (head == nullptr) return false;
      Node* current = head; // Start at the head

      do {
        if (current->data == data) return true;
        current = current->next;
      } while (current != head);
      return false;
    }
};

#endif // CIRCULARLINKEDLIST_HPP