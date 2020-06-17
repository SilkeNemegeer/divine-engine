#pragma once
#include <string>
#include <fstream>
#include "Structs.h"
namespace divengine
{
	class BinaryReader
	{

	public:
		void Open(const std::string& filepath);
		void Close();
		bool isOpen();
		bool eof();

		template<typename T>
		void Read(T& value);

		void Read(std::string& string);
		void Read(glm::vec2& vec);
		void Read(Rectf& rect);

	private:
		std::ifstream m_ReadStream;
	};

	template<typename T>
	inline void BinaryReader::Read(T& value)
	{
		if (m_ReadStream.is_open())
		{
			m_ReadStream.read((char*)&value, sizeof(value));
		}
	}
}
