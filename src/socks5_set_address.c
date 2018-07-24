#include "socks5.h"

int socks5_set_address(socks5_t *socks5, char *address, uint16_t port) {
  {
    if (address == NULL || strlen(address) > 255)
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
  for (uint32_t itr = 0; address[itr] != 0; ++itr) {
  }
}
