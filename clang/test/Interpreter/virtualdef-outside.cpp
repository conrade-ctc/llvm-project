// REQUIRES: host-supports-jit
// RUN: cat %s | clang-repl | FileCheck %s
// virtual functions defined outside of class somehow got duplicate symbols:
//     duplicate definition of symbol '__ZTV3Two' (i.e., vtable for Two)
// see https://github.com/llvm/llvm-project/issues/141039.
// fixed in PR: XXX

extern "C" int printf(const char *, ...);

struct One { virtual void print() { printf("ONE\n"); } };
One().print();
// CHECK: ONE

struct Two { virtual void print(); };
void Two::print() { printf("TWO\n"); }
Two().print();
// CHECK: TWO

%quit
