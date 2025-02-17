#include "esphome/core/log.h"
#include "esphome/core/helpers.h"
#include "../miot/miot_utils.h"
#include "miot_legacy_auth_cipher.h"

namespace esphome {
namespace miot_client {
namespace cipher {

std::vector<uint8_t> mix_a(const uint8_t *mac, const uint16_t product_id) {
  return {
      mac[0], mac[2], mac[5], static_cast<uint8_t>(product_id & 0xFF), static_cast<uint8_t>(product_id & 0xFF),
      mac[4], mac[5], mac[1],
  };
}

std::vector<uint8_t> mix_a(const uint64_t &mac, const uint16_t product_id) {
  return mix_a(miot::mac_reverse(mac), product_id);
}

std::vector<uint8_t> mix_b(const uint8_t *mac, const uint16_t product_id) {
  return {
      mac[0], mac[2], mac[5], static_cast<uint8_t>((product_id >> 8) & 0xFF),
      mac[4], mac[0], mac[5], static_cast<uint8_t>((product_id >> 0) & 0xFF),
  };
}

std::vector<uint8_t> mix_b(const uint64_t &mac, const uint16_t product_id) {
  return mix_b(miot::mac_reverse(mac), product_id);
}

std::vector<uint8_t> cipher_init(const std::vector<uint8_t> &key) {
  std::vector<uint8_t> perm;
  for (int i = 0; i < 256; i++) {
    perm.push_back(i & 0xFF);
  }
  const int keyLen = key.size();
  int j = 0;
  for (int i = 0; i < 256; i++) {
    j += perm[i] + key[i % keyLen];
    j = j & 0xFF;
    auto v = perm[i];
    perm[i] = perm[j];
    perm[j] = v;
  }
  return perm;
}

// More information: https://github.com/drndos/mikettle
std::vector<uint8_t> cipher(const std::vector<uint8_t> &key, const uint8_t *input, int size) {
  auto perm = cipher_init(key);
  int index1 = 0;
  int index2 = 0;
  std::vector<uint8_t> output;
  for (int i = 0; i < size; i++) {
    index1 = index1 + 1;
    index1 = index1 & 0xFF;
    index2 += perm[index1];
    index2 = index2 & 0xFF;
    auto v = perm[index1];
    perm[index1] = perm[index2];
    perm[index2] = v;
    auto idx = perm[index1] + perm[index2];
    idx = idx & 0xFF;
    auto outputByte = input[i] ^ perm[idx];
    output.push_back(outputByte & 0xFF);
  }
  return output;
}

std::vector<uint8_t> generate_random_token() {
  std::vector<uint8_t> token;
  for (int i = 0; i < 12; i++) {
    token.push_back(fast_random_8());
  }
  return token;
}

}  // namespace cipher
}  // namespace miot_client
}  // namespace esphome
