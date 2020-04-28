#include "NBT.h"

#include "NBTByte.h"
#include "NBT_List.h"
#include "NBTShort.h"
#include "NBTInt.h"
#include "NBTLongArray.h"
#include "NBTIntArray.h"
#include "NBTByteArray.h"
#include "NBTShort.h"
#include "NBTString.h"
#include "NBTCompound.h"
#include "NBT_List.h"
#include "NBTFloat.h"
#include "NBTLong.h"
#include "NBTDouble.h"

void NBT::Write(Buffer& dest) {
	dest.writeUInt8((uint8_t)type);

    if (!isUnnamed) {
  	    dest.writeUInt16_BE((uint16_t)name.length());
  	    dest.writeStr(name);
    }
}

void NBT::Read(Buffer& src) {
    type = static_cast<NBTDataType>(src.readUInt8());

    if (!isUnnamed) {
  	    uint16_t nameLength = src.readUInt16_BE();
  	    name = src.readStr(nameLength);
    }
}

NBT* NBT::BuildNBTFromType(NBTDataType gType) {
    NBT* pResult = nullptr;

    switch (gType) {
        case NBTDataType::TAG_End: break;
        case NBTDataType::TAG_Long:
            pResult = new NBTLong();
            break;
        case NBTDataType::TAG_Byte:
            pResult = new NBTByte();
            break;
        case NBTDataType::TAG_Byte_Array:
            pResult = new NBTByteArray();
            break;
        case NBTDataType::TAG_Compound:
            pResult = new NBTCompound();
            break;
        case NBTDataType::TAG_Double:
            pResult = new NBTDouble();
            break;
        case NBTDataType::TAG_Float:
            pResult = new NBTFloat();
            break;
        case NBTDataType::TAG_Int:
            pResult = new NBTInt();
            break;
        case NBTDataType::TAG_Int_Array:
            pResult = new NBTIntArray();
            break;
        case NBTDataType::TAG_List: 
            pResult = new NBTList();
            break;
        case NBTDataType::TAG_Long_Array:
            pResult = new NBTLongArray();
            break;
        case NBTDataType::TAG_Short:
            pResult = new NBTShort();
            break;
        case NBTDataType::TAG_String:
            pResult = new NBTString();
            break;
    }

    return pResult;
}

NBT* NBT::ReadNBTSafely(Buffer& src) {
    NBTDataType dataType = static_cast<NBTDataType>(src.readUInt8());
    src.setReadOffset(src.getReadOffset() - 1);

    NBT* pResult = NBT::BuildNBTFromType(dataType);

    if(pResult)
        pResult->Read(src);

    return pResult;
}
