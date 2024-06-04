#include"command_handler.h"

void CommandHandler::processCommand() {
	
	using std::cin;
	using std::cout;

	cout << "Welcome to Spreadsheet-MM monitor.\n\n";
	cout << "Commands end with ; \nType 'help;' for help. Type 'clear;' to clear the buffer.\n";

	char buffer[64];
	char delimiter;
	CustomTable* table = nullptr;
	while (true) {
		cout << "SS-MM>";
		cin.getline(buffer, sizeof(buffer), '\n');

		if (!cin) {
			cin.clear();
			cin.sync();
			cout << "Unexpected error occurred from the input. Try again.\n";
			continue;
		}

		if (strcmp(buffer, "exit;") == 0) {
			delete table;
			break;
		}
		else if (strcmp(buffer, "help;") == 0) {
			guide.getGuideline();
		}
		else if (strcmp(buffer, "clear;") == 0) {
			cout << "\x1B[2J\x1B[H";
		}
		else if (strcmp(buffer, "open;") == 0) {
			try {
				fp.free();									// Clear the file buffer.

				cout << "file: ";
				cin.getline(buffer, sizeof(buffer));

				if (!cin) {
					do {
						cin.clear();
						cin.sync();
						cout << "Unexpected error occurred from the input. Try again.\n";
						cout << "file: ";
						cin.getline(buffer, sizeof(buffer));
					} while (!cin);
				}

				cout << "delimiter: ";
				cin >> delimiter;

				if (!cin) {
					do {
						cin.clear();
						cin.sync();
						cout << "Unexpected error occurred from the input. Try again.\n";
						cout << "delimiter: ";
						cin.getline(buffer, sizeof(buffer));
					} while (!cin);
				}

				fp.open(buffer);
				cout << "Loading data from file successfully.\n";

				delete table;										// delete previous tables.
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				table = new CustomTable(fp.getContent(), delimiter);
				cout << "Creating table successfully.\n\n";
			}
			catch (const char*) {
				cout << "Failed to load data from file. Examine the file path.\n";
			}
			catch (std::invalid_argument& e) {
				cout << e.what();
			}
			catch (std::runtime_error& e) {
				cout << e.what();
			}
			catch (...) {
				cout << "Generic error.\n";
			}
		}
		else if (strcmp(buffer, "save;") == 0) {

			fp.save(fp.getPath(), table->convertToFileFormat());
		}
		else if (strcmp(buffer, "save as;") == 0) {
			
			cout << "path: ";
			cin.getline(buffer, sizeof(buffer));

			if (!cin) {
				do {
					cin.clear();
					cin.sync();
					cout << "Unexpected error occurred from the input. Try again.\n";
					cout << "path: ";
					cin.getline(buffer, sizeof(buffer));
				} while (!cin);
			}
			fp.saveAs(buffer, table->convertToFileFormat());
		}
		else if (strcmp(buffer, "print;") == 0) {
			try {
				if (!table) {
					cout << "No table to be displayed\n";
					continue;
				}
				cout << '\n';
				table->print();
				
				cout << '\n';
			}
			catch (...) {
				cout << "Generic error.\n";
			}
		}
		else if (strcmp(buffer, "edit;") == 0) {
			try {
				if (!table) {
					cout << "No table to be modified\n";
					continue;
				}

				unsigned short row, column;
			
				cout << "row: ";
				cin >> row;

				if (!cin) {
					cin.clear();
					cin.sync();
					cout << "Input problem occurred. Try again\n";
					continue;
				}

				cout << "column: ";
				cin >> column;

				if (!cin) {
					cin.clear();
					cin.sync();
					cout << "Input problem occurred. Try again\n";
					continue;
				}

				cout << "new cell: ";
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin.getline(buffer, sizeof(buffer), '\n');

				if (!cin) {
					cin.clear();
					cin.sync();
					cout << "Input problem occurred. Try again\n";
					continue;
				}

				table->edit(row, column, buffer);
			}
			catch (std::invalid_argument e) {
				cout << e.what();
			}
			catch (std::bad_alloc e) {
				cout << "Failed to edit table. Memory limit.\n";
			}
			catch (...) {
				cout << "Generic error.\n";
			}
		}
		
		cin.sync();
		//cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}
 