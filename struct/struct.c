#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
	char name[10];
	int age;
	float salary;
} human_being;

int main(){
	human_being person1;

	strcpy(person1.name, "Nullname");
	person1.age = 21;
	person1.salary = 0;

	printf("name:%s,age:%d,salary:%f\n",person1.name, person1.age,person1.salary);

	return 0;
}
