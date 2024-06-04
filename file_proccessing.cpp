#define _CRT_SECURE_NO_WARNINGS
#include"file_proccessing.h"
#include<fstream>

FileProcessing::FileProcessing(const FileProcessing& other) : FileProcessing() {
	
	content = new char[strlen(other.content) + 1];
	strcpy(content, other.content);
		
	try {
		path = new char[strlen(other.path) + 1];
		strcpy(path, other.path);
	}
	catch (...) {
		delete[] content;
		throw;
	}
}

FileProcessing::~FileProcessing() {
	free();
}

void FileProcessing::open(const char* path) {

	if (!path) {
		throw std::invalid_argument("Empty path");
	}
	std::ifstream file(path);

	if (!file.is_open()) {
		throw "Failed to open file";
	}
	
	
	this->path = new char[strlen(path) + 1];
	strcpy(this->path, path);

	if (firstReadingAttemp(file)) {
		try {
			this->path = new char[strlen(path) + 1];
			strcpy(this->path, path);
		}
		catch (...) {
			free();
			file.close();
			throw;
		}
		file.close();
		return;
	}

	if (secondReadingAttemp(file)) {
		try {
			this->path = new char[strlen(path) + 1];
			strcpy(this->path, path);
		}
		catch (...) {
			free();
			file.close();
			throw;
		}
		file.close();
		return;
	}
	
	file.close();
	throw "Failed operation of reading file";
}
void FileProcessing::save(const char* path, const char* content) {

	if (!path)
		throw "Failed to save content. Empty fail name found.";

	std::ofstream file(path, std::ios::trunc);

	if (!file.is_open()) {
		throw "Failed to save content. Unable to open file";
	}

	if (!file) {
		throw "Failed to save content.";
	}

	if (!this->content) {
		throw "No table to be stored in file";
	}

	file << content;
	
	if (!file) {
		throw "Failed operation of saving content.";
	}

	if (strcmp(this->content, content) != 0) {
		try {
			char* newContent = new char[strlen(content) + 1];
			strcpy(newContent, content);
			delete[] this->content;
			this->content = newContent;
		}
		catch (...) {
			// TODO
		}
	}

	file.close();
}
void FileProcessing::saveAs(const char* path, const char* cont) {

	save(path, cont);
}

const char* FileProcessing::getContent() const {
	return content;
}

const char* FileProcessing::getPath() const {
	return path;
}

void FileProcessing::free() {
	delete[] content;
	delete[] path;
}

bool FileProcessing::firstReadingAttemp(std::ifstream& file) {

	if (!file) {
		file.clear();
		return false;
	}

	file.seekg(0, std::ios::end);
	if (!file) {
		file.clear();
		return false;
	}

	std::streamsize fileSize = file.tellg();
	if (!file) {
		file.clear();
		return false;
	}

	file.seekg(0, std::ios::beg);
	if (!file) {
		file.clear();
		return false;
	}

	content = new char[fileSize + 1];
	file.getline(content, fileSize, file.eof());

	if (!file) {
		delete[] content;
		std::cin.clear();
		std::cin.sync();
		return false;
	}

	file.close();
	return true;
}

bool FileProcessing::secondReadingAttemp(std::ifstream& file) {

	if (!file) {
		file.clear();
		return false;
	}

	char c;
	std::string buffer;
	std::streamsize bytes = 0;
	while (!file.eof()) {
		
		file.get(c);
		if (!file) {
			file.clear();
			return false;
		}
		buffer += c;
	}

	content = new char[buffer.size() + 1];
	strcpy(content, buffer.c_str());

	return true;
}
