// ���ӿ� ���� ������ ���� �����ϴ� �ڵ��̴�
// �� �ý��� ��ü�� ������ ��� �̰����� �����ȴ�!
// ���� ���ÿ� ����ϴ� ��Ȳ�� ��� ���⼭�� ��� PlaySound�� ���� ������ ó���Ѵ�!
// ���⼭ ó���ϴ� ��� ������ ���ҽ����� �о���µ� MAKEINTRESOURCE(���ҽ� �̸�) �� ���ڷ� �Ѱ��ָ� �ȴ�!

#pragma once

#include "Include.h"

extern void Music_play(const char* music);
extern void Music_stop(const char* music);
extern void Music_set_background(const char* music);
extern void Music_stop_background();