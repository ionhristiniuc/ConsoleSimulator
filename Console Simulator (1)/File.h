#pragma once

#include <string>
#include "Entity.h"

class Directory;

class File : public Entity
{
public:	
	File(const std::string& fileName, const Directory *parentDir);
	File(const std::string& fileName, const Directory *parentDir, const std::string& content);

	bool operator==(const File& right) const;
	bool operator<(const File& right) const;
private:
	std::string content;
};