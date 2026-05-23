#include <stddef.h>

void copy_data_8(char* dst, const char* src, size_t size)
{
	while(size) {
		*dst = *src;
		dst += 1;
		src += 1;
		size -= 1;
	}
}
