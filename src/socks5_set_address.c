#include "socks5.h"

int socks5_set_address(socks5_t *socks5, char *address, uint16_t port) {
  {
    if (address == NULL || strlen(address) > 255)
      return -1;
    free_socks5(socks5);
  }
  socks5->port = port;
  for (uint32_t itr = 0; address[itr] != 0; ++itr) {
  }
}
