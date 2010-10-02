#include <iostream>
#include <string>
#include "strmath.cpp"
#include "knowledge.cpp"

using namespace std;

int main()
{
    ANIMAL *bill = new HUMAN("bill");
    OBJECT *obj1 = new GENERIC_OBJECT();
    obj1->set_name("Flowers");
    obj1->set_desc("A simple lifeform often used as decoration.");
    bill->Display();
    delete obj1, bill;
}

