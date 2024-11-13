#include <stdio.h>
#include <assert.h>

typedef struct {
	int age, m1, m2;
} Person;


void update3(int size, const char *str) {
	puts("--------------------------------");
	printf("str: %s\n", str);
}


void update4(int type, Person *p) {
//void update4(int type, Person2 p) {
	puts("--------------------------------");
	printf("person type: %u\n", type);
	printf("person.age: %d\n", p->age);
	printf("person.m1: %d\n", p->m1);
	printf("person.m2: %d\n", p->m2);
}

void update5(int size, Person *p) {
//void update4(int type, Person2 p) {
	puts("--------------------------------");
	printf("person size: %u\n", size);
	printf("person.age: %d\n", p->age);
	printf("person.m1: %d\n", p->m1);
	printf("person.m2: %d\n", p->m2);
}
