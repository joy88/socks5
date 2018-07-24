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
      if (len == 4)
        return -1;
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
  socks5->ipv4[0] = tmp[0];
  socks5->ipv4[1] = tmp[1];
  socks5->ipv4[2] = tmp[2];
  socks5->ipv4[3] = tmp[3];
  return 0;
}

static int get_ipv6(socks5_t *socks5, char *address) { return -1; }

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
