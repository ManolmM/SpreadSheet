#pragma once
#include"cell.h"

class AdditionCell : public I_Operation_Cell {

public:

	AdditionCell();

	virtual std::string getValue() const override;
	virtual I_Cell* clone() const override;

	virtual bool operator< (I_Operation_Cell* other) const override;
	virtual bool operator> (I_Operation_Cell* other) const override;
	virtual bool operator<=(I_Operation_Cell* other) const override;
	virtual bool operator>=(I_Operation_Cell* other) const override;
	virtual bool operator==(I_Operation_Cell* other) const override;
	virtual bool operator!=(I_Operation_Cell* other) const override;
};

class SubstractionCell : public I_Operation_Cell {

public:

	SubstractionCell();

	virtual std::string getValue() const override;
	virtual I_Cell* clone() const override;

	virtual bool operator< (I_Operation_Cell* other) const override;
	virtual bool operator> (I_Operation_Cell* other) const override;
	virtual bool operator<=(I_Operation_Cell* other) const override;
	virtual bool operator>=(I_Operation_Cell* other) const override;
	virtual bool operator==(I_Operation_Cell* other) const override;
	virtual bool operator!=(I_Operation_Cell* other) const override;
};

class DivisionCell : public I_Operation_Cell {

public:

	DivisionCell();

	virtual std::string getValue() const override;
	virtual I_Cell* clone() const override;

	virtual bool operator< (I_Operation_Cell* other) const override;
	virtual bool operator> (I_Operation_Cell* other) const override;
	virtual bool operator<=(I_Operation_Cell* other) const override;
	virtual bool operator>=(I_Operation_Cell* other) const override;
	virtual bool operator==(I_Operation_Cell* other) const override;
	virtual bool operator!=(I_Operation_Cell* other) const override;
};

class MultiplicationCell : public I_Operation_Cell {

public:

	MultiplicationCell();

	virtual std::string getValue() const override;
	virtual I_Cell* clone() const override;

	virtual bool operator< (I_Operation_Cell* other) const override;
	virtual bool operator> (I_Operation_Cell* other) const override;
	virtual bool operator<=(I_Operation_Cell* other) const override;
	virtual bool operator>=(I_Operation_Cell* other) const override;
	virtual bool operator==(I_Operation_Cell* other) const override;
	virtual bool operator!=(I_Operation_Cell* other) const override;
};
