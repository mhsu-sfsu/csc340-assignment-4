#include <iostream>
#include <cstdlib> 

// Function return type: long long
// Given an integer n, calculates the corresponding value and returns it through recursion
long long jacobsthal(int n){
    long long curnum = n; // Converting integer to long long
    if (curnum == 0 || curnum == 1){ // Base case - returns 0 or 1 depending on the value of n
        return curnum;
    } else { // if n > 1, J(n − 1) + 2 × J(n − 2)
        return jacobsthal(n-1) + (2 * jacobsthal(n-2));
    }
}

int main(int argc, char* argv[]) {
    // Read n from command line argument
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <n>" << std::endl;
        return 1; 
    }

    // Convert n to an integer
    int n = std::atoi(argv[1]); 

    // Compute Jacobsthal of n
    long long result = jacobsthal(n); 
    std::cout << "Jacobsthal(" << n << ") = " << result << std::endl;

    return 0; 
}
