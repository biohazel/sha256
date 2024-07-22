#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <array>
#include <cstdint>
#include <cstring>

class SHA256 {
public:
    SHA256() { reset(); }
    SHA256& update(const uint8_t* data, size_t len);
    SHA256& update(const std::string& data);
    std::string final();

private:
    void reset();
    void transform(const uint8_t* chunk);

    static constexpr size_t BlockSize = 64;
    static constexpr size_t HashSize = 32;

    std::array<uint32_t, 8> state;
    std::array<uint8_t, BlockSize> buffer;
    uint64_t bitCount;
    size_t bufferLen;
};

SHA256& SHA256::update(const uint8_t* data, size_t len) {
    while (len > 0) {
        size_t toCopy = std::min(len, BlockSize - bufferLen);
        std::memcpy(&buffer[bufferLen], data, toCopy);
        bufferLen += toCopy;
        data += toCopy;
        len -= toCopy;

        if (bufferLen == BlockSize) {
            transform(buffer.data());
            bitCount += BlockSize * 8;
            bufferLen = 0;
        }
    }
    return *this;
}

SHA256& SHA256::update(const std::string& data) {
    return update(reinterpret_cast<const uint8_t*>(data.c_str()), data.size());
}

std::string SHA256::final() {
    bitCount += bufferLen * 8;
    buffer[bufferLen++] = 0x80;

    if (bufferLen > 56) {
        std::fill(buffer.begin() + bufferLen, buffer.end(), 0);
        transform(buffer.data());
        bufferLen = 0;
    }

    std::fill(buffer.begin() + bufferLen, buffer.end() - 8, 0);
    for (size_t i = 0; i < 8; ++i) {
        buffer[BlockSize - 1 - i] = bitCount >> (8 * i);
    }
    transform(buffer.data());

    std::ostringstream result;
    for (uint32_t value : state) {
        result << std::hex << std::setw(8) << std::setfill('0') << value;
    }

    reset();
    return result.str();
}

void SHA256::reset() {
    state = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };
    bufferLen = 0;
    bitCount = 0;
}

void SHA256::transform(const uint8_t* chunk) {
    static constexpr uint32_t K[] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
        0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
        0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
        0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
        0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
        0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    auto ROTR = [](uint32_t x, uint32_t n) { return (x >> n) | (x << (32 - n)); };
    auto CH = [](uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (~x & z); };
    auto MAJ = [](uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (x & z) ^ (y & z); };
    auto SIGMA0 = [ROTR](uint32_t x) { return ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22); };
    auto SIGMA1 = [ROTR](uint32_t x) { return ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25); };
    auto sigma0 = [ROTR](uint32_t x) { return ROTR(x, 7) ^ ROTR(x, 18) ^ (x >> 3); };
    auto sigma1 = [ROTR](uint32_t x) { return ROTR(x, 17) ^ ROTR(x, 19) ^ (x >> 10); };

    uint32_t W[64];
    for (size_t i = 0; i < 16; ++i) {
        W[i] = (chunk[4 * i] << 24) | (chunk[4 * i + 1] << 16) | (chunk[4 * i + 2] << 8) | (chunk[4 * i + 3]);
    }
    for (size_t i = 16; i < 64; ++i) {
        W[i] = sigma1(W[i - 2]) + W[i - 7] + sigma0(W[i - 15]) + W[i - 16];
    }

    uint32_t a = state[0];
    uint32_t b = state[1];
    uint32_t c = state[2];
    uint32_t d = state[3];
    uint32_t e = state[4];
    uint32_t f = state[5];
    uint32_t g = state[6];
    uint32_t h = state[7];

    for (size_t i = 0; i < 64; ++i) {
        uint32_t T1 = h + SIGMA1(e) + CH(e, f, g) + K[i] + W[i];
        uint32_t T2 = SIGMA0(a) + MAJ(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    state[5] += f;
    state[6] += g;
    state[7] += h;
}

int main() {
    SHA256 sha256;
    std::string input = "hello world";
    std::string output = sha256.update(input).final();
    std::cout << "SHA-256 of \"" << input << "\" is: " << output << std::endl;
    return 0;
}
