#include <iostream>
#include "Customer.h"

using namespace std;

int main() {
    string aa = "Hello";
    std::cout << "Hello, World!" << std::endl;
    std::cout << aa << std::endl;
    Customer customer = Customer("John", "Smith");
    std::cout << customer.name << std::endl;
    std::cout << customer.age << std::endl;

    return 0;
}