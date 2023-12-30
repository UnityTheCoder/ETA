#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../commons/types.h"
#include "nwriter.hpp"

Executable *c_exec;

void Compiler::new_exec(size_t data_size, size_t text_size, size_t ro_size) {
    c_exec = (Executable*)malloc(sizeof(Executable));
    c_exec->data = (Variable**)malloc(sizeof(Variable)*data_size);
    c_exec->text = (Function**)malloc(sizeof(Function)*text_size);
    c_exec->rodata = (char**)malloc(sizeof(char*)*ro_size);
    c_exec->data_i = 0;
    c_exec->text_i = 0;
    c_exec->ro_i   = 0;
}

void Compiler::new_variable(const char *name, char type, Value *data) {
    Variable *var = (Variable*)malloc(sizeof(Variable));
    var->name = name;
    var->type = type;
    var->data = data;
    c_exec->data[c_exec->data_i] = var;
    c_exec->data_i++;
}

void Compiler::new_function(const char *name, Parameter *parameters, Instruction **body) {
    Function *func = (Function*)malloc(sizeof(Function));
    func->name = name;
    func->parameters = parameters;
    func->instructions = body;
    c_exec->text[c_exec->text_i] = func;
    c_exec->text_i++;
}

Value *Values::new_integer(uint32_t value) {
    Value *val = (Value*)malloc(sizeof(Value));
    val->type = TYPE_INT32;
    val->value = value;
    return val;
}

Value *Values::new_string(const char *value) {
    Value *val = (Value*)malloc(sizeof(Value));
    val->type = TYPE_STRING;
    c_exec->rodata[c_exec->ro_i] = const_cast<char*>(value);
    val->value = c_exec->ro_i;
    c_exec->ro_i++;
    return val;
}

Value *Values::vregister(char opcode) {
  Value *val = (Value*)malloc(sizeof(Value));
  val->type = TYPE_REGISTER;
  val->value = opcode;
  return val;
}

Instruction *Compiler::move(Value *target, Value *source) {
  Instruction *inst = (Instruction*)malloc(sizeof(Instruction));
  inst->opcode = INS_MOV;
  inst->target = target;
  inst->source = source;
  return inst;
}

Instruction *Compiler::add(Value *target, Value *source) {
  Instruction *inst = (Instruction*)malloc(sizeof(Instruction));
  inst->opcode = INS_ADD;
  inst->target = target;
  inst->source = source;
  return inst;
}

Instruction *Compiler::sub(Value *target, Value *source) {
  Instruction *inst = (Instruction*)malloc(sizeof(Instruction));
  inst->opcode = INS_SUB;
  inst->target = target;
  inst->source = source;
  return inst;
}

Instruction *Compiler::mul(Value *target, Value *source) {
  Instruction *inst = (Instruction*)malloc(sizeof(Instruction));
  inst->opcode = INS_MUL;
  inst->target = target;
  inst->source = source;
  return inst;
}

Instruction *Compiler::div(Value *target, Value *source) {
  Instruction *inst = (Instruction*)malloc(sizeof(Instruction));
  inst->opcode = INS_DIV;
  inst->target = target;
  inst->source = source;
  return inst;
}


