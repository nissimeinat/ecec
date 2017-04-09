#include "test.h"

#include <string.h>

#include <openssl/rand.h>

typedef struct webpush_aes128gcm_encrypt_ok_test_s {
  const char* desc;
  const char* payload;
  const char* senderPrivKey;
  const char* recvPubKey;
  const char* authSecret;
  const char* salt;
  const char* plaintext;
  size_t plaintextLen;
  size_t maxPayloadLen;
  size_t payloadLen;
  uint32_t rs;
  uint8_t pad;
} webpush_aes128gcm_encrypt_ok_test_t;

static webpush_aes128gcm_encrypt_ok_test_t
  webpush_aes128gcm_encrypt_ok_tests[] = {
    {
      .desc = "Example from draft-ietf-webpush-encryption-latest",
      .payload = "\x0c\x6b\xfa\xad\xad\x67\x95\x88\x03\x09\x2d\x45\x46\x76\xf3"
                 "\x97\x00\x00\x10\x00\x41\x04\xfe\x33\xf4\xab\x0d\xea\x71\x91"
                 "\x4d\xb5\x58\x23\xf7\x3b\x54\x94\x8f\x41\x30\x6d\x92\x07\x32"
                 "\xdb\xb9\xa5\x9a\x53\x28\x64\x82\x20\x0e\x59\x7a\x7b\x7b\xc2"
                 "\x60\xba\x1c\x22\x79\x98\x58\x09\x92\xe9\x39\x73\x00\x2f\x30"
                 "\x12\xa2\x8a\xe8\xf0\x6b\xbb\x78\xe5\xec\x0f\xf2\x97\xde\x5b"
                 "\x42\x9b\xba\x71\x53\xd3\xa4\xae\x0c\xaa\x09\x1f\xd4\x25\xf3"
                 "\xb4\xb5\x41\x4a\xdd\x8a\xb3\x7a\x19\xc1\xbb\xb0\x5c\xf5\xcb"
                 "\x5b\x2a\x2e\x05\x62\xd5\x58\x63\x56\x41\xec\x52\x81\x2c\x6c"
                 "\x8f\xf4\x2e\x95\xcc\xb8\x6b\xe7\xcd",
      .senderPrivKey =
        "\xc9\xf5\x8f\x89\x81\x3e\x9f\x8e\x87\x2e\x71\xf4\x2a\xa6"
        "\x4e\x17\x57\xc9\x25\x4d\xcc\x62\xb7\x2d\xdc\x01\x0b\xb4"
        "\x04\x3e\xa1\x1c",
      .recvPubKey =
        "\x04\x25\x71\xb2\xbe\xcd\xfd\xe3\x60\x55\x1a\xaf\x1e\xd0\xf4"
        "\xcd\x36\x6c\x11\xce\xbe\x55\x5f\x89\xbc\xb7\xb1\x86\xa5\x33"
        "\x39\x17\x31\x68\xec\xe2\xeb\xe0\x18\x59\x7b\xd3\x04\x79\xb8"
        "\x6e\x3c\x8f\x8e\xce\xd5\x77\xca\x59\x18\x7e\x92\x46\x99\x0d"
        "\xb6\x82\x00\x8b\x0e",
      .authSecret =
        "\x05\x30\x59\x32\xa1\xc7\xea\xbe\x13\xb6\xce\xc9\xfd\xa4\x88\x82",
      .salt =
        "\x0c\x6b\xfa\xad\xad\x67\x95\x88\x03\x09\x2d\x45\x46\x76\xf3\x97",
      .plaintext = "When I grow up, I want to be a watermelon",
      .plaintextLen = 41,
      .maxPayloadLen = 334,
      .payloadLen = 144,
      .rs = 4096,
      .pad = 0,
    },
    {
      .desc = "rs = 24, pad = 6",
      .payload = "\xff\x80\x50\x30\xa1\x08\xe1\x14\xe6\xc1\x7f\xad\x61\x86\xa1"
                 "\xa6\x00\x00"
                 "\x00\x18\x41\x04\x30\xef\xcb\x1e\xb0\x43\xb8\x05\xe4\xe4\x4b"
                 "\xab\x35\xf8"
                 "\x25\x13\xc3\x3f\xed\xb2\x87\x00\xf7\xe5\x68\xac\x8b\x61\xe8"
                 "\xd8\x35\x66"
                 "\x5a\x51\xeb\x66\x79\xb2\xdb\x22\x8a\x10\xc0\xc3\xfe\x50\x77"
                 "\x06\x28\x48"
                 "\xd9\xbb\x3d\x60\x27\x9f\x93\xce\x35\x48\x47\x28\xaa\x1f\xd2"
                 "\xc1\x71\x39"
                 "\x49\xae\xc9\x8f\x05\x09\x6c\x72\x98\xfd\x3f\x51\xc4\xf8\x18"
                 "\xfa\xfa\x1f"
                 "\xe6\x15\xd8\x44\x7b\x3a\x05\x40\x60\x31\xf6\x40\x1a\xc2\x4f"
                 "\x2a\x77\x5c"
                 "\xa5\x24\x56\xa9\x21\xb8\x3b\x9e\x00\x42\xc3\xa6\x3e\x1a\xfa"
                 "\x1a\xe0\x12"
                 "\x77\x4d\x9d\x77\x5b\xe8\xd1\x94\x19\x45\x1d\x37\xff\x59\xff"
                 "\x59\x2e\x84"
                 "\xf0\x74\x40\xa6\x3f\xc1\x7f\x5c\xab\xcb\x9a\x50\xed\xda\xf7"
                 "\x53\x70\xdb"
                 "\x64\x7f\x94\x44\x7d\x3f\x16\x62\x69\xd8\x71\x1d\xf0\xf5\x7e"
                 "\x56\x04\x95"
                 "\x76\xe1\x13\x0a\x5a\x5e\x1f\x94\xba\x8a\x5d\x0b\x00\x07\xc6"
                 "\xc0\xfd\x29"
                 "\x98\x42\x9e\x7d\x63\xd4\xef\x91\x97\x98\xf4\x6e\xcf\x5f\x0b"
                 "\x28\xfb\x80"
                 "\xf5\xb2\x43\x9d\xe2\x6b\x8a\x52\x20\x0b\xc7\xd6\xaf\x7a\x48"
                 "\x40\x72\x1f"
                 "\xe8\xbe\x85\x24\xa6\x91\xb6\xef\x0e\xda\xe9\x0b\xb6\xf5\x92"
                 "\x78\x94\x81"
                 "\x9b\x83\x1b\x45\xb5\x3f\x84\x01\xfe\x02\x2d\xbb\x64\xed\x75"
                 "\x65\x35\x09"
                 "\x04\xac\x0b\x51\x71\x35\xd7\xf8\xab\xbc\x98\x12\x7f\xb1\x63"
                 "\x86\x4d\x4d"
                 "\x4a\x30\x74\x25\xb2\xcd\x43\xdb\x22\xaf\x26\x7d\x71\xc3\x71"
                 "\x46\x99\x4a"
                 "\x8c\x48\x05\xad\xc3\x41\xbf\xba\x27\xaf\x09\xfd\x80\xbd\x5e"
                 "\xff\x51\xd8"
                 "\x77\x28\x2a\x2f\xbf\xbf\xeb\x10\x19\x9e\x78\x79\xe4\xb9\xd1"
                 "\x3a\x46\xd5"
                 "\x7f\xb7\xd7\x86\x82\x48\x53\xe1\xcc\x89\xca\xfb\xaf\x14\xde"
                 "\x1e\x92\x4c"
                 "\x94\x4f\xeb\x8b\x62\x6c\xe0\x20\x7d\x6f\x9f\xa9\xd8\x49\xee"
                 "\xca\xc6\x9b"
                 "\x42\xd6\xe7\xa2\x3b\xd5\x12\x4d\x49\x62\x2b\x44\xb3\x5c\x5b"
                 "\x15\xfb\x0e"
                 "\x6a\x77\x81\xa5\x03\xf1\xa4\xe0\x62\xe0\x15\xd5\x57\xd9\x5d"
                 "\x44\xd9\xd8"
                 "\xb0\x79\x9b\x3a\xaf\xce\x83\xd5\xd4",
      .senderPrivKey =
        "\x0f\x28\xbe\xaf\x7e\x27\x79\x3c\x03\x63\x8d\xc2\x97\x3a"
        "\x15\xb0\x01\x6e\x1b\x36\x7c\xbf\xfd\xa8\x86\x1a\xb1\x75"
        "\xf3\x1b\xce\x02",
      .recvPubKey =
        "\x04\xc0\xd1\xa8\x12\xb2\x91\x29\x1d\xd7\xbe\xee\x35\x87\x13"
        "\xc1\x26\xc5\x89\xf3\x63\x3c\x26\xd1\xa2\x01\x31\x1d\xe0\x36"
        "\xdc\x10\x93\x1e\x4e\xe1\x42\xf6\x19\x21\xa3\xea\x58\x64\xe8"
        "\x72\xa9\x38\x41\xa5\x29\x44\xe5\xb3\xf6\xac\xce\xcc\xe8\xc8"
        "\x28\xfb\x04\xa4\xcd",
      .authSecret =
        "\x9d\x77\x35\xd8\xde\x19\x62\xb9\x83\x94\xb0\x7f\xfe\x28\x7e\x20",
      .salt =
        "\xff\x80\x50\x30\xa1\x08\xe1\x14\xe6\xc1\x7f\xad\x61\x86\xa1\xa6",
      .plaintext = "I am the very model of a modern Major-General, I've "
                   "information vegetable, animal, and mineral",
      .plaintextLen = 94,
      .maxPayloadLen = 631,
      .payloadLen = 441,
      .rs = 24,
      .pad = 6,
    },
    {
      // This test is also interesting because the data length (54) is a
      // multiple
      // of rs (18). We'll allocate memory to hold 4 records, but only write 3.
      .desc = "rs = 18, pad = 31",
      .payload = "\xe4\x98\x88\xd2\xb2\x8f\x27\x7f\x84\x7b\xc5\xde\x96\xf0\xf8"
                 "\x1b\x00\x00"
                 "\x00\x12\x41\x04\x00\xb8\x33\xe4\x81\xa9\x9a\xa3\x30\xdc\xb2"
                 "\x77\x92\x2d"
                 "\x5f\x84\xaf\x2e\x9c\xe6\x11\xad\x2a\xd3\xed\x0f\x5b\x43\x19"
                 "\x12\xd3\x5e"
                 "\xa7\x2f\xc5\xbf\x76\xb7\x69\xd9\x52\x67\x78\xf5\xab\xfa\x05"
                 "\x86\x50\x98"
                 "\x8d\xa5\xe5\x31\xff\x82\xd1\xa7\x04\x37\x94\xc7\x17\x06\x3a"
                 "\xeb\x95\x8b"
                 "\xf1\x16\xbc\xcf\x50\x74\x2f\xd4\xd6\x9b\xd0\xea\x7e\x3f\x61"
                 "\x1c\x70\x9b"
                 "\xf2\xcd\xf5\xcd\x47\xc6\x42\x6c\xb8\x32\x3b\x53\x98\xc4\x3c"
                 "\x0d\x0b\x92"
                 "\xcc\x98\x2d\xa1\xc2\x4c\xe5\xfe\xe2\xb2\x03\xf7\xad\x78\xca"
                 "\x44\xf0\x49"
                 "\x0f\x34\x07\xf5\xfe\xe8\x83\x26\x6e\xe4\x70\x35\x19\x5d\xe0"
                 "\xfe\x6d\x8a"
                 "\x75\xe4\x87\xdf\x25\x6d\xb5\x97\xa7\x5e\x45\xae\x4f\xb5\x5b"
                 "\x82\x59\xcb"
                 "\x0b\x2d\x19\xe7\xb0\x57\x14\x26\x7e\xb5\x60\xae\x07\x2b\x7a"
                 "\x66\x59\x51"
                 "\x91\x7a\x06\x87\x32\xdf\x30\x9b\xe2\x56\xf9\x0f\x2a\xdd\xa3"
                 "\x2f\x05\xfe"
                 "\xaa\x5e\x9b\x06\x95\xbc\xa2\xcc\xf2\x2a\xae\xfc\x7d\xa9\xce"
                 "\xeb\xc5\xd4"
                 "\x0c\x12\xd3\x2a\xdb\x5c\x84\xcb\x32\x0a\xf9\x44\x01\x60\x95"
                 "\x36\x2f\xeb"
                 "\xba\x4f\xfa\x4a\x99\x83\x0e\x49\x58\xea\x2b\xba\x50\x8c\xb6"
                 "\x83\xa5\x8d"
                 "\x20\x27\xd4\xb7\x47\x26\xa8\x53\xb2\x4b\x47\xcc\xba\x75\x1a"
                 "\xbe\x9d\x9a"
                 "\xb2\xda\x9e\xc2\xba\x9c\x7c\xcf\x0c\xf1\x73\x05\xba\xe3\x14"
                 "\xd3\x8a\x68"
                 "\x76\x18\xb0\x77\x2f\xcb\x71\xd4\x41\x90\x27\xa4\xbf\x43\x5c"
                 "\xb7\x21\xaa"
                 "\xd7\x4e\xfc\x17\x99\x81\xb7\x16\x96\x04\xbf\x97\xec\xac\x41"
                 "\xe7\x38\x84"
                 "\x45\x69\x33\x73\x48\x18\x13\x29\x23\xb5\x6c\x15\x2d\x6c\x9e"
                 "\x59\xae\xf9"
                 "\x95\xac\xa5\x9d\xe0\xbf\x2c\x80\x3a\x07\x18\x08\x89\x67\x0a"
                 "\x08\xe6\x4a"
                 "\x20\xd2\xbf\xa8\x53\xe0\x11\x28\x72\x94\x7b\xaa\xaf\xfb\x51"
                 "\x0c\xc9\xe7"
                 "\x5d\x63\x10\xed\x6a\xac\xbd\x2e\x0b\xa3\xa2\x9b\xe4\x2c\x65"
                 "\x32\xea\x4e"
                 "\x33\x46\xe1\xf0\x57\x16\x46\x37\x1c\x71\x66\x5e\x3f\xac\x9d"
                 "\x76\xfa\xee"
                 "\x1f\x12\x2e\x64\xd4\x90\xdd\x2a\x3e\x31\x81\x6e\xab\x58\x3f"
                 "\x17\x28\x41"
                 "\xa0\x75\xd2\x05\xf3\x18\x71\x4a\x8c\x70\xce\x0f\x32\x7f\x4d"
                 "\x92\xb8\xc9"
                 "\xdc\xb8\x13\xe6\xd2\x4f\xe8\x56\x33\xf1\xa9\xc7\xc1\xe4\xa1"
                 "\xfb\x31\x4d"
                 "\xd5\xfe\x3e\x28\x0e\x39\x08\xf3\x6c\x8c\xbf\xb8\x0b\x7d\x92"
                 "\x43\xab\xaf"
                 "\xfa\x65\xc2\x16\xcf\x1a\xa8\xb8\xd6\x26\xa6\x30\xdf\xe8\x18"
                 "\x6c\xe9\x77"
                 "\xa5\xb8\xf3\x64\x9d\x37\x53\xb9\x17\x6c\x36\x7e\x4e\x07\xf2"
                 "\x20\xa1\x75"
                 "\x80\x61\x38\xe8\x88\x25\xa2\xf3\x49\x84\x20\x58\x2b\x96\x20"
                 "\x96\x58\xbb"
                 "\xfa\x8f\x2b\xa6\x93\x3a\x83\xc2\x5e\xdb\x26\x91\x87\x79\x65"
                 "\x42\xe2\xac"
                 "\x49\xb8\x07\x86\x36\xbd\xdc\x26\x8e\x11\x62\x5e\x8b\xff\x9f"
                 "\x0a\x34\x3d"
                 "\x3a\x4c\x06\x08\x0e\xf0\x80\x3b\x8d\xcd\x8e\x84\x1d\x0e\x27"
                 "\x59\xe4\x83"
                 "\xea\x19\xb9\x03\x32\x4d\x9e\xc4\xd5\x2f\x49\x1a\xce\xf3\xee"
                 "\xff\x44\x1c"
                 "\x37\x88\x1c\x75\x93\xea\xc3\x16\x21\x33\x7a\x5e\x86\x59\xf9"
                 "\x3e\x20\x07"
                 "\x9b\x0e\x26\xeb\xfe\x56\xc1\x04\x55\xd1\x09\x71\x13\x0b\xd2"
                 "\xa2\xc1\x59"
                 "\xc7\x4f\x48\xb2\xe5\x26\x53\x0a\x76\xf6\x4c\xca\x2e\xfb\x24"
                 "\x6e\x79\x3d"
                 "\x11\xfb\x75\xa6\x68\x01\x8e\x70\xc3\x10\x71\x00\xf8\x1b\xa3"
                 "\xb1\x6a\xe4"
                 "\x0a\x83\x8f\x18\xd4\xc4\x7f\x1d\x71\x32\xf1\x74\x68\x8e\xc5"
                 "\x38\x23\x94"
                 "\xe0\x11\x99\x21\x73\x1a\x16\x87\x9b\x85\x8f\xf3\x8f\x72\x85"
                 "\x1e\xa3\xd9"
                 "\xf5\x26\x3f\xec\x5a\x60\x6d\x12\x71\xa8\x9b\x84\xcc\xa5\x3e"
                 "\xd7\x3c\x52"
                 "\x54\xe2\x45\xbf\x8f\x2f\x27\xc2\xc1\xc8\x7f\x39\xee\xa7\x8c"
                 "\x70\x17\xc8"
                 "\xc6\xb5\xab\x01\x66\x30\x32\xb5\x8d\xa3\x10\x57\x28\x5e\x56"
                 "\xc2\x03\xf4"
                 "\xe4\x8d\x67\x89\xc6\x6b\x26\x95\xa9\x00\xe0\x04\x82\xbd\x84"
                 "\x65\x59\xec"
                 "\xdd\xd4\x02\x64\xb3\x8e\x27\x96\x47\xd1\xec\x0f\xcc\xdc\x18"
                 "\x81\x83\x8b"
                 "\xbe\x0c\x83\x5e\x26\x90\xef\x05\x8b\x8f\x6a\x03\xe2\x9c\xd9"
                 "\xeb\x95\x84"
                 "\xe9\x7f\xbc\x30\x97\x73\xc3\x68\x8e\x5e\x03\xf9\xd3\x8e\x3e"
                 "\x45\x48\x73"
                 "\x8a\x5f\x56\x9c\x59\x14\x7d\x3e\x82\x3c\xcc\xac\x71\xd5\xe8"
                 "\x82\x5d\x51"
                 "\x34\xce\x98\x13\xcd\x0b\x8f\x96\x27\xa3\xdb\xfa\x45\xb8\x3a"
                 "\x59\xc8\x3d"
                 "\x2b\x4d\x3a\xd4\x37\x77\x8a\x3c\xb1\xbc\x77\xba\x16\xc9\x23"
                 "\x06\xf4\x26"
                 "\x1a\x2a\x1f\x0d\x5c\x7e\xda\xec\xf9\x26\xf9\x2d\x7c\x9d\xfc"
                 "\xae\x87\x51"
                 "\x3a\x68\xb8\xc7\xef\x7c\x63\x26\x4b\x85\x87\x67\xc1\x1a\xaa"
                 "\x41\xd2\x7c"
                 "\x63\x6f\x52\xe2\x85\x51\xe9\x3a\x96\x9c\xdc\x96\xd4\x38\x67"
                 "\xb7\xcb\xd6"
                 "\x8f\xe0\x35\x7b\xd3\x34\x15\xfa\xf2\x2a\xae\xeb\xc9\x57\xf4"
                 "\xb5\x73\x7a"
                 "\x04\xab\x72\x77\xb4\xed\x40\x08\xf0\x9e\xda\xff\x5a\x6d\xb6"
                 "\x9f\x6c\xb0"
                 "\x6f\x3d\x0b\x76\x68\x89\x06\xb2\xf5\x3b\x27\xe6\x3f\x37\x28"
                 "\xba\x2e\xda"
                 "\x50\x5f\xb1\xb3\x2f\x81\xdd\xdc\x6d\x30\x5f\xd5\x94\x9e\xdd"
                 "\x05\x49\x0c"
                 "\xb1\x61\x8f\x0c\xe1\x43\x0e\x9f\x5e\xdf\x50\x01\x2d\xc3",
      .senderPrivKey =
        "\x78\x30\x57\x7b\xaf\xcf\xc4\x58\x28\xda\x0c\x40\xaa\xb0"
        "\x9f\xb2\x27\xbf\xea\xe0\x68\xaa\xb8\xc0\x64\x22\x2a\xcb"
        "\xe6\xef\xfd\x34",
      .recvPubKey =
        "\x04\xc3\xd7\x14\xcb\x42\xe2\xb0\xa1\xd6\xf9\x85\x99\xe2\xf1"
        "\x86\xb8\xc2\xba\x6f\x6f\xab\x5e\x09\xa2\xab\xca\x86\x5c\x08"
        "\x05\x89\x2b\x2c\x37\x29\x33\x0e\xf8\x3d\xc9\xdf\x4b\x44\x36"
        "\x2b\x03\x9a\x06\x09\xd3\x6b\xeb\x93\x21\xa4\x31\xec\x12\x35"
        "\x06\xdd\xd9\x0f\x24",
      .authSecret =
        "\xe4\xd7\xb7\x9d\xec\xde\xde\x12\xc3\xe9\xd9\x0d\x3e\x05\x73\x0f",
      .salt =
        "\xe4\x98\x88\xd2\xb2\x8f\x27\x7f\x84\x7b\xc5\xde\x96\xf0\xf8\x1b",
      .plaintext = "Push the button, Frank!",
      .plaintextLen = 23,
      .maxPayloadLen = 1265,
      .payloadLen = 1058,
      .rs = 18,
      .pad = 31,
    },
};

void
test_webpush_aes128gcm_encrypt_ok(void) {
  size_t tests = sizeof(webpush_aes128gcm_encrypt_ok_tests) /
                 sizeof(webpush_aes128gcm_encrypt_ok_test_t);
  for (size_t i = 0; i < tests; i++) {
    webpush_aes128gcm_encrypt_ok_test_t t =
      webpush_aes128gcm_encrypt_ok_tests[i];

    size_t payloadLen =
      ece_aes128gcm_payload_max_length(t.rs, t.pad, t.plaintextLen);
    ece_assert(payloadLen == t.maxPayloadLen,
               "Got payload max length %zu for `%s`; want %zu", payloadLen,
               t.desc, t.maxPayloadLen);

    uint8_t* payload = calloc(payloadLen, sizeof(uint8_t));

    int err = ece_aes128gcm_encrypt_with_keys(
      (const uint8_t*) t.senderPrivKey, 32, (const uint8_t*) t.authSecret, 16,
      (const uint8_t*) t.salt, 16, (const uint8_t*) t.recvPubKey, 65, t.rs,
      t.pad, (const uint8_t*) t.plaintext, t.plaintextLen, payload,
      &payloadLen);
    ece_assert(!err, "Got %d encrypting payload for `%s`", err, t.desc);

    ece_assert(payloadLen == t.payloadLen,
               "Got actual payload length %zu for `%s`; want %zu", payloadLen,
               t.desc, t.payloadLen);
    ece_assert(!memcmp(payload, t.payload, payloadLen),
               "Wrong payload for `%s`", t.desc);

    free(payload);
  }
}

void
test_webpush_aes128gcm_encrypt_pad(void) {
  static const uint32_t maxRs = 128;

  const void* senderPrivKey = "\xac\xae\xc1\xc3\x7c\x30\x7c\xb9\x02\x8f\xbb\xd9"
                              "\xc7\xf3\xc6\x89\x26\x60\x08\x95\x9a\x5e\xd4\x03"
                              "\x42\x21\xb2\xda\x72\x01\x82\x8f";
  const void* authSecret =
    "\x44\x29\x81\x2d\x53\x5f\xbf\xdb\xea\xc8\x6d\xb7\x14\x5c\x6a\xf2";
  const void* salt =
    "\x45\x2b\xfb\xea\x8c\xc7\xa7\x57\x14\xd2\x03\xcf\xf1\x02\xe8\x76";
  const void* recvPubKey =
    "\x04\x2d\x78\x8d\x3e\x8e\x82\xf2\xd7\xea\xef\xbd\xe3\xa1\xbe\xde\xa2\x1f"
    "\x3b\xc9\x60\x33\x15\x73\x22\xa0\x9e\x14\x46\x55\xa3\xdf\x78\xfd\xca\xc8"
    "\x10\xe3\x02\x2a\xb5\x6a\x0e\xa9\xb8\xec\x06\x73\x8a\xce\x41\x1f\x49\x54"
    "\x7b\xc0\x0d\x1a\x1c\xde\x97\xce\x7b\xdd\x26";

  // For rs = `ECE_AES128GCM_MIN_RS`, we allow any amount of padding, because we
  // can only include one byte of data per record.
  for (uint32_t rs = ECE_AES128GCM_MIN_RS + 1; rs <= maxRs; rs++) {
    // Generate a random plaintext.
    size_t plaintextLen = (size_t)(rand() % (maxRs - 1) + 1);
    uint8_t* plaintext = calloc(plaintextLen, sizeof(uint8_t));
    int ok = RAND_bytes(plaintext, (int) plaintextLen);
    ece_assert(ok == 1, "Got %d generating plaintext for rs = %d", ok, rs);

    size_t maxPadLen = (rs - ECE_AES128GCM_MIN_RS) * (plaintextLen + 1);

    // Encrypting with the maximum padding length should succeed.
    size_t payloadLen =
      ece_aes128gcm_payload_max_length(rs, maxPadLen, plaintextLen);
    uint8_t* payload = calloc(payloadLen, sizeof(uint8_t));

    int err = ece_aes128gcm_encrypt_with_keys(
      senderPrivKey, 32, authSecret, 16, salt, 16, recvPubKey, 65, rs,
      maxPadLen, plaintext, plaintextLen, payload, &payloadLen);
    ece_assert(!err, "Got %d encrypting with rs = %d, padLen = %zu", err, rs,
               maxPadLen);

    // Adding more padding should fail.
    size_t badPadLen = maxPadLen + 1;
    payloadLen = ece_aes128gcm_payload_max_length(rs, badPadLen, plaintextLen);
    payload = realloc(payload, payloadLen);

    err = ece_aes128gcm_encrypt_with_keys(
      senderPrivKey, 32, authSecret, 16, salt, 16, recvPubKey, 65, rs,
      badPadLen, plaintext, plaintextLen, payload, &payloadLen);
    ece_assert(err == ECE_ERROR_ENCRYPT_PADDING,
               "Want error encrypting with rs = %d, padLen = %zu", rs,
               badPadLen);

    free(plaintext);
    free(payload);
  }
}
