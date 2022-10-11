#include "GobangGame_demo.h"

GobangGame_demo::GobangGame_demo(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setStyleSheet("background-color:white");
	this->setFixedSize(600, 200);
	
	titleLabel = new QLabel(this);
	titleLabel->setText("Gobang Game");
	titleLabel->setGeometry(32, 32, 255, 32);
	titleLabel->setAlignment(Qt::AlignCenter);
	titleLabel->setStyleSheet("QLabel{background-color:rgb(255,255,255);color:rgb(0,0,0);font-size:20px;font-weight:bold;font-family:Arial;}");
	titleLabel->show();

	authorLabel = new QLabel(this);
	authorLabel->setText("Author: yangyf83");
	authorLabel->setGeometry(32, 64, 255, 32);
	authorLabel->setAlignment(Qt::AlignCenter);
	authorLabel->setStyleSheet("background-color:rgb(255,255,255);color:rgb(0,0,0);font-size:14px;font-weight:bold;font-family:Arial;}");
	authorLabel->show();

	PVPbtn = new QPushButton(this);
	PVPbtn->setText("PVP");
	PVPbtn->setGeometry(320, 120, 240, 32);
	PVPbtn->setStyleSheet("border:2px solid #000000; border-radius:10px;text-decoration:underline;font-size:14px;"
		"font - weight:bold; font - family:Arial; ");

	PVEbtn = new QPushButton(this);
	PVEbtn->setText("PVE");
	PVEbtn->setGeometry(320, 160, 240, 32);
	PVEbtn->setStyleSheet("border:2px solid #000000; border-radius:10px;text-decoration:underline;font-size:14px;"
		"font  -weight:bol d;f  ont-family:A rial;");

	connect(PVPbtn, &QPushButton::clicked, this, &GobangGame_demo::createPVP);
	connect(PVEbtn, &QPushButton::clicked, this, &GobangGame_demo::createPVE);
	//initGameTable(false);
}

GobangGame_demo::~GobangGame_demo()
{
	delete titleLabel;
	delete authorLabel;
	delete PVPbtn;
	delete PVEbtn;
	if (playWidget != nullptr) {
		delete playWidget;
	}
}

void GobangGame_demo::initGameTable(bool isPVP)
{
	playWidget = new PlayWidget(isPVP);
	playWidget->show();
	this->hide();
}

void GobangGame_demo::createPVP() {
	initGameTable(true);
}

void GobangGame_demo::createPVE()
{
	initGameTable(false);
}