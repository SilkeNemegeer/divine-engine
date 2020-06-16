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


protected:
	friend class divengine::Singleton<FileManager>;

private:
	FileManager();
	//template<typename T>
	//void Write(const T& value);

	//template<typename T>
	//void Read(T& value);

	divengine::BinaryReader m_Reader;
	divengine::BinaryWriter m_Writer;

	//std::ifstream m_ReadStream;	//reader
	//std::ofstream m_WriteStream; //writer
};

//template<typename T>
//inline void FileManager::Write(const T& value)
//{
//	if (std::is_pod<T>::value)
//	{
//		if (m_WriteStream.is_open())
//			m_WriteStream.write((const char*)&value, sizeof(value));
//	}
//	else
//	{
//		divengine::Debug::LogWarning("FileManager::Write: could not write value that is not a pod to file");
//	}
//}
//
//template<typename T>
//inline void FileManager::Read(T& value)
//{
//	if (m_ReadStream.is_open())
//	{
//		m_ReadStream.read((char*)&value, sizeof(value));
//	}
//}