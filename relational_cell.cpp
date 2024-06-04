#include"relational_cell.h"

// ----------------------------------

EqualCell::EqualCell() 
	: I_Relational_Cell(Type::EQUAL) {
}

std::string EqualCell::getValue() const {
	return "==";
}
I_Cell* EqualCell::clone() const {
	return new EqualCell(*this);
}



// ----------------------------------

NotEqualCell::NotEqualCell()
	: I_Relational_Cell(Type::NOT_EQUAL) {
}

std::string NotEqualCell::getValue() const {
	return "!=";
}
I_Cell* NotEqualCell::clone() const {
	return new NotEqualCell(*this);
}

// ----------------------------------

LessThanCell::LessThanCell()
	: I_Relational_Cell(Type::LESS) {
}

std::string LessThanCell::getValue() const {
	return "<";
}
I_Cell* LessThanCell::clone() const {
	return new LessThanCell(*this);
}

// ----------------------------------

GreaterThanCell::GreaterThanCell()
	: I_Relational_Cell(Type::GREATER) {
}

std::string GreaterThanCell::getValue() const {
	return ">";
}
I_Cell* GreaterThanCell::clone() const {
	return new GreaterThanCell(*this);
}

// ----------------------------------

GreaterThanOrEqualCell::GreaterThanOrEqualCell()
	: I_Relational_Cell(Type::GREATER_OR_EQUAL) {
}

std::string GreaterThanOrEqualCell::getValue() const {
	return ">=";
}

I_Cell* GreaterThanOrEqualCell::clone() const {
	return new GreaterThanOrEqualCell(*this);
}

// ----------------------------------

LessThanOrEqualCell::LessThanOrEqualCell()
	: I_Relational_Cell(Type::LESS_OR_EQUAL) {
}

std::string LessThanOrEqualCell::getValue() const {
	return "<=";
}

I_Cell* LessThanOrEqualCell::clone() const {
	return new LessThanOrEqualCell(*this);
}
