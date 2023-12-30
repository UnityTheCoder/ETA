#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../commons/types.h"

FILE *binary_file;
size_t binary_offset;

namespace ByteWriter {
  void write_i32(int32_t value) {
    fwrite(&value, 4, 1, binary_file);
  }

  void write_i8(char value) {
    fwrite(&value, 1, 1, binary_file);
  }

  void write_i32_a(int32_t *value, size_t n) {
    fwrite(&value, 4, n, binary_file);
  }

  void write_i8_a(const char *value, size_t n) {
    fwrite(&value, 1, n, binary_file);
  }

  void write_string(const char *value) {
    size_t s_size = strlen(value);
    ByteWriter::write_i8(s_size);
    fwrite(&value, sizeof(char),s_size, binary_file);
  }

  int32_t read_i32() {
    fseek(binary_file, binary_offset, SEEK_SET);
    int32_t buffer=0; 
    fread(&buffer, 4, 1, binary_file);
    binary_offset+=4;
    return buffer;
  }

  char read_i8() {
    fseek(binary_file, binary_offset, SEEK_SET);
    char buffer=0;
    fread(&buffer, 1, 1, binary_file);
    binary_offset++;
    return buffer;
  }

  char *read_i8_a(size_t n) {
    fseek(binary_file, binary_offset, SEEK_SET);
    char *buffer = (char*)malloc(sizeof(char)*n);
    fread(&buffer, 1, n, binary_file);
    binary_offset+=n;
    return buffer;
  }

  int32_t *read_i32_a(size_t n) {
    fseek(binary_file, binary_offset, SEEK_SET);
    int32_t *buffer = (int32_t*)malloc(sizeof(int32_t)*n);
    fread(&buffer, 4, n, binary_file);
    binary_offset+=4*n;
    return buffer;
  }

  char *read_string() {
    fseek(binary_file, binary_offset, SEEK_SET);
    size_t s_size = ByteWriter::read_i8();
    char *buffer = (char*)malloc(sizeof(char)*s_size);
    fread(&buffer, sizeof(char), s_size, binary_file);
    binary_offset+=s_size;
    return buffer;
  }

  void openw(const char *path) {
    binary_file = fopen(path, "wb");
  }
  
  void openr(const char *path) {
    binary_file = fopen(path, "rb");
    binary_offset = 0;
  }

  void close() {
    fclose(binary_file);
  }
}

namespace NativeWriter {
  void initialize(const char *path) {
    ByteWriter::openw(path);
    ByteWriter::write_i8_a(SIGN_ETA, 4);
  }
}
