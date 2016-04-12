#include "CharacterManager.hpp"
#include "Tree.hpp"

Tree::Tree(unsigned int x, unsigned int y) : Character(NULL, 0, x, y, "Árvore", 0xffffffff) {
	_TypeID = TYPEID_TREE1;
}

Character* Tree::Clone(float x, float y) {
	Tree* t = new Tree(*this);
	t->SetPosition(x, y);
	t->_ID = t->lastID++;

	return t;
}