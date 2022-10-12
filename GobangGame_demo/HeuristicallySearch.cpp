#include "HeuristicallySearch.h"

HeuristicallySearch::HeuristicallySearch()
{
	score.resize(tableSize);
	for (size_t i = 0; i < tableSize; i++) {
		score[i].resize(tableSize);
	}

	for (size_t i = 0; i < tableSize; i++) {
		for (size_t j = 0; j < tableSize; j++) {
			score[i][j] = 0;
		}
	}
}

HeuristicallySearch::~HeuristicallySearch()
{
}

void HeuristicallySearch::flushScore() {
	for (size_t i = 0; i < tableSize; i++) {
		for (size_t j = 0; j < tableSize; j++) {
			score[i][j] = 0;
		}
	}
}

QPair<size_t, size_t> HeuristicallySearch::search(QVector<QVector<Role::role>> table, Role::role role) {
	size_t maxScore = evaluate(table, role);
	QVector<QPair<size_t, size_t>> maxPoints;
	// 遍历所有空白位置，求出最高分的位置
	for (size_t i = 0; i < tableSize; ++i) {
		for (size_t j = 0; j < tableSize; ++j) {
			if (table[i][j] == Role::ROLE_NONE && score[i][j] == maxScore) {
				maxPoints.push_back(QPair<size_t, size_t>(i, j));
			}
		}
	}

	// randomly chose a point in the QVector
	QRandomGenerator generator;
	int index = generator.bounded(0, maxPoints.size());
	return maxPoints[index];
}

size_t HeuristicallySearch::evaluate(QVector<QVector<Role::role>> table, Role::role role)
{
	Role::role enemy = role == Role::ROLE_WHITE ? Role::ROLE_BLACK : Role::ROLE_WHITE;
	// flush score
	flushScore();
	size_t nowScore = 0, maxScore = 0;
	size_t myCount, enemyCount, emptyCount;
	for (size_t i = 0; i < tableSize; ++i) {
		for (size_t j = 0; j < tableSize; ++j) {
			// only evaluate empty points
			if (table[i][j] != Role::ROLE_NONE) {
				continue;
			}
			nowScore = 0;
			// evaluate the point in eight directions
			for (int x = -1; x <= 1; ++x) {
				for (int y = -1; y <= 1; ++y) {
					if (x == 0 && y == 0) {
						continue;
					}
					myCount = 0;
					enemyCount = 0;
					emptyCount = 0;
					// evaluate the point in the direction
					for (int k = 1; k < 5; ++k) {
						// out of range
						if (i + x * k < 0 || i + x * k >= tableSize
							|| j + y * k < 0 || j + y * k >= tableSize) {
							break;
						}
						if (table[i + x * k][j + y * k] == role) {
							myCount++;
						}
						else if (table[i + x * k][j + y * k] == enemy) {
							enemyCount++;
						}
						else {
							emptyCount++;
						}
					}

					for (int k = 1; k < 5; ++k) {
						// out of range
						if (i - x * k < 0 || i - x * k >= tableSize
							|| j - y * k < 0 || j - y * k >= tableSize) {
							break;
						}
						if (table[i - x * k][j - y * k] == role) {
							myCount++;
						}
						else if (table[i - x * k][j - y * k] == enemy) {
							enemyCount++;
						}
						else {
							emptyCount++;
						}
					}

					// evaluate the score
					switch (myCount)
					{
					case 0: // no chess
						nowScore += 5;
						break;
					case 1: // one chess
						nowScore += 10;
						break;
					case 2: // two chess
						if (emptyCount == 1) {
							nowScore += 35;
						}
						else {
							nowScore += 60;
						}
						break;
					case 3: // three chess
						if (emptyCount == 1) {
							nowScore += 75;
						}
						else {
							nowScore += 100;
						}
						break;
					case 4: // four chess
						nowScore += 1000;
						break;
					default:
						nowScore += 2500;
						break;
					}

					switch (enemyCount)
					{
					case 0: // no chess
						break;
					case 1: // one chess
						nowScore += 20;
						break;
					case 2: // two chess
						if (emptyCount == 1) {
							nowScore += 100;
						}
						else {
							nowScore += 145;
						}
						break;
					case 3: // three chess
						if (emptyCount == 1) {
							nowScore += 200;
						}
						else {
							nowScore += 500;
						}
						break;
					case 4: // four chess
						nowScore += 1000;
						break;
					default:
						nowScore += 3000;
						break;
					}
				}
			}
			score[i][j] = nowScore;
			if (nowScore > maxScore) {
				maxScore = nowScore;
			}
		}
	}
	return maxScore;
}
