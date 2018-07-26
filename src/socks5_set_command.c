#include "socks5.h"

void socks5_set_command(socks5_t *socks5, int command) {
  socks5->command = command;
}
