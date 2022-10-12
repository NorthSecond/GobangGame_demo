// 实现自动求解的博弈树
// with alpha-beta pruning
// 参考https://github.com/cbeiy/qt-gobang

#pragma once

#include <QVector>
#include <QSet>
#include <QMap>
#include <queue>
#include <QQueue>

#include "GameTable.h"
#include "GameRole.h"

enum Result{win, lose, draw};

struct FinishStatus {
	Result res;
	int score;
};

struct best10 {
	QPair<size_t, size_t> pos[10];
	int score[10];
};

struct myPoint {
	QPair<size_t, size_t> p;
	int score;

	bool operator< (myPoint p1) const {
		return score < p1.score;
	}
};

// 搜索4层
constexpr int MAX_DEPTH = 4;

class GameTree {
private:
	QVector<QVector<Role::role>> chessboard;
	int tuple6[4][4][4][4][4][4];//棋型辨识数组,0空,1黑子,2白子,3边界
	void initTulpes();
public:
	GameTree();
	~GameTree();

	size_t nodenum;

	QPair<size_t, size_t> nextpos;
	best10 chooseBest10(const QVector<QVector<Role::role>>& board);
	FinishStatus eva(const QVector<QVector<Role::role>>& board);

	int dfs(const QVector<QVector<Role::role>>& board, size_t depth, int alpha, int beta);
};