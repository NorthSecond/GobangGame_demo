#pragma once

#include <QPoint>

#include "GameRole.h"

class Piece
{
private:
	Role::role role;
	QPoint position;
public:
	Piece(Role::role role, QPoint position);
	~Piece();

	Role::role getRole();
	QPoint getPosition();
	
	bool operator==(const Piece& pieces);
};
