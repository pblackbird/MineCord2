#include "MinecraftTypes.h"

std::string MinecraftTypes::ReadString(Buffer& buff) {
    int size = ReadVarInt(buff);
    std::string ret = buff.readStr(size);

    return ret;
}

void MinecraftTypes::WriteString(Buffer& buff, std::string str) {
    WriteVarInt(buff, (int)str.length());
    buff.writeStr(str);
}

void MinecraftTypes::WriteString(Buffer& buff, char str[], int size) {
    WriteVarInt(buff, size);
    buff.writeStr(str);
}

void MinecraftTypes::WriteVarInt(Buffer& buff, int val) {
    do {
        uint8_t temp = (uint8_t)(val & 0b01111111);
        val >>= 7;

        if (val != 0) {
            temp |= 0b10000000;
        }

        buff.writeUInt8(temp);
    } while (val != 0);
}

int MinecraftTypes::ReadVarInt(Buffer& buff, int* bytesRead) {
    int numRead = 0;
    int result = 0;
    uint8_t read;
    do {
        read = buff.readUInt8();
        int value = (read & 0b01111111);
        result |= (value << (7 * numRead));

        numRead++;
        if (numRead > 5) {
            return 0;
        }
    } while ((read & 0b10000000) != 0);

    if (bytesRead != nullptr) {
        *bytesRead = numRead;
    }

    return result;
}
