#include "Piece.h"

Piece::Piece(Role::role role, QPair<size_t, size_t> position)
	:role(role), position(position){}

Piece::~Piece() {
	
}

Role::role Piece::getRole()
{
	return role;
}

QPair<size_t, size_t> Piece::getPosition()
{
	return position;
}

bool Piece::operator==(const Piece& pieces)
{
	return (role == pieces.role && position == pieces.position);
}