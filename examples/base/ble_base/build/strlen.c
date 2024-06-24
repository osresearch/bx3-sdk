#include <stdint.h>
#include <stddef.h>

int strlen(const char * s)
{
	int i = 0;
	while(*s++ != 0)
		i++;
	return i;
}

int qsort()
{
	return -1;
}

int __ctzsi2(unsigned x)
{
	return -1;
}

void * memcpy(void * dest, const void * src, size_t n)
{
	uint8_t * d = dest;
	const uint8_t * s = src;

	while(n-- != 0)
		*d++ = *s++;
	return dest;
}
