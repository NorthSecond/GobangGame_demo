#include "GameTree.h"


#define R_WIN 5000000
#define R_FLEX4 50000
#define R_BLOCK4 400
#define R_FLEX3 400
#define R_BLOCK3 20
#define R_FLEX2 20
#define R_BLOCK2 1
#define R_FLEX1 1

#define WIN -10000000
#define FLEX4 -100000
#define BLOCK4 -100000
#define FLEX3 -8000
#define BLOCK3 -50
#define FLEX2 -50
#define BLOCK2 -3
#define FLEX1 -3

GameTree::GameTree() {
	initTulpes();
	nodenum = 0;
	chessboard.resize(tableSize + 2);
	for (size_t i = 0; i < tableSize + 2; ++i) {
		chessboard[i].resize(tableSize + 2);
	}
}

GameTree::~GameTree() {

}

void GameTree::initTulpes() {
	//0空,1黑子,2白子,3边界
	//第0位非己方棋子，第1位己方棋子
	//黑连5
	tuple6[0][1][1][1][1][1] = WIN;
	tuple6[2][1][1][1][1][1] = WIN;
	tuple6[3][1][1][1][1][1] = WIN;
	//黑活4
	tuple6[0][1][1][1][1][0] = FLEX4;
	//黑冲4
	tuple6[2][1][1][1][1][0] = BLOCK4;
	tuple6[3][1][1][1][1][0] = BLOCK4;
	tuple6[0][1][1][1][1][2] = BLOCK4;
	tuple6[0][1][1][1][1][3] = BLOCK4;
	for (int i = 0; i < 4; ++i)
	{
		if (i == 1) continue;
		tuple6[i][1][0][1][1][1] = BLOCK4;
		tuple6[i][1][1][0][1][1] = BLOCK4;
		tuple6[i][1][1][1][0][1] = BLOCK4;
	}
	//黑活3
	tuple6[0][1][1][0][1][0] = FLEX3;
	tuple6[0][1][0][1][1][0] = FLEX3;
	for (int i = 0; i < 4; ++i)
	{
		if (i == 1) continue;
		tuple6[0][1][1][1][0][i] = FLEX3;
	}
	//黑眠3
	for (int i = 2; i <= 3; ++i)
	{
		tuple6[i][1][1][1][0][0] = BLOCK3;
		tuple6[i][1][1][0][1][0] = BLOCK3;
		tuple6[i][1][0][1][1][0] = BLOCK3;
		tuple6[0][1][0][1][1][i] = BLOCK3;
		tuple6[0][1][1][0][1][i] = BLOCK3;
		tuple6[0][0][1][1][1][i] = BLOCK3; //特例
	}
	for (int i = 0; i < 4; ++i)
	{
		if (i == 1) continue;
		tuple6[i][1][1][0][0][1] = BLOCK3;
		tuple6[i][1][0][0][1][1] = BLOCK3;
		tuple6[i][1][0][1][0][1] = BLOCK3;
	}
	//黑活2
	tuple6[0][1][0][0][1][0] = FLEX2;
	for (int i = 0; i < 4; ++i)
	{
		if (i == 1) continue;
		tuple6[0][1][0][1][0][i] = FLEX2;
	}
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			if (i == 1 || j == 1) continue;
			tuple6[0][1][1][0][i][j] = FLEX2;
		}
	//黑活1、眠2
	//黑眠2
	tuple6[2][1][1][0][0][0] = BLOCK2;
	//黑活1
	tuple6[0][1][0][0][0][0] = FLEX1;
	for (int i = 0; i < 4; ++i)
	{
		if (i == 1) continue;
		tuple6[i][0][1][0][0][0] = FLEX1;
		tuple6[i][0][0][1][0][0] = FLEX1;
		tuple6[i][0][0][0][1][0] = FLEX1;
		tuple6[i][0][0][0][0][1] = FLEX1;
	}

	//0空,1黑子,2白子,3边界
	//第0位非己方棋子，第1位己方棋子
	//白连5
	tuple6[0][2][2][2][2][2] = R_WIN;
	tuple6[1][2][2][2][2][2] = R_WIN;
	tuple6[3][2][2][2][2][2] = R_WIN;
	//白活4
	tuple6[0][2][2][2][2][0] = R_FLEX4;
	//白冲4
	tuple6[1][2][2][2][2][0] = R_BLOCK4;
	tuple6[3][2][2][2][2][0] = R_BLOCK4;
	tuple6[0][2][2][2][2][1] = R_BLOCK4;
	tuple6[0][2][2][2][2][3] = R_BLOCK4;
	for (int i = 0; i < 4; ++i)
	{
		if (i == 2) continue;
		tuple6[i][2][0][2][2][2] = R_BLOCK4;
		tuple6[i][2][2][0][2][2] = R_BLOCK4;
		tuple6[i][2][2][2][0][2] = R_BLOCK4;
	}
	//白活3
	tuple6[0][2][2][0][2][0] = R_FLEX3;
	tuple6[0][2][0][2][2][0] = R_FLEX3;
	for (int i = 0; i < 4; ++i)
	{
		if (i == 2) continue;
		tuple6[0][2][2][2][0][i] = R_FLEX3;
	}
	//白眠3
	for (int i = 1; i <= 3; ++i)
	{
		if (i == 2) continue;
		tuple6[i][2][2][2][0][0] = R_BLOCK3;
		tuple6[i][2][2][0][2][0] = R_BLOCK3;
		tuple6[i][2][0][2][2][0] = R_BLOCK3;
		tuple6[0][2][0][2][2][i] = R_BLOCK3;
		tuple6[0][2][2][0][2][i] = R_BLOCK3;
		tuple6[0][0][2][2][2][i] = R_BLOCK3; //特例
	}
	for (int i = 0; i < 4; ++i)
	{
		if (i == 2) continue;
		tuple6[i][2][2][0][0][2] = R_BLOCK3;
		tuple6[i][2][0][0][2][2] = R_BLOCK3;
		tuple6[i][2][0][2][0][2] = R_BLOCK3;
	}
	//白活2
	tuple6[0][2][0][0][2][0] = R_FLEX2;
	for (int i = 0; i < 4; ++i)
	{
		if (i == 2) continue;
		tuple6[0][2][0][2][0][i] = R_FLEX2;
	}
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			if (i == 2 || j == 2) continue;
			tuple6[0][2][2][0][i][j] = R_FLEX2;
		}
	//白活1、眠2
	//白眠2
	tuple6[1][2][2][0][0][0] = R_BLOCK2;
	//白活1
	tuple6[0][2][0][0][0][0] = R_FLEX1;
	for (int i = 0; i < 4; ++i)
	{
		if (i == 2) continue;
		tuple6[i][0][2][0][0][0] = R_FLEX1;
		tuple6[i][0][0][2][0][0] = R_FLEX1;
		tuple6[i][0][0][0][2][0] = R_FLEX1;
		tuple6[i][0][0][0][0][2] = R_FLEX1;
	}
}

FinishStatus GameTree::eva(const QVector<QVector<Role::role>>& board) {
	QVector<QVector<Role::role>> bigBoard;
	bigBoard.resize(tableSize + 2);
	for (size_t i = 0; i < tableSize + 2; ++i) {
		bigBoard[i].resize(tableSize + 2);
	}

	for (int i = 0; i < tableSize + 2; ++i) {
		bigBoard[i][0] = Role::BORDER;
		bigBoard[0][i] = Role::BORDER;
		bigBoard[i][tableSize + 1] = Role::BORDER;
		bigBoard[tableSize + 1][i] = Role::BORDER;
	}

	for (size_t i = 0; i < tableSize; ++i) {
		for (size_t j = 0; j < tableSize; ++j) {
			bigBoard[i + 1][j + 1] = board[i][j];
		}
	}
	FinishStatus status;
	status.score = 0;
	bool win = false, lose = false;
	int tmpScore;
	
	for (size_t i = 1; i < tableSize; ++i) {
		for (size_t j = 0; j < tableSize - 4; ++j) {
			tmpScore = tuple6[bigBoard[i][j]][bigBoard[i][j + 1]][bigBoard[i][j + 2]][bigBoard[i][j + 3]][bigBoard[i][j + 4]][bigBoard[i][j + 5]];
			status.score += tmpScore;
			if (tmpScore == WIN) {
				win = true;
			}
			else if (tmpScore == R_WIN) {
				lose = true;
			}
		}
	}

	for (size_t i = 0; i < tableSize - 4; ++i) {
		for (size_t j = 1; j < tableSize; ++j) {
			tmpScore = tuple6[bigBoard[i][j]][bigBoard[i + 1][j]][bigBoard[i + 2][j]][bigBoard[i + 3][j]][bigBoard[i + 4][j]][bigBoard[i + 5][j]];
			status.score += tmpScore;
			if (tmpScore == WIN) {
				win = true;
			}
			else if (tmpScore == R_WIN) {
				lose = true;
			}
		}
	}

	for (size_t i = 0; i < tableSize - 4; ++i) {
		for (size_t j = 0; j < tableSize - 4; ++j) {
			tmpScore = tuple6[bigBoard[i][j]][bigBoard[i + 1][j + 1]][bigBoard[i + 2][j + 2]][bigBoard[i + 3][j + 3]][bigBoard[i + 4][j + 4]][bigBoard[i + 5][j + 5]];
			status.score += tmpScore;
			if (tmpScore == WIN) {
				win = true;
			}
			else if (tmpScore == R_WIN) {
				lose = true;
			}
		}
	}

	for (size_t i = 0; i < tableSize - 4; ++i) {
		for (size_t j = tableSize + 1; j > 4; --j) {
			tmpScore = tuple6[bigBoard[i][j]][bigBoard[i + 1][j - 1]][bigBoard[i + 2][j - 2]][bigBoard[i + 3][j - 3]][bigBoard[i + 4][j - 4]][bigBoard[i + 5][j - 5]];
			status.score += tmpScore;
			if (tmpScore == WIN) {
				win = true;
			}
			else if (tmpScore == R_WIN) {
				lose = true;
			}
		}
	}

	if (win) {
		status.res = Result::win;
	}
	else if (lose) {
		status.res = Result::lose;
	}
	else
	{
		status.res = Result::draw;
	}
	
	return status;
}

best10 GameTree::chooseBest10(const QVector<QVector<Role::role>>& board) {
	best10 ans;
	
	QVector<QVector<Role::role>> tmpBoard;
	tmpBoard.resize(tableSize);
	for (size_t i = 0; i < tableSize; ++i) {
		tmpBoard[i].resize(tableSize);
	}

	for (size_t i = 0; i < tableSize; ++i) {
		for (size_t j = 0; j < tableSize; ++j) {
			tmpBoard[i][j] = board[i][j];
		}
	}

	std::priority_queue<myPoint> qu;
	for (size_t i = 0; i < tableSize; ++i) {
		for (size_t j = 0; j < tableSize; ++j) {
			if (tmpBoard[i][j] != Role::ROLE_NONE) { 
				continue; 
			}
			tmpBoard[i][j] = Role::ROLE_WHITE;
			QPair<size_t, size_t> tmp = QPair<size_t, size_t>(i, j);
			myPoint tmpPoint;
			tmpPoint.p = tmp;
			tmpPoint.score = eva(tmpBoard).score;
			qu.push(tmpPoint);
			tmpBoard[i][j] = Role::ROLE_NONE;
		}
	}

	for (int i = 0; i < 10; ++i) {
		if (qu.empty()) break;
		ans.pos[i] = qu.top().p;
		ans.score[i] = qu.top().score;
		qu.pop();
	}

	return ans;
}

int GameTree::dfs(const QVector<QVector<Role::role>>& board, 
	size_t depth, int alpha, int beta) {
	FinishStatus status = eva(board);

	if (depth == MAX_DEPTH || status.res != Result::draw) {
		++nodenum;
		if (depth == MAX_DEPTH) {
			best10 tmp = chooseBest10(board);
			return tmp.score[0];
		}
		return status.score;
	}

	if (depth % 2 == 0) {
		best10 tmp = chooseBest10(board);
		for (int i = 0; i < 10; ++i) {
			QVector<QVector<Role::role>> tmpBoard;
			tmpBoard.resize(tableSize);
			for (size_t i = 0; i < tableSize; ++i) {
				tmpBoard[i].resize(tableSize);
			}

			for (size_t i = 0; i < tableSize; ++i) {
				for (size_t j = 0; j < tableSize; ++j) {
					tmpBoard[i][j] = board[i][j];
				}
			}
			
			tmpBoard[tmp.pos[i].first][tmp.pos[i].second] = Role::ROLE_WHITE;
			int a = dfs(tmpBoard, depth + 1, alpha, beta);
			if (a > alpha) {
				alpha = a;
				if (depth == 0) {
					nextpos.first = tmp.pos[i].first;
					nextpos.second = tmp.pos[i].second;
				}
			}
			if (alpha >= beta) {
				break;
			}
		}
		return alpha;
	}
	else {
		QVector<QVector<Role::role>> reversetmpBoard;
		reversetmpBoard.resize(tableSize);
		for (size_t i = 0; i < tableSize; ++i) {
			reversetmpBoard[i].resize(tableSize);
		}

		for (size_t i = 0; i < tableSize; ++i) {
			for (size_t j = 0; j < tableSize; ++j) {
				if (board[i][j] == Role::ROLE_WHITE) {
					reversetmpBoard[i][j] = Role::ROLE_BLACK;
				}
				else if (board[i][j] == Role::ROLE_BLACK) {
					reversetmpBoard[i][j] = Role::ROLE_WHITE;
				}
				else {
					reversetmpBoard[i][j] = Role::ROLE_NONE;
				}
			}
		}

		best10 tmp = chooseBest10(reversetmpBoard);
		for (size_t i = 0; i < 10; ++i) {
			QVector<QVector<Role::role>> tmpBoard;
			tmpBoard.resize(tableSize);
			for (size_t i = 0; i < tableSize; ++i) {
				tmpBoard[i].resize(tableSize);
			}

			for (size_t i = 0; i < tableSize; ++i) {
				for (size_t j = 0; j < tableSize; ++j) {
					tmpBoard[i][j] = board[i][j];
				}
			}

			tmpBoard[tmp.pos[i].first][tmp.pos[i].second] = Role::ROLE_BLACK;
			beta = std::min(dfs(tmpBoard, depth + 1, alpha, beta), beta);
			if (alpha >= beta) {
				break;
			}
		}
		return beta;
	}
}