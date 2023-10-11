#undef UDEBUG
#include <assert.h>
#include <lcthw/dbg.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <lcthw/ringbuffer.h>

#define report_exceptional_condition() abort()

// Linux 上环形缓冲区的长度至少要为 1UL << 12，wiki上的实现的长度均为 2 的整数幂
RingBuffer *RingBuffer_create(int length) 
{
	RingBuffer *buffer;
	char path[] = "/dev/shm/ring-buffer-XXXXXX";
	int file_descriptor;
	void *address;
	int status;
	file_descriptor = mkstemp(path);
	check(file_descriptor >= 0, "file_descriptor error.");
	status = unlink(path);
	check(status == 0, "unlink error.");
	buffer->length = length;
	buffer->start = 0;
	buffer->end = 0;
	status = ftruncate(file_descriptor, buffer->length);
	check(status == 0, "ftruncate error.");
	buffer->buffer = mmap (NULL, buffer->length << 1, PROT_NONE, MAP_ANOYMOUS | MAP_PRIVATE, -1, 0);
	check(buffer->buffer != MAP_FAILED,"mmap failed.");
	address = mmap(buffer->buffer, buffer->length, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_SHARED, file_descriptor, 0);

}
