#include "types.h"
#include <iostream>

int main(void) {
    std::vector<int> collection1 = { 1, 2, 3, 4, 5 };
    std::vector<int> collection2 = { 5, 2, 9, 8, 6 };
    Set<int> A;
    Set<int> B;
    auto un = A.Union(B);
    auto di = A.Difference(B);
    auto ps = A.PowerSet();
    std::cout << "A: " << A << "\n";
    std::cout << "B: " << B << "\n";
    std::cout << "A U B" << un << "\n";
    std::cout << "A - B" << di << "\n";
    std::cout << "PowerSet(A): " << ps << "\n";
    return 0;
}
