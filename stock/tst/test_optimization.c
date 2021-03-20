#include "../src/optimization.h"

int test_nb_terms_min()
{
  printf("*** TEST NB_TERMS_MIN ***\n");

  for (int i=0; i < 1000; i++)
    {
      int len = rand()%200;
      //printf("len = %d\n",len);
      int tab[len];
      for (int j=0; j < len; j++)
	{
	  tab[j]=rand()%100;
	}
      sort(tab,0,len-1);
      //printf_tab(tab,len);
      int obj = rand()%10000;
  
      
      int res = nb_terms_min(tab,len,obj);
      

      //printf_tab(tab,len);
      int sum = 0;
      //printf("  sum = %d  \n",sum);
      for (int j = 0; j<res ; j++)
	{
	  //printf("  terme %d  ",tab[len-1-j]);
	  sum+= tab[len-1-j];
	  //printf("  sum = %d  \n",sum);
	}
      //printf("\n\n");
      //printf("obj: %d\n res: %d\n sum: %d\n",obj,res,sum);
      

      if(sum > obj)
	{
	  printf("error: res trop grande\n\n");
	}
      else if(res < len && sum+tab[len-1-res]<=obj)
	{
	  printf("error: res trop petit\n\n");
	}
    }
  
  return 1;
}


int test_nb_terms_max()
{
  printf("*** TEST NB_TERMS_MAX ***\n");

  for (int i=0; i < 1000; i++)
    {
      int len = rand()%200;
      //printf("len = %d\n",len);
      int tab[len];
      for (int j=0; j < len; j++)
	{
	  tab[j]=rand()%100;
	}
      sort(tab,0,len-1);
      //printf_tab(tab,len);
      int obj = rand()%10000;
  
      
      int res = nb_terms_max(tab,len,obj);
      

      //printf_tab(tab,len);
      int sum = 0;
      //printf("  sum = %d  \n",sum);
      for (int j = 0; j<res ; j++)
	{
	  //printf("  terme %d  ",tab[len-1-j]);
	  sum+= tab[j];
	  //printf("  sum = %d  \n",sum);
	}
      //printf("\n\n");
      //printf("obj: %d\n res: %d\n sum: %d\n",obj,res,sum);
      //printf("sum inf : %d\n\n",sum-tab[res-1]);

      if(sum <= obj && res<len)
	{
	  printf("error: res trop petit\n\n");
	}
      else if(sum-tab[res-1] > obj)
	{
	  printf("error: res trop grand\n\n");
	}
    }
  
  return 1;
}


int test_in_tab()
{
  printf("*** TEST IN_TAB ***\n");

  for (int i=0; i < 30; i++)
    {
      int len = rand()%200;
      //printf("len = %d\n",len);
      int tab[len];
      for (int j=0; j < len; j++)
	{
	  tab[j]=rand()%100;
	}


      for (int j = 0; j < 100; j++)
	{
	  int val = rand()%500;
	  int res = in_tab(tab,len,val);
	  //printf("%d\n",res);
	  if (res != -1 && tab[res] != val)
	    {
	      printf("error : valeur non contenue\n");
	    }

	  int idx = rand()%len;
	  res = in_tab(tab,len,tab[idx]);
	  if (tab[res] != tab[idx] || res == -1)
	    {
	      printf("error : valeur non identifiee\n");
	    }
	}
    }
  return 1;
}


int test_next_step()
{
  printf("*** TEST NEXT_STEP ***\n");

  
   int len = 4 + rand()%200;
   printf("len = %d\n",len);
   /*int tab[len];
   for (int j=0; j < len; j++)
     {
       tab[j]=rand()%100;
       }*/


   int len_idx = 4; //<= len car len >= 4
   printf("len_idx = %d\n",len_idx);
   int tab_idx[len_idx];
   for (int j=0; j < len_idx; j++)
     {
       tab_idx[j]=len-1 - (len_idx-1) + j;
     }
   printf_tab(tab_idx,len_idx);
   

   int res = 1;
   while (res >= 0 )//&& tab_idx[2] < len)
     {
       int copy[len_idx];
	 for (int k = 0; k < len_idx ;k++)
	   {
	     copy[k] = tab_idx[k];
	   }

	 
       res = next_step(tab_idx,len_idx,0);
       //printf("rang %d ",res);
       //printf_tab(tab_idx,len_idx);
       for (int k = 0; k < len_idx ; k++)
	 {
	   if (k <= res)
	     {
	       if (tab_idx[k] != tab_idx[res] - res + k)
		 {
		   printf("error : mauvaise succession valeur <= res\n");
		 }
	     }
	   else
	     {
	       if(tab_idx[k] != copy[k])
		 {
		   printf("error : changement valeur > res\n");
		 }
	     }
	 }
     }
   return 1;
}


int test_change_max()
{
  printf("*** TEST CHANGE_MAX ***\n");

  int len = 4 + rand()%200;
  //printf("len = %d\n",len);
  int tab[len];
  for (int j=0; j < len; j++)
    {
      tab[j]=rand()%100;
    }
  sort(tab,0,len-1);
  
  for (int i = 0; i < 100; i++)
    {
      int len_idx = 4; //<= len car len >= 4
      //printf("len_idx = %d\n",len_idx);
      int tab_idx[len_idx];
      for (int j=0; j < len_idx; j++)
	{
	  tab_idx[j]=rand()%len;
	}
      sort(tab_idx,0,len_idx-1);
      //printf_tab(tab_idx,len_idx);
      
      
      int res = 1;
      while (res >= 0 )//&& tab_idx[2] < len)
	{
	  int copy[len_idx];
	  for (int k = 0; k < len_idx ;k++)
	    {
	      copy[k] = tab_idx[k];
	    }
	  
	  
	  res = change_max(tab_idx,len_idx,0);
	  //printf("rang %d ",res);
	  //printf_tab(tab_idx,len_idx);
	  
	  
	  if (tab_idx[res] != copy[res]-1 && res != -1)
	    {
	      printf("error : mauvais changement max");
	    }
	 }
      //printf("\n");
    }
  return 1;
}


int test_find_n()
{
  int obj = rand()%10000;
  printf("obj: %d\n",obj);

  
  int len = 6 + rand()%200;
  printf("len = %d\n",len);
  int tab[len];
  for (int j=0; j < len; j++)
    {
      tab[j]=rand()%1000;
    }
  sort(tab,0,len-1);


  int len_idx = 6; //<= len car len >= 4
   //printf("len_idx = %d\n",len_idx);
  int tab_idx[len_idx];


  struct response* res = find_n(tab,len,tab_idx,len_idx,obj);
  printf("res: %d\n",res->record);


  printf_tab(res->tab_record,res->len_record);


  int assos_val[len_idx];
  for (int k = 0; k<res->len_record ; k++)
    {
      assos_val[k] = tab[res->tab_record[k]];
    }
  printf_tab(assos_val,len_idx);
  
  return 1;
}


int test_optimize()
{
  int obj = 100000;
  printf("obj: %d\n",obj);

  
  int len = 2000;
  printf("len = %d\n",len);
  int tab[len];
  for (int j=0; j < len; j++)
    {
      tab[j]=rand()%10000;
    }

  struct response* res = optimize(tab,len,obj);
  printf("record : %d\n",res->record);
  printf_tab(res->tab_record,res->len_record);


  int tab_val[res->len_record];
  for (int i = 0; i < res->len_record; i++)
    {
      tab_val[i] = tab[res->tab_record[i]];
    }
  printf_tab(tab_val,res->len_record);

  return 1;
}

int main(int argc, char** argv)
{
  srand(30);
  //test_nb_terms_min();
  //test_nb_terms_max();
  //test_in_tab();
  //test_next_step();
  //test_change_max();
  //test_find_n();
  test_optimize();
  return 0;
}
