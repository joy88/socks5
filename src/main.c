#include "socks5.h"

int main(void) {
  socks5_t socks5;
  socks5.fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socks5.fd == -1) {
    printf("Error\n");
    return 0;
  }
  struct sockaddr_in addr = {0};
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr.sin_family = AF_INET;
  addr.sin_port = htons(9050);
  if (connect(socks5.fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    printf("Error connect\n");
    return 0;
  }
  socks5_set_address(&socks5, "82.102.24.167", 22);

  // socks5_set_address(&socks5, "5800:10C3:E3C3:F1AA:48E3:D923:D494:AAFF", 22);
  // socks5_set_address(&socket, "google.com", 80);
  socks5_connect(&socks5);
  return 0;
}
