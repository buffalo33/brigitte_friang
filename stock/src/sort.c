#include "sort.h"

int myrand(int min, int max)
{
  int res = min + rand()%(max - min + 1);
  return res;
}

void swap(int* tab, int i, int j)
{
  int tmp = tab[i];
  tab[i] = tab[j];
  tab[j] = tmp;
}


void printf_tab(int* tab, int len)
{
  printf("{");
  for (int i = 0; i < len-1 ; i++)
    {
      printf(" %d,",tab[i]);
    }
  printf(" %d}\n",tab[len-1]);
}

int pivot_choice(int first,int last)
{
  int res = myrand(first,last);
  return res;
}



int partition(int* tab, int first, int last, int pivot)
{
  //printf_tab(tab+first,last-first+1);
  swap(tab,pivot,last);
  //printf_tab(tab+first,last-first+1);
  int curs_piv = first;
  for (int pos_tab = first ; pos_tab < last ; pos_tab++)
    {
      if (tab[pos_tab] <= tab[last])
	{
	  swap(tab,curs_piv,pos_tab);
	  curs_piv++;
	}
      //printf_tab(tab+first,last-first+1);
    }
  swap(tab,curs_piv,last);
  //printf("curs_piv = %d\n",curs_piv);
  return curs_piv;
}


void sort(int* tab, int first, int last)
{
  if (first < last)
    {
      int pivot;
      pivot = pivot_choice(first,last);
      pivot = partition(tab,first,last,pivot);
      sort(tab,first,pivot-1);
      sort(tab,pivot+1,last);
    }
}

int in_tab(int* tab,int len,int val)
{
  for (int i = 0; i <len; i++)
    {
      if (tab[i] == val)
	{
	  return i;
	}
    }
  return -1;
}


void copy_tab(int* src, int len, int* dst)
{
  for (int i=0 ; i < len ; i++)
    {
      dst[i] = src[i];
    }
}

void free_assos(struct assos* to_free)
{
  free(to_free->init_tab);
  free(to_free->sorted_idx);
  free(to_free);
}

struct assos* init_assos(int* tab, int len)
{
  int* copy = malloc(sizeof(int)*len);
  copy_tab(tab,len,copy);
  struct assos* init = malloc(sizeof(struct assos));


  init->len = len;
  init->init_tab=copy;
  init->sorted_idx = NULL;
  
  return init;
}


void put_idx(int* sorted_tab, struct assos* to_fill)
{
  int* tab_idx = malloc(sizeof(int)*to_fill->len);
  for (int i = 0; i < to_fill->len; i++)
    {
      tab_idx[i] = -1;
    }
  to_fill->sorted_idx = tab_idx;
  
  for (int i = 0; i < to_fill->len ; i++)
    {
      //to_fill->sorted_idx[i] = in_tab(sorted_tab,to_fill->len,to_fill->init_tab[i]);
      int pos = 0;
      int ok = 0;
      //printf("%d\n",sorted_tab[i]);
      while (ok == 0)
	{
	  pos += in_tab(to_fill->init_tab + pos,to_fill->len - pos,sorted_tab[i]);
	  //printf(" %d \n",pos);
	  if (to_fill->sorted_idx[pos] == -1)
	    {
	      to_fill->sorted_idx[pos] = i;
	      ok = 1;
	    }
	  else
	    {
	      pos++;
	    }
	  //printf("zebi\n");
	}
    }
  printf("\n");
}
