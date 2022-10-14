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
	// ����
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

	// ����
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

	// ��б��
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

	// ��б��
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
	// ���ﲻ�����ˣ�����һ�¸��Ӷ�
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
	// �����������
	if (x < 0 || x > tableSize - 1 || y < 0 || y > tableSize - 1)
	{
		return false;
	}
	
	// �����������
	if (table[x][y] != 0)
	{
		return false;
	}
	
	// д��stack�У����ڻ���
	// TODO: ����PVE���߳̿���Stack���̰߳�ȫ������
	Node_action node;
	node.x = x;
	node.y = y;
	node.role = role;
	actionStack.push(node);
	
	// ����
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
	// ˢ�»������״̬
	return flushGameStatus();
}

void GameTable::endGame()
{
	// FIXME: VS �����ļ���������
	// msgbox ֱ�ӵ������в���
	switch (gameStatus)
	{
	case BLACK_WIN:
		if (gameType == PVP)
		{
			QMessageBox::information(parent, QString("Game Over"), QString("Black wins!"));
			//QMessageBox::information(parent, QString("��Ϸ����"), QString("����ʤ��"));
		}
		else
		{
			QMessageBox::information(parent, QString("Game Over"), QString("You win!"));
			//QMessageBox::information(parent, QString("��Ϸ����"), QString("��Ӯ��"));
		}
		break;
	case WHITE_WIN:
		if (gameType == PVP) {
			QMessageBox::information(parent, QString("Game Over"), QString("White wins!"));
			//QMessageBox::information(parent, QString("��Ϸ����"), QString("����ʤ��"));
		}
		else {
			QMessageBox::information(parent, QString("Game Over"), QString("You lose!"));
			//QMessageBox::information(parent, QString("��Ϸ����"), QString("������"));
		}
		break;
	case DRAW:
		QMessageBox::information(parent, QString("Game Over"), QString("Draw!"));
		//QMessageBox::information(parent, QString("��Ϸ����"), QString("ƽ��"));
		break;
	default:
		break;
	}
	parent->close();
	exit(0);
}

// �޸���һЩ�������ע����Ϣ
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

// �Ƿ���Ի���
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