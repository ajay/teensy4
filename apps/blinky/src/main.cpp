#include <iostream>

#include "Arduino.h"

int main()
{
    Serial.begin(115200);
    pinMode(13, OUTPUT);

    size_t counter = 0;
    while(true)
    {
        digitalWriteFast(13, HIGH);
        delay(500);
        digitalWriteFast(13, LOW);
        delay(500);
        std::cout << "Hello world" << ++counter << '\n';
    }
}
