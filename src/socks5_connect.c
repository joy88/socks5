#include "socks5.h"

static int reponse_method(socks5_t *socks5, unsigned char method) {
  if (method == 0x00) // NO AUTHENTICATION REQUIRED
    return 0;
  else if (method == 0x01) // GSSAPI
    return -1;
  else if (method == 0x02) // USERNAME / PASSWORD
    return socks5_connect_user(socks5);
  else if (method >= 0x03 && method <= 0x7F) // IANA ASSIGNED
    return -1;
  else if (method >= 0x80 && method <= 0xFE) // RESERVED FOR PRIVATE METHODS
    return -1;
  else // NO ACCEPTABLE METHODS
    return -1;
}

static int request_method_dependent(socks5_t *socks5) {
  msg[0] = 0x05;
  msg[1] = socks5->command;
  msg[2] = 0x00;
  if (socks5->ipv4 != NULL) {
    msg[3] = 0x01;
  } else if (socks5->domainName != NULL) {
    msg[3] = 0x03;
    msg[4] = (uint8_t)strlen(socks5->domainName);
    for (uint32_t itr = 0; itr != mag[4]; ++itr)
      msg[itr + 5] = socks5->domainName[itr];
  } else if (socks5->ipv6 != NULL) {
    msg[3] = 0x04;
  }
}

int socks5_connect(socks5_t *socks5) {
  if (socks5->fd == -1)
    return -1;
  write(socks5->fd, "\x05\x01\x00", 3);
  unsigned char tmp[512];
  if (read(socks5->fd, tmp, 512) != 2)
    return -1;
  reponse_method(socks5, tmp[1]);
  request_method_dependent(socks5);

  int ret = read(socks5->fd, tmp, 512);

  for (int itr = 0; itr < ret; ++itr)
    printf("%d:", tmp[itr]);

  printf("\n");
  return 0;
}
