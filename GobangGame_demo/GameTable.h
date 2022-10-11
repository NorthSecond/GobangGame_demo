#pragma once

#include <QVector>
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

class GameTable
{
private:
	QVector<QVector<Role::role>> table;
	QWidget* parent;
	GameType gameType;
	GameStatus gameStatus;
	unsigned int blackCount;
	unsigned int whiteCount;
	
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

	//unsigned int getBlackCount();
	//unsigned int getWhiteCount();
};

