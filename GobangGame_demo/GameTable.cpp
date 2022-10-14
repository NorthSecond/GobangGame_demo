#include "GameTable.h"

GameTable::GameTable(QWidget* parent, bool isPVP)
	: parent(parent)
{
	setGameType(isPVP ? GameType::PVP : GameType::PVE);
	initGame();
}

GameTable::~GameTable()
{

}

GameStatus GameTable::getNewStatus() {
	// if someone wins
	// 横向
	for (size_t i = 0; i < tableSize; ++i) {
		for (size_t j = 0; j < tableSize - 4; j++)
		{
			if (table[i][j] != Role::ROLE_NONE && table[i][j] == table[i][j + 1] &&
				table[i][j] == table[i][j + 2] && table[i][j] == table[i][j + 3] && table[i][j] == table[i][j + 4])
			{
				if (table[i][j] == Role::ROLE_BLACK)
				{
					return BLACK_WIN;
				}
				else
				{
					return WHITE_WIN;
				}
			}
		}
	}

	// 纵向
	for (size_t i = 0; i < tableSize - 4; ++i)
	{
		for (size_t j = 0; j < tableSize; j++)
		{
			if (table[i][j] != Role::ROLE_NONE && table[i][j] == table[i + 1][j] &&
				table[i][j] == table[i + 2][j] && table[i][j] == table[i + 3][j] && table[i][j] == table[i + 4][j])
			{
				if (table[i][j] == Role::ROLE_BLACK)
				{
					return BLACK_WIN;
				}
				else
				{
					return WHITE_WIN;
				}
			}
		}
	}

	// 右斜向
	for (size_t i = 0; i < tableSize - 4; ++i)
	{
		for (size_t j = 0; j < tableSize - 4; j++)
		{
			if (table[i][j] != Role::ROLE_NONE && table[i][j] == table[i + 1][j + 1] &&
				table[i][j] == table[i + 2][j + 2] && table[i][j] == table[i + 3][j + 3] && table[i][j] == table[i + 4][j + 4])
			{
				if (table[i][j] == Role::ROLE_BLACK)
				{
					return BLACK_WIN;
				}
				else
				{
					return WHITE_WIN;
				}
			}
		}
	}

	// 左斜向
	for (size_t i = 0; i < tableSize - 4; ++i)
	{
		for (size_t j = 4; j < tableSize; j++)
		{
			if (table[i][j] != Role::ROLE_NONE && table[i][j] == table[i + 1][j - 1] &&
				table[i][j] == table[i + 2][j - 2] && table[i][j] == table[i + 3][j - 3] && table[i][j] == table[i + 4][j - 4])
			{
				if (table[i][j] == Role::ROLE_BLACK)
				{
					return BLACK_WIN;
				}
				else
				{
					return WHITE_WIN;
				}
			}
		}
	}
	// Draw
	// 这里不遍历了，降低一下复杂度
	if (blackCount + whiteCount == tableSize * tableSize) {
		return DRAW;
	}
	return PLAYING;
}

void GameTable::initGame()
{
	// init table
	table.resize(tableSize);
	for (int i = 0; i < tableSize; i++)
	{
		table[i].resize(tableSize);
		for (int j = 0; j < tableSize; j++)
		{
			table[i][j] = 0;
		}
	}
	// init game status
	gameStatus = PLAYING;
	blackCount = 0;
	whiteCount = 0;
}

void GameTable::startGame()
{
	// abstruct.
	initGame();
}

bool GameTable::act(Role::role role, int x, int y)
{
	// 落点在棋盘外
	if (x < 0 || x > tableSize - 1 || y < 0 || y > tableSize - 1)
	{
		return false;
	}
	
	// 落点已有棋子
	if (table[x][y] != 0)
	{
		return false;
	}
	
	// 写入stack中，用于悔棋
	// TODO: 后期PVE多线程考虑Stack的线程安全和有序！
	Node_action node;
	node.x = x;
	node.y = y;
	node.role = role;
	actionStack.push(node);
	
	// 落子
	table[x][y] = role;
	if (role == Role::ROLE_BLACK)
	{
		blackCount++;
	}
	else if (role == Role::ROLE_WHITE)
	{
		whiteCount++;
	}
	else
	{
		return false;
	}
	// 刷新获得最新状态
	return flushGameStatus();
}

void GameTable::endGame()
{
	// FIXME: VS 保存文件编码问题
	// msgbox 直接弹看看行不行
	switch (gameStatus)
	{
	case BLACK_WIN:
		if (gameType == PVP)
		{
			QMessageBox::information(parent, QString("Game Over"), QString("Black wins!"));
			//QMessageBox::information(parent, QString("游戏结束"), QString("黑棋胜利"));
		}
		else
		{
			QMessageBox::information(parent, QString("Game Over"), QString("You win!"));
			//QMessageBox::information(parent, QString("游戏结束"), QString("你赢了"));
		}
		break;
	case WHITE_WIN:
		if (gameType == PVP) {
			QMessageBox::information(parent, QString("Game Over"), QString("White wins!"));
			//QMessageBox::information(parent, QString("游戏结束"), QString("白棋胜利"));
		}
		else {
			QMessageBox::information(parent, QString("Game Over"), QString("You lose!"));
			//QMessageBox::information(parent, QString("游戏结束"), QString("你输了"));
		}
		break;
	case DRAW:
		QMessageBox::information(parent, QString("Game Over"), QString("Draw!"));
		//QMessageBox::information(parent, QString("游戏结束"), QString("平局"));
		break;
	default:
		break;
	}
	parent->close();
	exit(0);
}

// 修复了一些不合理的注释信息
bool GameTable::flushGameStatus()
{
	gameStatus = getNewStatus();
	if (gameStatus != PLAYING)
	{
		endGame();
		return false;
	}
	return true;
}

GameStatus GameTable::getGameStatus()
{
	return gameStatus;
}

GameType GameTable::getGameType()
{
	return gameType;
}

void GameTable::setGameType(GameType type)
{
	gameType = type;
}

QVector<QVector<int>> GameTable::getTable()
{
	return table;
}

//unsigned int GameTable::getBlackCount()
//{
//	return blackCount;
//}
//
//unsigned int GameTable::getWhiteCount()
//{
//	return whiteCount;
//}

// 是否可以悔棋
bool GameTable::canRegret() {
	return blackCount + whiteCount > 0;
}

void GameTable::regret() {
	// pop the last action from stack
	if (actionStack.isEmpty()) {
		return;
	}
	Node_action node = actionStack.top();
	actionStack.pop();
	
	// remove the chess
	table[node.x][node.y] = Role::ROLE_NONE;
	if (node.role == Role::ROLE_BLACK)
	{
		blackCount--;
	}
	else if (node.role == Role::ROLE_WHITE)
	{
		whiteCount--;
	}
	
	flushGameStatus();
}