#ifndef _POSIX_PTHREAD_PRIORITY_PRIVATE_H
#define _POSIX_PTHREAD_PRIORITY_PRIVATE_H

#include <stdint.h>
#include <math.h>
#include "pthread.h"

typedef uint64_t pthread_priority_t;
#define _PTHREAD_PRIORITY_FLAGS_MASK		0xFFFF000000000000
#define _PTHREAD_PRIORITY_PRIORITY_MASK		0xFF
#define _PTHREAD_PRIORITY_SCHED_PRI_MASK	0xFF
#define _PTHREAD_PRIORITY_QOS_CLASS_SHIFT	16

#define _PTHREAD_PRIORITY_OVERCOMMIT_FLAG		0x80000000
#define _PTHREAD_PRIORITY_NEEDS_UNBIND_FLAG		0x40000000
#define _PTHREAD_PRIORITY_EVENT_MANAGER_FLAG	0x20000000
#define _PTHREAD_PRIORITY_FALLBACK_FLAG			0x10000000
#define _PTHREAD_PRIORITY_SCHED_PRI_FLAG		0x08000000

static inline thread_qos_t _pthread_priority_thread_qos(pthread_priority_t priority) {
	return (thread_qos_t)((priority >> _PTHREAD_PRIORITY_QOS_CLASS_SHIFT) & 0xFF);
}

static inline integer_t _pthread_priority_relpri(pthread_priority_t priority) {
	return (qos_class_t)(priority & 0xFF);
}

static inline pthread_priority_t _pthread_priority_make_from_thread_qos(thread_qos_t qos, integer_t priority, unsigned long flags) {
	uint64_t qos_bit = 1 << (qos + _PTHREAD_PRIORITY_QOS_CLASS_SHIFT);

	uint64_t retval = 0;
	retval |= qos_bit;
	retval |= (priority & 0xFF);
	retval |= flags;

	return retval;
}

static inline pthread_priority_t _pthread_unspecified_priority(void) {
	return _pthread_priority_make_from_thread_qos(QOS_CLASS_UNSPECIFIED, 0, 0);
}

static inline pthread_priority_t _pthread_default_priority(int unknown __unused) {
	return _pthread_unspecified_priority();
}

#endif
