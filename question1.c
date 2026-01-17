#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_ARR_SIZE 50

int min_distance(char* arr[], int n);
int sentence_distance(char arr[], int length);
int word_distance(char word1[], char word2[]);
char** get_all_sub_strings(char* str, int n);
int str_len(char arr[]);
bool compare_string(char arr1[], char arr2[]);
int count_words(char arr[]);
void reset_int_arr(int arr[], int n);
int* count_each_word_length(char arr[], int length);
char** str_split(char arr[]);
int find_word_end(char arr[], int start, int* update_arr_p);

//initialization functions:
void* allocate(int n) {
    char* str = (char*) malloc(n);
    if(str == NULL) {
        exit(1);
    }
    return str;
}

char* get_string() {
    char* str, *str_i;
    str_i = str = (char*) allocate(MAX_ARR_SIZE);
    while(1) {
        int f = scanf("%c", str_i);
        if(f == 0) {
            exit(1);
        }
        if(f == EOF || *(str_i) == '\n') {
            *str_i = '\0';
            return str;
        }
        str_i++;
    }
}

char** get_all_string(int n) {

    char** arr = (char**) allocate(n* sizeof(char*));
    for(int i = 0; i < n; i++) {
        arr[i] = get_string();
    }
    return arr;
}
void free_all_strings(char** arr, int n) {
    for(int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
}

int main() {
    int n;
    int r = scanf("%d ", &n);
    if(r == 0) {
        exit(1);
    }
    char** arr = get_all_string(n);
    printf("%s\n", arr[min_distance(arr,n)]);
    free_all_strings(arr,n);

    return 0;
}

// auxiliary functions for get_all_sub_strings:
int count_num_of_one(int n) {
    int count = 0;
    while (n > 0) {
        count += n % 2;
        n = n / 2;
    }
    return count;
}

char* get_sub_string(char* str, int num_of_ones, int mask) {
    char* sub_str, * sub_str_i;
    sub_str_i = sub_str = (char*) allocate(num_of_ones + 1);
    while(*str) {
        if(mask % 2) {
            *sub_str_i = *str;
            sub_str_i++;
        }
        mask = mask / 2;
        str++;
    }
    *sub_str_i = 0;
    return sub_str;
}

int pow_of_2(int n) {
    int p = 1;
    while(n-- > 0) {
        p *= 2;
    }
    return p;
}

char** get_all_sub_strings(char* str, int n) {
    int amount_of_sub_strings = pow_of_2(n);
    char** arr = (char**) allocate(amount_of_sub_strings *sizeof(char*));
    for(int i = 0; i < amount_of_sub_strings; i++) {
        arr[i] = get_sub_string(str, count_num_of_one(i),i);
    }
    return arr;
}

// auxiliary function for is_sub_string, compare two strings
bool compare_string(char arr1[], char arr2[]) {
    int word1_length = str_len(arr1);
    int word2_length = str_len(arr2);
    if (word1_length != word2_length) {
        return false;
    }
    for (int i = 0; i < word1_length; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

// auxiliary function for is_sub_string, return words length
int str_len(char arr[]) {
    int length = 0;
    while (*arr) {
        length++;
        arr++;
    }
    return length;
}

/* find the biggest common substrings of 2 given strings
 * return the length of the first minus the most common sub_string
 * and the length of the second minus the most common one */
int word_distance(char word1[], char word2[]) {

    int distance = 0, word1_length = str_len(word1), max = 0;
    int word2_length = str_len(word2);
    char** sub_strings1 = get_all_sub_strings(word1, word1_length);
    int sub_strings1_length = pow_of_2(word1_length);
    char** sub_strings2 = get_all_sub_strings(word2, word2_length);
    int sub_strings2_length = pow_of_2(word2_length);

    //iter all the substrings to find the biggest common one
    for (int i = 0; i < sub_strings1_length; i++) {
        for (int j = 0; j < sub_strings2_length; j++) {
            if (compare_string(sub_strings1[i], sub_strings2[j])) {
                int sub_s_length = str_len(sub_strings1[i]);
                if (sub_s_length > max) {
                    max = sub_s_length;
                }
            }
        }
    }
    //calculate the distance as described
    distance = word1_length - max + word2_length - max;

    //free the mallocs
    free_all_strings(sub_strings1, sub_strings1_length);
    free_all_strings(sub_strings2, sub_strings2_length);

    return distance;
}

int count_words(char arr[]) {
    int count = 0;
    bool flag = false;
    while (*arr) {
        while (*arr == ' ' && *arr) {
            arr++;
        }
        while (*arr != ' ' && *arr) {
            flag = true;
            arr++;
        }
        if (flag) {
            count++;
        }
        flag = false;
    }
    return count;
}

void reset_int_arr(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = 0;
    }
}

int* count_each_word_length(char arr[], int length) {
    int* count_words_length = (int *)malloc(sizeof(int) * length);
    reset_int_arr(count_words_length, length);
    int count = 0, i = 0;
    while (*arr) {
        while (*arr == ' ' && *arr) {
            arr++;
        }
        if (!*arr) break;

        while (*arr != ' ' && *arr) {
            count++;
            arr++;
        }
        count_words_length[i] = count;
        i++;
        count = 0;
    }
    return count_words_length;
}

char** str_split(char arr[]) {
    int words_in_arr = count_words(arr), i = 0;
    char** splitted_arr = (char **) malloc(words_in_arr * sizeof(char*));
    int* count_words_length = count_each_word_length(arr, words_in_arr);
    while (*arr) {
        while (*arr == ' ' && *arr) {
            arr++;
        }

        if (!*arr) break;

        splitted_arr[i] = (char *) malloc(count_words_length[i]
            * sizeof(char) + 1);
        int j = 0;
        while (*arr != ' ' && *arr) {
            splitted_arr[i][j] = *arr; arr++; j++;
        }
        splitted_arr[i][j] = '\0'; i++;
    }
    free(count_words_length);
    return splitted_arr;
}

int find_word_end(char arr[], int start, int* update_arr_p) {
    int end = start;
    while (*arr != ' ' && *arr != '\0') {
        end++;
        arr++;
        update_arr_p++;
    }
    return end;
}

//auxiliary function for min_distance, calculate a sentence distance
int sentence_distance(char arr[], int length) {
    int max_distance = 0;
    int new_arr_length = count_words(arr);
    if (new_arr_length <= 1) {
        return 0; //only one word in the sentence thus the distance is 1
    }
    char** arr_split = str_split(arr);
    for (int i = 0; i < new_arr_length; i++) {
        for (int j = i + 1; j < new_arr_length; j++) {
            int w_d = word_distance(arr_split[i], arr_split[j]);
            if (w_d > max_distance) {
                max_distance = w_d;
            }
        }
    }

    free_all_strings(arr_split, new_arr_length);
    return max_distance;
}

int min_distance(char* arr[], int n) {
    int min_distance = sentence_distance(arr[0], str_len(arr[0]));
    int min_distance_index = 0;
    for (int i = 1; i < n; i++) {
        int s_d = sentence_distance(arr[i], str_len(arr[i]));
        if (s_d < min_distance) {
            min_distance = s_d;
            min_distance_index = i;
        }
    }
    return min_distance_index;
}
