#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <vec_macro.h>

VEC_CREATE(char)

typedef struct string {
    char *str;
    int capacity;
    int size;
} String;

// String funcs
String *create_string(int capacity);
void str_push_back(String *str, char ch);
void str_pop_back(String *str);
void free_string(String *str);

// C String funcs
char *removeDuplicates(char *S);
void reverseString(char* s, int sSize);

void str_push_back(String *str, char ch) {
    if (str->size >= str->capacity) {
        str->capacity *= 3;
        str->str = realloc(str->str, sizeof(char) * (str->capacity + 1));
    }
    str->str[str->size++] = ch;
    str->str[str->size] = '\0';
}

void str_pop_back(String *str) {
    str->size--;
}

void free_string(String *str) {
    free(str->str);
    free(str);
}

// Random array funcs
int max_sub_array(int *nums, int numsSize);

String *create_string(int capacity) {
    String *new = malloc(sizeof(String));
    new->capacity = capacity;
    new->size = 0;
    new->str = calloc(capacity + 1, sizeof(char));
    new->str[0] = '\0';
    return new;
}


int max_sub_array(int* nums, int numsSize){
    if (numsSize == 0) return 0;
    int true_max = INT_MIN;
    int curr_sum = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] >= 0) {
            if (curr_sum < 0) curr_sum = nums[i];
            else curr_sum += nums[i];
        } else { 
            true_max = (curr_sum > true_max) ? curr_sum : true_max;
            curr_sum = (nums[i] > curr_sum) ? nums[i] : curr_sum + nums[i];
        }
    }
    return (curr_sum > true_max) ? curr_sum : true_max;
}

char * removeDuplicates(char * S){
    if (S==NULL||S[0]=='\0'||S[1]=='\0') return S;
    char_vec *s = char_vinit(30);
    for (int i = 0; S[i] != '\0'; i++) {
        if (s->size == 0 || (S[i] != char_peek(s))) char_push(s, S[i]);
        else char_pop(s);
    }
    char_push(s, '\0');

    for (int i = s->size - 1; i >= 0; i--) {
        S[i] = char_pop(s);
    }
    return S;

}

void reverseString(char* s, int sSize) {
    for (int i = 0; i < sSize/2; i++) {
        char tmp = s[i];
        int in = sSize - i - 1;
        s[i] = s[in];
        s[in] = tmp;
    }
}
