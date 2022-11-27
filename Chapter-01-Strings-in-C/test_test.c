#include <stdio.h>
#include <stdlib.h>

#include <utest.h>

// clang-format off
#define slice_type(T_)             struct { T_ *buf; size_t len; }
#define slice_from_array(A_, LEN_) { .buf = A_, .len = LEN_ }
#define slice(S_, I_, J_)          { .buf = S_.buf + I_, .len = J_ - I_ }
// clang-format on

typedef slice_type(int) int_slice;
static void print_int_slice(int_slice slice)
{
    for (size_t i = 0; i < slice.len; i++)
    {
        printf("%d\n", slice.buf[i]);
    }
    printf("\n");
}

int main(void)
{
    int arr[] = {1, 2, 3};
    int_slice slice = slice_from_array(arr, sizeof arr);
    int_slice suf1 = slice(slice, 1, slice.len);
    print_int_slice(suf1);
    return 0;
}