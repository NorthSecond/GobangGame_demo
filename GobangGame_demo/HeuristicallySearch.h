// 实现人机对战的启发式搜索算法
// 相对于 alpha-beta 剪枝的博弈树，启发式搜索算法速度其实要快不少
// 可能是博弈树代码写的太垃了…… 有时间优化一下吧
#pragma once

#include <QVector> 
#include <QRandomGenerator>

#include "GameRole.h"
#include "GameTable.h"

class HeuristicallySearch
{
private:
	QVector<QVector<unsigned int>> score;

	// 评分函数
	size_t evaluate(QVector<QVector<Role::role>> , Role::role role = Role::ROLE_WHITE);
	void flushScore();

public:
	HeuristicallySearch();
	~HeuristicallySearch();


	// 启发式搜索
	// 返回最佳的落子位置
	QPair<size_t, size_t> search(QVector<QVector<Role::role>>, Role::role role = Role::ROLE_WHITE);
};
