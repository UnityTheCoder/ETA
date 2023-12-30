#include <stdint.h>
#include <stdlib.h>

#ifndef TYPES_HPP
#define TYPES_HPP

#define TYPE_INT32    0x00
#define TYPE_INT8     0x01
#define TYPE_REGISTER 0x02
#define TYPE_VARIABLE 0x03
#define TYPE_STRING   0x04

#define REG_RAX       0x00
#define REG_RBX       0x01
#define REG_RCX       0x02
#define REG_RDX       0x03
#define REG_RSI       0x04

#define INS_MOV       0x00
#define INS_ADD       0x01
#define INS_SUB       0x02
#define INS_MUL       0x03
#define INS_DIV       0x04

const char SIGN_ETA[5]      {0x1E, 0x45, 0x54, 0x41};
#define SIGN_FUNC     0xF3


typedef struct Value {
  short type;
  uint32_t value;
} Value;

typedef struct Variable {
  const char *name;
  char type;
  Value *data;
} Variable;

typedef struct Instruction {
  char opcode;
  Value *target;
  Value *source;
} Instruction;

typedef struct Parameter {
  const char *name;
  char type;
} Parameter;

typedef struct Function {
  const char *name;
  Parameter *parameters;
  Instruction **instructions;
} Function;

typedef struct Executable {
  Variable **data;
  Function **text;
  char **rodata;
  size_t data_i;
  size_t text_i;
  size_t ro_i;
} Executable;

namespace Compiler {
  void new_exec(size_t data_size, size_t text_size, size_t ro_size);
  void new_variable(const char *name, char type, Value *data);
  void new_function(const char *name, Parameter *parameters, Instruction **body);
  Instruction *move(Value *target, Value *source);
  Instruction *add(Value *target, Value *source);
  Instruction *sub(Value *target, Value *source);
  Instruction *mul(Value *target, Value *source);
  Instruction *div(Value *target, Value *source);
}

namespace Values {
    Value *new_integer(uint32_t value);
    Value *new_string(const char* value);
    Value *vregister(char opcode);
}

#endif
