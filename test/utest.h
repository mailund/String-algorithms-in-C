#ifndef UTEST_H
#define UTEST_H

struct ut_state
{
  int no_tests;
  int no_errors;
};

// clang-format off
#define UT_BLOCK(CODE) do { CODE } while(0)
// clang-format on

#define UT_PRINT_ERR(FMT, ...)                                                 \
  fprintf(stderr, "error: %s(%d): " FMT, __FILE__, __LINE__, __VA_ARGS__);

#define UT_ERROR_IF_(EXPR, FMT, ...)                                           \
  UT_BLOCK(_tl_state_.no_tests++; if (EXPR) {                                  \
    _tl_state_.no_errors++;                                                    \
    UT_PRINT_ERR(FMT, __VA_ARGS__);                                            \
  })
#define UT_FATAL_IF_(EXPR, FMT, ...)                                           \
  UT_BLOCK(_tl_state_.no_tests++; if (EXPR) {                                  \
    _tl_state_.no_errors++;                                                    \
    UT_PRINT_ERR(FMT, __VA_ARGS__);                                            \
    goto _tl_escape_;                                                          \
  })

#define UT_ERROR_IF(EXPR) UT_ERROR_IF_(EXPR, "%s\n", #EXPR)
#define UT_FATAL_IF(EXPR) UT_FATAL_IF_(EXPR, "%s\n", #EXPR)

#endif