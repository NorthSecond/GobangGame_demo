#pragma once

// The const values used in controling the size of the game view.
constexpr size_t tableSize = 20U; // The number of the rows and lines used in table
constexpr size_t UNIT_SIZE = 48U; // The size of a unit
// The size of the game view
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
	// 3: border value used in AI
	constexpr int BORDER = 3;
};