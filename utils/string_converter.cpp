#include "pch.h"

namespace Utils
{
  bool Convert::didConvertWindowsApiSucceed(DWORD error)
  {
		switch (error)
		{
		case NOERROR:
			std::cout << "OK!" << std::endl;
			return true;

		case ERROR_INSUFFICIENT_BUFFER:
			std::cout << "ERROR_INSUFFICIENT_BUFFER" << std::endl;
			break;

		case ERROR_INVALID_FLAGS:
			std::cout << "ERROR_INVALID_FLAGS" << std::endl;
			break;

		case ERROR_INVALID_PARAMETER:
			std::cout << "ERROR_INVALID_PARAMETER" << std::endl;
			break;

		case ERROR_NO_UNICODE_TRANSLATION:
			std::cout << "ERROR_NO_UNICODE_TRANSLATION" << std::endl;
			break;

		default:
			std::cout << "(default) UNKNOWN ERROR" << std::endl;
			break;
		}

		return false;
  }

	std::wstring Convert::stringToWstring(const std::string& src)
	{
		int bufferSize = MultiByteToWideChar(CP_ACP, 0, src.c_str(), -1, static_cast<wchar_t*>(NULL), 0);
		if (bufferSize <= 0)
		{
			Convert::didConvertWindowsApiSucceed(GetLastError());
			return std::wstring();
		}

		wchar_t* wcharBuffer = new wchar_t[bufferSize];
		if (MultiByteToWideChar(CP_ACP, 0, src.c_str(), -1, wcharBuffer, bufferSize) <= 0)
		{
			Convert::didConvertWindowsApiSucceed(GetLastError());

			delete[] wcharBuffer;
			return std::wstring();
		}
		std::wstring wstr(wcharBuffer);

		delete[] wcharBuffer;
		return wstr;
	}

	std::string Convert::wstringToString(const std::wstring& src)
	{
		int bufferSize = WideCharToMultiByte(CP_ACP, 0, src.c_str(), -1, NULL, 0, NULL, NULL);
		if (bufferSize <= 0)
		{
			Convert::didConvertWindowsApiSucceed(GetLastError());
			return std::string();
		}

		char* charBuffer = new char[bufferSize];
		if (WideCharToMultiByte(CP_ACP, 0, src.c_str(), -1, charBuffer, bufferSize, NULL, NULL) <= 0)
		{
			Convert::didConvertWindowsApiSucceed(GetLastError());

			delete[] charBuffer;
			return std::string();
		}
		std::string str(charBuffer);

		delete[] charBuffer;
		return str;
	}

	std::string Convert::lpctstrToString(LPCTSTR src)
	{
#ifdef UNICODE
		return Convert::wstringToString(src);
#else
		return std::string(src);
#endif
	}

	std::string Convert::lptstrToString(LPTSTR src)
	{
		return lpctstrToString(src);
	}

	std::string Convert::halfWidthKanaToFullWidthKana(const std::string& src)
	{
		int bufferSize = LCMapStringA(GetSystemDefaultLCID(), LCMAP_FULLWIDTH, src.c_str(), -1, NULL, 0);
		if (bufferSize <= 0)
		{
			Convert::didConvertWindowsApiSucceed(GetLastError());
			return std::string();
		}

		char* charBuffer = new char[bufferSize];
		if (LCMapStringA(GetSystemDefaultLCID(), LCMAP_FULLWIDTH, src.c_str(), -1, charBuffer, bufferSize) <= 0)
		{
			Convert::didConvertWindowsApiSucceed(GetLastError());

			delete[] charBuffer;
			return std::string();
		}

		std::string str(charBuffer);

		delete[] charBuffer;
		return str;
	}

	std::wstring Convert::halfWidthKanaToFullWidthKana(const std::wstring& src)
	{
		int bufferSize = LCMapStringW(GetSystemDefaultLCID(), LCMAP_FULLWIDTH, src.c_str(), -1, NULL, 0);
		if (bufferSize <= 0)
		{
			Convert::didConvertWindowsApiSucceed(GetLastError());
			return std::wstring();
		}

		wchar_t* wcharBuffer = new wchar_t[bufferSize];
		if (LCMapStringW(GetSystemDefaultLCID(), LCMAP_FULLWIDTH, src.c_str(), -1, wcharBuffer, bufferSize) <= 0)
		{
			Convert::didConvertWindowsApiSucceed(GetLastError());

			delete[] wcharBuffer;
			return std::wstring();
		}

		std::wstring wstr(wcharBuffer);

		delete[] wcharBuffer;
		return wstr;
	}

	wchar_t Convert::toLowerWchar(wchar_t c)
	{
		return std::iswalpha(c) ? std::tolower(c) : c;
	}

	char Convert::toLowerChar(char c)
	{
		return std::isalpha(c) ? std::tolower(c) : c;
	}

	std::wstring Convert::toLower(std::wstring str)
	{
		std::wstring lowered = str;
		std::transform(str.begin(), str.end(), lowered.begin(), toLowerWchar);
		return lowered;
	}
	
	std::string Convert::toLower(std::string str)
	{
		std::string lowered = str;
		std::transform(str.begin(), str.end(), lowered.begin(), toLowerChar);
		return lowered;
	}
}