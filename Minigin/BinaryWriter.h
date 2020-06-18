#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include "Structs.h"
namespace divengine
{
	struct Vector3;

	class BinaryWriter
	{
	public:
		void Open(const std::string& filepath);
		void Close();
		bool isOpen();

		template<typename T>
		void Write(const T& value);
		void Write(const Vector3& vector);

		void Write(const std::string& string);
		void Write(const char* string);
		void Write(const Rectf& rect);
		void Write(const SDL_Rect& rect);
		void Write(const SDL_Color& color);
		void Write(const glm::vec2& vec);
		void Write(const Circlef& circle);

	private:
		std::ofstream m_WriteStream;
	};

	template<typename T>
	inline void BinaryWriter::Write(const T& value)
	{
		if (std::is_pod<T>::value)
		{
			if (m_WriteStream.is_open())
				m_WriteStream.write((const char*)&value, sizeof(value));
		}
		else
		{
			std::cout << "Not a pod\n";
		}
	}
}