#include "socks5.h"

static int get_ipv4(socks5_t *socks5, char *address) {
  uint32_t index = 0;
  uint32_t len = 0;
  uint32_t length = strlen(address);
  uint32_t tmp[4] = {0};
  for (uint32_t itr = 0; itr != length; ++itr) {
    if (index == 4)
      return 0;
    if (address[itr] >= '0' && address[itr] <= '9') {
      if (len == 0 && address[itr] == '0' && address[itr + 1] != 0 &&
          address[itr + 1] != '.')
        return -1;
      tmp[index] = tmp[index] * 10 + address[itr] - '0';
      ++len;
      if (tmp[index] > 255)
        return -1;
    } else if (address[itr] == '.') {
      len = 0;
      ++index;
    }
  }
  socks5->ipv4 = (uint8_t *)malloc(sizeof(uint8_t) * 4);
  for (uint32_t itr = 0; itr != 4; ++itr)
    socks5->ipv4[itr] = tmp[itr];
  return 0;
}

static int get_ipv6(socks5_t *socks5, char *address) {
  uint32_t index = 0;
  uint32_t len = 0;
  uint32_t length = strlen(address);
  uint32_t tmp[8] = {0};
  for (uint32_t itr = 0; itr != length; ++itr) {
    if (index == 8)
      return -1;
    if ((address[itr] >= '0' && address[itr] <= '9') ||
        (address[itr] >= 'a' && address[itr] <= 'f') ||
        (address[itr] >= 'A' && address[itr] <= 'F')) {
      if (len == 3)
        return -1;
      tmp[index] *= 16;
      if (address[itr] >= '0' && address[itr] <= '9')
        tmp[index] += address[itr] - '0';
      else if (address[itr] >= 'a' && address[itr] <= 'f')
        tmp[index] += address[itr] - 'a' + 10;
      else if (address[itr] >= 'A' && address[itr] <= 'F')
        tmp[index] += address[itr] - 'A' + 10;
      ++len;
    } else if (address[itr] == ':') {
      len = 0;
      ++index;
    }
  }
  socks5->ipv6 = (uint16_t *)malloc(sizeof(uint16_t) * 8);
  for (uint32_t itr = 0; itr != 8; ++itr)
    socks5->ipv6[itr] = tmp[itr];
  return 0;
}

static int get_domainName(socks5_t *socks5, char *address) { return -1; }

int socks5_set_address(socks5_t *socks5, char *address, uint16_t port) {
  {
    if (address == NULL && strlen(address) > 255)
      return -1;
    if (socks5->domainName != NULL)
      free(socks5->domainName);
    if (socks5->ipv4 != NULL)
      free(socks5->ipv4);
    if (socks5->ipv6 != NULL)
      free(socks5->ipv6);
    if (socks5->password != NULL)
      free(socks5->password);
    if (socks5->username != NULL)
      free(socks5->username);
  }
  socks5->port = port;
  if (get_ipv4(socks5, address) == 0)
    return 0;
  else if (get_ipv6(socks5, address) == 0)
    return 0;
  else if (get_domainName(socks5, address) == 0)
    return 0;
  return -1;
}
