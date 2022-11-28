// SaveFile 객체: 파일을 추상화하는 객체이다!
// 모든 파일 읽기/쓰기에는 표준 파일 입출력 대신 이 추상화된 입출력을 사용한다
// SaveFile_new, SaveFile_load로 생성한 SaveFile 객체는 꼭 SaveFile_free로 없애줘야 한다

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

extern SaveFile* SaveFile_new(int sz); // 새 SaveFile 객체를 만든다
extern SaveFile* SaveFile_load(const char* filename); // 파일을 읽어서 SaveFile 객체를 만든다

// SaveFile_append와 SaveFile_read는 혼용하면 아마 제대로 작동하지 않을 것이다! 

extern void SaveFile_append(SaveFile* sf, int a); // SaveFile 객체에 데이터를 추가한다
extern int SaveFile_read(SaveFile* sf); // SaveFile 객체에서 데이터를 읽어온다

extern bool SaveFile_write(SaveFile* sf, const char* filename); // SaveFile 객체를 파일에 쓴다!

extern void SaveFile_free(SaveFile* sf); // SaveFile 객체를 메모리에서 없앤다