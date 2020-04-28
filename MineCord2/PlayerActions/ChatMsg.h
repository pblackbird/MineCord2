#pragma once

#include "../Player.h"

static Logger logger(L"Chat debugger");

void OnPlayerChatMessage(Player* player, BaseNetPacket& msg);