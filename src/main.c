#include "socks5.h"

int main(void) {
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    printf("Error\n");
    return 0;
  }
  struct sockaddr_in addr = {0};
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr.sin_family = AF_INET;
  addr.sin_port = htons(9050);
  if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    printf("Error connect\n");
    return 0;
  }

  printf("%x\n", inet_addr("127.0.0.1"));

  // socks5_connect(fd, "82.102.24.167", 22);

  return 0;
}
