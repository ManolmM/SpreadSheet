#include"modifiable_cell.h"


IntegerCell::IntegerCell(long long v)
	: I_Atomic_Cell(Type::INTEGER), value(v)
{
}

IntegerCell::IntegerCell(std::string value)
	: I_Atomic_Cell(Type::INTEGER)
{
	
	this->value = std::stoll(isInteger(value));
	
}


std::string IntegerCell::getValue() const {
	return std::to_string(value);  // TODO Fix the precision of the convertion.
}

void IntegerCell::setValue(std::string value) {
	if (value.empty())
		throw std::invalid_argument("Empty string casting to long long");

	this->value = std::stoll(value);
}



I_Cell* IntegerCell::clone() const {
	return new IntegerCell(*this);
}

void IntegerCell::setValue(long long value) {

}

long long IntegerCell::getLongLongValue() const{
	return value;
}

I_Value_Cell* IntegerCell::operator+(I_Value_Cell* other) const {
	if (this != other) {
		
		if (other->getType() == Type::INTEGER) {
			return new IntegerCell(value + std::stoll(other->getValue()));
		}
		else if (other->getType() == Type::FLOATING_POINT_NUMBER) {
			return new FloatingPointNumberCell(value + std::stod(other->getValue()));
		}
		else if (other->getType() == Type::STRING) {
			try {
				IntegerCell* newInt = new IntegerCell(other->getValue());
				newInt->setValue(value + newInt->getLongLongValue());
				return newInt;
			}
			catch (std::invalid_argument e) {
				
			}
			catch (...) {
				throw;
			}

			try {
				FloatingPointNumberCell* newFloat = new FloatingPointNumberCell(other->getValue());
				newFloat->setValue(value + newFloat->getDoubleValue());
				return newFloat;
			}
			catch (std::invalid_argument e) {

			}
			catch (...) {
				throw;
			}

			return new IntegerCell(value);
		}
		else if (other->getType() == Type::REFERENCE) {
			return new FormulaCell(getValue() + "+" + other->getValue());
		}
		else if (other->getType() == Type::FORMULA) {
			return new FormulaCell(getValue() + "+" + other->getValue());
		}
		else if (other->getType() == Type::INVALID) {
			return new InvalidCell("ERROR");
		}

		return new IntegerCell(value);
	}
	return new IntegerCell(value + value);
}

I_Value_Cell* IntegerCell::operator-(I_Value_Cell* other) const {
	
	if (this != other) {

		if (other->getType() == Type::INTEGER) {
			return new IntegerCell(value - std::stoll(other->getValue()));
		}
		else if (other->getType() == Type::FLOATING_POINT_NUMBER) {
			return new FloatingPointNumberCell(value - std::stod(other->getValue()));
		}
		else if (other->getType() == Type::STRING) {
			try {
				IntegerCell* newInt = new IntegerCell(other->getValue());
				newInt->setValue(value - newInt->getLongLongValue());
				return newInt;
			}
			catch (std::invalid_argument e) {

			}
			catch (...) {
				throw;
			}

			try {
				FloatingPointNumberCell* newFloat = new FloatingPointNumberCell(other->getValue());
				newFloat->setValue(value - newFloat->getDoubleValue());
				return newFloat;
			}
			catch (std::invalid_argument e) {

			}
			catch (...) {
				throw;
			}

			return new IntegerCell(value);
		}
		else if (other->getType() == Type::REFERENCE) {
			return new FormulaCell(getValue() + "-" + other->getValue());
		}
		else if (other->getType() == Type::FORMULA) {
			return new FormulaCell(getValue() + "-" + other->getValue());
		}
		else if (other->getType() == Type::INVALID) {
			return new InvalidCell("ERROR");
		}

		return new IntegerCell(value);
	}
	return new IntegerCell(value - value);
}

I_Value_Cell* IntegerCell::operator*(I_Value_Cell* other) const {

	if (this != other) {

		if (other->getType() == Type::INTEGER) {
			return new IntegerCell(value * std::stoll(other->getValue()));
		}
		else if (other->getType() == Type::FLOATING_POINT_NUMBER) {
			return new FloatingPointNumberCell(value * std::stod(other->getValue()));
		}
		else if (other->getType() == Type::STRING) {
			try {
				IntegerCell* newInt = new IntegerCell(other->getValue());
				newInt->setValue(value * newInt->getLongLongValue());
				return newInt;
			}
			catch (std::invalid_argument e) {

			}
			catch (...) {
				throw;
			}

			try {
				FloatingPointNumberCell* newFloat = new FloatingPointNumberCell(other->getValue());
				newFloat->setValue(value * newFloat->getDoubleValue());
				return newFloat;
			}
			catch (std::invalid_argument e) {

			}
			catch (...) {
				throw;
			}

			return new IntegerCell(0);
		}
		else if (other->getType() == Type::REFERENCE) {
			return new FormulaCell(getValue() + "*" + other->getValue());
		}
		else if (other->getType() == Type::FORMULA) {
			return new FormulaCell(getValue() + "*" + other->getValue());
		}
		else if (other->getType() == Type::INVALID) {
			return new InvalidCell("ERROR");
		}

		return new IntegerCell(0);
	}
	return new IntegerCell(value * value);
}

I_Value_Cell* IntegerCell::operator/(I_Value_Cell* other) const {

	if (this != other) {

		if (other->getType() == Type::INTEGER) {
			if (strcmp(other->getValue().c_str(), "0") == 0)
				throw std::invalid_argument("Fatal operation. Cannot divide by 0");


			if (value % std::stoll(other->getValue()) == 0) 
				return new IntegerCell(value / std::stoll(other->getValue()));


			return new FloatingPointNumberCell(value / std::stoll(other->getValue()));
		}
		else if (other->getType() == Type::FLOATING_POINT_NUMBER) {

			if (strcmp(other->getValue().c_str(), "0.0") == 0)
				throw std::invalid_argument("Fatal operation. Cannot divide by 0.0");

			return new FloatingPointNumberCell(value / std::stod(other->getValue()));
		}
		else if (other->getType() == Type::STRING) {
			try {
				if (strcmp(other->getValue().c_str(), "0") == 0)
					throw std::invalid_argument("Fatal operation. Cannot divide by 0");

				IntegerCell* newInt = new IntegerCell(other->getValue());
				newInt->setValue(value / newInt->getLongLongValue());
				return newInt;
			}
			catch (std::invalid_argument e) {
			}
			catch (...) {
				throw;
			}

			try {
				if (strcmp(other->getValue().c_str(), "0.0") == 0)
					throw std::invalid_argument("Fatal operation. Cannot divide by 0.0");

				FloatingPointNumberCell* newFloat = new FloatingPointNumberCell(other->getValue());
				newFloat->setValue(value / newFloat->getDoubleValue());
				return newFloat;
			}
			catch (std::invalid_argument e) {
			}
			catch (...) {
				throw;
			}

			return new IntegerCell(value);
		}
		else if (other->getType() == Type::REFERENCE) {
			return new FormulaCell(getValue() + "/" + other->getValue());
		}
		else if (other->getType() == Type::FORMULA) {
			return new FormulaCell(getValue() + "/" + other->getValue());
		}
		else if (other->getType() == Type::INVALID) {
			return new InvalidCell("ERROR");
		}

		return new IntegerCell(value);
	}
	
	return value == 0 ? new IntegerCell(1) : throw std::invalid_argument("Fatal operation. Cannot divide by 0.0");
}

I_Atomic_Cell* IntegerCell::operator<(I_Atomic_Cell* other) const {
	if (this != other) {

		if (other->getType() == Type::INTEGER) {
			return value < std::stoll(other->getValue()) ? new IntegerCell(1) : new IntegerCell(0);
		} else if (other->getType() == Type::FLOATING_POINT_NUMBER) {
			return value < std::stod(other->getValue()) ? new IntegerCell(1) : new IntegerCell(0);
		}
		else if (other->getType() == Type::STRING) {
			I_Value_Cell* number = nullptr;
			try {
				number = new IntegerCell(other->getValue());
				if (number) {
					if (value < std::stoll(number->getValue())) {
						delete number;
						return new IntegerCell(1);
					}
					delete number;
					return new IntegerCell(0);
				}
			}
			catch (std::invalid_argument e) {
				delete number;
			}
			catch (...) {  
				delete number;
				throw;
			}
			try {
				
				number = new FloatingPointNumberCell(other->getValue());
				if (number) {
					if (value < std::stod(number->getValue())) {
						delete number;
						return new IntegerCell(1);
					}
					delete number;
					return new IntegerCell(0);
				}
				if (value < 0) {
					delete number;
					return new IntegerCell(1);
				}

				return new IntegerCell(0);
			}
			catch (std::invalid_argument e) {
				delete number;
			}
			catch (...) {
				delete number;
				throw;
			}
		}
		
		return value < 0 ? new IntegerCell(1) : new IntegerCell(0);
	}

	return new IntegerCell(0);
}

I_Atomic_Cell* IntegerCell::operator>(I_Atomic_Cell* other) const {

	if (this != other) {

		if (other->getType() == Type::INTEGER) {
			return value > std::stoll(other->getValue()) ? new IntegerCell(1) : new IntegerCell(0);
		}
		else if (other->getType() == Type::FLOATING_POINT_NUMBER) {
			return value > std::stod(other->getValue()) ? new IntegerCell(1) : new IntegerCell(0);
		}
		else if (other->getType() == Type::STRING) {
			I_Value_Cell* number = nullptr;
			try {
				number = new IntegerCell(other->getValue());
				if (number) {
					if (value > std::stoll(number->getValue())) {
						delete number;
						return new IntegerCell(1);
					}
					delete number;
					return new IntegerCell(0);
				}
			}
			catch (std::invalid_argument e) {
				delete number;
			}
			catch (...) {
				delete number;
				throw;
			}
			try {

				number = new FloatingPointNumberCell(other->getValue());
				if (number) {
					if (value > std::stod(number->getValue())) {
						delete number;
						return new IntegerCell(1);
					}
					delete number;
					return new IntegerCell(0);
				}
				if (value > 0) {
					delete number;
					return new IntegerCell(1);
				}

				return new IntegerCell(0);
			}
			catch (std::invalid_argument e) {
				delete number;
			}
			catch (...) {
				delete number;
				throw;
			}
		}

		return value > 0 ? new IntegerCell(1) : new IntegerCell(1);
	}

	return new IntegerCell(0);
}

I_Atomic_Cell* IntegerCell::operator<=(I_Atomic_Cell* other) const {
	I_Atomic_Cell* res = *this > other;
	
	if (res->getValue() == "0")
		res->setValue("1");
	else 
		res->setValue("0");

	return res;
}

I_Atomic_Cell* IntegerCell::operator>=(I_Atomic_Cell* other) const {
	I_Atomic_Cell* res = *this < other;

	if (res->getValue() == "0")
		res->setValue("1");
	else
		res->setValue("0");

	return res;
}

I_Atomic_Cell* IntegerCell::operator==(I_Atomic_Cell* other) const {
	if (this != other) {

		if (other->getType() == Type::INTEGER) {
			return value == std::stoll(other->getValue()) ? new IntegerCell(1) : new IntegerCell(0);
		}
		else if (other->getType() == Type::FLOATING_POINT_NUMBER) {
			return value == std::stod(other->getValue()) ? new IntegerCell(1) : new IntegerCell(0);
		}
		else if (other->getType() == Type::STRING) {
			I_Value_Cell* number = nullptr;
			try {
				number = new IntegerCell(other->getValue());
				if (number) {
					if (value == std::stoll(number->getValue())) {
						delete number;
						return new IntegerCell(1);
					}
					delete number;
					return new IntegerCell(0);
				}
			}
			catch (std::invalid_argument e) {
				delete number;
			}
			catch (...) {
				delete number;
				throw;
			}
			try {

				number = new FloatingPointNumberCell(other->getValue());
				if (number) {
					if (value == std::stod(number->getValue())) {
						delete number;
						return new IntegerCell(1);
					}
					delete number;
					return new IntegerCell(0);
				}
				if (value == 0) {
					delete number;
					return new IntegerCell(1);
				}

				return new IntegerCell(0);
			}
			catch (std::invalid_argument e) {
				delete number;
			}
			catch (...) {
				delete number;
				throw;
			}
		}

		return value == 0 ? new IntegerCell(0) : new IntegerCell(1);
	}

	return new IntegerCell(1);
}

I_Atomic_Cell* IntegerCell::operator!=(I_Atomic_Cell* other) const {
	I_Atomic_Cell* res = *this == other;

	if (res->getValue() == "0")
		res->setValue("1");
	else
		res->setValue("0");

	return res;
}

// TODO 00 is invalid and 001 
std::string IntegerCell::isInteger(std::string value) {

	if (value.empty()) throw std::invalid_argument("Empty value");

	std::string storeInt;							    // Extracted integer value with trimmed spaces.
	const char* str = value.c_str();

	while (*str && *str == ' ')							// Skips spaces until it reach another character.
		++str;

	if (!*str) throw std::invalid_argument("Invalid format");
	if (*str != '-' && *str != '+' &&
		*str < '0' && *str > '9') {
		throw std::invalid_argument("Invalid format");
	}

	short at = 0;
	if (str[at] == '-' || str[at] == '+') {
		if (str[++at] && str[at++] == '0') {
			while (str[at])
				if (str[at++] != ' ') 
					throw std::invalid_argument("Invalid format");
		}
	}
	else {
		if (str[at++] == '0') {
			while (str[at])
				if (str[at++] != ' ')
					throw std::invalid_argument("Invalid format");
		}
	}

	bool passNumber = false;
	bool isZero = false;
	bool isFirstNumberZero = false;

	if (*str == '-' || *str == '+') {
		storeInt += *str++;
	}

	while (*str) {

		if ((*str < '0' || *str > '9') && *str != ' ') {
			throw std::invalid_argument("Invalid format");
		}

		if (*str == '0') {
			if (isZero && !passNumber) {
				throw std::invalid_argument("Invalid format");
			}

			if (!isZero) {
				isZero = true;
				passNumber = true;
				isFirstNumberZero = true;
			}
			storeInt += *str++;
			continue;
		}

		if (*str == ' ') {
			while (*str) {
				if (*str++ != ' ') {
					throw std::invalid_argument("Invalid format");
				}
			}
			if (passNumber) {

				return storeInt;
			}

			throw std::invalid_argument("Invalid format");
		}
		passNumber = true;
		storeInt += *str++;
		isZero = false;
	}
	if (passNumber) {
		while (*str) {
			if (*str++ != ' ') throw std::invalid_argument("Invalid format");
		}
		return storeInt;
	}
	throw std::invalid_argument("Invalid format");

}


//------------------------------------------



I_Value_Cell* StringCell::operator+(I_Value_Cell* other) const {
	if (this != other) {

		try {
			I_Value_Cell* newInt = new IntegerCell(value);
			I_Value_Cell* result = *newInt + other;
			delete newInt;
			return result;
		}
		catch (std::invalid_argument e) {

		}
		catch (...) {
			throw;
		}

		try {
			I_Value_Cell* newDouble = new FloatingPointNumberCell(value);
			I_Value_Cell* result = *newDouble + other;
			delete newDouble;
			return result;
		}
		catch (std::invalid_argument e) {

		}
		catch (...) {
			throw;
		}


		if (other->getType() == Type::INTEGER) {
			return new IntegerCell(other->getValue());
		}
		else if (other->getType() == Type::FLOATING_POINT_NUMBER) {
			return new IntegerCell(other->getValue());
		}
		else if (other->getType() == Type::REFERENCE) {
			return new ReferenceCell(other->getValue());
		}
		else if (other->getType() == Type::FORMULA) {
			return new FormulaCell(other->getValue());
		}
		else if (other->getType() == Type::INVALID) {
			return new InvalidCell("ERROR");
		}
		else if (other->getType() == Type::STRING) {
			try {
				I_Value_Cell* newInt = new IntegerCell(other->getValue());
				return newInt;
			}
			catch (std::invalid_argument e) {

			}
			catch (...) {
				throw;
			}

			try {
				I_Value_Cell* newDouble = new FloatingPointNumberCell(other->getValue());
				return newDouble;
			}
			catch (std::invalid_argument e) {

			}
			catch (...) {
				throw;
			}
		}

		return new IntegerCell("0");
	}
	try {
		IntegerCell* newInt = new IntegerCell(value);
		newInt->setValue(std::stoll(value) * 2);
		return newInt;
	}
	catch (std::invalid_argument e) {

	}
	try {
		FloatingPointNumberCell* newDouble = new FloatingPointNumberCell(value);
		newDouble->setValue(std::stoll(value) * 2);
		return newDouble;
	}
	catch (std::invalid_argument e) {

	}
	catch (...) {
		throw;
	}
	return new IntegerCell("0");
}

I_Value_Cell* StringCell::operator-(I_Value_Cell* other) const {
	if (this != other) {

		try {
			I_Value_Cell* newInt = new IntegerCell(value);
			I_Value_Cell* result = *newInt - other;
			delete newInt;
			return result;
		}
		catch (std::invalid_argument e) {

		}
		catch (...) {
			throw;
		}

		try {
			I_Value_Cell* newDouble = new FloatingPointNumberCell(value);
			I_Value_Cell* result = *newDouble - other;
			delete newDouble;
			return result;
		}
		catch (std::invalid_argument e) {

		}
		catch (...) {
			throw;
		}


		if (other->getType() == Type::INTEGER) {
			return new IntegerCell(other->getValue());
		}
		else if (other->getType() == Type::FLOATING_POINT_NUMBER) {
			return new IntegerCell(other->getValue());
		}
		else if (other->getType() == Type::REFERENCE) {
			return new ReferenceCell(other->getValue());
		}
		else if (other->getType() == Type::FORMULA) {
			return new FormulaCell(other->getValue());
		}
		else if (other->getType() == Type::INVALID) {
			return new InvalidCell("ERROR");
		}
		else if (other->getType() == Type::STRING) {
			try {
				I_Value_Cell* newInt = new IntegerCell(other->getValue());
				return newInt;
			}
			catch (std::invalid_argument e) {

			}
			catch (...) {
				throw;
			}

			try {
				I_Value_Cell* newDouble = new FloatingPointNumberCell(other->getValue());
				return newDouble;
			}
			catch (std::invalid_argument e) {

			}
			catch (...) {
				throw;
			}
		}

		return new IntegerCell("0");
	}
	try {
		IntegerCell* newInt = new IntegerCell(value);
		newInt->setValue(0);
		return newInt;
	}
	catch (std::invalid_argument e) {

	}
	try {
		FloatingPointNumberCell* newDouble = new FloatingPointNumberCell(value);
		newDouble->setValue(0.0);
		return newDouble;
	}
	catch (std::invalid_argument e) {

	}
	catch (...) {
		throw;
	}
	return new IntegerCell("0");
}

I_Value_Cell* StringCell::operator*(I_Value_Cell* other) const {
	if (this != other) {

		try {
			I_Value_Cell* newInt = new IntegerCell(value);
			I_Value_Cell* result = *newInt * other;
			delete newInt;
			return result;
		}
		catch (std::invalid_argument e) {

		}
		catch (...) {
			throw;
		}

		try {
			I_Value_Cell* newDouble = new FloatingPointNumberCell(value);
			I_Value_Cell* result = *newDouble * other;
			delete newDouble;
			return result;
		}
		catch (std::invalid_argument e) {

		}
		catch (...) {
			throw;
		}


		if (other->getType() == Type::INTEGER) {
			return new IntegerCell(0);
		}
		else if (other->getType() == Type::FLOATING_POINT_NUMBER) {
			return new IntegerCell(0.0);
		}
		else if (other->getType() == Type::REFERENCE) {
			return new IntegerCell(0);
		}
		else if (other->getType() == Type::FORMULA) {
			return new IntegerCell(0);
		}
		else if (other->getType() == Type::INVALID) {
			return new InvalidCell("ERROR");
		}
		else if (other->getType() == Type::STRING) {
			try {
				I_Value_Cell* newInt = new IntegerCell(0);
				return newInt;
			}
			catch (std::invalid_argument e) {

			}
			catch (...) {
				throw;
			}

			try {
				I_Value_Cell* newDouble = new FloatingPointNumberCell(0.0);
				return newDouble;
			}
			catch (std::invalid_argument e) {

			}
			catch (...) {
				throw;
			}
		}

		return new IntegerCell("0");
	}
	try {
		IntegerCell* newInt = new IntegerCell(value);
		newInt->setValue(0);
		return newInt;
	}
	catch (std::invalid_argument e) {

	}
	try {
		FloatingPointNumberCell* newDouble = new FloatingPointNumberCell(value);
		newDouble->setValue(0.0);
		return newDouble;
	}
	catch (std::invalid_argument e) {

	}
	catch (...) {
		throw;
	}
	return new IntegerCell("0");
}

I_Value_Cell* StringCell::operator/(I_Value_Cell* other) const {

	if (this != other) {

		try {
			I_Value_Cell* newInt = new IntegerCell(value);
			I_Value_Cell* result = *newInt / other;
			delete newInt;
			return result;
		}
		catch (std::invalid_argument e) {

		}
		catch (...) {
			throw;
		}

		try {
			I_Value_Cell* newDouble = new FloatingPointNumberCell(value);
			I_Value_Cell* result = *newDouble / other;
			delete newDouble;
			return result;
		}
		catch (std::invalid_argument e) {

		}
		catch (...) {
			throw;
		}

		if ((strcmp(other->getValue().c_str(), "0") == 0) || (strcmp(other->getValue().c_str(), "0.0") == 0)) {
			throw std::invalid_argument("Fatal operation. Cannot divide by 0 or 0.0.");
		}

		if (other->getType() == Type::INTEGER) {
			return new IntegerCell(0);
		}
		else if (other->getType() == Type::FLOATING_POINT_NUMBER) {
			return new IntegerCell(0.0);
		}
		else if (other->getType() == Type::REFERENCE) {
			return new IntegerCell(0);
		}
		else if (other->getType() == Type::FORMULA) {
			return new IntegerCell(0);
		}
		else if (other->getType() == Type::INVALID) {
			return new InvalidCell("ERROR");
		}
		else if (other->getType() == Type::STRING) {
			throw std::invalid_argument("Fatal operation. Cannot divide by 0 or 0.0.");
		}

	}
	if ((strcmp(value.c_str(), "0") == 0) || (value.c_str(), "0.0") == 0) {
		throw std::invalid_argument("Fatal operation. Cannot divide by 0 or 0.0.");
	}

	try {
		IntegerCell* newInt = new IntegerCell(value);
		newInt->setValue(1);
		return newInt;
	}
	catch (std::invalid_argument e) {

	}
	try {
		FloatingPointNumberCell* newDouble = new FloatingPointNumberCell(value);
		newDouble->setValue(1.0);
		return newDouble;
	}
	catch (std::invalid_argument e) {

	}
	catch (...) {
		throw;
	}
	throw std::invalid_argument("Fatal operation. Cannot divide by 0 or 0.0.");
}

I_Atomic_Cell* StringCell::operator<(I_Atomic_Cell* other) const {
	
	I_Atomic_Cell* number = nullptr;
	I_Atomic_Cell* res = nullptr;
	if (this != other) {

		try {
			number = new IntegerCell(value);	
			res = *number < other;
			delete number;
			return res;
		}
		catch (std::invalid_argument e) {		
			delete number;
		}
		catch (...) {
			delete number;
			throw;
		}

		try {
			number = new FloatingPointNumberCell(value);
			res = *number < other;
			delete number;
			return res;
		}
		catch (std::invalid_argument e) {
			delete number;
		}
		catch (...) {
			delete number;
			throw;
		}
	}

	try {
		number = new IntegerCell(0);
		res = *number < other;
		delete number;
		return res;
	}
	catch (std::invalid_argument e) {
		delete number;
	}
	catch (...) {
		delete number;
		throw;
	}
}

I_Atomic_Cell* StringCell::operator>(I_Atomic_Cell* other) const {
	
	I_Atomic_Cell* number = nullptr;
	I_Atomic_Cell* res = nullptr;
	if (this != other) {

		try {
			number = new IntegerCell(value);
			res = *number > other;
			delete number;
			return res;
		}
		catch (std::invalid_argument e) {
			delete number;
		}
		catch (...) {
			delete number;
			throw;
		}

		try {
			number = new FloatingPointNumberCell(value);
			res = *number > other;
			delete number;
			return res;
		}
		catch (std::invalid_argument e) {
			delete number;
		}
		catch (...) {
			delete number;
			throw;
		}
	}

	try {
		number = new IntegerCell(0);
		res = *number > other;
		delete number;
		return res;
	}
	catch (std::invalid_argument e) {
		delete number;
	}
	catch (...) {
		delete number;
		throw;
	}
}

I_Atomic_Cell* StringCell::operator<=(I_Atomic_Cell* other) const {
	I_Atomic_Cell* res = *this > other;

	if (res->getValue() == "0")
		res->setValue("1");
	else
		res->setValue("0");

	return res;
}

I_Atomic_Cell* StringCell::operator>=(I_Atomic_Cell* other) const {
	I_Atomic_Cell* res = *this < other;

	if (res->getValue() == "0")
		res->setValue("1");
	else
		res->setValue("0");

	return res;
}

I_Atomic_Cell* StringCell::operator==(I_Atomic_Cell* other) const {
	
	I_Atomic_Cell* number = nullptr;
	I_Atomic_Cell* res = nullptr;
	if (this != other) {

		try {
			number = new IntegerCell(value);
			res = *number == other;
			delete number;
			return res;
		}
		catch (std::invalid_argument e) {
			delete number;
		}
		catch (...) {
			delete number;
			throw;
		}

		try {
			number = new FloatingPointNumberCell(value);
			res = *number == other;
			delete number;
			return res;
		}
		catch (std::invalid_argument e) {
			delete number;
		}
		catch (...) {
			delete number;
			throw;
		}
	}

	try {
		number = new IntegerCell(0);
		res = *number == other;
		delete number;
		return res;
	}
	catch (std::invalid_argument e) {
		delete number;
	}
	catch (...) {
		delete number;
		throw;
	}
}

I_Atomic_Cell* StringCell::operator!=(I_Atomic_Cell* other) const {
	I_Atomic_Cell* res = *this == other;

	if (res->getValue() == "0")
		res->setValue("1");
	else
		res->setValue("0");

	return res;
}

StringCell::StringCell(std::string value) : I_Atomic_Cell(Type::STRING) {

	isText(value);
}


std::string StringCell::getValue() const {
	return value;
}

std::string StringCell::getRawString() {

	size_t size = value.size();
	std::string r;
	bool subQuoted = false;

	if (value[0] == '"') {
		subQuoted = true;
	}

	for (size_t i = 0; i < size; i++)
	{
		if (value[i] == '"') {
			r += "\"\"";
		}
		else {
			r += value[i];
		}
	}

	if (subQuoted == false) {
		r = "\"" + r + "\"";
	}
	return r;
}

void StringCell::setValue(std::string v) {
	this->value = value;
}

I_Cell* StringCell::clone() const {
	return new StringCell(*this);
}

void StringCell::isText(std::string value) {

	if (value.empty()) throw std::invalid_argument("Empty value");

	std::string storeText;							   // Extracted	text with trimmed spaces.
	const char* str = value.c_str();

	while (*str && *str == ' ')						   // Skips spaces until it reach another character.
		++str;

	if (!*str) throw std::invalid_argument("Empty value");

	if (*str++ != '"') throw std::invalid_argument("Invalid format");

	std::vector<char> stack;
	while (*str) {

		if (*str == '"')							   // Delimiter for end of proccessing the string.
			break;

		if (*str == '\\') {
			if (*++str != '\0') {
				if (*str == '"') {
					if (!stack.empty()) {
						stack.pop_back();
					}
					else {
						stack.push_back('"');
					}
				}
				else if (*str == '\\') {
					storeText += '\\';
				}
				else {
					throw std::invalid_argument("Invalid format");
				}
			}
			else {
				throw std::invalid_argument("Invalid format");
			}
		}

		storeText += *str++;
	}
	if (stack.empty()) {
		this->value = storeText;
		return;
	}

	throw std::invalid_argument("Invalid format");
}

//------------------

FloatingPointNumberCell::FloatingPointNumberCell(double value)
	: I_Atomic_Cell(Type::FLOATING_POINT_NUMBER), value(value)
{}

FloatingPointNumberCell::FloatingPointNumberCell(std::string value)
	: I_Atomic_Cell(Type::FLOATING_POINT_NUMBER)
{
	setValue(value);
}


std::string FloatingPointNumberCell::getValue() const {
	return std::to_string(value);
}

void FloatingPointNumberCell::setValue(std::string value) {

	this->value = std::stod(isFloatingPointNumber(value));
}

void FloatingPointNumberCell::setValue(double value) {
	this->value = value;
}
double FloatingPointNumberCell::getDoubleValue() const {
	return value;
}

I_Cell* FloatingPointNumberCell::clone() const {
	return new FloatingPointNumberCell(*this);
}

I_Value_Cell* FloatingPointNumberCell::operator+(I_Value_Cell* other) const {

	if (this != other) {

		if (other->getType() == Type::INTEGER) {
			return new FloatingPointNumberCell(value + std::stoll(other->getValue()));
		}
		else if (other->getType() == Type::FLOATING_POINT_NUMBER) {
			return new FloatingPointNumberCell(value + std::stod(other->getValue()));
		}
		else if (other->getType() == Type::STRING) {
			try {
				IntegerCell* newInt = new IntegerCell(other->getValue());
				FloatingPointNumberCell* newDouble = new FloatingPointNumberCell(value + newInt->getLongLongValue());
				delete newInt;
				return newDouble;
			}
			catch (std::invalid_argument e) {

			}
			catch (...) {
				throw;
			}

			try {
				FloatingPointNumberCell* newFloat = new FloatingPointNumberCell(other->getValue());
				newFloat->setValue(value + newFloat->getDoubleValue());
				return newFloat;
			}
			catch (std::invalid_argument e) {

			}
			catch (...) {
				throw;
			}

			return new IntegerCell(value);
		}
		else if (other->getType() == Type::REFERENCE) {
			return new FormulaCell(getValue() + "+" + other->getValue());
		}
		else if (other->getType() == Type::FORMULA) {
			return new FormulaCell(getValue() + "+" + other->getValue());
		}
		else if (other->getType() == Type::INVALID) {
			return new InvalidCell("ERROR");
		}

		return new FloatingPointNumberCell(value);
	}
	return new FloatingPointNumberCell(value + value);
}

I_Value_Cell* FloatingPointNumberCell::operator-(I_Value_Cell* other) const {
	
	if (this != other) {

		if (other->getType() == Type::INTEGER) {
			return new FloatingPointNumberCell(value - std::stoll(other->getValue()));
		}
		else if (other->getType() == Type::FLOATING_POINT_NUMBER) {
			return new FloatingPointNumberCell(value - std::stod(other->getValue()));
		}
		else if (other->getType() == Type::STRING) {
			try {
				IntegerCell* newInt = new IntegerCell(other->getValue());
				FloatingPointNumberCell* newDouble = new FloatingPointNumberCell(value - newInt->getLongLongValue());
				delete newInt;
				return newDouble;
			}
			catch (std::invalid_argument e) {

			}
			catch (...) {
				throw;
			}

			try {
				FloatingPointNumberCell* newFloat = new FloatingPointNumberCell(other->getValue());
				newFloat->setValue(value - newFloat->getDoubleValue());
				return newFloat;
			}
			catch (std::invalid_argument e) {

			}
			catch (...) {
				throw;
			}

			return new IntegerCell(value);
		}
		else if (other->getType() == Type::REFERENCE) {
			return new FormulaCell(getValue() + "-" + other->getValue());
		}
		else if (other->getType() == Type::FORMULA) {
			return new FormulaCell(getValue() + "-" + other->getValue());
		}
		else if (other->getType() == Type::INVALID) {
			return new InvalidCell("ERROR");
		}

		return new FloatingPointNumberCell(value);
	}
	return new FloatingPointNumberCell(value - value);
}

I_Value_Cell* FloatingPointNumberCell::operator*(I_Value_Cell* other) const {
	if (this != other) {

		if (other->getType() == Type::INTEGER) {
			return new FloatingPointNumberCell(value * std::stoll(other->getValue()));
		}
		else if (other->getType() == Type::FLOATING_POINT_NUMBER) {
			return new FloatingPointNumberCell(value * std::stod(other->getValue()));
		}
		else if (other->getType() == Type::STRING) {
			try {
				IntegerCell* newInt = new IntegerCell(other->getValue());
				FloatingPointNumberCell* newDouble = new FloatingPointNumberCell(value * newInt->getLongLongValue());
				delete newInt;
				return newDouble;
			}
			catch (std::invalid_argument e) {

			}
			catch (...) {
				throw;
			}

			try {
				FloatingPointNumberCell* newFloat = new FloatingPointNumberCell(other->getValue());
				newFloat->setValue(value * newFloat->getDoubleValue());
				return newFloat;
			}
			catch (std::invalid_argument e) {

			}
			catch (...) {
				throw;
			}

			return new IntegerCell(value);
		}
		else if (other->getType() == Type::REFERENCE) {
			return new FormulaCell(getValue() + "*" + other->getValue());
		}
		else if (other->getType() == Type::FORMULA) {
			return new FormulaCell(getValue() + "*" + other->getValue());
		}
		else if (other->getType() == Type::INVALID) {
			return new InvalidCell("ERROR");
		}

		return new FloatingPointNumberCell(value);
	}
	return new FloatingPointNumberCell(value * value);
}

I_Value_Cell* FloatingPointNumberCell::operator/(I_Value_Cell* other) const {
	
	if (this != other) {

		if ((strcmp(other->getValue().c_str(), "0") == 0) || (strcmp(other->getValue().c_str(), "0.0") == 0)) {
			throw std::invalid_argument("Fatal operation. Cannot divide by 0 or 0.0.");
		}

		if (other->getType() == Type::INTEGER) {

			return new FloatingPointNumberCell(value / std::stoll(other->getValue()));
		}
		else if (other->getType() == Type::FLOATING_POINT_NUMBER) {

			return new FloatingPointNumberCell(value / std::stod(other->getValue()));
		}
		else if (other->getType() == Type::STRING) {
			try {

				IntegerCell* newInt = new IntegerCell(other->getValue());
				FloatingPointNumberCell* newDouble = new FloatingPointNumberCell(value * newInt->getLongLongValue());
				delete newInt;
				return newDouble;
			}
			catch (std::invalid_argument e) {
			}
			catch (...) {
				throw;
			}

			try {
			
				FloatingPointNumberCell* newFloat = new FloatingPointNumberCell(other->getValue());
				newFloat->setValue(value / newFloat->getDoubleValue());
				return newFloat;
			}
			catch (std::invalid_argument e) {
			}
			catch (...) {
				throw;
			}

			return new IntegerCell(value);
		}
		else if (other->getType() == Type::REFERENCE) {
			return new FormulaCell(getValue() + "/" + other->getValue());
		}
		else if (other->getType() == Type::FORMULA) {
			return new FormulaCell(getValue() + "/" + other->getValue());
		}
		else if (other->getType() == Type::INVALID) {
			return new InvalidCell("ERROR");
		}

		return new FloatingPointNumberCell(value);
	}
	
	return value == 0.0 ? new FloatingPointNumberCell(1) : throw std::invalid_argument("Fatal operation. Cannot divide by 0 or 0.0");
}

I_Atomic_Cell* FloatingPointNumberCell::operator<(I_Atomic_Cell* other) const {

	if (this != other) {

		if (other->getType() == Type::INTEGER) {
			return value < std::stoll(other->getValue()) ? new IntegerCell(1) : new IntegerCell(0);
		}
		else if (other->getType() == Type::FLOATING_POINT_NUMBER) {
			return value < std::stod(other->getValue()) ? new IntegerCell(1) : new IntegerCell(0);
		}
		else if (other->getType() == Type::STRING) {
			I_Value_Cell* number = nullptr;
			try {
				number = new IntegerCell(other->getValue());
				if (number) {
					if (value < std::stoll(number->getValue())) {
						delete number;
						return new IntegerCell(1);
					}
					delete number;
					return new IntegerCell(0);
				}
			}
			catch (std::invalid_argument e) {
				delete number;
			}
			catch (...) { 
				delete number;
				throw; 
			}
			try {
				number = new FloatingPointNumberCell(other->getValue());
				if (number) {
					if (value < std::stod(number->getValue())) {
						delete number;
						return new IntegerCell(1);
					}
					delete number;
					return new IntegerCell(0);
				}
				if (value < 0) {
					delete number;
					return new IntegerCell(1);
				}

				return new IntegerCell(0);
			}
			catch (std::invalid_argument e) {
				delete number;
			}
			catch (...) {
				delete number;
				throw;
			}
		}

		return value < 0 ? new IntegerCell(1) : new IntegerCell(0);
	}

	return new IntegerCell(0);
}

I_Atomic_Cell* FloatingPointNumberCell::operator>(I_Atomic_Cell* other) const {
	
	if (this != other) {

		if (other->getType() == Type::INTEGER) {
			return value > std::stoll(other->getValue()) ? new IntegerCell(1) : new IntegerCell(0);
		}
		else if (other->getType() == Type::FLOATING_POINT_NUMBER) {
			return value > std::stod(other->getValue()) ? new IntegerCell(1) : new IntegerCell(0);
		}
		else if (other->getType() == Type::STRING) {
			I_Atomic_Cell* number = nullptr;
			
			try {
				number = new IntegerCell(other->getValue());
				if (number) {
					if (value < std::stoll(number->getValue())) {
						delete number;
						return new IntegerCell(1);
					}
					delete number;
					return new IntegerCell(0);
				}
			}
			catch (std::invalid_argument e) {
				delete number;
			}
			catch (...) {
				delete number;
				throw;
			}
			try {
				number = new FloatingPointNumberCell(other->getValue());
				if (number) {
					if (value < std::stod(number->getValue())) {
						delete number;
						return new IntegerCell(1);
					}
					delete number;
					return new IntegerCell(0);
				}
				if (value < 0) {
					delete number;
					return new IntegerCell(1);
				}

				return new IntegerCell(0);
			}
			catch (std::invalid_argument e) {
				delete number;
			}
			catch (...) {
				delete number;
				throw;
			}
		}

		return value > 0 ? new IntegerCell(1) : new IntegerCell(0);
	}

	return new IntegerCell(0);
}

I_Atomic_Cell* FloatingPointNumberCell::operator<=(I_Atomic_Cell* other) const {
	I_Atomic_Cell* res = *this > other;

	if (res->getValue() == "0")
		res->setValue("1");
	else
		res->setValue("0");

	return res;
}

I_Atomic_Cell* FloatingPointNumberCell::operator>=(I_Atomic_Cell* other) const {
	I_Atomic_Cell* res = *this < other;

	if (res->getValue() == "0")
		res->setValue("1");
	else
		res->setValue("0");

	return res;
}

I_Atomic_Cell* FloatingPointNumberCell::operator==(I_Atomic_Cell* other) const {
	
	if (this != other) {

		if (other->getType() == Type::INTEGER) {
			return value == std::stoll(other->getValue()) ? new IntegerCell(1) : new IntegerCell(0);
		}
		else if (other->getType() == Type::FLOATING_POINT_NUMBER) {
			return value == std::stod(other->getValue()) ? new IntegerCell(1) : new IntegerCell(0);
		}
		else if (other->getType() == Type::STRING) {
			I_Value_Cell* number = nullptr;
			try {
				number = new IntegerCell(other->getValue());
				if (number) {
					if (value == std::stoll(number->getValue())) {
						delete number;
						return new IntegerCell(0);
					}
					delete number;
					return new IntegerCell(1);
				}
			}
			catch (std::invalid_argument e) {
				delete number;
			}
			catch (...) {
				delete number;
				throw;
			}
			try {
				number = new FloatingPointNumberCell(other->getValue());
				if (number) {
					if (value == std::stod(number->getValue())) {
						delete number;
						return new IntegerCell(0);
					}
					delete number;
					return new IntegerCell(1);
				}
				if (value == 0) {
					delete number;
					return new IntegerCell(0);
				}

				return new IntegerCell(1);
			}
			catch (std::invalid_argument e) {
				delete number;
			}
			catch (...) { 
				delete number; 
				throw; 
			}
		}

		return value == 0 ? new IntegerCell(0) : new IntegerCell(1);
	}

	return new IntegerCell(1);
}

I_Atomic_Cell* FloatingPointNumberCell::operator!=(I_Atomic_Cell* other) const {
	I_Atomic_Cell* res = *this < other;

	if (res->getValue() == "0")
		res->setValue("1");
	else
		res->setValue("0");

	return res;
}

std::string FloatingPointNumberCell::isFloatingPointNumber(std::string value) {

	if (value.empty()) throw std::invalid_argument("Empty value");

	std::string storeCoreFloat;
	const char* str = value.c_str();

	while (*str && *str == ' ')							// Skips spaces until it reach another character.
		++str;

	if (!*str) throw std::invalid_argument("Invalid format");
	if (*str != '-' && *str != '+' &&
		*str < '0' && *str  > '9') {
		throw std::invalid_argument("Invalid format");
	}

	bool passNumber = false;
	bool hasZeroBeforeFloatingPoint = false;
	bool hasFloatingPoint = false;

	if (*str == '-') 
		storeCoreFloat += *str++;

	if (*str == '+')
		*str++;

	while (*str) {

		if (*str == '.' && passNumber) {
			if (hasFloatingPoint) {
				throw std::invalid_argument("Invalid format");
			}
			hasFloatingPoint = true;
			storeCoreFloat += *str++;
			continue;
		}

		if ((*str < '0' || *str > '9') && *str != ' ') {
			throw std::invalid_argument("Invalid format");
		}

		if (*str == '0') {
			if (!hasFloatingPoint && hasZeroBeforeFloatingPoint) {
				throw std::invalid_argument("Invalid format");
			}
			hasZeroBeforeFloatingPoint = true;
			passNumber = true;
			storeCoreFloat += *str++;
			continue;
		}

		if (*str == ' ') {
			//while (*++str) {
			//	if (*++str != ' ') {
			//		throw std::invalid_argument("Invalid format");
			//	}
			//}
			if (passNumber) {
				while (*str)
					if (*str++ != ' ')
						throw std::invalid_argument("Invalid format");

				return storeCoreFloat;
			}

			throw std::invalid_argument("Invalid format");
		}
		passNumber = true;
		storeCoreFloat += *str++;
	}
	if (passNumber && hasFloatingPoint && *--str != '.') {
		return storeCoreFloat;
	}

	throw std::invalid_argument("Invalid format");
}

//--------------------------

ReferenceCell::ReferenceCell(std::string reference) 
	: I_Value_Cell(Type::REFERENCE), reference(isReference(reference))
{}

std::string ReferenceCell::getValue() const {
	return reference;
}

void ReferenceCell::setValue(std::string ref) {
	try {
		std::string newRef = isReference(ref);
		reference = newRef;
	}
	catch (std::invalid_argument e) {
	}
}

I_Cell* ReferenceCell::clone() const {
	return new ReferenceCell(*this);
}

I_Value_Cell* ReferenceCell::operator+(I_Value_Cell* other) const {
	if (this != other) {

		if (other->getType() == Type::INVALID) {
			return new InvalidCell(reference);
		}
	}
	return new ReferenceCell(reference);
}


I_Value_Cell* ReferenceCell::operator-(I_Value_Cell* other) const {
	return nullptr;
}
I_Value_Cell* ReferenceCell::operator*(I_Value_Cell* other) const {
	return nullptr;
}
I_Value_Cell* ReferenceCell::operator/(I_Value_Cell* other) const {
	return nullptr;
}


std::string ReferenceCell::isReference(std::string value) {
	if (value.empty()) {
		throw std::invalid_argument("Empty value");
	}

	std::string storeRef;
	const char* str = value.c_str();

	while (*str && *str == ' ')						    // Skips leading spaces.
		++str;

	if (!*str) throw std::invalid_argument("Invalid format");

	bool passIndicator = false;
	char firstIndicator;
	bool passNumber = false;
	char* cellRefer = nullptr;						    // Extracted cell reference with trimmed spaces. 
	if (*str != 'R' && *str != 'C') 
		throw std::invalid_argument("Invalid format");

	firstIndicator = *str;
	storeRef += *str++;

	char lastChar = *str;

	while (*str) {

		if (*str >= '1' && *str <= '9') {
			if (passIndicator) {
				passNumber = true;
			}
			lastChar = *str;
			storeRef += *str++;
			continue;
		}

		if (*str == '0' && lastChar != 'R' && lastChar != 'C') {
			lastChar = *str;
			storeRef += "0";
			*str++;
			continue;
		}

		if (*str != 'R' && *str != 'C' && *str != ' ') throw std::invalid_argument("Invalid format");

		if (*str == firstIndicator) throw std::invalid_argument("Invalid format");

		if ((*str == 'R' || *str == 'C') && lastChar != *str) {
			lastChar = *str;
			passIndicator = true;
			storeRef += *str++;
			continue;
		}

		if (*str == ' ' && passIndicator)
			break;
		*str++;
	}

	while (*str)
		if (*str++ != ' ') {
			throw std::invalid_argument("Invalid format");
		}

	if (!passIndicator || !passNumber) throw std::invalid_argument("Invalid format");

	return storeRef;
}


// ------------------------------


FormulaCell::FormulaCell(std::string formula)
	: I_Value_Cell(Type::FORMULA), formula(isFormula(formula)) {
}

FormulaCell::FormulaCell(const FormulaCell& other) : I_Value_Cell(other) {
	
	copy(other);
}

FormulaCell& FormulaCell::operator=(const FormulaCell& other) {

	if (this != &other) {
		I_Value_Cell::operator=(other);

		free();
		copy(other);
	}
	return *this;
}

FormulaCell::~FormulaCell() {
	free();
}

void FormulaCell::free() {

	for (size_t i = 0; i < size; i++)
	{
		delete formula[i];
	}
	delete[] formula;
}

void FormulaCell::copy(const FormulaCell& other) {

	try {
		size = other.size;
		formula = new I_Cell * [size];

		for (size_t i = 0; i < size; i++)
		{
			this->formula[i] = other.formula[i]->clone();
		}

		this->strFormula = other.strFormula;
	}
	catch (...) {
		free();
		throw;
	}
}

std::string FormulaCell::getValue() const {
	std::string toStrformula;
	for (size_t i = 0; i < size; i++)
	{
		toStrformula += formula[i]->getValue() + " ";
	}

	return toStrformula;
}

void FormulaCell::setValue(std::string newFormula) {
	
	try {
		if (isFormula(newFormula)) {
			strFormula = newFormula;
		}
	}
	catch (...) {
		throw;
	}
}

I_Cell* FormulaCell::clone() const {
	return new FormulaCell(*this);
}

I_Value_Cell* FormulaCell::operator+(I_Value_Cell* other) const {

	I_Value_Cell* newCell = new FormulaCell(strFormula + "+" + other->getValue());
	return newCell;
}

I_Value_Cell* FormulaCell::operator-(I_Value_Cell* other) const {
	return nullptr;
}
I_Value_Cell* FormulaCell::operator*(I_Value_Cell* other) const {
	return nullptr;
}
I_Value_Cell* FormulaCell::operator/(I_Value_Cell* other) const {
	return nullptr;
}


I_Cell** FormulaCell::isFormula(std::string buffer) {

	if (buffer.empty()) 
		throw std::invalid_argument("Empty value");

	if (buffer.size() < 4) 
		throw std::invalid_argument("Invalid format");

	const char* str = buffer.c_str();
	while (*str && *str == ' ')						    // Skips leading spaces.
		++str;

	if (*str && *str++ != '=') 
		throw std::invalid_argument("Invalid format");


	std::vector<I_Cell*> stack;
	std::vector<I_Operation_Cell*> opStack;
	std::string value;
	bool relatinalOp = false;
	bool arithmeticOp = false;

	while (*str) {

		if (isArithmeticOperation(*str)) {
			if (arithmeticOp)
				throw std::invalid_argument("Invalid format");

			arithmeticOp = true;

			I_Value_Cell* cell = nullptr;
			cell = getValueCell(value);
			if (cell->getType() == Type::INVALID) {
				throw std::invalid_argument("Invalid format");
			}
			stack.push_back(cell);
			
			value.clear();

			I_Operation_Cell* current = getOperationCell(*str);
			while (!opStack.empty()) {
				if (*opStack.back() <= current) {    // TODO operator< in I_Operation_Cell
					break;
				}
				I_Cell* lastOp = opStack.back()->clone();
				stack.push_back(lastOp);
				opStack.pop_back();
			}
			opStack.push_back(getOperationCell(*str));
			*str++;
		}

		if (*str == '<' || *str == '>' || *str == '!' || *str == '=') {
			std::string relOp;
			relOp += *str;
			if (*++str && *str == '=') {
				if (relatinalOp || arithmeticOp) {
					throw std::invalid_argument("Invalid format");
				}
				relOp += *str++ + "=";
			}

			if (relatinalOp || arithmeticOp)
				throw std::invalid_argument("Invalid format");

			relatinalOp = true;
			I_Value_Cell* cell = getValueCell(value);
			if (cell->getType() == Type::INVALID) {
				throw std::invalid_argument("Invalid format");
			}
			stack.push_back(cell);
			value.clear();

			while (!opStack.empty()) {
				I_Cell* lastOp = opStack.back()->clone();
				stack.push_back(lastOp);
				opStack.pop_back();
			}
			//stack.push_back(getOperationCell(*str));
			I_Relational_Cell* ro = getRelationalCell(relOp);
			stack.push_back(ro);
		}

		value += *str++;
		arithmeticOp = false;
	}

	I_Value_Cell* lastValue = getValueCell(value);
	if (lastValue->getType() == Type::INVALID || lastValue->getType() == Type::EMPTY)
		throw std::invalid_argument("Invalid format");

	stack.push_back(lastValue);

	if (arithmeticOp) 
		throw std::invalid_argument("Invalid format");

	if (relatinalOp && opStack.size() != 0 && isRelationalOperation(opStack.back()->getType()))
		throw std::invalid_argument("Invalid format");
	
	while (!opStack.empty()) {
		stack.push_back(opStack.back()->clone());
		opStack.pop_back();
	}

	if (stack.size() + opStack.size() % 2 == 0) 
		throw std::invalid_argument("Invalid format");

	this->size = stack.size();
	I_Cell** formula = new I_Cell * [size];
	try {
		for (size_t i = 0; i < size; i++)
		{
			formula[i] = stack[i]->clone();
		}
	}
	catch (...) {
		for (size_t i = 0; i < size; i++)
		{
			delete formula[i];
		}
		delete[] formula;
	}

	return formula;
}

I_Value_Cell* FormulaCell::getValueCell(std::string buffer) {


	I_Value_Cell* value = nullptr;

	try {
		value = new IntegerCell(buffer);
		return value;
	}
	catch (...) {
	}

	try {
		value = new StringCell(buffer);
		return value;
	}
	catch (...) {
	}

	try {
		value = new FloatingPointNumberCell(buffer);
		return value;
	}
	catch (...) {
	}

	try {
		value = new ReferenceCell(buffer);
		return value;
	}
	catch (...) {
	}

	try {
		value = new EmptyCell(buffer);
		return value;
	}
	catch (...) {
	}

	return new InvalidCell("ERROR");
}

I_Cell** FormulaCell::getFormula() const {
	return formula;
}

unsigned short FormulaCell::getSize() const {
	return size;
}



I_Operation_Cell* FormulaCell::getOperationCell(char op) {

	if (op == '+') return new AdditionCell();
	if (op == '-') return new SubstractionCell();
	if (op == '*') return new MultiplicationCell();
	if (op == '/') return new DivisionCell();

	throw std::invalid_argument("Unknown arithmetic operation");
}

I_Relational_Cell* FormulaCell::getRelationalCell(std::string relationalOp) {

	if (relationalOp == "==") return new EqualCell();
	if (relationalOp == "!=") return new NotEqualCell();
	if (relationalOp == "<") return new LessThanCell();
	if (relationalOp == "<=") return new LessThanOrEqualCell();
	if (relationalOp == ">") return new GreaterThanCell();
	if (relationalOp == ">=") return new GreaterThanOrEqualCell();

	throw std::invalid_argument("Unknown arithmetic operation");
}

bool FormulaCell::isArithmeticOperation(char op) {
	return op == '+' || op == '-' || op == '*' || op == '/';
}

bool FormulaCell::isRelationalOperation(enum Type type) {

	if (type == Type::EQUAL) return true;
	if (type == Type::NOT_EQUAL) return true;
	if (type == Type::GREATER) return true;
	if (type == Type::GREATER_OR_EQUAL) return true;
	if (type == Type::LESS) return true;
	if (type == Type::LESS_OR_EQUAL) return true;

	return false;
}


//-------------------------------

EmptyCell::EmptyCell(std::string value)
	: I_Atomic_Cell(Type::EMPTY)
{
	isEmpty(value);
}

std::string EmptyCell::getValue() const {
	return value;
}

void EmptyCell::setValue(std::string s) {
	
	isEmpty(s);
}

I_Cell* EmptyCell::clone() const {
	return new EmptyCell(*this);
}

I_Value_Cell* EmptyCell::operator+(I_Value_Cell* other) const {
	if (this != other) {

		if (other->getType() == Type::INTEGER) {
			return new IntegerCell(other->getValue());
		}
		else if (other->getType() == Type::FLOATING_POINT_NUMBER) {
			return new FloatingPointNumberCell(std::stod(other->getValue()));
		}
		else if (other->getType() == Type::STRING) {
			return new StringCell(value);
		}
		else if (other->getType() == Type::INVALID) {
			return new InvalidCell(value);
		}
	}
	return new EmptyCell(value);
}

I_Value_Cell* EmptyCell::operator-(I_Value_Cell* other) const {
	return nullptr;
}
I_Value_Cell* EmptyCell::operator*(I_Value_Cell* other) const {
	return nullptr;
}
I_Value_Cell* EmptyCell::operator/(I_Value_Cell* other) const {
	return nullptr;
}

I_Atomic_Cell* EmptyCell::operator<(I_Atomic_Cell* other) const {
	
	if (this != other) {

		if (other->getType() == Type::INTEGER) {
			return 0 < std::stoll(other->getValue()) ? new IntegerCell(1) : new IntegerCell(0);
		}
		else if (other->getType() == Type::FLOATING_POINT_NUMBER) {
			return 0 < std::stod(other->getValue()) ? new IntegerCell(1) : new IntegerCell(0);
		}
		else if (other->getType() == Type::STRING) {
			I_Value_Cell* number = nullptr;
			try {
				number = new IntegerCell(other->getValue());
				if (number) {
					if (0 < std::stoll(number->getValue())) {
						delete number;
						return new IntegerCell(1);
					}
					delete number;
					return new IntegerCell(0);
				}
			}
			catch (std::invalid_argument e) {
				delete number;
			}
			catch (...) { 
				delete number;
				throw; 
			}
			try {
				number = new FloatingPointNumberCell(other->getValue());
				if (number) {
					if (0.0 < std::stod(number->getValue())) {
						delete number;
						return new IntegerCell(1);
					}
					delete number;
					return new IntegerCell(0);
				}
			}
			catch (std::invalid_argument e) {
				delete number;
			}
			catch (...) {
				delete number;
				throw;
			}
		}
	}

	return new IntegerCell(0);
}

I_Atomic_Cell* EmptyCell::operator>(I_Atomic_Cell* other) const {
	
	if (this != other) {

		if (other->getType() == Type::INTEGER) {
			return 0 > std::stoll(other->getValue()) ? new IntegerCell(1) : new IntegerCell(0);
		}
		else if (other->getType() == Type::FLOATING_POINT_NUMBER) {
			return 0 > std::stod(other->getValue()) ? new IntegerCell(1) : new IntegerCell(0);
		}
		else if (other->getType() == Type::STRING) {
			I_Value_Cell* number = nullptr;
			try {
				number = new IntegerCell(other->getValue());
				if (number) {
					if (0 > std::stoll(number->getValue())) {
						delete number;
						return new IntegerCell(1);
					}
					delete number;
					return new IntegerCell(0);
				}

				number = new FloatingPointNumberCell(other->getValue());
				if (number) {
					if (0.0 > std::stod(number->getValue())) {
						delete number;
						return new IntegerCell(1);
					}
					delete number;
					return new IntegerCell(0);
				}

				return new IntegerCell(0);
			}
			catch (std::invalid_argument e) {
			}
			catch (...) { throw; }
		}
	}

	return new IntegerCell(0);
}

I_Atomic_Cell* EmptyCell::operator<=(I_Atomic_Cell* other) const {
	I_Atomic_Cell* res = *this > other;

	if (res->getValue() == "0")
		res->setValue("1");
	else
		res->setValue("0");

	return res;
}

I_Atomic_Cell* EmptyCell::operator>=(I_Atomic_Cell* other) const {
	I_Atomic_Cell* res = *this < other;

	if (res->getValue() == "0")
		res->setValue("1");
	else
		res->setValue("0");

	return res;
}

I_Atomic_Cell* EmptyCell::operator==(I_Atomic_Cell* other) const {
	
	if (this != other) {

		if (other->getType() == Type::INTEGER) {
			return 0 == std::stoll(other->getValue()) ? new IntegerCell(1) : new IntegerCell(0);
		}
		else if (other->getType() == Type::FLOATING_POINT_NUMBER) {
			return 0.0 == std::stod(other->getValue()) ? new IntegerCell(1) : new IntegerCell(0);
		}
		else if (other->getType() == Type::STRING) {
			I_Value_Cell* number = nullptr;
			try {
				number = new IntegerCell(other->getValue());
				if (number) {
					if (0 == std::stoll(number->getValue())) {
						delete number;
						return new IntegerCell(0);
					}
					delete number;
					return new IntegerCell(1);
				}

				number = new FloatingPointNumberCell(other->getValue());
				if (number) {
					if (0.0 == std::stod(number->getValue())) {
						delete number;
						return new IntegerCell(0);
					}
					delete number;
					return new IntegerCell(1);
				}

				return new IntegerCell(0);
			}
			catch (std::invalid_argument e) {
			}
			catch (...) { 
				throw; 
			}
		}
	}

	return new IntegerCell(0);
}

I_Atomic_Cell* EmptyCell::operator!=(I_Atomic_Cell* other) const {
	I_Atomic_Cell* res = *this == other;

	if (res->getValue() == "0")
		res->setValue("1");
	else
		res->setValue("0");

	return res;
}


void EmptyCell::isEmpty(std::string buffer) {
	if (buffer.empty()) {
		return;
	}

	const char* str = buffer.c_str();
	while (*str) {
		if (*str != ' ' && *str != '\t') {
			throw std::invalid_argument("Invalid format. Not empty");
		}
		*str++;
	}
}

InvalidCell::InvalidCell(std::string value)
	: StringCell(value)
{}

std::string InvalidCell::getValue() const {
	return value;
}

I_Cell* InvalidCell::clone() const {
	return new InvalidCell(*this);
}

I_Value_Cell* InvalidCell::operator+(I_Value_Cell* other) const {

	return new InvalidCell(value);
}

I_Value_Cell* InvalidCell::operator-(I_Value_Cell* other) const {
	return nullptr;
}

I_Value_Cell* InvalidCell::operator*(I_Value_Cell* other) const {
	return nullptr;
}

I_Value_Cell* InvalidCell::operator/(I_Value_Cell* other) const {
	return nullptr;
}

I_Atomic_Cell* InvalidCell::operator<(I_Atomic_Cell* other) const {

	return new InvalidCell(value);
}

I_Atomic_Cell* InvalidCell::operator>(I_Atomic_Cell* other) const {

	return new InvalidCell(value);
}

I_Atomic_Cell* InvalidCell::operator<=(I_Atomic_Cell* other) const {

	return new InvalidCell(value);
}

I_Atomic_Cell* InvalidCell::operator>=(I_Atomic_Cell* other) const {

	return new InvalidCell(value);
}

I_Atomic_Cell* InvalidCell::operator==(I_Atomic_Cell* other) const {

	return new InvalidCell(value);
}

I_Atomic_Cell* InvalidCell::operator!=(I_Atomic_Cell* other) const {

	return new InvalidCell(value);
}
