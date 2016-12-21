#include <stdio.h>
#include <stdlib.h>

enum Week{
	Sunday,
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday
};

int main(){
	enum Week week;
	week = Sunday;
	printf("Sunday:%d\n",week);
	week = Monday;
	printf("Monday:%d\n",week);
	week = Tuesday;
	printf("Tuesday:%d\n",week);
	week = Wednesday;
	printf("Wednesday:%d\n",week);
	week = Thursday;
	printf("Thursday:%d\n",week);
	week = Friday;
	printf("Friday:%d\n",week);
	week = Saturday;
	printf("Saturday:%d\n",week);
	return 0;
}
