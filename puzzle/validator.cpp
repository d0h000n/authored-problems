#include "testlib.h"

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, 9, "n"); inf.readSpace();
    int m = inf.readInt(1, 9, "m"); inf.readEoln();
    inf.readEof();
    ensuref(n*m > 1, "n*m is 1.");
    ensuref(n*m <= 9, "n*m is greater than 9.");
    return 0;
}
