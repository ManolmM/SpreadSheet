#include"cell.h"
#include"modifiable_cell.h"
#include"operation_cell.h"
#include"file_proccessing.h"
#include"table.h"
#include"command_handler.h"
#include<fstream>

int main() {

	try {

		//FileProcessing fp;
		//fp.open("C:\\Users\\ManolMilev\\source\\repos\\OOP_Project\\Arithmetic _Table\\Arithmetic _Table\\table.txt");

		//CustomTable ct(fp.getContent(), ',');


		CommandHandler commandH;
		commandH.processCommand();

	}
	catch (std::exception& e) {
		std::cout << e.what();
	}
	catch (const char* e) {
		std::cout << e;
	}
	catch (std::bad_alloc& e) {
		std::cout << e.what();
	}
	catch (...) {
		std::cout << "Error";
	}
	
}