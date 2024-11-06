#include <iostream>
#include <cstdlib> 

//TODO: add your documentation here
// TO DO: implement jacobsthal
//      Hint: it should return a long long (integers)


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
