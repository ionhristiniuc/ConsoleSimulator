#include "stdafx.h"
#include "File.h"
#include <iostream>

File::File(const std::string& fileName, const Directory *parentDir)
	: Entity(fileName.size() != 0 ? fileName : throw std::invalid_argument("File name cannot be empty"), parentDir)
{}

File::File(const std::string& fileName, const Directory *parentDir, const std::string& fileContent)
	: Entity(fileName.size() != 0 ? fileName : throw std::invalid_argument("File name cannot be empty"), parentDir),
	content(fileContent)
{}

bool File::operator==(const File& right) const
{
	return Entity::operator==(right);
}

bool File::operator<(const File& right) const
{
	return Entity::operator<(right);
}