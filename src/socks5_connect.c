#include "socks5.h"

/*
 * @brief Method
 *
 * 0x00         : NO AUTHENTICATION REQUIRED
 * 0x01         : GSSAPI
 * 0x02         : USERNAME / PASSWORD
 * 0x03 to 0x7F : IANA ASSIGNED
 * 0x80 to 0xFE : RESERVED FOR PRIVATE METHODS
 * 0xFF         : NO ACCEPTABLE METHODS
 */

static int reponse_method(socks5_t *socks5, unsigned char method) {
  if (method == 0x00)
    return 0;
  else if (method == 0x01)
    return -1;
  else if (method == 0x02)
    return socks5_connect_user(socks5);
  else if (method >= 0x03 && method <= 0x7F)
    return -1;
  else if (method >= 0x80 && method <= 0xFE)
    return -1;
  else
    return -1;
}

static int request_method_dependent(socks5_t *socks5) {
  uint32_t lenght = 0;
  unsigned char msg[512] = {0};
  msg[0] = 0x05;
  msg[1] = socks5->command;
  msg[2] = 0x00;
  if (socks5->ipv4 != NULL) {
    msg[3] = 0x01;
    msg[4] = socks5->ipv4[0];
    msg[5] = socks5->ipv4[1];
    msg[6] = socks5->ipv4[2];
    msg[7] = socks5->ipv4[3];
    msg[8] = 0;
    msg[9] = 0;
    lenght = 10;
  } else if (socks5->domainName != NULL) {
    msg[3] = 0x03;
    msg[4] = (uint8_t)strlen(socks5->domainName);
    for (uint32_t itr = 0; itr != msg[4]; ++itr)
      msg[itr + 5] = socks5->domainName[itr];
    lenght = 10;
  } else if (socks5->ipv6 != NULL) {
    msg[3] = 0x04;
    lenght = 10;
  }
  write(socks5->fd, msg, lenght);
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
  if (tmp[1] != 0)
    return -1;
  return 0;
}
