#include "optimization.h"

int nb_terms_min(int* tab,int len, int obj)
{
  int res = 0;
  int top = 0;
  while (top+tab[len-1-res] <= obj && res < len)
    {
      top+=tab[len-1-res];
      res++; 
    }
  return res;
}

int nb_terms_max(int* tab, int len, int obj)
{
  int res = len;
  int bottom = 0;
  for (int i = 0; i < len ; i++)
    {
      bottom+=tab[i];
    }
  while(bottom-tab[res-1] > obj && res > 0)
    {
      bottom-=tab[res-1];
      res--;
    }
  return res;
}

int next_step(int *tab_idx, int len_idx, int rank)
{
  //printf("rank %d & len_idx %d\n",rank,len_idx);
 if(rank == len_idx)
    {
      //printf("Entree boucle erreur\n");
      //printf("tableau inchange\n");
      return -1;
    }

 else if (tab_idx[rank]-1 >= 0 && in_tab(tab_idx,len_idx,tab_idx[rank]-1) == -1)
    {
      tab_idx[rank]-=1;
      for (int i = 1; i<rank+1; i++)
	{
	  tab_idx[rank-i]=tab_idx[rank]-i;
	}
      return rank;
    }
  
  else
    {
      //printf("Entree boucle rang+1\n");
      int res = next_step(tab_idx,len_idx,rank+1);
      return res;
    }
}

int sum_tab_idx(int* tab,int* tab_idx, int len_idx)
{
  int sum = 0;
  for (int i = 0; i < len_idx ; i++)
    {
      sum+= tab[tab_idx[i]];
    }
  return sum;
}

int change_max(int* tab_idx, int len_idx, int rank)
{
  if (rank == len_idx-1)
    {
      //printf("Tableau inchange\n");
      return -1;
    }
  else if (tab_idx[rank+1] > tab_idx[rank]+1)
    {
      int res = next_step(tab_idx,len_idx,rank+1);
      return res;
    }
  else if(tab_idx[rank+1] == tab_idx[rank]+1)
    {
      int res = change_max(tab_idx,len_idx,rank+1);
      return res;
    }
  else
    {
      //printf("error");
      return -1;
    }
}

int change_min(int* tab_idx, int len_idx, int rank)
{
  if (rank == len_idx)
    {
      //printf("tableau inchange pour min\n");
      return -1;
    }
  else if (tab_idx[rank] == rank)
    {
      int res = change_min(tab_idx,len_idx,rank+1);
      return res;
    }
  else
    {
      tab_idx[rank] = rank;
      for (int i = 0 ; i < rank; i++)
	{
	  tab_idx[i]=i;
	}
      return rank;
    }
}

struct response* find_n(int* tab, int len, int* tab_idx,int len_idx,int obj)
{
   for (int j=0; j < len_idx; j++)
     {
       tab_idx[j]=len-1 - (len_idx-1) + j;
     }


   struct response* res = malloc(sizeof(struct response));
   res->record = 0;
   int* tab_res = malloc(sizeof(int)*len_idx);
   res->tab_record = tab_res;
   copy_tab(tab_idx,len_idx,res->tab_record);
   res->len_record = len_idx;
   

   int ok = 0;
   while(ok >= 0)
     {
       int tot = sum_tab_idx(tab,tab_idx,len_idx);
       //printf("tot: %d\n",tot);
       //printf_tab(tab_idx,len_idx);


       int copy_current[len_idx];
       copy_tab(tab_idx,len_idx,copy_current);
       change_min(copy_current,len_idx,0);

       
       if (tot < res->record)
	 {
	   ok = change_max(tab_idx, len_idx,0);
	   continue;
	 }
       else if (tot == obj)
	 {
	    res->record = tot;
	   copy_tab(tab_idx,len_idx,res->tab_record);
	   ok = -1;
	   continue;
	   }
       else if(sum_tab_idx(tab,copy_current,len_idx) > obj)
	 {
	   change_min(tab_idx,len_idx,0);
	   continue;
	   }
       else if (tot > res->record && tot <= obj)
	 {
	   res->record = tot;
	   copy_tab(tab_idx,len_idx,res->tab_record);

	   
	   ok = next_step(tab_idx,len_idx,0);
	   continue;
	 }
       else
	 {
	   ok = next_step(tab_idx,len_idx,0);
	   continue;
	 }
     }
   return res;
}

void free_response(struct response* res)
{
  free(res->tab_record);
  free(res);
}

struct response* optimize(int* tab, int len, int obj)
{
  sort(tab,0,len-1);
  //printf_tab(tab,len);
  
  int min = nb_terms_min(tab,len,obj);
  int max = nb_terms_max(tab,len,obj);
  //printf("min: %d\n max: %d\n",min,max);

  int c[1] = {0};
  struct response* res = malloc(sizeof(struct response));
  res->record = 0;
  res->tab_record = c;
  res->len_record = 1;
  
  for (int i = min; i < max+1 ; i++)
    {
      //printf("i = %d\n",i);

      
      int len_idx = i;
      int tab_idx[len_idx];
      for (int j=0; j < len_idx; j++)
     {
       tab_idx[j]=len-1 - (len_idx-1) + j;
     }

      
      struct response* tmp= find_n(tab, len, tab_idx, len_idx, obj);


      if (tmp->record == obj)
	{
	  free(res);
	  res = tmp;


	  //printf("record : %d\n",res->record);
	  //printf("\n");
	  //printf_tab(res->tab_record,res->len_record);
	  
	  
	  return res;
	}
      else if(tmp->record >= res->record)
	{
	  free(res);
	  res = tmp;
	}


      //printf("record : %d\n",res->record);
      //printf("\n");
      //printf_tab(res->tab_record,res->len_record);
    }
  return res;
}


