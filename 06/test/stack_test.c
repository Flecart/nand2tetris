#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "aritTrans.h"

void test_constant_push() {
    char *line = "push constant 1";
    char *asmCode = push(line, "hello");

    char *testCode = ""
        "@1\n"
        "D=A\n"
        "@SP\n"
        "A=M\n"
        "M=D\n"
        "@SP\n"
        "M=M+1\n";

    assert(strcmp(testCode, asmCode) == 0);
    free(asmCode);
}

void test_static_push() {
    char *line = "push static 1";
    char *asmCode = push(line, "hello");

    char *testCode = ""
        "@hello.1\n"
        "D=M\n"
        "@SP\n"
        "A=M\n"
        "M=D\n"
        "@SP\n"
        "M=M+1\n";

    assert(strcmp(testCode, asmCode) == 0);
    free(asmCode);
}

void test_argument_push() {
    char *line = "push argument 1";
    char *asmCode = push(line, "hello");

    char *testCode = ""
        "@ARG\n"
        "D=A\n"
        "@1\n"
        "A=D+A\n"
        "D=M\n"
        "@SP\n"
        "A=M\n"
        "M=D\n"
        "@SP\n"
        "M=M+1\n";

    assert(strcmp(testCode, asmCode) == 0);
    free(asmCode);
}

void test_local_push() {
    char *line = "push local 1";
    char *asmCode = push(line, "hello");

    char *testCode = ""
        "@LCL\n"
        "D=A\n"
        "@1\n"
        "A=D+A\n"
        "D=M\n"
        "@SP\n"
        "A=M\n"
        "M=D\n"
        "@SP\n"
        "M=M+1\n";

    assert(strcmp(testCode, asmCode) == 0);
    free(asmCode);
}

void test_notpush_push() {
    char *line = "altro local 1";
    char *asmCode = push(line, "hello");
    char *testCode = NULL;
    assert(asmCode==testCode);
    free(asmCode);
}

int main() {
    test_constant_push();
    test_static_push();
    test_argument_push();
    test_local_push();
    test_notpush_push();
    return 0;
}