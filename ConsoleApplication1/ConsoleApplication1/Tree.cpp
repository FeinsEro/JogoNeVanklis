#include "Tree.hpp"


Character* Tree::Clone(float x, float y) {
	Tree* t = new Tree(*this);
	t->SetPosition(x, y);
	t->_ID = t->lastID++;

	return t;
}