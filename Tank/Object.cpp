#include <iostream>
#include "Object.h"
#include "Utility.h"
using namespace std;

Object::Object(int _x, int _y, Shape _form, ObjectType _type) : pos(_x, _y), beforePos(_x, _y), form(_form), type(_type)
{}

Object::~Object() {}

void Object::DrawThis()
{
	Utility::gotoxy(beforePos.x, beforePos.y);
	cout << " ";

	int shift = form.length() >> 1;
	Utility::gotoxy(this->GetPotion().x - shift, this->GetPotion().y);
	cout << this->GetShape();
}