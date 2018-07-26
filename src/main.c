#include "socks5.h"

int main(int argc, char **argv) {
  if (argc != 3)
    return -1;
  socks5_t socks5 = {0};
  socks5.fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socks5.fd == -1)
    return -1;
  struct sockaddr_in addr = {0};
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr.sin_family = AF_INET;
  addr.sin_port = htons(9050);
  if (connect(socks5.fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    return -1;
  socks5_set_command(&socks5, 0x01);
  socks5_set_address(&socks5, argv[1], atoi(argv[2]));
  socks5_connect(&socks5);
  return 0;
}
