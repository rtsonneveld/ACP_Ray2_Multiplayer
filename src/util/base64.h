// Source code obtained from https://base64.dev/articles/base64-cpp

#include <string>
#include <cstdint>
#include <array>

static const char kEncodeTable[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

std::string base64_encode(char* data, std::size_t len) {
    std::string out;
    out.reserve(((len + 2) / 3) * 4);

    std::size_t i = 0;
    while (i + 3 <= len) {
        std::uint32_t n = (data[i] << 16) | (data[i + 1] << 8) | data[i + 2];
        out.push_back(kEncodeTable[(n >> 18) & 0x3F]);
        out.push_back(kEncodeTable[(n >> 12) & 0x3F]);
        out.push_back(kEncodeTable[(n >> 6) & 0x3F]);
        out.push_back(kEncodeTable[n & 0x3F]);
        i += 3;
    }

    if (std::size_t rem = len - i; rem > 0) {
        std::uint32_t n = data[i] << 16;
        if (rem == 2) n |= data[i + 1] << 8;
        out.push_back(kEncodeTable[(n >> 18) & 0x3F]);
        out.push_back(kEncodeTable[(n >> 12) & 0x3F]);
        out.push_back(rem == 2 ? kEncodeTable[(n >> 6) & 0x3F] : '=');
        out.push_back('=');
    }
    return out;
}

static std::array<int, 256> build_decode_table() {
    std::array<int, 256> t;
    t.fill(-1);
    for (int i = 0; i < 64; ++i)
        t[static_cast<unsigned char>(kEncodeTable[i])] = i;
    return t;
}

std::string base64_decode(const std::string& in) {
    static const auto table = build_decode_table();
    std::string out;
    out.reserve((in.size() / 4) * 3);

    std::uint32_t buffer = 0;
    int bits = 0;
    for (unsigned char c : in) {
        if (c == '=') break;
        int v = table[c];
        if (v < 0) continue;
        buffer = (buffer << 6) | v;
        bits += 6;
        if (bits >= 8) {
            bits -= 8;
            out.push_back(static_cast<char>((buffer >> bits) & 0xFF));
        }
    }
    return out;
}