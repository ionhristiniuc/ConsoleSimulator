#pragma once

#include "Directory.h"

class DirectoryTree
{
public:
	DirectoryTree();
	void changeDirectory(const std::string& path);
	void makeDirectory(const std::string& dirPathAndName);
	void deleteEntity(const std::string& entPath);
	std::string getDirectoryString(const std::string &path) const;
	std::string currentDirectoryPath() const;
	void createFile(const std::string &filePath, const std::string &content);
	int count(const std::string &path) const;
private:
	Directory root;	
	Directory* currentDirectory;	// a reference to the current directory
	
	Directory* getDirectory(const std::string &path) const;
	bool isAncestorTo(const Directory *ancestor, const Directory* descendant) const;
};