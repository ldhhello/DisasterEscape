#define _CRT_SECURE_NO_WARNINGS

#include "SaveFile.h"
#include <stdlib.h>
#include <string.h>

SaveFile* SaveFile_new(int sz)
{
	SaveFile* sf = malloc(sizeof(SaveFile) + sizeof(int) * sz);
	memset(sf, 0, sizeof(SaveFile) + sizeof(int) * sz);

	sf->sz = sz;
	sf->cursor_in = 0;
	sf->cursor_out = 0;

	return sf;
}

SaveFile* SaveFile_load(const char* filename)
{
	FILE* fp = fopen(filename, "r");

	int sz;
	fread(&sz, 4, 1, fp);

	if (sz > 10000)
		return NULL;

	SaveFile* sf = malloc(sizeof(SaveFile) + sizeof(int) * sz);
	memset(sf, 0, sizeof(SaveFile) + sizeof(int) * sz);

	fread(sf->data, 4, sz, fp);

	sf->sz = sz;

	fclose(fp);

	return sf;
}

void SaveFile_append(SaveFile* sf, int a)
{
	sf->data[sf->cursor_out] = a;
	sf->cursor_out++;
}

int SaveFile_read(SaveFile* sf)
{
	if (sf->cursor_in >= sf->sz)
		return 0;

	int res = sf->data[sf->cursor_in];

	sf->cursor_in++;
	return res;
}

// 얘는 구조체 전체 크기가 아니라 append 된 만큼만 write함
bool SaveFile_write(SaveFile* sf, const char* filename)
{
	FILE* fp = fopen(filename, "w");

	fwrite(&sf->cursor_out, 4, 1, fp);

	fwrite(sf->data, 4, sf->cursor_out, fp);

	fclose(fp);

	return true;
}

void SaveFile_free(SaveFile* sf)
{
	free(sf);
}