#include "socks5.h"

/*
o X '00' NO AUTHENTICATION REQUIRED
o X '01' GSSAPI
o X '02' USERNAME / PASSWORD
o X '03' to X '7F' IANA ASSIGNED
o X '80' to X 'FE' RESERVED FOR PRIVATE METHODS
o X 'FF' NO ACCEPTABLE METHODS
*/

static int reponse_method(unsigned char method, socks5_t *socks5) {
  if (method == 0x00)
    return 0;
  else if (method == 0x01)
    return 0;
  else if (method == 0x02)
    return socks5_connect_user(socks5);
  else if (method >= 0x03 && method <= 0x7F)
    return 0;
  else if (method >= 0x80 && method <= 0xFE)
    return 0;
  else
    return -1;
}

/*
o VER protocol version: X '05'
o CMD
  o CONNECT X '01'
  o BIND X '02'
  o UDP ASSOCIATE X '03'
o RSV RESERVED
o ATYP address type of following address
  o IP V4 address: X '01'
  o DOMAINNAME : X '03'
  o IP V6 address: X '04'
o DST.ADDR desired destination address
o DST.PORT desired destination port in network octet order
*/

static void set_atyp(unsigned char *msg, socks5_t socks5) {}

static int method_dependent() {}

int socks5_connect(socks5_t *socks5) {
  // First Request 0x05 0x01 0x00
  return 0;
  write(socks5->fd, "\x05\x01\x00", 3);
  // Response

  unsigned char tmp[512];
  int ret = read(socks5->fd, tmp, 512);
  for (int itr = 0; itr < ret; ++itr)
    printf("%d", tmp[itr]);
  //  reponse_method(tmp[1]);

  method_dependent();

  return 0;
}
