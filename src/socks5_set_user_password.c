#include "socks5.h"

int socks5_set_user_password(socks5_t *socks5, char *username, char *password) {
  if (strlen(username) > 255 || strlen(password) > 255)
    return -1;
  if (socks5->username != NULL)
    free(socks5->username);
  if (socks5->password != NULL)
    free(socks5->password);
  socks5->username = strdup(username);
  socks5->password = strdup(password);
  return 0;
}
