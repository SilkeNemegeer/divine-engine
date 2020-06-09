#pragma once

namespace divengine
{
	class Debug final
	{
		public:
			static void Log(const std::string& text);
			static void LogWarning(const char* const text, ...);
			static void LogError(const std::string& text);

		private:
			Debug() {};
			~Debug() {};
	};
}
