#pragma once

#include <stdio.h>
#include <stdbool.h>

// Struct Hack!!!!
typedef struct
{
	int sz;
	int cursor_in;
	int cursor_out;

	int data[0];
} SaveFile;

extern SaveFile* SaveFile_new(int sz);
extern SaveFile* SaveFile_load(const char* filename);

extern void SaveFile_append(SaveFile* sf, int a);
extern int SaveFile_read(SaveFile* sf);

extern bool SaveFile_write(SaveFile* sf, const char* filename);

extern void SaveFile_free(SaveFile* sf);