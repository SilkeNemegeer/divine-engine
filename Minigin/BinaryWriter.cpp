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

void divengine::BinaryWriter::Write(const Rectf& rect)
{
	if (!m_WriteStream.is_open())
		return;

	m_WriteStream.write((const char*)&rect.bottomLeft.x, sizeof(rect.bottomLeft.x));
	m_WriteStream.write((const char*)&rect.bottomLeft.y, sizeof(rect.bottomLeft.y));
	m_WriteStream.write((const char*)&rect.width, sizeof(rect.width));
	m_WriteStream.write((const char*)&rect.height, sizeof(rect.height));
}

void divengine::BinaryWriter::Write(const glm::vec2& vec)
{
	if (!m_WriteStream.is_open())
		return;

	m_WriteStream.write((const char*)&vec.x, sizeof(vec.x));
	m_WriteStream.write((const char*)&vec.y, sizeof(vec.y));
}
