#define QUEUE_CREATE(TYPE) \
        typedef struct TYPE##_q {\
            TYPE *arr;\
            int start;\
            int end;\
            int size;\
            int capacity;\
        } TYPE##_queue;\
        TYPE##_queue *TYPE##_qinit(int capacity) {\
            TYPE##_queue *res = malloc(sizeof(TYPE##_queue));\
            res->arr = malloc(sizeof(TYPE)*capacity);\
            res->start = 0;\
            res->end = 0;\
            res->size = 0;\
            res->capacity = capacity;\
            return res;\
        }\
        void TYPE##_qfree(TYPE##_queue *q) {\
            free(q->arr);\
            free(q);\
        }\
        TYPE TYPE##_qpop(TYPE##_queue *q) {\
            if (q->size == 0) return q->arr[0];\
            TYPE res = q->arr[q->start++];\
            q->start %= q->capacity;\
            q->size--;\
            return res;\
        }\
        TYPE##_queue *TYPE##_qpush(TYPE##_queue *q, TYPE val) {\
            if (q->size < q->capacity) {\
                q->arr[q->end++] = val;\
                q->end %= q->capacity;\
                q->size++;\
            } else {\
                TYPE##_queue *new = TYPE##_qinit(q->capacity * 5);\
                while (q->size > 0) {\
                    TYPE##_qpush(new, TYPE##_qpop(q));\
                }\
                TYPE##_qfree(q);\
                q = new;\
                q->arr[q->end++] = val;\
                q->end %= q->capacity;\
                q->size++;\
            }\
            return q;\
    }
