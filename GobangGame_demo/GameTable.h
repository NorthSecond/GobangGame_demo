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

/**
The core class of the game. 
It cantains the game logic and the game's status.
*/
class GameTable
{
private:
	QVector<QVector<Role::role>> table;
	QWidget* parent;
	GameType gameType;
	GameStatus gameStatus;
	unsigned int blackCount;
	unsigned int whiteCount;
	// The stack used to record the actions of the game.
	// Used in regret function.
	QStack<Node_action> actionStack;
	
	void initGame();
	void setGameType(GameType type);
	
	bool flushGameStatus();
	GameStatus getNewStatus();
	
	void startGame();
	void endGame();
	
public:
	GameTable(QWidget* parent = nullptr, bool isPVP = false); 
	~GameTable();

	bool act(Role::role role, int x, int y);

	GameStatus getGameStatus();
	GameType getGameType();
	QVector<QVector<Role::role>> getTable();

	// Functions about regret
	bool canRegret();
	void regret();

	//unsigned int getBlackCount();
	//unsigned int getWhiteCount();
};
