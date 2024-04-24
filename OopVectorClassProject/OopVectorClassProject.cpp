#include <iostream>
#include "Vector.h"

int main()
{
    srand(time(nullptr));

    Vector<int> v(10);
    for (int i{}; i < v.Size(); i++)
        v[i] = rand() % 100;

    for (int i{}; i < v.Size(); i++)
        std::cout << v[i] << " ";
    std::cout << "\n";

    auto it = v.GetIterator();
    for (it.Set(); !it.EndOf(); it.Next())
        std::cout << it.Current() << " ";
    std::cout << "\n";
}
