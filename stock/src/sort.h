#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SEED 45

struct assos {
  int len;
  int* init_tab;
  int* sorted_idx;
};

int myrand(int min, int max);

void swap(int* tab, int i, int j);

void printf_tab(int* tab, int len);

int pivot_choice(int first,int last);

int partition(int* tab, int first, int last, int pivot);

void sort(int* tab, int first, int last);

int in_tab(int* tab,int len,int val);

void copy_tab(int* src, int len, int* dst);

void free_assos(struct assos* to_free);

struct assos* init_assos(int* tab, int len);

void put_idx(int* sorted_tab, struct assos* to_fill);
