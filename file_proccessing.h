#pragma once
#include"modifiable_cell.h"
#include"operation_cell.h"
#include<vector>


class FileProcessing {

public:

	FileProcessing() : content(nullptr), path(nullptr) {}
	FileProcessing(const FileProcessing& other);
	FileProcessing& operator=(const FileProcessing& other) = delete;
	~FileProcessing();

	void open(const char* path);   
	void save(const char* path, const char* content);
	void saveAs(const char* path, const char* content);

	const char* getContent() const;
	const char* getPath() const;
	void free();

private:

	bool firstReadingAttemp(std::ifstream& is);
	bool secondReadingAttemp(std::ifstream& is);

private:
	char* content;								   // Raw content from file.
	char* path;
};