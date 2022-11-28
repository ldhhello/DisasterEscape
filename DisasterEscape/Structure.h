// Structure ��ü: ���ӿ� �ִ� �������� ��Ÿ���� Ŭ����!

#pragma once
#include "Include.h"

typedef struct
{
	int x, y; // �̹����� x, y��ǥ
	int width, height; // �̹����� ����, ���� ũ��
	
	HBITMAP bitmap; // ��� �̹���

	bool is_hide; // ���� ����. �̰� true�� ������ �Ǿ� �������� �ʰ� ��ȣ�ۿ������� �ʴ´�
	bool passable; // ��� ����. �̰� true�� �������� ��ȣ�ۿ����� �ʴ´�

	void (*on_active)(int st, int dir); // ��ȣ�ۿ� �� ȣ��Ǵ� �Լ�. �̰� NULL�̸� �⺻�� (Scene�� ���ǵǴ�) �� ȣ��ȴ�

	double scale; // �̹��� ������ (��ä��� ImageLayer�� �⺻�� 16�� ������)

} Structure;