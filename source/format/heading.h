#include <stdint.h>

#ifndef HEADING_H
#define HEADING_H

typedef struct p_header {
  char *signature;
} __attribute__((packed)) p_header;

#endif
