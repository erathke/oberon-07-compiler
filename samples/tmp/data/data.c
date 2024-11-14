#include <stdio.h>

typedef struct {
	char name[32];
	int age, m1, m2;
} Person;


void update2(Person *p) {
	puts("---------------update2-----------------");
	printf("person size: %u\n", sizeof(Person));
	printf("person.age: %d\n", p->age);
	printf("person.m1: %d\n", p->m1);
	printf("person.m2: %d\n", p->m2);
}

void update4(int type, Person *p) {
	puts("---------------update4-----------------");
	printf("person type: %u\n", type);
	printf("person.age: %d\n", p->age);
	printf("person.m1: %d\n", p->m1);
	printf("person.m2: %d\n", p->m2);
}

void update5(int size, Person *p) {
	puts("---------------update5-----------------");
	printf("person size: %u\n", size);
	printf("person.age: %s\n", p->name);
	printf("person.age: %d\n", p->age);
	printf("person.m1: %d\n", p->m1);
	printf("person.m2: %d\n", p->m2);
}


void updateName(Person *p, int size, const char *name) {
	strncpy(p->name, name, size);
}

void update7(Person *p) {
	puts("---------------update7-----------------");
	printf("person.name: %s\n", p->name);
	printf("person.age: %d\n", p->age);
	printf("person.m1: %d\n", p->m1);
	printf("person.m2: %d\n", p->m2);
	p->m2 = 876;
}
