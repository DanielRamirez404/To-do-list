#ifndef LINKED_LIST
#define LINKED_LIST
#include <cstddef>  //for size_t
#include <cassert>  //for assert()

template <typename T> class node {
public:
  T value{};
  node* previousNode{};
  node* nextNode{};
  node(T initializationValue);
};

template <typename T> node<T>::node(T initializationValue) { value = initializationValue; }


template <typename T> class linkedList {
private:
  size_t size{0};
  node<T>* head{NULL};
  node<T>* tail{NULL};
  node<T>* iterator{NULL};
public:
  void addFirstValue(T value);
  void append(T value);
  void preppend(T value);
  node<T>* iterate();
  T getIteratorValue() { return iterator->value; };
  T& operator[](size_t index);
  void resetIterator() { iterator = NULL; };
  size_t getSize() { return size; };
};

template <typename T> void linkedList<T>::addFirstValue(T value) {
  head = new node<T>(value);
  tail = head;
}

template <typename T> void linkedList<T>::append(T value) {
  if (size == 0) {
    addFirstValue(value);
  } else {
    tail->nextNode = new node<T>(value);
    tail->nextNode->previousNode = tail;
    tail = tail->nextNode;
  }
  size++;
}

template <typename T> void linkedList<T>::preppend(T value) {
  if (size == 0) {
    addFirstValue(value);
  } else {
    head->previousNode = new node<T>(value);
    head->previousNode->nextNode = head;
    head = head->previousNode;
  }
  size++;
}

template <typename T> node<T>* linkedList<T>::iterate() {
  iterator = (iterator == NULL) ? head : iterator->nextNode;
  return iterator;
}

template <typename T> T& linkedList<T>::operator[](size_t index) {
  assert(index < size);
  size_t i{0};
  node<T>* requestedNode{};
  while (iterate() != NULL) {
    if (i == index) {
      requestedNode = iterator;
      break;
    } else {
      i++;
    }
  };
  resetIterator();
  return requestedNode->value;
}

#endif
