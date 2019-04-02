#include <stdio.h>

int main()
{
	long long a = 1;

	for(int i = 10; i < 19; ++i, a = a * 100 + 11)
		printf("%*lld\n", i, a);
	for(int i = 19; i > 9; --i, a /= 100)
		printf("%*lld\n", i, a);

	return 0;
}