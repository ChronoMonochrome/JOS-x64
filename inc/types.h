#ifndef JOS_INC_TYPES_H
#define JOS_INC_TYPES_H

#ifndef NULL
#define NULL ((void*) 0)
#endif

// Represents true-or-false values
typedef _Bool bool;
enum { false, true };

// Explicitly-sized versions of integer types
// Using __extension__ to allow long long in strict C99
__extension__ typedef __signed char int8_t;
__extension__ typedef unsigned char uint8_t;
__extension__ typedef short int16_t;
__extension__ typedef unsigned short uint16_t;
__extension__ typedef int int32_t;
__extension__ typedef unsigned int uint32_t;

// Use compiler-defined types to avoid conflicts with system headers
typedef __INT64_TYPE__ int64_t;
typedef __UINT64_TYPE__ uint64_t;

// Pointers and addresses are 64 bits long in x86_64.
typedef int64_t intptr_t;
typedef uint64_t uintptr_t;
typedef uint64_t physaddr_t;

// Page numbers and memory object sizes
typedef uint64_t ppn_t;
typedef __SIZE_TYPE__ size_t;
typedef __PTRDIFF_TYPE__ ssize_t;

// off_t is used for file offsets and lengths.
typedef int64_t off_t;

// Efficient min and max operations
#define MIN(_a, _b)                                              \
({                                                               \
	typeof(_a) __a = (_a);                                   \
	typeof(_b) __b = (_b);                                   \
	__a <= __b ? __a : __b;                                  \
})
#define MAX(_a, _b)                                              \
({                                                               \
	typeof(_a) __a = (_a);                                   \
	typeof(_b) __b = (_b);                                   \
	__a >= __b ? __a : __b;                                  \
})

// Rounding operations (efficient when n is a power of 2)
#define ROUNDDOWN(a, n)                                          \
({                                                               \
	uintptr_t __a = (uintptr_t) (a);                         \
	(typeof(a)) (__a - __a % (n));                           \
})
#define ROUNDUP(a, n)                                            \
({                                                               \
	uintptr_t __n = (uintptr_t) (n);                         \
	(typeof(a)) (ROUNDDOWN((uintptr_t) (a) + __n - 1, __n)); \
})

#define ARRAY_SIZE(a)   (sizeof(a) / sizeof(a[0]))

// Return the offset of 'member' relative to the beginning of a struct type
#define offsetof(type, member)  ((size_t) (&((type*)0)->member))

#endif /* !JOS_INC_TYPES_H */
