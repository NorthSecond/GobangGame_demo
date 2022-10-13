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

bool Piece::operator==(const Piece& pieces)
{
	return (role == pieces.role && position == pieces.position);
}