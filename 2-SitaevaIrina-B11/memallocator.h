#pragma once
struct HEAD;
int meminit(void* pMemory, int size);
void memdone();
void* memalloc(int size);
void memfree(void* p);
int memgetminimumsize();
int memgetblocksize();

