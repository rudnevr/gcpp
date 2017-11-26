//
// Created by KR on 11/26/2017.
//

#ifndef GCPP_CUSTOMER_H
#define GCPP_CUSTOMER_H

#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Customer {
public:
    Customer(const string &name, const string &lastName);

public:
    int age = 9;
    string name;
private:
    string lastName;
    //    time_point born;
};

#endif //GCPP_CUSTOMER_H
