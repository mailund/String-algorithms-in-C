#include <stdio.h>
#include <stdlib.h>

#include <utest.h>

// clang-format off
#define slice_type(T_) struct      { T_ *buf; size_t len; }
#define slice_from_array(A_, LEN_) { .buf = A_, .len = LEN_ }
#define sub(S_, I_, J_)            { .buf = S_.buf + I_, .len = J_ - I_ }
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

struct match_iter;
struct match_iter_type
{
    void *(*alloc)(const char *x, const char *p);
    void (*dealloc)(struct match_iter *itr);
    int (*next)(struct match_iter *itr);
};
struct match_iter
{
    struct match_iter_type *type;
};

void new_match_iter(const char *x, const char *p, struct match_iter_type *type)
{
    struct match_iter *itr = type->alloc(x, p);
}

void free_match_iter(struct match_iter *itr)
{
    itr->type->dealloc(itr);
}

void init_match_iter(struct match_iter *itr,
                     struct match_iter_type *type,
                     const char *x, const char *p)
{
    itr->type = type;
    itr->x = x;
    itr->p = p;
}

int next(struct match_iter *itr)
{
    return itr->type->next(itr);
}

void dealloc(struct match_iter *itr)
{
    itr->type->dealloc(itr);
}

struct naive_match_iter
{
    struct match_iter_type *vtable;
    const char *x, *p;
};

int main(void)
{
    int arr[] = {1, 2, 3};
    int_slice x = slice_from_array(arr, sizeof arr);
    int_slice suf1 = sub(x, 1, x.len);
    print_int_slice(suf1);
    return 0;
}