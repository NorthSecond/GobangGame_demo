#include "PlayWidget.h"

PlayWidget::PlayWidget(bool isPVP, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	table = GameTable(this, isPVP);
	
	// set title
	// FIXME: VS 保存文件编码问题
	setWindowTitle(isPVP ? QString("PVP") : QString("PVE"));
	
	// 写死大小
	resize(CHESSVIEW_SIZE, CHESSVIEW_SIZE);
	setFixedSize(CHESSVIEW_SIZE, CHESSVIEW_SIZE);
	setMaximumSize(CHESSVIEW_SIZE, CHESSVIEW_SIZE);
	setMinimumSize(CHESSVIEW_SIZE, CHESSVIEW_SIZE);

	turns = Role::ROLE_BLACK;
	drawBoard();
}

PlayWidget::~PlayWidget()
{}

void PlayWidget::paintEvent(QPaintEvent* e) {
	drawBoard();
	drawPieces();

	update();
}

void PlayWidget::drawBoard() {
	QPainter painter(this);
	// 高质量采样
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::TextAntialiasing, true);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
	painter.setRenderHint(QPainter::Antialiasing, true);

	// color: Burlywood2
	painter.setBrush(QBrush(QColor("#DEB887"), Qt::SolidPattern));
	painter.drawRect(0, 0, CHESSVIEW_SIZE, CHESSVIEW_SIZE);

	// lines
	painter.setPen(QPen(QColor(Qt::black), 2));
	// FIXME: 四周留一点空隙出来可能会好看一点
	for (size_t i = 0; i < tableSize; i++)
	{
		painter.drawLine(0, i * UNIT_SIZE, CHESSVIEW_SIZE, i * UNIT_SIZE);
		painter.drawLine(i * UNIT_SIZE, 0, i * UNIT_SIZE, CHESSVIEW_SIZE);
	}
	update();
}

void PlayWidget::drawPieces()
{
	QPainter painter(this);

	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::TextAntialiasing, true);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
	painter.setRenderHint(QPainter::Antialiasing, true);
	
	QVector<QVector<Role::role>> nowTable = table.getTable();
	
	// TODO: 棋子添加渐变
	for (size_t i = 0; i < tableSize; i++)
	{
		for (size_t j = 0; j < tableSize; j++)
		{
			if (nowTable[i][j] == Role::ROLE_BLACK)
			{
				painter.setBrush(QBrush(QColor(Qt::black)));
				painter.drawEllipse(i * UNIT_SIZE + 5, j * UNIT_SIZE + 5, UNIT_SIZE - 10, UNIT_SIZE - 10);
			}
			else if (nowTable[i][j] == Role::ROLE_WHITE)
			{
				painter.setBrush(QBrush(QColor(Qt::white)));
				painter.drawEllipse(i * UNIT_SIZE + 5, j * UNIT_SIZE + 5, UNIT_SIZE - 10, UNIT_SIZE - 10);
			}
		}
	}
}

void PlayWidget::mousePressEvent(QMouseEvent* e) {
	if (e->button() != Qt::LeftButton) { // 右键是用不到的
		return;
	}
	
	// Get mouse position
	size_t x_pos = e->pos().x();
	size_t y_pos = e->pos().y();
	// if wrong position
	if (x_pos < 0 || x_pos > CHESSVIEW_SIZE || y_pos < 0 || y_pos > CHESSVIEW_SIZE)
		return;
	// Get index
	size_t x_index, y_index;
	if ((x_pos % UNIT_SIZE) < (UNIT_SIZE / 2)) {
		x_index = x_pos / UNIT_SIZE;
	}
	else {
		x_index = x_pos / UNIT_SIZE + 1;
	}
	if ((y_pos % UNIT_SIZE) < (UNIT_SIZE / 2)) {
		y_index = y_pos / UNIT_SIZE;
	}
	else {
		y_index = y_pos / UNIT_SIZE + 1;
	}
	table.act(turns, x_index, y_index);
	
	if (table.getGameType() == PVP) { // PVP
		
	}
	else { // PVE
		
	}
}