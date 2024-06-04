#pragma once
#include"command_guideline.h"
#include"table.h"
#include"file_proccessing.h"

class CommandHandler {

public:

	void processCommand();

private:

	CommandGuideline guide;
	FileProcessing fp;
	//CustomTable* table;
};