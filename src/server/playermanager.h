#pragma once

#include "../network/network.h"

namespace R2MP {
	namespace SER {
		class PlayerManager {
		public:
			void Add(NET::NetworkConnection& connection);
			void Remove(uint32_t playerId);
		};
	};
}