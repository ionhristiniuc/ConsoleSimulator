#include "stdafx.h"
#include "Directory.h"
#include <iostream>

Directory::Directory(const std::string& dirName, const Directory *parentDir)
	: Entity(!dirName.empty() ? dirName : throw std::invalid_argument("Directory name cannot be empty"), parentDir)
{}

Directory::~Directory()
{
	for (EntType::iterator iter = entities.begin(), endIter = entities.end(); iter != endIter; ++iter)					
		delete *iter;
}

void Directory::addFile(const std::string& fileName, const std::string& content)
{
	entities.insert(new File(fileName, this, content));
}

void Directory::addDirectory(const std::string& dirName)
{
	entities.insert(new Directory(dirName, this));
}

void Directory::removeEntity(const std::string& entName)
{
	const Entity *tempPtr = getEntity(entName);
	if (tempPtr != nullptr)
	{
		entities.erase(&Entity(entName, this));
		delete tempPtr;
	}
	else
		throw std::invalid_argument("No " + entName + " entity found");
}

bool Directory::containsEntity(const std::string& name) const
{
	return getEntity(name) != nullptr;
}

const Entity * Directory::getEntity(const std::string name) const
{
	EntType::const_iterator iter = entities.find(&Entity(name, this));
	return iter != entities.end() ? *iter : nullptr;
}

int Directory::nrOfEntities() const
{
	return entities.size();
}

bool Directory::operator==(const Directory& right) const
{
	return Entity::operator==(right);
}

bool Directory::operator<(const Directory& right) const
{
	return Entity::operator<(right);
}

const Directory* Directory::getSubdirectory(const std::string dirName) const
{
	const Entity *ent;
	if ( ( ent = getEntity(dirName) ) != nullptr )
	{
		const Directory *dir = nullptr;
		if ((dir = dynamic_cast< const Directory *>(ent)) != 0)
			return dir;
	}		
	
	throw std::invalid_argument("No such directory found \"" + dirName + "\"");
}

std::string Directory::toString() const
{
	std::string toReturn;		

	toReturn = "." + std::string("\t<DIR>\n");
	if (this->parent != nullptr)
		toReturn += ".." + std::string("\t<DIR>\n");

	for each (Entity * ent in entities)
	{		
		if (dynamic_cast< const Directory *>(ent) != nullptr )
			toReturn += ent->getName() + "\t<DIR>\n";
		else
			toReturn += ent->getName() + "\t<FILE>\n";
	}		

	return toReturn;
}