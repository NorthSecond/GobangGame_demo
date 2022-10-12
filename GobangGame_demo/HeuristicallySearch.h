// ʵ���˻���ս������ʽ�����㷨
// ����� alpha-beta ��֦�Ĳ�����������ʽ�����㷨�ٶ���ʵҪ�첻��
// �����ǲ���������д��̫���ˡ��� ��ʱ���Ż�һ�°�
#pragma once

#include <QVector> 
#include <QRandomGenerator>

#include "GameRole.h"
#include "GameTable.h"

class HeuristicallySearch
{
private:
	QVector<QVector<unsigned int>> score;

	// ���ֺ���
	size_t evaluate(QVector<QVector<Role::role>> , Role::role role = Role::ROLE_WHITE);
	void flushScore();

public:
	HeuristicallySearch();
	~HeuristicallySearch();


	// ����ʽ����
	// ������ѵ�����λ��
	QPair<size_t, size_t> search(QVector<QVector<Role::role>>, Role::role role = Role::ROLE_WHITE);
};
