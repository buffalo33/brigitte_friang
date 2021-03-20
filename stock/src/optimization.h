#include "sort.h"

struct response{
  int record;
  int* tab_record;
  int len_record;
};

int nb_terms_min(int* tab,int len, int obj);

int nb_terms_max(int* tab,int len, int obj);

int next_step(int *tab_idx, int len_idx, int range);

int sum_tab_idx(int* tab,int* tab_idx, int len_idx);

int change_max(int* tab_idx, int len_idx, int rank);

int change_min(int* tab_idx, int len_idx, int rank);

struct response* find_n(int* tab, int len, int* tab_idx,int len_idx,int obj);

struct response* optimize(int* tab, int len, int obj);
