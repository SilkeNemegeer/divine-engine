#include "MiniginPCH.h"
#include "BinaryReader.h"

void divengine::BinaryReader::Open(const std::string& filepath)
{
	m_ReadStream.open(filepath, std::ios::in | std::ios::binary);
}

void divengine::BinaryReader::Close()
{
	m_ReadStream.close();
}

bool divengine::BinaryReader::isOpen()
{
	return m_ReadStream.is_open();
}

bool divengine::BinaryReader::eof()
{
	return m_ReadStream.eof();
}

void divengine::BinaryReader::Read(std::string& string)
{
	if (m_ReadStream.is_open())
	{
		size_t size;
		m_ReadStream.read((char*)&size, sizeof(size_t));
		string.resize(size, ' ');
		m_ReadStream.read((char*)&string[0], sizeof(char) * size);
	}
}
