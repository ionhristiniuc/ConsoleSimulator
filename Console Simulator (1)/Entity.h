#ifndef ENTITY_H
#define ENTITY_H

class Directory;

class Entity
{
public:
	Entity( const std::string entName, const Directory *parentEntity )	: parent( parentEntity ), name( entName ) {  }
	virtual ~Entity() {	}

	bool operator==(const Entity& right) const
	{
		return name == right.name && parent == right.parent;
	}

	bool operator<(const Entity& right) const
	{
		return name < right.name && parent == right.parent;
	}

	virtual std::string toString() const
	{
		return name;
	}

	std::string getName() const
	{
		return name;
	}

	const Directory const *parent;
private:
	std::string name;	
};

#endif