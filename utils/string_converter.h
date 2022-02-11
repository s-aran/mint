#pragma once
#include "framework.h"
#include <iostream>
#include <algorithm>
#include <cwctype>

namespace Utils
{
	class Convert
	{
	private:
		static bool didConvertWindowsApiSucceed(DWORD error);

	public:
		static std::wstring stringToWstring(const std::string& src);
		static std::string wstringToString(const std::wstring& src);
		
		static std::string lpctstrToString(LPCTSTR src);
		static std::string lptstrToString(LPTSTR src);

		static std::string halfWidthKanaToFullWidthKana(const std::string& src);
		static std::wstring halfWidthKanaToFullWidthKana(const std::wstring& src);

		static wchar_t toLowerWchar(wchar_t c);
		static char toLowerChar(char c);

		static std::wstring toLower(std::wstring str);
		static std::string toLower(std::string str);
	};
}

