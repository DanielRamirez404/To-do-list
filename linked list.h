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
  void addInBetween(size_t index, T value);
  void placeNodeOnHead(node<T>* nodeToPlace);
  void placeNodeOnTail(node<T>* nodeToPlace);
  void placeNodeInBetween(node<T>* nodeToPlace, node<T>* previousNode);
  void displaceHead(node<T>* oldHead);
  void displaceTail(node<T>* oldTail);
  void displaceInBewtweenNode(node<T>* nodeToDisplace);
  void displaceNode(node<T>* nodeToDisplace, size_t index);
  void moveNodeInBewteen(size_t oldIndex, size_t newIndex);
  bool isAddedValueInBetween(size_t index) { return ((index != 0) && (index != size)); };
  bool isExistingValueInBetween(size_t index) { return ((index != 0) && (index != size - 1)); };
public:
  node<T>* operator[](size_t index);
  void preppend(T value);
  void append(T value);
  void addByIndex(size_t index, T value);
  void moveNodeToHead(size_t index);
  void moveNodeToTail(size_t index);
  void moveNode(size_t oldIndex, size_t newIndex);
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
  bool isEmpty() { return (size == 0); };
};

template <typename T> node<T>* linkedList<T>::operator[](size_t index) {
  assert((index < size) && "Index value isn\'t valid");
  node<T>* requestedNode{};
  for (size_t i{0}; iterate() != NULL; ++i) {
    if (i == index) {
      requestedNode = iterator;
      break;
    }
  }
  resetIterator();
  return requestedNode;
}

template <typename T> void linkedList<T>::addFirstValue(T value) {
  head = new node<T>(value);
  tail = head;
}

template <typename T> void linkedList<T>::preppend(T value) {
  (isEmpty()) ? addFirstValue(value) : placeNodeOnHead(new node<T>(value));
  ++size;
}

template <typename T> void linkedList<T>::append(T value) {
  (isEmpty()) ? addFirstValue(value) : placeNodeOnTail(new node<T>(value));
  ++size;
}

template <typename T> void linkedList<T>::addByIndex(size_t index, T value) {
  assert((index <= size) && "Index value is greater than the list\'s size");
  if (isAddedValueInBetween(index)) {
    addInBetween(index, value);
  } else {
    (index == 0) ? preppend(value) : append(value);
  }
}

template <typename T> void linkedList<T>::addInBetween(size_t index, T value) {
  for (size_t i{0}; iterate() != NULL; ++i) {
    if (i == index - 1) {
      placeNodeInBetween(new node<T>(value), iterator);
      break;
    }
  }
  resetIterator();
  ++size;
}

template <typename T> void linkedList<T>::placeNodeOnHead(node<T>* nodeToPlace) {
  head->previousNode = nodeToPlace;
  nodeToPlace->nextNode = head;
  head = nodeToPlace;
}

template <typename T> void linkedList<T>::placeNodeOnTail(node<T>* nodeToPlace) {
  tail->nextNode = nodeToPlace;
  nodeToPlace->previousNode = tail;
  tail = nodeToPlace;
}

template <typename T> void linkedList<T>::placeNodeInBetween(node<T>* nodeToPlace, node<T>* priorNode) {
  nodeToPlace->previousNode = priorNode;
  nodeToPlace->nextNode = priorNode->nextNode;
  priorNode->nextNode->previousNode = nodeToPlace;
  priorNode->nextNode = nodeToPlace;
}

template <typename T> void linkedList<T>::displaceNode(node<T>* nodeToDisplace, size_t index) {
  if (isExistingValueInBetween(index)) {
    displaceInBewtweenNode(nodeToDisplace);
  } else {
    (index == 0) ? displaceHead(nodeToDisplace) : displaceTail(nodeToDisplace);
  }
}

template <typename T> void linkedList<T>::displaceHead(node<T>* oldHead) {
  head = oldHead->nextNode;
  head->previousNode = NULL;
  oldHead->nextNode = NULL;
}

template <typename T> void linkedList<T>::displaceTail(node<T>* oldTail) {
  tail = oldTail->previousNode;
  tail->nextNode = NULL;
  oldTail->previousNode = NULL;
}

template <typename T> void linkedList<T>::displaceInBewtweenNode(node<T>* nodeToDisplace) {
  nodeToDisplace->previousNode->nextNode = nodeToDisplace->nextNode;
  nodeToDisplace->nextNode->previousNode = nodeToDisplace->previousNode;
  nodeToDisplace->nextNode = NULL;
  nodeToDisplace->previousNode = NULL;
}

template <typename T> void linkedList<T>::moveNode(size_t oldIndex, size_t newIndex) {
  if (isExistingValueInBetween(newIndex)) {
    moveNodeInBewteen(oldIndex, newIndex);
  } else {
    (newIndex == 0) ? moveNodeToHead(oldIndex) : moveNodeToTail(oldIndex);
  }
}

template <typename T> void linkedList<T>::moveNodeToHead(size_t index) {
  assert((index < size) && "Index value is greater than or equals the list\'s size");
  node<T>* selectedNode{ this->operator[](index) };
  displaceNode(selectedNode, index);
  placeNodeOnHead(selectedNode);
  resetIterator();
}

template <typename T> void linkedList<T>::moveNodeToTail(size_t index) {
  assert((index < size) && "Index value is greater than or equals the list\'s size");
  node<T>* selectedNode{ this->operator[](index) };
  displaceNode(selectedNode, index);
  placeNodeOnTail(selectedNode);
  resetIterator();    //This isn't really needed, but it's added to match the other move functions
}



template <typename T> void linkedList<T>::moveNodeInBewteen(size_t oldIndex, size_t newIndex) {
  assert((oldIndex < size) && "Old index value is greater than or equals the list\'s size");
  assert((newIndex < size) && "New index value is greater than or equals the list\'s size");
  assert((oldIndex != newIndex) && "Both index values shouldn\'t be equal");
  node<T>* selectedNode{ this->operator[](oldIndex) };
  displaceNode(selectedNode, oldIndex);
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

#endif
