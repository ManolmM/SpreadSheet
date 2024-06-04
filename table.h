#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include"modifiable_cell.h"
#include"operation_cell.h"
#include<vector>
#include"exception"

class I_BaseTable {

public:
	virtual ~I_BaseTable(){}
	virtual void print() const = 0;

};


class I_ModifiableTable : public I_BaseTable {

public:

	virtual void edit(unsigned short row, unsigned short column, std::string value) = 0;

};

class CustomTable : public I_ModifiableTable {

public:

	CustomTable(const char* content, char delimiter);
	CustomTable(const CustomTable& other);
	CustomTable& operator=(const CustomTable& other);
	virtual ~CustomTable();


	size_t getRowsSize() const;
	size_t getColumnsSize() const;
	const char* convertToFileFormat(char delimiter = ',') const;
	void addCell(std::vector<I_Value_Cell*>& row, std::string& buffer);

	virtual void print() const override;
	virtual void edit(unsigned short row, unsigned short column, std::string value) override;

private:

	void copyTable(I_Atomic_Cell*** table);
	void freeTable();
	void updateColumnOffset(size_t index, short value);
	void copy(const CustomTable& other);
	void copyTable(const std::vector<std::vector<I_Value_Cell*>>& table);
	I_Atomic_Cell* evaluate(unsigned short row, unsigned short columns, I_Cell** expression, unsigned short size);
	I_Atomic_Cell* find(std::string reference);
	void scan(const char* content, char delimiter);
	I_Atomic_Cell* identifyValueCell(std::string buffer) const;
	I_Atomic_Cell* identifyValueCellByType(enum Type type, const std::string& v) const;
	I_Atomic_Cell* applyOperationOnCells(std::vector<I_Cell*>& valueStack, std::vector<I_Cell*>& opStack);
	bool isArithmeticOperation(enum Type op) const;
	bool isRelationalOperation(enum Type type) const;


private:

	I_Atomic_Cell*** table;
	size_t rows;
	size_t columns;
	std::vector<short> columnOffset;					// Contains max display space of the values in each column.
	//CellProcessing cp;
	
};