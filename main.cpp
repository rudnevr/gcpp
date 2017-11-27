#include <iostream>
#include "Customer.h"

using namespace std;


extern "C" {
#include "foo.h" //a C header, so wrap it in extern "C"
}

int main() {
//    string aa = "Hello";
//    std::cout << "Hello, World!" << std::endl;
//    std::cout << aa << std::endl;
//    Customer customer = Customer("John", "Smith");
//    std::cout << customer.name << std::endl;
//    std::cout << customer.age << std::endl;
    foo();
    return 0;
}
