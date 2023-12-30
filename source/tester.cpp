#include <stdio.h>
#include <stdlib.h>
#include "./commons/types.h"
#include "./generator/nwriter.hpp"

int main() {
  Compiler::new_exec(1,0,1);
  Value* mystr = Values::new_string("hello_offset");
  Compiler::new_variable("offset", TYPE_STRING, mystr);
  
  Parameter *params = (Parameter*)malloc(sizeof(Parameter)*2);
  params[0] = (Parameter){"a", TYPE_INT32};
  params[1] = (Parameter){"b", TYPE_INT32};

  Instruction **body = (Instruction**)malloc(sizeof(Instruction)*1);
  body[0] = Compiler::move(
    Values::vregister(REG_RAX),
    Values::new_integer(20)
  );

  Compiler::new_function("add", params, body);
  NativeWriter::initialize("testbin");
}


