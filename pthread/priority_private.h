#ifndef _POSIX_PTHREAD_PRIORITY_PRIVATE_H
#define _POSIX_PTHREAD_PRIORITY_PRIVATE_H

#include <stdint.h>

typedef uint64_t pthread_priority_t;

static inline pthread_priority_t _pthread_unspecified_priority(void) {
	return 0;
}

static inline integer_t _pthread_priority_thread_qos(pthread_priority_t priority) {
	return (priority >> 32) & 0xFFFFFFFF;
}

static inline integer_t _pthread_priority_relpri(pthread_priority_t priority) {
	return priority & 0xFFFFFFFF;
}

static inline pthread_priority_t _pthread_priority_make_from_thread_qos(integer_t tier, integer_t priority, pthread_priority_t unk __unused) {
	uint64_t tier64 = (uint64_t)tier;
	return (tier64 << 32) | priority;
}

#endif
