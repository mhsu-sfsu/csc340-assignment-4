//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT bag: Link-based implementation.
	 @file LinkedBag.cpp */

#include "LinkedBag.h"
#include "Node.h"
#include <cstddef>
#include <type_traits>

//   SORTING ----------------------------------------------------
template<class ItemType>
void LinkedBag<ItemType>::sort(int method){
	if (itemCount <= 1)
		return;
	
	if (method == 0){
		// update function call if you change the prototype. 
		mergeSort();
	}else{
		// for EC, update function call if you change the prototype.
		// If you do implement quickSort, not action needed here
		quickSort(); 
	}
}

//TO DO: implement merge sort and change its prototype if you need to.
template<class ItemType>
void LinkedBag<ItemType>::mergeSort(){
    headPtr = mergeSort(headPtr);  // Sort the list starting from the head pointer
}

// Recursive merge sort for linked list
template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::mergeSort(Node<ItemType>* head){
    if (head == nullptr || head->getNext() == nullptr) {
        return head;  // Base case: empty list or single node
    }

    Node<ItemType>* left = nullptr;
    Node<ItemType>* right = nullptr;

    // Split the list into two halves
    split(head, &left, &right);

    // Recursively sort each half
    left = mergeSort(left);
    right = mergeSort(right);

    // Merge the two sorted halves
    return merge(left, right);
}

// Splits the linked list into two halves
template<class ItemType>
void LinkedBag<ItemType>::split(Node<ItemType>* source, Node<ItemType>** leftRef, Node<ItemType>** rightRef) {
    Node<ItemType>* slow = source;
    Node<ItemType>* fast = source->getNext();

    // Use slow/fast pointer technique to find the midpoint
    while (fast != nullptr) {
        fast = fast->getNext();
        if (fast != nullptr) {
            slow = slow->getNext();
            fast = fast->getNext();
        }
    }

    // Split the list into two parts
    *leftRef = source;
    *rightRef = slow->getNext();
    slow->setNext(nullptr);  // Break the list into two
}

// Merges two sorted linked lists
template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::merge(Node<ItemType>* left, Node<ItemType>* right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    Node<ItemType>* result = nullptr;

    // Compare the data in the nodes and link them in sorted order
    if (left->getItem() <= right->getItem()) {
        result = left;
        result->setNext(merge(left->getNext(), right));
    } else {
        result = right;
        result->setNext(merge(left, right->getNext()));
    }

    return result;
}

//Extra Credit -- TO DO: implement quick sort and change its prototype 
//                       if you need to.
template<class ItemType>
void LinkedBag<ItemType>::quickSort(){
	headPtr = quickSort(headPtr, getTail(headPtr));
}

template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::getTail(Node<ItemType>* head) {
    while (head != nullptr && head->getNext() != nullptr) {
        head = head->getNext();
    }
    return head;
}

template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::quickSort(Node<ItemType>* head, Node<ItemType>* end) {
    if (!head || head == end) {
        return head;
    }

    Node<ItemType>* newHead = nullptr;
    Node<ItemType>* newEnd = nullptr;

    Node<ItemType>* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {

        Node<ItemType>* temp = newHead;
        while (temp->getNext() != pivot) {
            temp = temp->getNext();
        }
        temp->setNext(nullptr);

        newHead = quickSort(newHead, temp);

        temp = getTail(newHead);
        temp->setNext(pivot);
    }

    pivot->setNext(quickSort(pivot->getNext(), newEnd));

    return newHead;
}

template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::partition(Node<ItemType>* head, Node<ItemType>* end, Node<ItemType>** newHead, Node<ItemType>** newEnd) {
    Node<ItemType>* pivot = end;
    Node<ItemType>* prev = nullptr;
    Node<ItemType>* curr = head;
    Node<ItemType>* tail = pivot;


    while (curr != pivot) {
        if (curr->getItem() < pivot->getItem()) {
            if (!(*newHead)) *newHead = curr;
            prev = curr;
            curr = curr->getNext();
        } else {
            if (prev) prev->setNext(curr->getNext());
            Node<ItemType>* temp = curr->getNext();
            curr->setNext(nullptr);
            tail->setNext(curr);
            tail = curr;
            curr = temp;
        }
    }

    if (!(*newHead)) *newHead = pivot;
    *newEnd = tail;

    return pivot;
}
// --------------------------------------------------------------

template<class ItemType>
LinkedBag<ItemType>::LinkedBag() : headPtr(nullptr), itemCount(0){
}  // end default constructor

template<class ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType>& aBag){
	itemCount = aBag.itemCount;
	Node<ItemType>* origChainPtr = aBag.headPtr;  // Points to nodes in original chain
	
	if (origChainPtr == nullptr)
		headPtr = nullptr;  // Original bag is empty
	else
	{
		// Copy first node
		headPtr = new Node<ItemType>();
		headPtr->setItem(origChainPtr->getItem());
		
		// Copy remaining nodes
		Node<ItemType>* newChainPtr = headPtr;		// Points to last node in new chain
		origChainPtr = origChainPtr->getNext();	  // Advance original-chain pointer
		
		while (origChainPtr != nullptr)
		{
			// Get next item from original chain
			ItemType nextItem = origChainPtr->getItem();
				  
			// Create a new node containing the next item
			Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
			
			// Link new node to end of new chain
			newChainPtr->setNext(newNodePtr);
			
			// Advance pointer to new last node
			newChainPtr = newChainPtr->getNext();

			// Advance original-chain pointer
			origChainPtr = origChainPtr->getNext();
		}  // end while
		
		newChainPtr->setNext(nullptr);				  // Flag end of chain
	}  // end if
}  // end copy constructor

template<class ItemType>
LinkedBag<ItemType>::~LinkedBag(){
	clear();
}  // end destructor

template<class ItemType>
bool LinkedBag<ItemType>::isEmpty() const{
	return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int LinkedBag<ItemType>::getCurrentSize() const{
	return itemCount;
}  // end getCurrentSize

template<class ItemType>
bool LinkedBag<ItemType>::add(const ItemType& newEntry){
	// Add to beginning of chain: new node references rest of chain;
	// (headPtr is null if chain is empty)		  
	Node<ItemType>* nextNodePtr = new Node<ItemType>();

	nextNodePtr->setItem(newEntry);
	nextNodePtr->setNext(headPtr);  // New node points to chain
	headPtr = nextNodePtr;			 // New node is now first node
	itemCount++;
	
	return true;
}  // end add

template<class ItemType>
std::vector<ItemType> LinkedBag<ItemType>::toVector() const{
	std::vector<ItemType> bagContents;
	Node<ItemType>* curPtr = headPtr;
	int counter = 0;
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		bagContents.push_back(curPtr->getItem());
		curPtr = curPtr->getNext();
		counter++;
	}  // end while
	
	return bagContents;
}  // end toVector

template<class ItemType>
bool LinkedBag<ItemType>::remove(const ItemType& anEntry){
	Node<ItemType>* entryNodePtr = getPointerTo(anEntry);
	bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
	if (canRemoveItem){
		// Copy data from first node to located node
		entryNodePtr->setItem(headPtr->getItem());
		
		// Delete first node
		Node<ItemType>* nodeToDeletePtr = headPtr;
		headPtr = headPtr->getNext();
		
		// Return node to the system
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;
		
		itemCount--;
	} // end if
	
	return canRemoveItem;
}  // end remove

template<class ItemType>
bool LinkedBag<ItemType>::removeAlt(const ItemType& anEntry){
	Node<ItemType>* prev = headPtr;
	Node<ItemType>* cur = headPtr;
	bool found = false;

	while((cur != nullptr) && !found){
		found = (*(cur->getItem()) == *anEntry);
		if (!found){
			prev = cur;
			cur = cur->getNext();
		}
	}

	if (found){
		prev->setNext(cur->getNext());
		// delete cur->getItem();
		delete cur;
		cur = nullptr;
		itemCount--;
	}

	return found;

}  // end remove

template<class ItemType>
void LinkedBag<ItemType>::clear(){
	Node<ItemType>* nodeToDeletePtr = headPtr;
	while (headPtr != nullptr){
		headPtr = headPtr->getNext();

		// Return node to the system
		nodeToDeletePtr->setNext(nullptr);

		// delete nodeToDeletePtr->getItem(); 
		delete nodeToDeletePtr;
		
		nodeToDeletePtr = headPtr;
	}  // end while
	// headPtr is nullptr; nodeToDeletePtr is nullptr
	
	itemCount = 0;
}  // end clear

template<class ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const{
	int frequency = 0;
	int counter = 0;
	Node<ItemType>* curPtr = headPtr;
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		if (anEntry == curPtr->getItem())
		{
			frequency++;
		} // end if
		
		counter++;
		curPtr = curPtr->getNext();
	} // end while
	
	return frequency;
}  // end getFrequencyOf

template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const{
	return (getPointerTo(anEntry) != nullptr);
}  // end contains


// private
// Returns either a pointer to the node containing a given entry 
// or the null pointer if the entry is not in the bag.
template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::getPointerTo(const ItemType& anEntry) const{
	bool found = false;
	Node<ItemType>* curPtr = headPtr;
	
	while (!found && (curPtr != nullptr))
	{
		if (anEntry == curPtr->getItem())
			found = true;
		else
			curPtr = curPtr->getNext();
	} // end while
	
	return curPtr;
} // end getPointerTo


