#include "PlayWidget.h"

// FIXME: 不行了搞个坐标转换函数吧

PlayWidget::PlayWidget(bool isPVP, QWidget* parent)
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
	for (size_t i = 0; i <= tableSize; i++)
	{
		painter.drawLine(20, i * UNIT_SIZE + 20, CHESSVIEW_SIZE - 20 , i * UNIT_SIZE + 20);
		painter.drawLine(i * UNIT_SIZE + 20, 20, i * UNIT_SIZE + 20, CHESSVIEW_SIZE - 20);
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
	size_t chSize = UNIT_SIZE / 3;
	for (size_t i = 0; i < tableSize; i++)
	{
		for (size_t j = 0; j < tableSize; j++)
		{
			if (nowTable[i][j] == Role::ROLE_BLACK)
			{
				painter.setBrush(QBrush(QColor(Qt::black)));
				painter.drawEllipse(QPoint(i * UNIT_SIZE + 20, j * UNIT_SIZE + 20), chSize, chSize);
			}
			else if (nowTable[i][j] == Role::ROLE_WHITE)
			{
				painter.setBrush(QBrush(QColor(Qt::white)));
				painter.drawEllipse(QPoint(i * UNIT_SIZE + 20, j * UNIT_SIZE + 20), chSize, chSize);
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
	if (x_pos < 20 || x_pos > CHESSVIEW_SIZE - 20 || y_pos < 20 || y_pos > CHESSVIEW_SIZE - 20) {
		return;
	}
	x_pos -= 20;
	y_pos -= 20;
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
		if (turns == Role::ROLE_BLACK) {
			turns = Role::ROLE_WHITE;
		}
		else {
			turns = Role::ROLE_BLACK;
		}
	}
	else { // PVE
		// TODO: AI
	}
}