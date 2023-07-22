#ifndef LINKED_LIST
#define LINKED_LIST
#include <cstddef>  //for size_t
#include <cassert>  //for assert()

template <typename T> class node {
public:
  T value{};
  node* previousNode{};
  node* nextNode{};
  node(T initializationValue) { value = initializationValue; };
};

template <typename T> class linkedList {
private:
  size_t size{0};
  node<T>* head{NULL};
  node<T>* tail{NULL};
  node<T>* iterator{NULL};
  void addFirstValue(T value);
  void addInBetweenValue(size_t index, T value);
public:
  T& operator[](size_t index);
  void append(T value);
  void preppend(T value);
  void addValueByIndex(size_t index, T value);
  void changeValueIndex(size_t oldIndex, size_t newIndex);
  void clear();
  node<T>* iterate();
  T getIteratorValue() { return iterator->value; };
  void resetIterator() { iterator = NULL; };
  T getHeadValue() { return head->value; };
  T getTailValue() { return tail->value; };
  size_t getSize() { return size; };
  bool isEmpty() { return (size == 0) ? true : false; };
};

template <typename T> void linkedList<T>::addFirstValue(T value) {
  head = new node<T>(value);
  tail = head;
}

template <typename T> void linkedList<T>::append(T value) {
  if (isEmpty()) {
    addFirstValue(value);
  } else {
    tail->nextNode = new node<T>(value);
    tail->nextNode->previousNode = tail;
    tail = tail->nextNode;
  }
  ++size;
}

template <typename T> void linkedList<T>::preppend(T value) {
  if (isEmpty()) {
    addFirstValue(value);
  } else {
    head->previousNode = new node<T>(value);
    head->previousNode->nextNode = head;
    head = head->previousNode;
  }
  ++size;
}

template <typename T> void linkedList<T>::addValueByIndex(size_t index, T value) {  //will be added as if it were an array index
  assert(index <= size);
  if (index == 0) {
    preppend(value);
  } else if (index == size) {
    append(value);
  } else {
    addInBetweenValue(index, value);
  }
}

template <typename T> void linkedList<T>::changeValueIndex(size_t oldIndex, size_t newIndex) {
  assert((oldIndex < size) && (newIndex < size) && (oldIndex != newIndex));
  size_t i{0};
  node<T>* selectedNode{NULL};
  while (iterate() != NULL) {
    if (i == oldIndex) {
      selectedNode = iterator;
      selectedNode->previousNode->nextNode = selectedNode->nextNode;
      selectedNode->nextNode->previousNode = selectedNode->previousNode;
      break;
    } else {
      ++i;
    }
  }
  resetIterator();
  i=0;
  while (iterate() != NULL) {
    if (i == newIndex - 1) {
      selectedNode->previousNode = iterator;
      selectedNode->nextNode = iterator->nextNode;
      selectedNode->previousNode->nextNode = selectedNode;
      selectedNode->nextNode->previousNode = selectedNode;
      break;
    } else {
      ++i;
    }
  }
  resetIterator();
}

template <typename T> void linkedList<T>::addInBetweenValue(size_t index, T value) {
  size_t i{0};
  node<T>* newNode{new node<T>(value)};
  while (iterate() != NULL) {
    if (i == index - 1) {
      newNode->previousNode = iterator;
      newNode->nextNode = iterator->nextNode;
      newNode->previousNode->nextNode = newNode;
      newNode->nextNode->previousNode = newNode;
      ++size;
      break;
    } else {
      ++i;
    }  
  }
  resetIterator();
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
      ++i;
    }
  };
  resetIterator();
  return requestedNode->value;
}

#endif
