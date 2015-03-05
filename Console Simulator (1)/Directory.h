#pragma once

#include <set>
#include <utility>
#include "File.h"
using namespace std::rel_ops;

template< typename T >
struct Comparer
{
	bool operator()(T *a, T *b)
	{
		return *a < *b;
	}
};

class Directory : public Entity
{
public:	
	Directory(const std::string& dirName, const Directory *parentDir);
	virtual ~Directory();

	void addFile(const std::string& fileName, const std::string& content);
	void addDirectory(const std::string& dirName);
	void removeEntity(const std::string& entName);
	virtual std::string toString() const;

	bool containsEntity(const std::string& name) const;
	bool operator==(const Directory& right) const;
	bool operator<(const Directory& right) const;	
	int nrOfEntities() const;

	const Directory* getSubdirectory(const std::string dirName) const;
private:		
	std::set < Entity*, Comparer< Entity > > entities;	// files and directories

	const Entity * getEntity(const std::string name) const;	// a nullptr if not found such a name
	typedef std::set < Entity*, Comparer< Entity > > EntType;	
};