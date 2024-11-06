#include <iostream>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    // Merge two sorted lists
    ListNode* merge(ListNode* l1, ListNode* l2) {
        // Create a dummy node to simplify the merge process
        ListNode* dummy = new ListNode(0);
        ListNode* current = dummy;

        // Merge the two lists
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val < l2->val) {
                current->next = l1;
                l1 = l1->next;
            } else {
                current->next = l2;
                l2 = l2->next;
            }
            current = current->next;
        }

        // If either list is not empty, append the remaining nodes
        if (l1 != nullptr) {
            current->next = l1;
        } else {
            current->next = l2;
        }

        return dummy->next;  // Return the merged sorted list
    }

    // Split the list into two halves using the slow and fast pointer technique
    ListNode* findMiddle(ListNode* head) {
        if (!head || !head->next) return head;
        
        ListNode* slow = head;
        ListNode* fast = head->next;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* middle = slow->next;
        slow->next = nullptr;  // Break the list into two halves
        return middle;
    }

    // Merge sort the linked list
    ListNode* mergeSort(ListNode* head) {
        if (!head || !head->next) return head;  // Base case: single node or empty list
        
        // Split the list into two halves
        ListNode* middle = findMiddle(head);
        
        // Recursively sort the two halves
        ListNode* left = mergeSort(head);
        ListNode* right = mergeSort(middle);
        
        // Merge the two sorted halves
        return merge(left, right);
    }

    // Function to print the list (helper function)
    void printList(ListNode* head) {
        ListNode* current = head;
        while (current != nullptr) {
            std::cout << current->val << " -> ";
            current = current->next;
        }
        std::cout << "nullptr\n";
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
    ListNode* head = solution.createList({4, 2, 1, 3});

    std::cout << "Original list: ";
    solution.printList(head);

    // Sort the linked list using merge sort
    ListNode* sortedList = solution.mergeSort(head);

    std::cout << "Sorted list: ";
    solution.printList(sortedList);

    return 0;
}
