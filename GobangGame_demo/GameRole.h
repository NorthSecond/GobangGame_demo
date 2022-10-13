#pragma once

constexpr size_t tableSize = 20U;
constexpr size_t UNIT_SIZE = 48U;
constexpr size_t CHESSVIEW_SIZE = UNIT_SIZE * tableSize + 40;

namespace Role {
	// roles in game
	typedef int role;
	// 0: empty
	constexpr int ROLE_NONE = 0;
	// 1: black
	constexpr int ROLE_BLACK = 1;
	// 2: white
	constexpr int ROLE_WHITE = 2;
	// 3: border for AI
	constexpr int BORDER = 3;
};

// defined values when using AI.

// ËÑË÷4²ã
constexpr int MAX_DEPTH = 4;

constexpr int R_WIN = 5000000;
constexpr int R_FLEX4 = 50000;
constexpr int R_BLOCK4 = 400;
constexpr int R_FLEX3 = 400;
constexpr int R_BLOCK3 = 20;
constexpr int R_FLEX2 = 20;
constexpr int R_BLOCK2 = 1;
constexpr int R_FLEX1 = 1;

constexpr int WIN = -10000000;
constexpr int FLEX4 = -100000;
constexpr int BLOCK4 = -100000;
constexpr int FLEX3 = -8000;
constexpr int BLOCK3 = -50;
constexpr int FLEX2 = -50;
constexpr int BLOCK2 = -3;
constexpr int FLEX1 = -3;