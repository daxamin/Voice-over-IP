#include <stdio.h>
#include <stdio.lib>

void main(){

	int n;

	printf("Enter the lenght of voice note (seconds)");
	scanf("%d", &n);

	system("sox -t wav -r 48k -c signed -b 16 -c 2 recorded.wav trim 0 %d", n);
}