#include "NBT_Test.h"
#include "../NBT.h"
#include "../NBTCompound.h"
#include "../../Utl.h"

void TestNBT(const std::string& path) {
	Logger logger(L"NBT tester");

	const auto fileSize = Utl::GetFileSize(path);

	if (fileSize <= 0) {
		logger.Error(L"ERROR! CANT OPEN FILE %ls!", std::wstring(path.begin(), path.end()).c_str());
		return;
	}

	std::vector<uint8_t> fileInputData, fileData;
	fileInputData.resize(fileSize);
	Utl::ReadFileOnceSync(path, fileInputData.data(), fileSize);

	if (!Utl::Decompress(fileInputData, fileData)) {
		logger.Error(L"Utl::Decompress() failed!");
		return;
	}

	Buffer buf(fileData);

	NBTCompound rootTag;
	rootTag.Read(buf);

	rootTag.WalkTree([](NBT* pTag) {
		std::cout << pTag->name << std::endl;
	});
}
