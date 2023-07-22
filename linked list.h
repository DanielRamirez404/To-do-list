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
  void placeNodeInBetween(node<T>* newNode, node<T>* previousNode);
  void displaceNodeInBetween(node<T>* nodeToDisplace);
public:
  T& operator[](size_t index);
  void append(T value);
  void preppend(T value);
  void addValueByIndex(size_t index, T value);
  void moveNodeToHead(size_t index);      //Not implemented yet
  void moveNodeToTail(size_t index);      //Not implemented yet
  void changeNodeIndex(size_t oldIndex, size_t newIndex);
  void deleteHead();                      //Not implemented yet
  void deleteTail();                      //Not implemented yet
  void deleteNodeByIndex(size_t index);   //Not implemented yet
  void clearList();                       //Not implemented yet
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
    node<T>* newNode{new node<T>(value)};
    tail->nextNode = newNode;
    newNode->previousNode = tail;
    tail = newNode;
  }
  ++size;
}

template <typename T> void linkedList<T>::preppend(T value) {
  if (isEmpty()) {
    addFirstValue(value);
  } else {
    node<T>* newNode{new node<T>(value)};
    head->previousNode = newNode;
    newNode->nextNode = head;
    head = newNode;
  }
  ++size;
}

template <typename T> void linkedList<T>::addValueByIndex(size_t index, T value) {
  assert((index <= size) && "Index value isn\'t valid");
  if (index == 0) {
    preppend(value);
  } else if (index == size) {
    append(value);
  } else {
    addInBetweenValue(index, value);
  }
}

template <typename T> void linkedList<T>::addInBetweenValue(size_t index, T value) {
  for (size_t i{0}; iterate() != NULL; ++i) {
    if (i == index - 1) {
      placeNodeInBetween(new node<T>(value), iterator);
      break;
    }
  }
  resetIterator();
  ++size;
}

template <typename T> void linkedList<T>::placeNodeInBetween(node<T>* newNode, node<T>* priorNode) {
  newNode->previousNode = priorNode;
  newNode->nextNode = priorNode->nextNode;
  priorNode->nextNode->previousNode = newNode;
  priorNode->nextNode = newNode;
}

template <typename T> void linkedList<T>::displaceNodeInBetween(node<T>* nodeToDisplace) {
  nodeToDisplace->previousNode->nextNode = nodeToDisplace->nextNode;
  nodeToDisplace->nextNode->previousNode = nodeToDisplace->previousNode;
}

template <typename T> void linkedList<T>::changeNodeIndex(size_t oldIndex, size_t newIndex) {
  assert((oldIndex < size) && "Old index value is greater than the list\'s size");
  assert((newIndex < size) && "New index value is greater than the list\'s size");
  assert((oldIndex != newIndex) && "Both index values shouldn\'t be equal");
  node<T>* selectedNode{};
  for (size_t i{0}; iterate() != NULL; ++i) {
    if (i == oldIndex) {
      selectedNode = iterator;
      displaceNodeInBetween(selectedNode);
      break;
    }
  }
  resetIterator();
  for (size_t i{0}; iterate() != NULL; ++i) {
    if (i == newIndex - 1) {
      placeNodeInBetween(selectedNode, iterator);
      break;
    }
  }
  resetIterator();
}

template <typename T> node<T>* linkedList<T>::iterate() {
  iterator = (iterator == NULL) ? head : iterator->nextNode;
  return iterator;
}

template <typename T> T& linkedList<T>::operator[](size_t index) {
  assert((index < size) && "Index value isn\'t valid");
  size_t i{0};
  node<T>* requestedNode{};
  for (size_t i{0}; iterate() != NULL; ++i) {
    if (i == index) {
      requestedNode = iterator;
      break;
    }
  }
  resetIterator();
  return requestedNode->value;
}

#endif
