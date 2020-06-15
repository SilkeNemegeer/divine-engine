#include "FileManager.h"
#include "MiniginPCH.h"
#include "FileManager.h"
#include "SceneManager.h"
#include <iostream>

void FileManager::LoadLevel(const std::string& file)
{
	UNREFERENCED_PARAMETER(file);
	//Open binary stream

	//Read amount of gameobjects

	//start reading all objects:
		//read component count for the object
		//read component type (check with switch)
		//create & load correct component

	//close stream
}

void FileManager::SaveLevel(const std::string& file) const
{
	UNREFERENCED_PARAMETER(file);
	//open stream
	//save gameObject count (from the current scene)

	//Start saving the objects:

		//save component count per gameobject (from gameobject itself)
		//save component type
		//call save components per component

	//close stream
}
