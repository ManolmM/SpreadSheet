#pragma warning(disable: 4996)
#pragma once
#include<iostream>
#include<string>
#include<vector>

class CommandGuideline {

public:

	CommandGuideline() : lines(8), guideline(load()) {}
	CommandGuideline(const CommandGuideline& other) : CommandGuideline() {
	}

	~CommandGuideline() {
		free();
	}

	void getGuideline() const {

		for (size_t i = 0; i < lines; i++)
		{
			std::cout << guideline[i];
		}
	}

	const char* getSpecifiedLine(unsigned short line) const {
		return guideline[line];
	}

private:

	char** load() {

		size_t max_size = 512;
		char** guide = new char* [lines];
		for (size_t i = 0; i < lines; i++)
		{
			guide[i] = new char[max_size];
		}

		try {
			strcpy(guide[0], "\n#######################################################\n\n");
			strcpy(guide[1], "(1)\nNAME\n\texit;\n\nDESCRIPTION\n\n\texit; terminates the program. If any changes are made following with no save; command, a warning message for saving the file will be displayed.\n\nPARAMETERS\n\n\tNone.\n\n\n");
			strcpy(guide[2], "(2)\nNAME\n\topen;\n\nDESCRIPTION\n\n\topen; opens a text file.\n\n\PARAMETERS:\n\n\tPath to the file.\n\tExample: open; /dir0/dir1/.../dirN/file_name.txt\n\n\n");
			strcpy(guide[3], "(3)\nNAME\n\tsave;\n\nDESCRIPTION\n\n\tsaves; saves table to the previously opened file. Any changes to the table will be taken into account.\n\nPARAMETERS\n\n\tNone.\n\n\n");
			strcpy(guide[4], "(4)\nNAME\n\tsave_as;\n\nDESCRIPTION\n\n\tsave_as; saves table to a specified file. Any changes to the table will be taken into account.\n\nPARAMETERS\n\n\tPath to the file.\n\tExample: save_as; /dir0/dir1/.../dirN/new_file_name.txt\n\n\n");
			strcpy(guide[5], "(5)\nNAME\n\tprint;\n\nDESCRIPTION\n\n\tprint; displays the file content presented in a table format.\n\nPARAMETERS\n\n\tNone.\n\n");
			strcpy(guide[6], "(6)\nNAME\n\tedit;\n\nDESCRIPTION\n\n\tedit; modifies a cell from the table.\n\nPARAMETERS\n\n\tRow of the table, starting from 1\n\tColumn of the table, starting from 1\n\tValue of the new cell: int, floating point, string, formula or reference cell.\n\tExample: edit; \n\t\t row: 2\n\t\t column: 4\n\t\t new cell: 40\n\n");
			strcpy(guide[7], "\n#######################################################\n");
		}
		catch (...) {
			free();
			throw;
		}
		return guide;
	}

	void free() {
		for (size_t i = 0; i < lines; i++)
		{
			delete guideline[i];
		}
		delete[] guideline;
	}

private:

	unsigned short lines;
	char** guideline;

};