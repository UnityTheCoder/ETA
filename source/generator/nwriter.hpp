#include <stdint.h>
#include <stdlib.h>

#ifndef NWRITER_HPP
#define NWRITER_HPP

namespace ByteWriter {
  void write_i32(int32_t value);
  void write_i8(char value);
  void write_i32_a(int32_t *value, size_t n);
  void write_i8_a(const char *value, size_t n);
  void write_string(const char *value);
  int32_t read_i32();
  char read_i8();
  char *read_i8_a(size_t n);
  int32_t *read_i32_a(size_t n);
  char *read_string();
  void openw(const char *path);
  void openr(const char *path);
  void close();
}

namespace NativeWriter {
  void initialize(const char *path);
}

#endif
