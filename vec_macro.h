#define VEC_CREATE(TYPE) \
    typedef struct TYPE##_Vec {\
        TYPE * arr;\
        int size;\
        int capacity;\
    } TYPE##_vec;\
    TYPE##_vec * TYPE##_vinit(int start_cap) {\
        TYPE##_vec *vec = (TYPE##_vec *) malloc(sizeof(TYPE##_vec)); \
        vec->arr = (TYPE *) malloc(start_cap * sizeof(TYPE));\
        vec->capacity = start_cap;\
        vec->size = 0;\
        return vec;\
    }\
    void TYPE##_push(TYPE##_vec *vec, TYPE val) {\
        if (vec->size < vec->capacity) {\
            (vec->arr)[vec->size] = val;\
            vec->size++;\
        } else {\
            (vec->arr) = (TYPE *) realloc(vec->arr, vec->capacity * 2 * sizeof(TYPE));\
            vec->capacity *= 2;\
            (vec->arr)[vec->size] = val;\
            vec->size++;\
        }\
    }\
    TYPE TYPE##_pop(TYPE##_vec *vec) {\
        if (vec->size > 0) {\
            TYPE ret = vec->arr[vec->size - 1];\
            vec->size--;\
            return ret;\
        } else {\
            return vec->arr[0];\
        }\
    }\
    void TYPE##_vfree(TYPE##_vec *vec) {\
        free(vec->arr);\
        free(vec);\
    }

#define PVEC_CREATE(TYPE) \
    typedef struct TYPE##_PVec {\
        TYPE ** arr;\
        int size;\
        int capacity;\
    } TYPE##_pvec;\
    TYPE##_pvec * TYPE##_pvinit(int start_cap) {\
        TYPE##_pvec *vec = (TYPE##_pvec *) malloc(sizeof(TYPE##_pvec)); \
        vec->arr = (TYPE **) malloc(start_cap * sizeof(TYPE *));\
        vec->capacity = start_cap;\
        vec->size = 0;\
        return vec;\
    }\
    void TYPE##_ppush(TYPE##_pvec *vec, TYPE *val) {\
        if (vec->size < vec->capacity) {\
            (vec->arr)[vec->size] = val;\
            vec->size++;\
        } else {\
            (vec->arr) = (TYPE **) realloc(vec->arr, vec->capacity * 2 * sizeof(TYPE *));\
            vec->capacity *= 2;\
            (vec->arr)[vec->size] = val;\
            vec->size++;\
        }\
    }\
    TYPE * TYPE##_ppop(TYPE##_pvec *vec) {\
        if (vec->size > 0) {\
            TYPE * ret = vec->arr[vec->size - 1];\
            vec->size--;\
            return ret;\
        } else {\
            return vec->arr[0];\
        }\
    }\
    void TYPE##_pvfree(TYPE##_pvec *vec) {\
        for (int i = 0; i < vec->size; i++) {\
            free(vec->arr[i]);\
        }\
        free(vec->arr);\
        free(vec);\
    }
