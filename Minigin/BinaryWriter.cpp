#include "MiniginPCH.h"
#include "BinaryWriter.h"

void divengine::BinaryWriter::Open(const std::string& filepath)
{
	m_WriteStream.open(filepath, std::ios::out | std::ios::binary);
}

void divengine::BinaryWriter::Close()
{
	m_WriteStream.close();
}

bool divengine::BinaryWriter::isOpen()
{
	return m_WriteStream.is_open();
}

void divengine::BinaryWriter::Write(const Vector3& vector)
{
	if (m_WriteStream.is_open())
	{
		m_WriteStream.write((const char*)&vector, sizeof(float) * 3);
	}
}

void divengine::BinaryWriter::Write(const std::string& string)
{
	if (m_WriteStream.is_open())
	{
		size_t sizeName = string.size();
		m_WriteStream.write((const char*)&sizeName, sizeof(sizeName));
		m_WriteStream.write((const char*)&string[0], sizeName);
	}
}