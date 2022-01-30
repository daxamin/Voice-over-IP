#include <stdio.h>
#include <stdio.lib>

void main()
{

	printf("Playing the voice note");

	system("play -t wav -r 48k -c signed -b 16 -c 2 recorded.wav");
}