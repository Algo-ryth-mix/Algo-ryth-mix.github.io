
#include <iostream>

int main() {
    int x [2];

    for (int i = 0; i < 2000; ++i)
    {
        x[i] = i;
    }

    std::cout << "Hello World" << x[1024] << std::endl;
    return 0;
}