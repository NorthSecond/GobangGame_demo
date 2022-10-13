#pragma once

#include <QVector>
#include <QStack>
#include <Qwidget>
#include <QPainter>
#include <QColor>
#include <QMouseEvent>
#include <QMessagebox>

#include "GameRole.h"
#include "Piece.h"

enum GameType {
	PVP,
	PVE
};

enum GameStatus
{
	PLAYING,
	BLACK_WIN,
	WHITE_WIN,
	DRAW
};

typedef struct {
	size_t x;
	size_t y;
	Role::role role;
} Node_action;

class GameTable
{
private:
	QVector<QVector<Role::role>> table;
	QWidget* parent;
	GameType gameType;
	GameStatus gameStatus;
	unsigned int blackCount;
	unsigned int whiteCount;
	QStack<Node_action> actionStack;
	
	void initGame();
	
public:
	GameTable(QWidget* parent = nullptr, bool isPVP = false); 
	~GameTable();

	GameStatus getNewStatus();
	void startGame();
	bool act(Role::role role, int x, int y);
	void endGame();

	bool flushGameStatus();
	GameStatus getGameStatus();
	void setGameType(GameType type);
	GameType getGameType();
	QVector<QVector<Role::role>> getTable();
	bool canRegret();
	void regret();

	//unsigned int getBlackCount();
	//unsigned int getWhiteCount();
};
