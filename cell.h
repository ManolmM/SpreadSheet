#pragma once
#include<iostream>
#include<string>
#include"cell_Type.h"

class I_Cell {

public: 
	I_Cell(enum Type type) : type(type) {}
	virtual ~I_Cell() {}

	virtual std::string getValue() const = 0;
	virtual I_Cell* clone() const = 0;
	virtual bool isValue() const = 0;

	Type getType() const {
		return type;
	}
	void setType(enum Type type) {
		this->type = type;
	}

private:

	enum Type type;
};

class I_Value_Cell : public I_Cell {

public:

	I_Value_Cell(enum Type type) : I_Cell(type) {}
	virtual ~I_Value_Cell() {}

	//virtual std::string getValue() const = 0;
	virtual void setValue(std::string) = 0;
	//virtual I_Value_Cell* clone() const = 0;
	virtual bool isValue() const {return true;}

	virtual I_Value_Cell* operator+(I_Value_Cell* other) const = 0;
	virtual I_Value_Cell* operator-(I_Value_Cell* other) const = 0;
	virtual I_Value_Cell* operator*(I_Value_Cell* other) const = 0;
	virtual I_Value_Cell* operator/(I_Value_Cell* other) const = 0;

};

class I_Atomic_Cell : public I_Value_Cell {

public:
	I_Atomic_Cell(enum Type type) : I_Value_Cell(type) {}
	virtual ~I_Atomic_Cell() {}


	virtual I_Atomic_Cell* operator<(I_Atomic_Cell* other) const = 0;
	virtual I_Atomic_Cell* operator>(I_Atomic_Cell* other) const = 0;
	virtual I_Atomic_Cell* operator<=(I_Atomic_Cell* other) const = 0;
	virtual I_Atomic_Cell* operator>=(I_Atomic_Cell* other) const = 0;
	virtual I_Atomic_Cell* operator==(I_Atomic_Cell* other) const = 0;
	virtual I_Atomic_Cell* operator!=(I_Atomic_Cell* other) const = 0;

};

class I_Operation_Cell : public I_Cell {

public:

	I_Operation_Cell(enum Type type) : I_Cell(type) {}
	virtual ~I_Operation_Cell() {}

	virtual std::string getValue() const = 0;
	virtual bool isValue() const { return false; }
	virtual bool operator< (I_Operation_Cell* op)    const = 0;
	virtual bool operator> (I_Operation_Cell* other) const = 0;
	virtual bool operator<=(I_Operation_Cell* other) const = 0;
	virtual bool operator>=(I_Operation_Cell* other) const = 0;
	virtual bool operator==(I_Operation_Cell* other) const = 0;
	virtual bool operator!=(I_Operation_Cell* other) const = 0;

};

class I_Relational_Cell : public I_Cell {

public:
	I_Relational_Cell(enum Type type) : I_Cell(type) {}
	virtual ~I_Relational_Cell() {}

	virtual std::string getValue() const = 0;
	virtual bool isValue() const { return true; }

};
