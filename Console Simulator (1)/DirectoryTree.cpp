#include "stdafx.h"
#include "DirectoryTree.h"
#include "Path.h"

DirectoryTree::DirectoryTree()
	: root("/", nullptr), currentDirectory( &root )
{}

std::string DirectoryTree::currentDirectoryPath() const
{
	if (currentDirectory == &root)
		return currentDirectory->getName();

	const Directory* temp = currentDirectory;
	std::string path;

	while (temp != &root)
	{
		path.insert( 0,"/" + temp->getName());
		temp = temp->parent;
	}

	return path;
}

void DirectoryTree::changeDirectory(const std::string& path)
{
	if (!path.empty())	
		currentDirectory = getDirectory(path);		
}

void DirectoryTree::makeDirectory(const std::string& dirPathAndName)
{	
	if (!dirPathAndName.empty())
	{						
		auto pathAndName = Path::getFilePathAndName(dirPathAndName);
		Directory *tempDirPtr = getDirectory(pathAndName.first);		

		if (!tempDirPtr->containsEntity(pathAndName.second))
			tempDirPtr->addDirectory(pathAndName.second);
		else
			throw std::invalid_argument("entity " + pathAndName.second + " already exists");
	}
}

int DirectoryTree::count(const std::string &path) const
{
	return getDirectory(path)->nrOfEntities();
}

std::string DirectoryTree::getDirectoryString(const std::string &path) const
{
	std::string toReturn;

	if (!path.empty())
	{
		Directory *tempDirPtr = getDirectory(path);
		toReturn += "Directory of " + tempDirPtr->getName() + '\n';
		toReturn += tempDirPtr->toString();		
	}

	return toReturn;
}

void DirectoryTree::deleteEntity(const std::string& entPath)
{
	if (!entPath.empty())
	{
		auto pathAndName = Path::getFilePathAndName(entPath);
		Directory *tempDirPtr = getDirectory(pathAndName.first);

		if (!pathAndName.second.empty())
		{
			const Directory* toRemove = nullptr;

			if (pathAndName.second == ".")
				toRemove = tempDirPtr;
			else
				if (pathAndName.second == "..")
					toRemove = tempDirPtr->parent;
				else
					toRemove = tempDirPtr->getSubdirectory(pathAndName.second);

			if (toRemove != nullptr && (toRemove == currentDirectory || isAncestorTo(toRemove, currentDirectory)))
				throw std::invalid_argument("Cannot remove directory, because it is being used by another process");
			else
				tempDirPtr->removeEntity(pathAndName.second);
		}
		else
			throw std::invalid_argument( pathAndName.first + " cannot be removed");		
	}
}

void DirectoryTree::createFile(const std::string &filePath, const std::string &content)
{
	if (!filePath.empty())
	{
		auto pathAndName = Path::getFilePathAndName(filePath);
		Directory *tempDirPtr = getDirectory(pathAndName.first);

		if (!tempDirPtr->containsEntity(pathAndName.second))
			tempDirPtr->addFile(pathAndName.second, content);
		else
			throw std::invalid_argument("entity " + pathAndName.second + " already exists");
	}
}

bool DirectoryTree::isAncestorTo(const Directory *ancestor, const Directory* descendant) const
{
	if (ancestor != descendant)
	{
		while (descendant != nullptr)
		{
			if (descendant == ancestor)
				return true;

			descendant = descendant->parent;
		}
	}	

	return false;
}

Directory* DirectoryTree::getDirectory( const std::string &path ) const
{
	if (!path.empty())
	{
		Directory *tempDirPtr = Path::isRelative( path ) ? currentDirectory : (Directory *) &root;		
		auto list = Path::pathAsAList(path);		

		for (auto iter = list.begin(), endIter = list.end(); iter != endIter; ++iter)
		{
			if (*iter == ".")
				;
			else if (*iter == "..")
			{
				if (tempDirPtr != &root)
					tempDirPtr = (Directory *)tempDirPtr->parent;
				else
					throw std::invalid_argument("root directory has no parent");
			}
			else
				tempDirPtr = (Directory *)tempDirPtr->getSubdirectory(*iter); // may throw exception
		}				

		return tempDirPtr;
	}	

	return currentDirectory;
}