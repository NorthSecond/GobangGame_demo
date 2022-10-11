#pragma once

#include <QWidget>
#include <QMouseEvent>

#include "ui_PlayWidget.h"
#include "GameTable.h"
#include "GameTree.h"

class PlayWidget : public QWidget
{
	Q_OBJECT

public:
	PlayWidget(bool isPVP, QWidget *parent = nullptr);
	~PlayWidget();
	//void drawStatus();

protected:
	void mousePressEvent(QMouseEvent* e);
	void paintEvent(QPaintEvent* e);
	void mouseMoveEvent(QMouseEvent* e);
	
private:
	Ui::PlayWidgetClass ui;
	GameTable table;
	void drawBoard();
	void drawPieces();
	Role::role turns;
	const static size_t chSize = UNIT_SIZE / 3;

public slots:
};
