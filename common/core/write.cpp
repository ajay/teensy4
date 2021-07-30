#include "Arduino.h"

extern "C" int _write(int fd [[gnu::unused]], char *ptr, int len)
{
    return Serial.write(ptr, len);
}
