#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(a) (sizeof a / sizeof a[0])

size_t copy_if(void *dst, size_t dst_size,
		void *src, size_t src_size, size_t elem_size,
		int (*predicate)(const void *, const void *), const void *context);

typedef struct person {
	char name[20];
	int age;
} Person;

Person people[] = {
	{"Luis", 20},
	{"António", 30},
	{"Manuel", 50}
};

Person found_people[3];

int older_than(const void *elem, const void *age) {
	return ((Person *)elem)->age > (int)(long)age;
}

int main() {
	size_t n = copy_if(found_people, ARRAY_SIZE(found_people),
						people, ARRAY_SIZE(people), sizeof(people[0]),
						older_than, (const void *)25);
	for (size_t i = 0; i < n; ++i)
		printf("%s, %d\n", found_people[i].name, found_people[i].age);
}
