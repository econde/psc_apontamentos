#include <stddef.h>
#include <string.h>

size_t copy_if(void *dst, size_t dst_size,
		void *src, size_t src_size, size_t elem_size,
		int (*predicate)(const void *, const void *), const void *context) {

    char *src_ptr = src, *src_last = (char *)src + src_size * elem_size;
    char *dst_ptr = dst, *dst_last = (char *)dst + dst_size * elem_size;

    for (src_ptr = src; src_ptr < src_last; src_ptr += elem_size)
        if (predicate(src_ptr, context) && dst_ptr < dst_last) {
            memcpy(dst_ptr, src_ptr, elem_size);
            dst_ptr += elem_size;
        }
    return (dst_ptr - (char*)dst) / elem_size;
}
