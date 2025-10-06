#include <iostream>
#include <optional>

int main() {
    std::optional<int> x = 5;
    if (x) std::cout << "x = " << *x << "\n";
}

