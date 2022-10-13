#include "PlayWidget.h"

// FIXME: 不行了搞个坐标转换函数吧

PlayWidget::PlayWidget(bool isPVP, QWidget* parent)
	: QWidget(parent)/*, searcher()*/, tree()
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

	// 侦测鼠标事件
	setMouseTracking(false); // 代码还没完全完善

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

void PlayWidget::mouseMoveEvent(QMouseEvent* e)
{
	size_t x_pos = e->pos().x();
	size_t y_pos = e->pos().y();
	x_pos -= 20;
	y_pos -= 20;
	QPainter painter(this);
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

	if (turns == Role::ROLE_BLACK) {
		painter.setBrush(QBrush(QColor(Qt::black)));
		painter.setPen(QPen(QColor(Qt::black)));
		painter.drawEllipse(QPoint(x_index * UNIT_SIZE + 20, y_index * UNIT_SIZE + 20), chSize, chSize);
	}
	else {
		painter.setBrush(QBrush(QColor(Qt::black)));
		painter.setPen(QPen(QColor(Qt::white)));
		painter.drawEllipse(QPoint(x_index * UNIT_SIZE + 20, y_index * UNIT_SIZE + 20), chSize, chSize);
	}

	update();
}

void PlayWidget::drawBoard() {
	QPainter painter(this);
	// 高质量采样
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::TextAntialiasing, true);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
	painter.setRenderHint(QPainter::Antialiasing, true);

	// color: Burlywood
	painter.setBrush(QBrush(QColor("#DEB887"), Qt::SolidPattern));
	painter.drawRect(0, 0, CHESSVIEW_SIZE, CHESSVIEW_SIZE);

	// lines
	painter.setPen(QPen(QColor(Qt::black), 2));
	// FIXME: 四周留一点空隙出来可能会好看一点
	for (size_t i = 0; i <= tableSize; i++)
	{
		painter.drawLine(20, i * UNIT_SIZE + 20, CHESSVIEW_SIZE - 20, i * UNIT_SIZE + 20);
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
	for (size_t i = 0; i < tableSize; i++)
	{
		for (size_t j = 0; j < tableSize; j++)
		{
			if (nowTable[i][j] == Role::ROLE_BLACK)
			{
				painter.setBrush(QBrush(QColor(Qt::black)));
				painter.setPen(QPen(QColor(Qt::black)));
				painter.drawEllipse(QPoint(i * UNIT_SIZE + 20, j * UNIT_SIZE + 20), chSize, chSize);
			}
			else if (nowTable[i][j] == Role::ROLE_WHITE)
			{
				painter.setBrush(QBrush(QColor(Qt::white)));
				painter.setPen(QPen(QColor(Qt::white)));
				painter.drawEllipse(QPoint(i * UNIT_SIZE + 20, j * UNIT_SIZE + 20), chSize, chSize);
			}
		}
	}
}

void PlayWidget::mousePressEvent(QMouseEvent* e) {
	if (e->button() != Qt::LeftButton) { // 右键
		//// 先写重开试一下
		//table.startGame();
		//turns = Role::ROLE_BLACK; // 重开后先手黑棋

		if (!table.canRegret()) {
			QMessageBox::information(this, QString("Can't regret!"), QString("No pawns to regret!"));
			return;
		}
		
		// 悔棋
		if (table.getGameType() == PVP) {
			// PVP 悔棋一次
			table.regret();
			if (turns == Role::ROLE_BLACK) {
				turns = Role::ROLE_WHITE;
			}
			else {
				turns = Role::ROLE_BLACK;
			}
		}
		else {
			// PVE 悔棋两次
			table.regret();
			table.regret();
			turns = Role::ROLE_BLACK;
		}
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
	//update();

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
		// 暂时只支持后手下
		//QPair<size_t, size_t> actPos = searcher.search(table.getTable(), Role::ROLE_WHITE);
		//table.act(Role::ROLE_WHITE, actPos.first, actPos.second);
		tree.nodenum = 0;
		tree.dfs(table.getTable(), 0, INT_MIN, INT_MAX);
		QPair<size_t, size_t> actPos = tree.nextpos;
		table.act(Role::ROLE_WHITE, actPos.first, actPos.second);
	}
}
