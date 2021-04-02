#define QUEUE_CREATE(TYPE)\
    typedef struct TYPE##_Queue {\
        TYPE *arr;\
        int front;\
        int rear;\
        int size;\
        int capacity;\
    } TYPE##_queue;\
    TYPE##_queue * TYPE##_qinit(int capacity);\
    TYPE##_queue * TYPE##_qreinit(TYPE##_queue *que);\
    void TYPE##_qfree(TYPE##_queue *que);\
    int TYPE##_qpush_back(TYPE##_queue *que, TYPE val);\
    TYPE TYPE##_qpop_front(TYPE##_queue *que);\
    TYPE TYPE##_qview_front(TYPE##_queue *que);\
    TYPE TYPE##_qview_back(TYPE##_queue *que);\
    TYPE TYPE##_qview_nth(TYPE##_queue *que, int n);\
    TYPE##_queue * TYPE##_qinit(int capacity) {\
        TYPE##_queue *que = (TYPE##_queue *) malloc(sizeof(TYPE##_queue));\
        que->size = 0;\
        que->capacity = capacity;\
        que->arr = (TYPE *) malloc(sizeof(TYPE) * capacity);\
        que->front = 0;\
        que->rear = 0;\
        return que;\
    }\
    TYPE##_queue * TYPE##_qreinit(TYPE##_queue *que) {\
        TYPE##_queue *new_que = TYPE##_qinit(que->capacity * 2);\
        while (que->size > 0) {\
            TYPE##_qpush_back(new_que, TYPE##_qpop_front(que));\
        }\
        TYPE##_qfree(que);\
        return new_que;\
    }\
    void TYPE##_qfree(TYPE##_queue *queue) {\
        free(queue->arr);\
        free(queue);\
    }\
    int TYPE##_qpush_back(TYPE##_queue *que, TYPE val) {\
        if (que->size < que->capacity) {\
            que->arr[(que->rear)++] = val;\
            if (que->rear >= que->capacity) {\
                que->rear = 0;\
            }\
            (que->size)++;\
            return 1;\
        } else {\
            return 0;\
        }\
    }\
    TYPE TYPE##_qpop_front(TYPE##_queue *que) {\
        if (que->size == 0) {\
            printf("Stack underflow\n");\
            return 0;\
        } else {\
            TYPE val = que->arr[que->front];\
            if (que->front == que->capacity - 1) {\
                que->front = 0;\
            } else {\
                (que->front)++;\
            }\
            (que->size)--;\
            return val;\
        }\
    }\
    TYPE TYPE##_qview_front(TYPE##_queue *que) {\
        return que->arr[que->front];\
    }\
    TYPE TYPE##_qview_back(TYPE##_queue *que) {\
        return que->arr[que->rear];\
    }\
    TYPE TYPE##_qview_nth(TYPE##_queue *que, int n) {\
        return que->arr[(que->front + n) % que->capacity];\
    }
