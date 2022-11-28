// SaveFile ��ü: ������ �߻�ȭ�ϴ� ��ü�̴�!
// ��� ���� �б�/���⿡�� ǥ�� ���� ����� ��� �� �߻�ȭ�� ������� ����Ѵ�
// SaveFile_new, SaveFile_load�� ������ SaveFile ��ü�� �� SaveFile_free�� ������� �Ѵ�

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

extern SaveFile* SaveFile_new(int sz); // �� SaveFile ��ü�� �����
extern SaveFile* SaveFile_load(const char* filename); // ������ �о SaveFile ��ü�� �����

// SaveFile_append�� SaveFile_read�� ȥ���ϸ� �Ƹ� ����� �۵����� ���� ���̴�! 

extern void SaveFile_append(SaveFile* sf, int a); // SaveFile ��ü�� �����͸� �߰��Ѵ�
extern int SaveFile_read(SaveFile* sf); // SaveFile ��ü���� �����͸� �о�´�

extern bool SaveFile_write(SaveFile* sf, const char* filename); // SaveFile ��ü�� ���Ͽ� ����!

extern void SaveFile_free(SaveFile* sf); // SaveFile ��ü�� �޸𸮿��� ���ش�