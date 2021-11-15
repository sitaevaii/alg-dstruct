#include <stdlib.h>
#include "memallocator.h"

typedef struct Head {
	struct Head* next;
	struct Head* prev;
	char reserved;
	unsigned size;
} Head;

static Head* begin;

int meminit(void* pMemory, int size) {
	begin = (Head*)pMemory;
	begin->size = size - sizeof(Head);
	begin->reserved = 0;
	begin->next = NULL;
	begin->prev = NULL;
	return 1;
}

void memdone() {
	begin = NULL;
}

void* memalloc(int size) {
	Head* block = begin;

	while (block != NULL) {
		if (block->reserved == 0 && block->size >= size) {
			if (block->size > sizeof(Head) + size) {
				Head* next_block = (Head*)(((char*)block) + sizeof(Head) + size);
				next_block->size = block->size - size - sizeof(Head);
				next_block->next = block->next;
				next_block->prev = block;
				if (next_block->next != NULL)
					next_block->next->prev = next_block;
				next_block->reserved = 0;
				block->size = size;
				block->next = next_block;
			}

			block->reserved = 1;

			return (void*)(((char*)block) + sizeof(Head));
		}
		block = block->next;
	}
	return NULL;
}

void memfree(void* p) {
	Head* free_mem_head = (Head*)(((char*)p) - sizeof(Head));

	free_mem_head->reserved = 0;

	if (free_mem_head->next != NULL && free_mem_head->next->reserved == 0) {
		free_mem_head->size += free_mem_head->next->size + sizeof(Head);
		free_mem_head->next = free_mem_head->next->next;

		if (free_mem_head->next != NULL)
			free_mem_head->next->prev = free_mem_head;
	}

	if (free_mem_head->prev != NULL && free_mem_head->prev->reserved == 0) {
		free_mem_head->prev->size += free_mem_head->size + sizeof(Head);
		free_mem_head->prev->next = free_mem_head->next;

		if (free_mem_head->prev->next != NULL)
			free_mem_head->prev->next->prev = free_mem_head->prev;
	}
}

int memgetminimumsize() {
	return sizeof(Head);
}

int memgetblocksize() {
	return sizeof(Head);
}









