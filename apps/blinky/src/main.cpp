#include <Arduino.h>

int main()
{
	pinMode(13, OUTPUT);
	while (true)
	{
		digitalWriteFast(13, HIGH);
		delay(1000);
		digitalWriteFast(13, LOW);
		delay(200);
	}
}
