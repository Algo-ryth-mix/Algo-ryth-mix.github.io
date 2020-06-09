#include "close_enough.hpp"

int main()
{
    using namespace pixl::util;

    float f = 2.0f;
    int i = 2;

    if(close_enough(f,i))
    {
        //stuff...
    }
}