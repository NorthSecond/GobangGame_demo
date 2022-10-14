#pragma once

#include <QPoint>
#include <QPair>

#include "GameRole.h"

class Piece
{
private:
	Role::role role;
	QPair<size_t, size_t> position;
public:
	Piece(Role::role role, QPair<size_t, size_t> position);
	~Piece();

	Role::role getRole();
	QPair<size_t, size_t> getPosition();
	
	bool operator==(const Piece& pieces);
};
