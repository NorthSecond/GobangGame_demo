#pragma once

#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QMessageBox>

#include "GameTable.h"
#include "ui_GobangGame_demo.h"
#include "PlayWidget.h"

class GobangGame_demo : public QMainWindow
{
    Q_OBJECT
        
public:
    GobangGame_demo(QWidget *parent = nullptr);
    ~GobangGame_demo();
    QWidget* playWidget = nullptr;    
private:
    Ui::GobangGame_demoClass ui;
    QLabel* titleLabel;
    QLabel* authorLabel;
    QPushButton* PVPbtn;
    QPushButton* PVEbtn;
    void initGameTable(bool isPVP);
    /*GameTable table;*/

public slots:
    void createPVP();
    void createPVE();
};
