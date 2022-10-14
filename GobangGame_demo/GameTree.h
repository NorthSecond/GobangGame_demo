// 实现自动求解的博弈树
// with alpha-beta pruning
// 参考https://github.com/cbeiy/qt-gobang

#pragma once

#include <queue>

#include <QVector>
#include <QSet>
#include <QMap>
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

class GameTree {
private:
	QVector<QVector<Role::role>> chessboard;
	int tuple6[4][4][4][4][4][4];//棋型辨识数组,0空,1黑子,2白子,3边界
	void initTulpes();

protected:
	// used been the defined global constexpr.
	const int MAX_DEPTH = 4;

	const int R_WIN = 5000000;
	const int R_FLEX4 = 50000;
	const int R_BLOCK4 = 400;
	const int R_FLEX3 = 400;
	const int R_BLOCK3 = 20;
	const int R_FLEX2 = 20;
	const int R_BLOCK2 = 1;
	const int R_FLEX1 = 1;

	const int WIN = -10000000;
	const int FLEX4 = -100000;
	const int BLOCK4 = -100000;
	const int FLEX3 = -8000;
	const int BLOCK3 = -50;
	const int FLEX2 = -50;
	const int BLOCK2 = -3;
	const int FLEX1 = -3;
	
public:
	GameTree();
	~GameTree();

	size_t nodenum;

	QPair<size_t, size_t> nextpos;
	best10 chooseBest10(const QVector<QVector<Role::role>>& board);
	FinishStatus eva(const QVector<QVector<Role::role>>& board);

	int dfs(const QVector<QVector<Role::role>>& board, size_t depth, int alpha, int beta);
};