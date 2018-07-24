#include "socks5.h"

void free_socks5(socks5_t *socks5) {
  if (socks5->domainName != NULL)
    free(socks5->domainName);
  socks5->fd = -1;
  if (socks5->ipv4 != NULL)
    free(socks5->ipv4);
  if (socks5->ipv6 != NULL)
    free(socks5->ipv6);
  if (socks5->password != NULL)
    free(socks5->password);
  if (socks5->username != NULL)
    free(socks5->username);
  socks5->port = 0;
}
