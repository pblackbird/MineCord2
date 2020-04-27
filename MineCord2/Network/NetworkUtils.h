#pragma once

#include <sstream>
#include <iostream>

namespace NetworkUtils {
	inline const std::wstring FormatIPv4(uint32_t ipv4) {
		std::wstringstream str;
		uint8_t* pData = (uint8_t*)&ipv4;

		str << pData[0] << L"." << pData[1] << L"." << pData[2] << L"." << pData[3];

		return str.str();
	}
}