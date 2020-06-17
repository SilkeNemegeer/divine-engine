#pragma once
#include "Singleton.h"
#include <string>
#include <fstream>
#include "Debug.h"
#include "BaseComponent.h"
#include "GameComponentType.h"
#include "BinaryReader.h"
#include "BinaryWriter.h"

class FileManager : public divengine::Singleton<FileManager>
{

public:
	void LoadLevel(const std::string& file, const std::string& sceneName);
	void SaveLevel(const std::string& file, const std::string& levelname);
	void ReloadLevel(const std::string& file, const std::string& name);

protected:
	friend class divengine::Singleton<FileManager>;

private:
	FileManager();

	divengine::BinaryReader m_Reader;
	divengine::BinaryWriter m_Writer;
};