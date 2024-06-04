#pragma once
#include"cell.h"
#include"cell_type.h"

class EqualCell : public I_Relational_Cell {

public:

	EqualCell();

	virtual std::string getValue() const override;
	virtual I_Cell* clone() const override;

};

class NotEqualCell : public I_Relational_Cell {

public:

	NotEqualCell();

	virtual std::string getValue() const override;
	virtual I_Cell* clone() const override;
};

class LessThanCell : public I_Relational_Cell {

public:

	LessThanCell();

	virtual std::string getValue() const override;
	virtual I_Cell* clone() const override;

};

class GreaterThanCell : public I_Relational_Cell {

public:

	GreaterThanCell();

	virtual std::string getValue() const override;
	virtual I_Cell* clone() const override;
};

class GreaterThanOrEqualCell : public I_Relational_Cell {

public:

	GreaterThanOrEqualCell();

	virtual std::string getValue() const override;
	virtual I_Cell* clone() const override;
};

class LessThanOrEqualCell : public I_Relational_Cell {

public:

	LessThanOrEqualCell();

	virtual std::string getValue() const override;
	virtual I_Cell* clone() const override;

};