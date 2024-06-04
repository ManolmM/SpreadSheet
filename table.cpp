#include"table.h"
#include"modifiable_cell.h"

CustomTable::CustomTable(const char* content, char delimiter) : table(nullptr), columnOffset(16, 0) {
	
	try {
		scan(content, delimiter);
	}
	catch (...) {
		throw;
	}
	
}

CustomTable::CustomTable(const CustomTable& other) : rows(other.rows), columns(other.columns) {
	try {
		columnOffset = other.columnOffset;
		copyTable(other.table);
	}
	catch (...) {
		freeTable();
		throw;
	}
}

CustomTable& CustomTable::operator=(const CustomTable& other) {

	if (this != &other) {
		freeTable();	

		rows = other.rows;
		columns = other.columns;
		copyTable(other.table);
		columnOffset = other.columnOffset;
		
	}
	return *this;
}

CustomTable::~CustomTable() {
	freeTable();
}

void CustomTable::print() const {

	size_t offset = 0;
	for (size_t i = 0; i < rows; i++)
	{
		std::cout << '|';
		for (size_t j = 0; j < columns; j++) {
			offset = columnOffset[j] - table[i][j]->getValue().length();
			for (size_t k = 0; k < offset + 1; k++)
			{
				std::cout << ' ';
			}
	
			std::cout << table[i][j]->getValue() << " |";
		}
		std::cout << '\n';
	}
}

void CustomTable::edit(unsigned short R, unsigned short C, std::string buffer) {
	
	if (R == 0 || C == 0 || R > rows || C > columns) {
		throw std::invalid_argument("Couldn't adjust the cell. Invalid parameters");
	}

	I_Atomic_Cell* atomic = nullptr;

	short row = R - 1;
	short col = C - 1;
	try {

		atomic = new IntegerCell(buffer);
		if (table[row][col]->getType() == atomic->getType()) {
			table[row][col]->setValue(atomic->getValue());
			delete atomic;
			return;
		}
		
		delete table[row][col];
		table[row][col] = atomic;
		
		return;
	}
	catch (std::bad_alloc& e) {
		delete atomic;
		throw std::runtime_error("Memory limit reached. Unable to modify the specified cell.");
	}
	catch (...) {
		delete atomic;
	}

	try {

		atomic = new StringCell(buffer);
		if (table[row][col]->getType() == atomic->getType()) {
			table[row][col]->setValue(atomic->getValue());
			delete atomic;
			return;
		}

		delete table[row][col];
		table[row][col] = atomic;

		return;
	}
	catch (std::bad_alloc& e) {
		delete atomic;
		throw std::runtime_error("Memory limit reached. Unable to modify the specified cell.");
	}
	catch (...) {
		delete atomic;
	}


	try {

		atomic = new FloatingPointNumberCell(buffer);
		if (table[row][col]->getType() == atomic->getType()) {
			table[row][col]->setValue(atomic->getValue());
			delete atomic;
			return;
		}

		delete table[row][col];
		table[row][col] = atomic;

		return;
	}
	catch (std::bad_alloc& e) {
		delete atomic;
		throw std::runtime_error("Memory limit reached. Unable to modify the specified cell.");
	}
	catch (...) {
		delete atomic;
	}

	I_Value_Cell* value = nullptr;
	try {

		value = new ReferenceCell(buffer);
		I_Atomic_Cell* ref = find(value->getValue());
		delete table[row][col];
		delete value;
		table[row][col] = ref;
		return;

	}
	catch (std::bad_alloc& e) {
		delete value;
		throw std::runtime_error("Memory limit reached. Unable to modify the specified cell.");
	}
	catch (...) {
		delete value;
	}

	FormulaCell* formula = nullptr;
	try {

		formula = new FormulaCell(buffer);

		I_Atomic_Cell* temp = evaluate(row, col, formula->getFormula(), formula->getSize());
		delete table[row][col];
		delete formula;
		table[row][col] = temp;
		return;
	}
	catch (std::bad_alloc& e) {
		delete formula;
		throw std::runtime_error("Memory limit reached. Unable to modify the specified cell.");
	}
	catch (...) {
		delete formula;
	}


	try {
		atomic = new EmptyCell(buffer);
		delete table[row][col];
		table[row][col] = atomic;
		return;
	}
	catch (std::bad_alloc& e) {
		delete atomic;
		throw std::runtime_error("Memory limit reached. Unable to modify the specified cell.");
	}
	catch (...) {
		delete atomic;
	}

	try {

		if (table[row][col]->getType() == Type::INVALID)
			return;

		atomic = new InvalidCell("ERROR");
		delete table[row][col];
		table[row][col] = atomic;
	}
	catch (std::bad_alloc& e) {
		delete atomic;
		throw std::runtime_error("Memory limit reached. Unable to modify the specified cell.");
	}
	catch (...) {
		delete atomic;
	}

	throw std::invalid_argument("Failed to modify the specified cell. Invalid format.");
}

void CustomTable::updateColumnOffset(size_t index, short value) {
	
	if (index < 0 || index >= rows) {
		throw std::invalid_argument("Update index max column index out of bounds");
	}

	columnOffset[index] = value;
}

void CustomTable::freeTable() {
	
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < columns; j++)
		{
			delete table[i][j];
		}
		delete[] table[i];
	}

	delete[] table;
}

void CustomTable::copyTable(I_Atomic_Cell*** t) {
	
	this->table = new I_Atomic_Cell **[rows];
	for (size_t i = 0; i < rows; i++)
	{
		table[i] = new I_Atomic_Cell * [columns];
		for (size_t j = 0; j < columns; j++)
		{
			this->table[i][j] = (I_Atomic_Cell*) t[i][j]->clone();  // TODO Check if it a good idea to cast to I_Atomic_Cell!!!!
		}
	}
}

void copyRow(std::vector<I_Cell*>& row, unsigned short indexRow) {
}

void CustomTable::copy(const CustomTable& other) {

}

void CustomTable::copyTable(const std::vector<std::vector<I_Value_Cell*>>& table) {

	this->table = new I_Atomic_Cell **[rows];
	for (size_t i = 0; i < rows; i++)
	{
		this->table[i] = new I_Atomic_Cell * [columns];
		for (size_t j = 0; j < columns; j++)
		{
			if (table[i].size() <= j) {	    //There is no allocated cells, so it has to me empty cell in the table.
				this->table[i][j] = new EmptyCell("");
			} else {
				this->table[i][j] = (I_Atomic_Cell*) table[i][j]->clone();
			}
		}
	}
}


I_Atomic_Cell* CustomTable::evaluate(unsigned short row, unsigned short columns, I_Cell** formula, unsigned short size) {

	std::vector<I_Cell*> valueStack;
	std::vector<I_Cell*> opStack;

	size_t at = 0;

	while (at < size) {

		if (isArithmeticOperation(formula[at]->getType())) {
			
			opStack.push_back(formula[at]);			
			valueStack.back() = applyOperationOnCells(valueStack, opStack);
			opStack.pop_back();
			++at;
			continue;
		}
		else if (isRelationalOperation(formula[at]->getType())) {		
			opStack.push_back(formula[at++]);

		}
		valueStack.push_back(formula[at++]);
	}

	if (valueStack.size() == 2) {
		if (opStack.size() == 1)
			return applyOperationOnCells(valueStack, opStack);	
	}
	else if (valueStack.size() == 1 && opStack.size() == 0) {
		return (I_Atomic_Cell*) valueStack.back()->clone();
	}

	throw "Failed to evaluate formula";
}

I_Atomic_Cell* CustomTable::find(std::string reference) {  //TODO has to return I_Atomic_Value

	if (reference.empty()) return nullptr;

	short row = 0;
	short col = 0;
	short at = 0;
	std::string buff;

	if (reference[at] == 'R') {
		while (reference[++at] != 'C')
			buff += reference[at];
		
		row = std::stoll(buff);

		++at;
		buff.clear();
		while (reference[at])
			buff += reference[at++];

		col = std::stoll(buff);
	}

	if (reference[at] == 'C') {
		while (reference[++at] != 'R')
			buff += reference[at];

		col = std::stoll(buff);

		++at;
		buff.clear();
		while (reference[at])
			buff += reference[at++];

		row = std::stoll(buff);
	}

	if (row == 0 || col == 0) throw std::invalid_argument("Invalid reference");

	return (I_Atomic_Cell*) table[row - 1][col - 1]->clone();
}

void CustomTable::scan(const char* content, char delimiter) {
	if (delimiter == ' ' || delimiter == '\n') {
		throw std::invalid_argument("Selected delimiter character is not allowed");
	}

	if (!content) {
		throw "File content is empty. No table to be generated";
	}
	size_t maxRow = 0, maxColumn = 0;
	size_t tempRow = 0, tempColumn = 0;
	size_t indexAt = 0;
	bool isfileEmpty = false;

	if (!*content) {
		isfileEmpty = true;
	}

	// Define rows and columns numbers.
	while (content[indexAt]) {

		if (content[indexAt++] == '\n')
			maxRow++;
	}

	if (tempRow == 0 && !isfileEmpty)
		tempRow++;

	// Sets the variable for another iteration.
	indexAt = 0;

	//table.resize;
	std::vector<std::vector<I_Value_Cell*>> tempTable;    // TODO check if Cell* is deleted and copied correctly
	std::vector<I_Value_Cell*> row;
	//row.resize(16);
	std::string buffer;


	try {
		while (content[indexAt] != '\0') {

			if (content[indexAt] == '\n') {						   // Assume the end of the row has occurred.

				addCell(row, buffer);
				tempTable.push_back(row);
				row.clear();
				indexAt++;
				buffer = "";									   // clear the buffer.
				tempColumn++;
				if (maxColumn < tempColumn)
					maxColumn = tempColumn;

				tempColumn = 0;
				continue;
			}

			if (content[indexAt] == delimiter) {

				addCell(row, buffer);
				indexAt++;
				buffer = "";									   // clear the buffer.
				tempColumn++;
				if (maxColumn < tempColumn)
					maxColumn = tempColumn;

				continue;
			}

			buffer += content[indexAt++];
		}

		if (strlen(content) > 0 && content[indexAt - 1] != '\n') {    // Assume that a potential cell could be stored.
			addCell(row, buffer);
			++tempRow;
			if (maxColumn < tempColumn)
				maxColumn = tempColumn;
		}

		this->rows = maxRow;
		this->columns = maxColumn;
		copyTable(tempTable);
	}
	catch (...) {
		throw;
	}
}

void CustomTable::addCell(std::vector<I_Value_Cell*>& row, std::string& buffer) {

	I_Value_Cell* newCell = identifyValueCell(buffer);
	row.push_back(newCell);

	try {
		if (row.size() == 1) {
			if (columnOffset[0] < newCell->getValue().size()) {					// Update max offset for each column.
				columnOffset[0] = newCell->getValue().size();
			}
			return;
		}
		if (row.size() > 1 && (columnOffset[row.size() - 1] < newCell->getValue().size())) {
			columnOffset[row.size() - 1] = newCell->getValue().size();
		}
	}
	catch (...) {
		throw;
	}
}


size_t CustomTable::getRowsSize() const {
	return rows;
}

size_t CustomTable::getColumnsSize() const {
	return columns;
}

const char* CustomTable::convertToFileFormat(char delimiter) const {
	
	std::string converted;
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < columns; j++)
		{
			if (table[i][j]->getType() == Type::STRING) {
				std::string t = "\"" + table[i][j]->getValue() + "\"";
				StringCell temp(t);
				std::string r = temp.getRawString();
				converted += temp.getRawString();
			}
			else {
				if (table[i][j]->getType() != Type::INVALID) {
					converted += table[i][j]->getValue();
				}
			}

			if (j < columns - 1) {
				converted += delimiter;
			}
		}
		converted += "\n";
	}

	char* result = new char[converted.size() + 1];
	strcpy(result, converted.c_str());
	
	return result;
}

I_Atomic_Cell* CustomTable::identifyValueCell(std::string buffer) const{

	I_Atomic_Cell* value = nullptr;

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
		value = new EmptyCell(buffer);
		return value;
	}
	catch (...) {
	}

	return new InvalidCell("ERROR");
}

I_Atomic_Cell* CustomTable::identifyValueCellByType(enum Type type, const std::string& value) const {
	
	if (type == Type::INTEGER) 
		return new IntegerCell(value);

	if (type == Type::FLOATING_POINT_NUMBER) 
		return new FloatingPointNumberCell(value);

	if (type == Type::EMPTY) 
		return new EmptyCell(value);

	if (type == Type::STRING) 
		return new StringCell(value);

		//return new InvalidCell(value);
}

I_Atomic_Cell* CustomTable::applyOperationOnCells(std::vector<I_Cell*>& valueStack, std::vector<I_Cell*>& opStack) {
	
	I_Cell* top = valueStack.back();
	I_Cell* operation = opStack.back();
	I_Atomic_Cell* rhs = nullptr;
	I_Atomic_Cell* lhs = nullptr;
	I_Value_Cell* result = nullptr;

	try {
		// process the rhs first.
		if (top->getType() == Type::REFERENCE) {
			rhs = find(top->getValue());
			valueStack.pop_back();
			top = valueStack.back();
		}
		else {
			rhs = identifyValueCellByType(top->getType(), top->getValue());
			valueStack.pop_back();
			top = valueStack.back();
		}

		// process the lhs
		if (top->getType() == Type::REFERENCE) {
			lhs = find(top->getValue());
			valueStack.pop_back();

		}
		else {
			lhs = identifyValueCellByType(top->getType(), top->getValue());
			valueStack.pop_back();
		}

		
		if (operation->getType() == Type::ADDITION) {
			result = *lhs + rhs;
		}
		else if (operation->getType() == Type::DIVISION) {
			result = *lhs / rhs;
		}
		else if (operation->getType() == Type::SUBTRACTION) {
			result = *lhs - rhs;
		}
		else if (operation->getType() == Type::MULTIPLICATION) {
			result = *lhs * rhs;
		}
		else if (operation->getType() == Type::EQUAL) {
			result = *lhs == rhs;
		}
		else if (operation->getType() == Type::NOT_EQUAL) {
			result = *lhs != rhs;
		}
		else if (operation->getType() == Type::LESS) {
			result = *lhs < rhs;
		}
		else if (operation->getType() == Type::LESS_OR_EQUAL) {
			result = *lhs <= rhs;
		}
		else if (operation->getType() == Type::GREATER) {
			result = *lhs > rhs;
		}
		else if (operation->getType() == Type::GREATER_OR_EQUAL) {
			result = *lhs >= rhs;
		}
			
		valueStack.push_back(result);
		
		delete lhs;
		delete rhs;
		return (I_Atomic_Cell*) result;
	}
	catch (...) {
		delete lhs;
		delete rhs;
		delete result;
		throw;
	}
}

bool CustomTable::isArithmeticOperation(enum Type op) const {
	return op == Type::ADDITION || op == Type::SUBTRACTION || op == Type::MULTIPLICATION || op == Type::DIVISION;
}

bool CustomTable::isRelationalOperation(enum Type relationalOp) const {

	if (relationalOp == Type::EQUAL) return true;
	if (relationalOp == Type::NOT_EQUAL) return true;
	if (relationalOp == Type::GREATER) return true;
	if (relationalOp == Type::GREATER_OR_EQUAL) return true;
	if (relationalOp == Type::LESS) return true;
	if (relationalOp == Type::LESS_OR_EQUAL) return true;

	return false;
}