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
};

