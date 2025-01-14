/*
*   name: include/core/mem.hpp
*   origin: Citrus Engine
*   purpose: Provide memory allocation functions
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_MEMORY_MANAGEMENT_HPP__
#define CITRUS_ENGINE_MEMORY_MANAGEMENT_HPP__

#include <cstdint>
#include <cstdlib>

#define MEM_FLAG_UNIT_BYTE 0 << 0
#define MEM_FLAG_UNIT_WORD 1 << 2
#define MEM_FLAG_UNIT_DWORD 1 << 3
#define MEM_FLAG_UNIT_QWORD 1 << 4
#define MEM_FLAG_UNIT_KB 1 << 5
#define MEM_FLAG_UNIT_MB 1 << 6
#define MEM_FLAG_UNIT_PAGE 1 << 7

#define HEAP_MAX_ALLOCATION_SIZE 96

namespace engine
{
	/*	The main memory allocation function
	*	Really just a wrapper around a couple different functions
	*	@param size Size in bytes
	*	@param flags Flags
	*	@return Pointer to the allocation, NULL if an error occurs
	*	errorcode will be set
	*/
	void *memalloc(size_t size, uint16_t flags);

	/* 	The main memory reallocation function
	*	@param ptr The old pointer
	*	@param size Size in bytes
	*	@param flags Flags, 0 to use previous flags
	*	@return Pointer to the new allocation, NULL if an error occurs
	*	errorcode will be set
	*/
	void *memrealloc(void *ptr, size_t size, uint16_t flags);

	/*	The main memory freeing function
	*	Really just a wrapper around a couple different functions
	*	@param ptr Pointer to free
	*/
	void memfree(void *ptr);

	// memnew is an exception to the no lambdas rule

	#define memnew(TYPE, COUNT) ( \
		([](size_t s) -> TYPE* \
		{ \
			TYPE *r = memalloc(s + 32, 0); \
			*(size_t*)r = COUNT; \
			r = (TYPE*)((uintptr_t)r + 32); \
			for(int i = 0; i < COUNT; i++) r[i] = TYPE(); \
			return r; \
		})(sizeof(TYPE) * COUNT) \
	)

	// memdelete is an exception to the no lambdas rule

	#define memdelete(TYPE, PTR) ( \
		([](TYPE *ptr) -> void \
		{ \
			size_t *s = (size_t*)((uintptr_t)ptr - 32); \
			for(int i = 0; i < *s; i++) ptr[i].~TYPE(); \
			memfree(s); \
		})(PTR) \
	)
};

#endif
