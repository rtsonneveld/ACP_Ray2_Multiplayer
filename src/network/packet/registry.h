#pragma once

#include <memory>
#include <vector>
#include "bitsery/bitsery.h"
#include "bitsery/adapter/buffer.h"
#include <bitsery/traits/vector.h>
#include <bitsery/traits/string.h>

namespace R2MP {
	namespace NET {
        /** An encoded packet which can be sent across a socket. */
        struct EncodedPacket {
            std::vector<uint8_t> data;

            /** Returns the raw data in this packet. */
            uint8_t* Get() {
                return data.data();
            }

            /** Returns the length of the packet. */
            size_t Length() const {
                return data.size();
            }
        };

        /** A decoded packet parsed from raw data. */
        class DecodedPacket {
        private:
            using Adapter = bitsery::InputBufferAdapter<std::vector<uint8_t>>;
            std::vector<uint8_t> buffer;
            bitsery::Deserializer<Adapter> deserializer;
            uint32_t playerId;

        public:
            DecodedPacket(const uint8_t* message, size_t length, uint32_t playerId)
                : buffer(message, message + length),
                deserializer(buffer.begin(), buffer.end()),
                playerId(playerId) {}

            /** Returns the associated player id, if applicable. */
            uint32_t PlayerId() {
                return playerId;
            }

            /** Returns the id of this packet. */
            uint16_t Id() {
                uint16_t id;
                deserializer.value2b(id);
                return id;
            }

            /** Returns the packet type itself. */
            template<typename T>
            T Get() {
                T packet;
                deserializer.object(packet);
                return packet;
            }
        };

        /** Encodes the given packet. */
        template<typename T>
        EncodedPacket EncodePacket(const T& packet) {
            using Adapter = bitsery::OutputBufferAdapter<std::vector<uint8_t>>;
            std::vector<uint8_t> output;
            output.reserve(256);
            bitsery::Serializer<Adapter> serializer(output);

            auto id = static_cast<uint16_t>(T::ID);
            auto copy = packet;
            serializer.value2b(id);
            serializer.object(copy);
            serializer.adapter().flush();

            return { std::move(output) };
        }

        /** Decodes the given data. */
        inline DecodedPacket DecodePacket(const uint8_t* message, size_t length, uint32_t playerId) {
            return DecodedPacket(message, length, playerId);
        }
	};
};