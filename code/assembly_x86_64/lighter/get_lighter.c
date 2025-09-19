#include <stddef.h>

typedef struct person {
    char name[20];
    int age;
    int weight;
    float height;
} Person;

Person *get_lighter(Person *people, size_t n_people) {
	size_t lighter = 0;
	for (size_t i = 1; i < n_people; ++i)
		if (people[i].weight < people[lighter].weight)
			lighter = i;
	return &people[lighter];
}
