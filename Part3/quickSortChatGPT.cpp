#include <iostream>

// Definition for singly-linked list
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    // Helper function to print the linked list
    void printList(ListNode* head) {
        ListNode* current = head;
        while (current != nullptr) {
            std::cout << current->val << " -> ";
            current = current->next;
        }
        std::cout << "nullptr\n";
    }

    // Function to partition the list around a pivot
    ListNode* partition(ListNode* head, ListNode* end, ListNode** newHead, ListNode** newEnd) {
        ListNode* pivot = end;
        ListNode* prev = nullptr;
        ListNode* curr = head;
        ListNode* tail = pivot;
        
        // Iterate through the list and partition around the pivot
        while (curr != pivot) {
            if (curr->val < pivot->val) {
                if (*newHead == nullptr) {
                    *newHead = curr;  // First node less than pivot
                }
                prev = curr;
                curr = curr->next;
            } else {
                // Move the node to the tail of the list
                if (prev) {
                    prev->next = curr->next;
                }
                ListNode* temp = curr->next;
                curr->next = nullptr;
                tail->next = curr;
                tail = curr;
                curr = temp;
            }
        }

        // Set the new tail to the pivot
        if (*newHead == nullptr) {
            *newHead = pivot;
        }
        *newEnd = tail;
        return pivot;
    }

    // Function to implement QuickSort on the linked list
    ListNode* quickSortRec(ListNode* head, ListNode* end) {
        if (!head || head == end) return head;  // Base case: empty or single element list

        ListNode *newHead = nullptr, *newEnd = nullptr;
        
        // Partition the list around a pivot
        ListNode* pivot = partition(head, end, &newHead, &newEnd);
        
        // If the pivot is not the first element, recursively sort the left part
        if (newHead != pivot) {
            ListNode* temp = newHead;
            // Recursively sort the list before the pivot
            while (temp->next != pivot) {
                temp = temp->next;
            }
            temp->next = nullptr;
            newHead = quickSortRec(newHead, temp);
            
            // Connect the sorted part to pivot
            temp = getTail(newHead);
            temp->next = pivot;
        }

        // Recursively sort the right part
        pivot->next = quickSortRec(pivot->next, newEnd);
        
        return newHead;
    }

    // Utility function to get the tail of the list
    ListNode* getTail(ListNode* head) {
        while (head != nullptr && head->next != nullptr) {
            head = head->next;
        }
        return head;
    }

    // Wrapper function to sort the linked list using QuickSort
    ListNode* quickSort(ListNode* head) {
        return quickSortRec(head, getTail(head));
    }

    // Helper function to create a list from an array
    ListNode* createList(std::initializer_list<int> values) {
        ListNode* head = nullptr;
        ListNode* tail = nullptr;

        for (int val : values) {
            ListNode* newNode = new ListNode(val);
            if (!head) {
                head = tail = newNode;
            } else {
                tail->next = newNode;
                tail = tail->next;
            }
        }
        return head;
    }
};

int main() {
    Solution solution;

    // Create a linked list from an array
    ListNode* head = solution.createList({4, 2, 1, 3, 5, 6});

    std::cout << "Original list: ";
    solution.printList(head);

    // Sort the linked list using QuickSort
    ListNode* sortedList = solution.quickSort(head);

    std::cout << "Sorted list: ";
    solution.printList(sortedList);

    return 0;
}
