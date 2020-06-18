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

void divengine::BinaryReader::Read(glm::vec2& vec)
{
	if (!m_ReadStream.is_open())
		return;

	m_ReadStream.read((char*)&vec.x, sizeof(vec.x));
	m_ReadStream.read((char*)&vec.y, sizeof(vec.y));
}

void divengine::BinaryReader::Read(const char* string)
{
	if (m_ReadStream.is_open())
	{
		size_t size;
		m_ReadStream.read((char*)&size, sizeof(size_t));
		for (size_t i = 0; i < size; i++)
		{
			m_ReadStream.read((char*)&string[i], sizeof(char));
		}
	}
}

void divengine::BinaryReader::Read(Rectf& rect)
{
	if (!m_ReadStream.is_open())
		return;

	m_ReadStream.read((char*)&rect.bottomLeft.x, sizeof(rect.bottomLeft.x));
	m_ReadStream.read((char*)&rect.bottomLeft.y, sizeof(rect.bottomLeft.y));
	m_ReadStream.read((char*)&rect.width, sizeof(rect.width));
	m_ReadStream.read((char*)&rect.height, sizeof(rect.height));
}

void divengine::BinaryReader::Read(SDL_Rect& rect)
{
	if (!m_ReadStream.is_open())
		return;

	m_ReadStream.read((char*)&rect.x, sizeof(rect.x));
	m_ReadStream.read((char*)&rect.y, sizeof(rect.y));
	m_ReadStream.read((char*)&rect.w, sizeof(rect.w));
	m_ReadStream.read((char*)&rect.h, sizeof(rect.h));
}

void divengine::BinaryReader::Read(SDL_Color& color)
{
	if (!m_ReadStream.is_open())
		return;

	m_ReadStream.read((char*)&color.a, sizeof(color.a));
	m_ReadStream.read((char*)&color.r, sizeof(color.r));
	m_ReadStream.read((char*)&color.g, sizeof(color.g));
	m_ReadStream.read((char*)&color.g, sizeof(color.g));
}

void divengine::BinaryReader::Read(Circlef& circle)
{
	if (!m_ReadStream.is_open())
		return;

	m_ReadStream.read((char*)&circle.center.x, sizeof(circle.center.x));
	m_ReadStream.read((char*)&circle.center.y, sizeof(circle.center.y));
	m_ReadStream.read((char*)&circle.radius, sizeof(circle.radius));
}
