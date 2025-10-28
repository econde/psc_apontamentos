int year;
int month;
int day;

void unpack_date(short, int *, int *, int *);

int main() {
	unpack_date(2024 - 2000 << 9 | 10 << 5 | 8,
				&year, &month, &day);
}
