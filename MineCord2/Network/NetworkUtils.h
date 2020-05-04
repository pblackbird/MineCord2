#pragma once

#include <string>
#include <iostream>

namespace NetworkUtils {
	inline const std::string FormatIPv4(uint32_t ipv4) {
		std::string str;
		uint8_t* pData = (uint8_t*)&ipv4;

		str = std::to_string(pData[0]) 
			+ "." + std::to_string(pData[1]) 
			+ "." + std::to_string(pData[2]) 
			+ "." + std::to_string(pData[3]);

		return str;
	}
}