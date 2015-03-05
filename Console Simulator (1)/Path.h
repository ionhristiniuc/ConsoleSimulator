#ifndef PATH_H
#define PATH_H
#include <list>

class Path
{
public:	
	static bool isAbsolute(const std::string& path)
	{
		return !path.empty() && path[0] == '/';
	}

	static bool isRelative(const std::string& path)
	{
		return !path.empty() && !isAbsolute(path);
	}

	static std::list< std::string > pathAsAList(const std::string &path)
	{
		std::list< std::string > list;
		int index = isRelative(path) ? 0 : 1;		
		auto iter = path.begin();
		int slashPos = path.find('/', index);

		while (slashPos != std::string::npos)
		{
			list.push_back(std::string(iter + index, iter + slashPos));
			index = slashPos + 1;
			slashPos = path.find('/', index);
		}

		if (iter + index != path.end())
			list.push_back(std::string(iter + index, path.end()));

		return list;
	}

	// returns a path without fileName for ex: A/B/File -> A/B
	static std::pair< std::string, std::string > getFilePathAndName(std::string path)	
	{
		std::string name;

		if (!path.empty())
		{
			int index = path.find_last_of("/");

			if (index != std::string::npos)
			{				
				name.assign(path.begin() + index + 1, path.end());				
				path.erase(path.begin() + index, path.end());

				if (path.empty())
					path = "/";
			}	
			else
			{
				name = path;
				path = "";
			}
		}

		return std::pair< std::string, std::string >( path, name );
	}
};

#endif