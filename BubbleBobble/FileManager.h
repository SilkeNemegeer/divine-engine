#pragma once
#include "Singleton.h"
#include <string>

class FileManager : public divengine::Singleton<FileManager>
{
public:
	void LoadLevel(const std::string& file);
	void SaveLevel(const std::string& file) const;

protected:
	friend class Singleton<FileManager>;

private:
};
