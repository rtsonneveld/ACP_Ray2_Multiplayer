#pragma once

#include <memory>
#include <vector>
#include "bitsery/bitsery.h"
#include "bitsery/adapter/buffer.h"
#include <bitsery/traits/vector.h>

/** An encoded packet which can be sent across a socket. */
struct EncodedPacket {
    std::vector<uint8_t> data;

    /** Returns the raw data in this packet. */
    uint8_t* get() {
        return data.data();
    }

    /** Returns the length of the packet. */
    size_t length() const {
        return data.size();
    }
};

/** A decoded packet parsed from raw data. */
class DecodedPacket {
private:
    using Adapter = bitsery::InputBufferAdapter<std::vector<uint8_t>>;
    std::vector<uint8_t> buffer;
    bitsery::Deserializer<Adapter> deserializer;

public:
    DecodedPacket(const uint8_t* message, size_t length)
        : buffer(message, message + length),
        deserializer(buffer.begin(), buffer.end()) {}

    /** Returns the id of this packet. */
    uint16_t id() {
        uint16_t id;
        deserializer.value2b(id);
        return id;
    }

    /** Returns the packet type itself. */
    template<typename T>
    T get() {
        T packet;
        deserializer.object(packet);
        return packet;
    }
};

/** Encodes the given packet. */
template<typename T>
EncodedPacket NTW_EncodePacket(const T& packet) {
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
inline DecodedPacket NTW_DecodePacket(const uint8_t* message, size_t length) {
    return DecodedPacket(message, length);
}