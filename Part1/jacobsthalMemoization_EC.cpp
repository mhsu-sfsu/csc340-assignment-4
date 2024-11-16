#include <iostream>
#include <cstdlib> 
#include <map> 

using namespace std;

//TODO: add your documentation here
/* This version of the function takes on a map called memo in addition to the integer that
specifies which value should be returned. By passing the map by reference, it is a lot quicker
to access values that have been calculated already, which greatly speeds up the amount of time
it takes to calculate larger values of n.*/
long long jacobsthal(int n, map<int, long long> &memo){
    if (memo.count(n) == 1){ // If the value for n exists in the map, we just use it
        return memo.find(n)->second;
    } else { // If it doesn't exist in the map, we do the calculation, add it to the map, and return the value
        if (n == 0 || n == 1){ // Adding values for 0 and 1
            long long num = n;
            memo.insert({n, num});
            return n;
        } else { // Case where n > 1 and is not in the map
            long long calc = jacobsthal(n-1, memo) + (2 * jacobsthal(n-2, memo));
            memo.insert({n, calc}); // Inserting into the map before returning 
            return jacobsthal(n-1, memo) + (2 * jacobsthal(n-2, memo));
        }
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

    // Jacobsthal numbers cache (could use vector, too)
    std::map<int, long long> memo;

    // Compute Jacobsthal of n
    long long j_n = jacobsthal(n, memo); 
    std::cout << "Jacobsthal(" << n << ") = " << j_n << std::endl;

    return 0; 
}
