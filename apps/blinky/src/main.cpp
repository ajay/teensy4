#include <iostream>

#include <Arduino.h>

int main()
{
    pinMode(13, OUTPUT);

    size_t counter = 0UL;
    while (true)
    {
        digitalWriteFast(13, HIGH);
        delay(1000);
        digitalWriteFast(13, LOW);
        delay(200);
        std::cout << "Hello world" << ++counter << '\n';
    }
}
