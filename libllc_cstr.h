/*
 * VERSION HISTORY
 *
 *   - 0.01 - Initial version
 */

// ...
// BEGIN_EXAMPLE: C example
// ...
#if 0
    #include <stdio.h>
    #include <stdlib.h>

    #define LIBLLC_CSTR_IMPLEMENTATION
    #include "libllc_cstr.h"

int main(int argc, char **argv) {
    {
        const char *original  = "Hello, world!";
        char       *duplicate = ll_dup_cstr(original);
        assert(strcmp(original, duplicate) == 0);
        free(duplicate);
    }
    {
        char* joined = ll_join_cstr("Hello, ", "world!");
        assert(strcmp(joined, "Hello, world!") == 0);
        free(joined);
    }
    return 0;
}
#endif
// ...
// END_EXAMPLE: C example
// ...

#ifndef LIBLLC_CSTR_H_
    #define LIBLLC_CSTR_H_

    #ifndef LL_ALLOC
        #define LL_ALLOC(size) malloc(size)
        #define LL_FREE(ptr)   free(ptr)
    #endif

    #ifndef _MSC_VER
        #ifdef __cplusplus
            #define ll_inline inline
        #else
            #define ll_inline
        #endif
    #else
        #define ll_inline __forceinline
    #endif

    #include <stddef.h>  // Use `stddef.h` for `size_t`
    #include <stdlib.h>
    #include <string.h>  // Required for memcpy, cstring functions.

    #ifdef __cplusplus
extern "C" {
    #endif

typedef char *llcstr;

typedef int llbool;
    #if !defined(LL_TRUE) || !defined(LL_FALSE)
        #define LL_TRUE  1
        #define LL_FALSE 0
    #endif

    #ifndef LL_SIZE_TYPE
        #define LL_SIZE_TYPE
typedef size_t llusize;
    #endif

    #ifndef LL_NULLPTR
        #if __cplusplus
            #if __cplusplus >= 201103L
                #define LL_NULLPTR nullptr
            #else
                #define LL_NULLPTR 0
            #endif
        #else
            #define LL_NULLPTR (void *)0
        #endif
    #endif

char *ll_dup_cstr(char const *cstr);
char *ll_dup_cstrn(const char *cstr, llusize len);
char *ll_join_cstr(const char *cstr, const char *other);

char *ll_str_alloc_size(char *const str);

    #ifdef __cplusplus
}  //  _end: extern "C" {
    #endif  // _end: __cplusplus

    #if defined(LL_STRING_CPP)

        #if !defined(__cplusplus)
            #error You forgot to compile as C++ for the C++ version of libllc_string.h
        #endif

namespace ll {
typedef llusize usize;

// void free_cstr(char *cstr) { ll_free_str(str); cstr = LL_NULLPTR; }
ll_inline char *dup_cstr(const char *cstr) { return ll_dup_cstr(cstr); };
ll_inline cstr  dup_cstrn(const char *cstr, usize len) {
    return ll_dup_cstrn(cstr, len);
};
ll_inline char *join_cstr(const char *cstr, const char *other) {
    str = ll_join_cstr(cstr, other);
};
}  // namespace ll
    #endif  // LL_STRING_CPP
#endif      // LIBLLC_CSTR_H_

#ifdef LIBLLC_CSTR_IMPLEMENTATION

// static char *ll_init_cstr(char const *cstr, llusize len);
// static void  ll_set_cstr_len(char *cstr, llusize len);
static void ll_free_cstr(char *cstr) {
    if (cstr == LL_NULLPTR) return;
    LL_FREE((char *)cstr - 1);
}

/// Duplicate S, returning an identical malloc'd string.
char *ll_dup_cstr(const char *cstr) {
    size_t size = strlen(cstr) + 1;
    char  *ptr  = (char *)malloc(size);
    if (ptr != NULL) memcpy(ptr, cstr, size);
    return ptr;
}

/// Duplicate S up to a specified length, returning malloc'd string.
char *ll_dup_cstrn(const char *cstr, size_t len) {
    size_t n_ptr;
    for (n_ptr = 0; n_ptr < len && cstr[n_ptr] != '\0'; n_ptr += 1) continue;
    char *ptr = (char *)malloc(n_ptr);
    if (ptr != NULL) {
        memcpy(ptr, cstr, n_ptr);
        ptr[n_ptr] = '\0';
    };
    return ptr;
}

/// Join one C-string to another.
char *ll_join_cstr(const char *cstr, const char *other) {
    if (cstr == LL_NULLPTR || other == LL_NULLPTR) return NULL;
    llusize len1 = strlen(cstr);
    llusize len2 = strlen(other);

    char *result = (char *)malloc((len1 + len2 + 1));
    assert(result != NULL);

    strcpy(result, cstr);
    strcat(result, other);
    return result;
}

/*
TODO: FIXME: Handle Invalid read of size 1
    source should be an allocated pointer, and can be reallocated with
    additional len of strlen(other)

void ll_append_cstr(char *cstr, const char *other) {
    if (cstr == LL_NULLPTR || other == LL_NULLPTR) return NULL;
    char *end = cstr;
    while (*end != '\0') end += 1;  // Find end of string.
    while (*other != '\0') {        // Copy second to end of first string.
        *end = *other;
        end += 1;
        other += 1;
    }
    *end = '\0';
}
*/

#endif  // LIBLLC_CSTR_IMPLEMENTATION
