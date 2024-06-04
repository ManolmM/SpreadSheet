#pragma once
#include"cell.h"
#include"cell_Type.h"
#include"operation_cell.h"
#include"relational_cell.h"
#include<iostream>
#include<vector>

class IntegerCell : public I_Atomic_Cell {

public:

	IntegerCell(long long value); 
	IntegerCell(std::string value);
	

	virtual std::string getValue() const override;
	virtual void setValue(std::string) override;
	virtual I_Cell* clone() const override;

	virtual I_Value_Cell* operator+(I_Value_Cell* other) const;
	virtual I_Value_Cell* operator-(I_Value_Cell* other) const override;
	virtual I_Value_Cell* operator*(I_Value_Cell* other) const override;
	virtual I_Value_Cell* operator/(I_Value_Cell* other) const override;

	virtual I_Atomic_Cell* operator<(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator>(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator<=(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator>=(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator==(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator!=(I_Atomic_Cell* other) const override;

	void setValue(long long);
	long long getLongLongValue() const;
	
private:

	std::string isInteger(std::string buffer);

private:
	long long value;

};

class FloatingPointNumberCell : public I_Atomic_Cell {

public:

	FloatingPointNumberCell(double value);
	FloatingPointNumberCell(std::string value);
	
	

	virtual std::string getValue() const override;
	virtual void setValue(std::string) override;
	virtual I_Cell* clone() const override;

	virtual I_Value_Cell* operator+(I_Value_Cell* other) const override;
	virtual I_Value_Cell* operator-(I_Value_Cell* other) const override;
	virtual I_Value_Cell* operator*(I_Value_Cell* other) const override;
	virtual I_Value_Cell* operator/(I_Value_Cell* other) const override;

	virtual I_Atomic_Cell* operator<(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator>(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator<=(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator>=(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator==(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator!=(I_Atomic_Cell* other) const override;

	void setValue(double);
	double getDoubleValue() const;

private:

	std::string isFloatingPointNumber(std::string value);
private:

	double value;
};


class StringCell : public I_Atomic_Cell {

public:

	StringCell(std::string value);

	virtual std::string getValue() const override;
	virtual void setValue(std::string) override;
	virtual I_Cell* clone() const override;

	virtual I_Value_Cell* operator+(I_Value_Cell* other) const override;
	virtual I_Value_Cell* operator-(I_Value_Cell* other) const override;
	virtual I_Value_Cell* operator*(I_Value_Cell* other) const override;
	virtual I_Value_Cell* operator/(I_Value_Cell* other) const override;

	virtual I_Atomic_Cell* operator<(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator>(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator<=(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator>=(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator==(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator!=(I_Atomic_Cell* other) const override;


	std::string getRawString();
private:

	void isText(std::string buffer);
private:

	std::string value;
};


class ReferenceCell : public I_Value_Cell {

public:

	ReferenceCell(std::string reference);

	virtual std::string getValue() const override;
	virtual void setValue(std::string) override;
	virtual I_Cell* clone() const override;

	virtual I_Value_Cell* operator+(I_Value_Cell* other) const override;
	virtual I_Value_Cell* operator-(I_Value_Cell* other) const override;
	virtual I_Value_Cell* operator*(I_Value_Cell* other) const override;
	virtual I_Value_Cell* operator/(I_Value_Cell* other) const override;

private:
	//bool equal()
	std::string isReference(std::string value);
private:

	std::string reference;

};

class FormulaCell : public I_Value_Cell {

public:

	FormulaCell(std::string formula);
	FormulaCell(const FormulaCell& other);
	FormulaCell& operator=(const FormulaCell& other);
	~FormulaCell();


	virtual std::string getValue() const override;
	virtual void setValue(std::string) override;
	virtual I_Cell* clone() const override;

	virtual I_Value_Cell* operator+(I_Value_Cell* other) const override;
	virtual I_Value_Cell* operator-(I_Value_Cell* other) const override;
	virtual I_Value_Cell* operator*(I_Value_Cell* other) const override;
	virtual I_Value_Cell* operator/(I_Value_Cell* other) const override;

	I_Cell** getFormula() const;
	unsigned short getSize() const;

private:

	I_Cell** isFormula(std::string buffer);
	I_Value_Cell* getValueCell(std::string buffer);
	I_Operation_Cell* getOperationCell(char op);
	I_Relational_Cell* getRelationalCell(std::string relationalOp);
	bool isArithmeticOperation(char op);
	bool isRelationalOperation(enum Type type);
	void free();
	void copy(const FormulaCell& other);

private:
	I_Cell** formula;
	short size;
	std::string strFormula;
};

class InvalidCell : public StringCell{

public:

	InvalidCell(std::string value);

	virtual std::string getValue() const override;
	virtual I_Cell* clone() const override;

	virtual I_Value_Cell* operator+(I_Value_Cell* other) const override;
	virtual I_Value_Cell* operator-(I_Value_Cell* other) const override;
	virtual I_Value_Cell* operator*(I_Value_Cell* other) const override;
	virtual I_Value_Cell* operator/(I_Value_Cell* other) const override;

	virtual I_Atomic_Cell* operator<(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator>(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator<=(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator>=(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator==(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator!=(I_Atomic_Cell* other) const override;

private:

	std::string value;

};



class EmptyCell : public I_Atomic_Cell {

public:
	EmptyCell(std::string value);

	virtual std::string getValue() const override;
	virtual void setValue(std::string) override;
	virtual I_Cell* clone() const override;

	virtual I_Value_Cell* operator+(I_Value_Cell* other) const override;
	virtual I_Value_Cell* operator-(I_Value_Cell* other) const override;
	virtual I_Value_Cell* operator*(I_Value_Cell* other) const override;
	virtual I_Value_Cell* operator/(I_Value_Cell* other) const override;

	virtual I_Atomic_Cell* operator<(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator>(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator<=(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator>=(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator==(I_Atomic_Cell* other) const override;
	virtual I_Atomic_Cell* operator!=(I_Atomic_Cell* other) const override;

private:

	void isEmpty(std::string value);
private:

	std::string value;
};