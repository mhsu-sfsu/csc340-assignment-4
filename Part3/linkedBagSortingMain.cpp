#include <iostream>
#include <vector>
#include "LinkedBagDS/LinkedBag.h"

using namespace std;

template<class T>
void displayBag(LinkedBag<T>& bag){
   std::vector<T> bagItems = bag.toVector();
   
   int numberOfEntries = (int) bagItems.size();
   for (int i = 0; i < numberOfEntries; i++){
      cout << bagItems[i] << " ";
   } 
   cout << endl;

} 

int main() {
    vector<int> arr = {35, 62, 15, 24, 40, 7};

    // Create a linked bag from the vector
    LinkedBag<int> lBag; 
    for(int num : arr){
        lBag.add(num);
    }
    std::cout << "Original bag elements" << endl;
    displayBag(lBag);

    // Sort the linked bag using QuickSort
    // 0 for merge sort and 1 for quick sort
    lBag.sort(0);

    cout << "Sorted bag elements" << endl;
    displayBag(lBag);

    return 0;
}