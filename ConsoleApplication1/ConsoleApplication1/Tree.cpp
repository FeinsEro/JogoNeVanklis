#include "Tree.hpp"


Character* Tree::Clone(unsigned int x, unsigned int y) {
	Tree* t = new Tree(*this);
	t->SetPosition(x, y);
	t->_ID = t->lastID++;

	return t;
}