#include"operation_cell.h"

AdditionCell::AdditionCell() :
	I_Operation_Cell(Type::ADDITION) {
}

std::string AdditionCell::getValue() const {
	return "+";
}
I_Cell* AdditionCell::clone() const {
	return new AdditionCell(*this);
}

bool AdditionCell::operator<(I_Operation_Cell* other) const {
	if (this != other) {
		if (other->getType() == Type::SUBTRACTION || other->getType() == Type::ADDITION) {
			return false;
		}

		return true;
	}
	return false;
}

bool AdditionCell::operator>(I_Operation_Cell* other) const {
	return !(*this <= other);
}

bool AdditionCell::operator<=(I_Operation_Cell* other) const {
	if (this != other) {
		if (other->getType() == Type::SUBTRACTION) {
			return false;
		}
		return true;
	}
	return true;
}

bool AdditionCell::operator>=(I_Operation_Cell* other) const {
	return !(*this < other);
}

bool AdditionCell::operator==(I_Operation_Cell* other) const {
	if (this != other) {
		return other->getType() == Type::ADDITION ? true : false; 
	}

	return true;
}

bool AdditionCell::operator!=(I_Operation_Cell* other) const {
	return !(*this == other);
}


// ----------------------------------

SubstractionCell::SubstractionCell() :
	I_Operation_Cell(Type::SUBTRACTION) {
}

std::string SubstractionCell::getValue() const {
	return "-";
}
I_Cell* SubstractionCell::clone() const {
	return new SubstractionCell(*this);
}

bool SubstractionCell::operator<(I_Operation_Cell* other) const {
	if (this != other) {
		if (other->getType() == Type::SUBTRACTION) {
			return false;
		}

		return true;
	}
	return false;
}

bool SubstractionCell::operator>(I_Operation_Cell* other) const {
	return !(*this <= other);
}

bool SubstractionCell::operator<=(I_Operation_Cell* other) const {
	return true;
}

bool SubstractionCell::operator>=(I_Operation_Cell* other) const {
	return !(*this < other);
}

bool SubstractionCell::operator==(I_Operation_Cell* other) const {
	if (this != other) {
		return other->getType() == Type::SUBTRACTION ? true : false;
	}

	return true;
}

bool SubstractionCell::operator!=(I_Operation_Cell* other) const {
	return !(*this == other);
}


// ----------------------------------

DivisionCell::DivisionCell() :
	I_Operation_Cell(Type::DIVISION) {
}

std::string DivisionCell::getValue() const {
	return "/";
}
I_Cell* DivisionCell::clone() const {
	return new DivisionCell(*this);
}

bool DivisionCell::operator<(I_Operation_Cell* other) const {
	if (this != other) {
		if (other->getType() == Type::MULTIPLICATION) {
			return true;
		}

		return false;
	}
	return false;
}

bool DivisionCell::operator>(I_Operation_Cell* other) const {
	return !(*this < other);
}

bool DivisionCell::operator<=(I_Operation_Cell* other) const {
	if (this != other) {
		if (other->getType() == Type::DIVISION) {
			return true;
		}

		if (other->getType() == Type::MULTIPLICATION) {
			return true;
		}

		return false;
	}
	return true;
}

bool DivisionCell::operator>=(I_Operation_Cell* other) const {
	return !(*this < other);
}

bool DivisionCell::operator==(I_Operation_Cell* other) const {
	if (this != other) {
		return other->getType() == Type::DIVISION ? true : false;
	}

	return true;
}

bool DivisionCell::operator!=(I_Operation_Cell* other) const {
	return !(*this == other);
}


// ----------------------------------

MultiplicationCell::MultiplicationCell() :
	I_Operation_Cell(Type::MULTIPLICATION) {
}

std::string MultiplicationCell::getValue() const {
	return "*";
}
I_Cell* MultiplicationCell::clone() const {
	return new MultiplicationCell(*this);
}

bool MultiplicationCell::operator<(I_Operation_Cell* other) const {
	
	return false;
}

bool MultiplicationCell::operator>(I_Operation_Cell* other) const {
	return !(*this <= other);
}

bool MultiplicationCell::operator<=(I_Operation_Cell* other) const {
	if (this != other) {
	
		if (other->getType() == Type::MULTIPLICATION) {
			return true;
		}

		return false;
	}
	return true;
}

bool MultiplicationCell::operator>=(I_Operation_Cell* other) const {
	return !(*this < other);
}

bool MultiplicationCell::operator==(I_Operation_Cell* other) const {
	if (this != other) {
		return other->getType() == Type::MULTIPLICATION ? true : false;
	}

	return true;
}

bool MultiplicationCell::operator!=(I_Operation_Cell* other) const {
	return !(*this == other);
}

