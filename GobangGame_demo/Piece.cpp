#include "Piece.h"

Piece::Piece(Role::role role, QPoint position)
	:role(role), position(position){}

Piece::~Piece() {
	
}

Role::role Piece::getRole()
{
	return role;
}

QPoint Piece::getPosition()
{
	return position;
}
