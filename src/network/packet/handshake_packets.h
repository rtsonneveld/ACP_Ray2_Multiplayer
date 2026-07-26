#pragma once

#include "constants.h"

namespace R2MP {
    namespace NET {
        /** Sent to peer to start the handshake. */
        struct HandshakeIntroductionPacket {
            static constexpr uint16_t ID = 0;
            std::string username;
            long long bootTime;
            bool isServer;
        };

        template<typename S>
        void serialize(S& s, HandshakeIntroductionPacket& p) {
            s.text1b(p.username, Constants::MAX_PLAYER_NAME_LENGTH);
            s.value8b(p.bootTime);
            s.value1b(p.isServer);
        }

        /** Sent to peer to request transferring to the play protocol. */
        struct HandshakeCompletePacket {
            static constexpr uint16_t ID = 1;
            std::string host;
        };

        template<typename S>
        void serialize(S& s, HandshakeCompletePacket& p) {
            s.text1b(p.host, Constants::MAX_PLAYER_NAME_LENGTH);
        }
    };
};