#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIBLLC_CSTR_IMPLEMENTATION
#include "libllc_cstr.h"

static int test__libllc__cstr();

int main(int argc, char **argv) {
    assert(test__libllc__cstr() == 0);
    return 0;
}

static int cstr__ll__dup__cstr();
static int cstr__ll__join__cstr();

static int test__libllc__cstr() {
    assert(cstr__ll__dup__cstr() == 0);
    assert(cstr__ll__join__cstr() == 0);
    return 0;
}

static int cstr__ll__dup__cstr() {
    const char *original  = "Hello, world!";
    char       *duplicate = ll_dup_cstr(original);
    assert(strcmp(original, duplicate) == 0);
    free(duplicate);
    return 0;
}
static int cstr__ll__join__cstr() {
    char *joined = ll_join_cstr("Hello, ", "world!");
    assert(strcmp(joined, "Hello, world!") == 0);
    free(joined);
    return 0;
}
