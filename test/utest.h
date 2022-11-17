#ifndef UTEST_H
#define UTEST_H

#include <setjmp.h>

struct ut_state
{
  int no_tests;
  int no_errors;
  jmp_buf abort;
};

// clang-format off
#define UT_BLOCK(CODE) do { CODE; } while(0)
#define UT_ABORT_ERROR() UT_BLOCK(longjmp(_ut_state_.abort, 1))
#define UT_ABORT_FATAL() UT_BLOCK(longjmp(_ut_state_.abort, 2))
// clang-format on

#define UT_SUITE(CODE)                                                         \
  int main(void)                                                               \
  {                                                                            \
    struct ut_state _ut_state_ = { .no_tests = 0, .no_errors = 0 };            \
    switch (setjmp(_ut_state_.abort)) {                                        \
      case 0:                                                                  \
        break;                                                                 \
      case 2: /* Fatal error */                                                \
        fprintf(stderr, "Aborted test after fatal error.\n");                  \
      case 1: /* Normal error */                                               \
        fprintf(stderr, "Test failed.\n");                                     \
        return 2;                                                              \
    }                                                                          \
    UT_BLOCK(CODE);                                                            \
    if (_ut_state_.no_errors > 0) {                                            \
      fprintf(stderr, "Encounterd %d errors.\n", _ut_state_.no_errors);        \
      UT_ABORT_ERROR();                                                        \
    }                                                                          \
    return 0;                                                                  \
  }

#define UT_PRINT_ERR(FMT, ...)                                                 \
  fprintf(stderr, "error: %s(%d): " FMT, __FILE__, __LINE__, __VA_ARGS__);

#define UT_ERROR_IF_(EXPR, FMT, ...)                                           \
  UT_BLOCK(_ut_state_.no_tests++; if (EXPR) {                                  \
    _ut_state_.no_errors++;                                                    \
    UT_PRINT_ERR(FMT, __VA_ARGS__);                                            \
  })
#define UT_FATAL_IF_(EXPR, FMT, ...)                                           \
  UT_BLOCK(_ut_state_.no_tests++; if (EXPR) {                                  \
    _ut_state_.no_errors++;                                                    \
    UT_PRINT_ERR(FMT, __VA_ARGS__);                                            \
    longjmp(_ut_state_.abort, 1);                                              \
  })

#define UT_ERROR_IF(EXPR) UT_ERROR_IF_(EXPR, "Error: %s\n", #EXPR)
#define UT_FATAL_IF(EXPR) UT_FATAL_IF_(EXPR, "Fatal error: %s\n", #EXPR)

#endif