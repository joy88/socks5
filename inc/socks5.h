#ifndef _SOCKS5_H
#define _SOCKS5_H

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct _socks5 socks5_t;

struct _socks5 {
  char *domainName;
  int fd;
  uint8_t *ipv4;
  uint16_t *ipv6;
  char *password;
  uint16_t port;
  char *username;
};

void free_socks5(socks5_t *socks5);
int socks5_connect(socks5_t *socks5);
int socks5_connect_user(socks5_t *socks5);
int socks5_set_address(socks5_t *socks5, char *address, uint16_t port);
int socks5_set_user_password(socks5_t *socks5, char *username, char *password);

#endif
