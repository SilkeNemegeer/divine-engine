#pragma once
#include <fstream>
#include <string>
#include <iostream>
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