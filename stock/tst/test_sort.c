#include "../src/sort.h"


int test_myrand()
{
  printf("*** TEST MYRAND ***\n");
  int min, max;
  min = 20;
  max = 157;
  for (int i = 0; i < 10000 ; i++)
    {
      int tmp = myrand(min,max);
      //printf("%d\n",tmp);
      if (tmp < min || tmp > max)
	{
	  printf("erreur : borne depassee :\n inf : %d\n sup : %d\n",tmp<min,tmp>max);
	}
      else if (tmp == min || tmp==max)
	{
	  //printf("borne atteinte :\n inf :%d\n sup : %d\n",tmp==min,tmp==max);
	}
    }
  return 1;
}

int test_swap()
{
  printf("*** TEST SWAP ***\n");
  int len_ran = rand()%1000;
  printf("len_ran = %d\n",len_ran);
  int tab_ran[len_ran];
  for (int i=0; i < len_ran; i++)
    {
      tab_ran[i]=rand();
    }
  int eq = rand()%1000;
  int arg_eq = tab_ran[eq];
  swap(tab_ran,eq,eq);
  if (tab_ran[eq] != arg_eq)
    {
      printf("error: faux pour un echange de meme indice\n");
    }
    for (int i=0; i < 1000; i++)
      {
	int ind1 = rand()%len_ran;
	int ind2 = rand()%len_ran;
	int arg1 = tab_ran[ind1];
	int arg2 = tab_ran[ind2];
	swap(tab_ran,ind1,ind2);
	if (arg1 != tab_ran[ind2] || arg2 != tab_ran[ind1])
	  {
	    printf("error : mauvais swap\n arg1 faux : %d\n arg2 faux : %d\n",arg1 != tab_ran[ind2],arg2 != tab_ran[ind1]);
	  }
	
      }
    return 1;
}


int test_printf_tab()
{
  printf("*** TEST PRINTF_TAB ***\n");
  int* ex1 = malloc(sizeof(int));
  *ex1 = 667;
  int ex2= 797;
  int tab[10] = {34,24325,14,45,132,35,32,*ex1,230,ex2};
  printf_tab(tab,10);
  free(ex1);
  return 0;
}

int test_pivot_choice()
{
  printf("*** TEST PIVOT_CHOICE ***\n");
  int first,last;
  first = 32;
  last = 7987;
  for (int i = 0; i<10000; i++)
    {
      int tmp = pivot_choice(first,last);
      //printf("%d\n",tmp);
      if (tmp < first || tmp>last)
	{
	  printf("erreur : borne depassee :\n inf : %d\n sup : %d\n",tmp<first,tmp>last);
	}
    }
  return 1;
}

int test_partition()
{
  printf("*** TEST PARTITION ***\n");
  int len = rand()%200;
  //printf("len = %d\n\n",len);
  int tab[len];
  for (int i=0; i < len; i++)
    {
      tab[i]=rand()%1000;
    }


  for (int i= 0; i < 50; i++)
    {
      //printf("***TEST %d***\n\n",i);
      int copy[len];
      for (int j=0; j < len; j++)
	{
	  copy[j]=tab[j];
	}


      int first,last,pivot;
      first = myrand(0,len-1);
      last = myrand(first,len);
      pivot = myrand(first,last);
      int val_pivot = copy[pivot];
      //printf("first = %d\n last = %d\n",first,last);
      //printf("pivot = %d\n val_pivot = %d\n\n",pivot,val_pivot);


      //printf_tab(copy+first,last-first+1);
      int res = partition(copy,first,last,pivot);
      //printf_tab(copy+first,last-first+1);
      //printf("pivot = %d\n\n",res);
      //printf("\n");


      if (val_pivot != copy[res])
	   {
	     printf("error: valeur pivot changee\n");
	   }
      for (int pos = first; pos < last+1 ; pos++)
	{
	  if (pos <= res && copy[pos] > copy[res])
	    {
	      printf("error : plus grand que pivot avant pivot\n");	      
	    }
	 else if (pos > res && copy[pos] <= copy[res])
	    {
	      printf("error : plus petit que pivot apres pivot\n");	      
	    }
	}
      //printf("\n");
      
    }
  return 1;
}


int test_sort()
{
printf("*** TEST SORT ***\n");

 for (int i = 0; i < 1000; i++)
   {
     int len = rand()%500;
     //printf("len = %d\n\n",len);
     int tab[len];
     for (int j=0; j < len; j++)
       {
	 tab[j]=rand()%1000000;
       }
     
     
     sort(tab,0,len-1);
     
     
     for(int j = 0; j < len-1; j++)
       {
	 if (tab[j] > tab[j+1])
	   {
	     printf("error: mauvais ordre rang %d pour test %d\n",j,i);
	     printf("rang %d: %d\n rang %d: %d\n",i,tab[i],i+1,tab[i+1]);
	   }
       }

     //printf("\n");
   } 
 return 1;
}


int test_init_assos()
{
  printf("*** TEST INIT_ASSOS ***\n");

for (int i = 0; i < 100; i++)
   {
     int len = rand()%500;
     //printf("len = %d\n\n",len);
     int tab[len];
     for (int j=0; j < len; j++)
       {
	 tab[j]=rand()%100000;
       }

       struct assos* test = init_assos(tab,len);

     if (test->sorted_idx != NULL)
       {
	 printf("error: mauvaise adresse pour sorted_idx\n");
       }
     if (test->len != len)
       {
	 printf("error: mauvaise longueur\n");
       }
     for (int j = 0; j < test->len; j++)
       {
	 if (test->init_tab[j] != tab[j])
	   {
	     printf("error : mauvaise valeur tableau\n");
	     printf("Pour i = %d et j = %d\n init_tab: %d\n tab: %d\n",i,j,test->init_tab[i],tab[i]);
	   }
       }

     free_assos(test);
   }

 
  return 1;
}

int test_put_idx()
{
  printf("*** TEST PUT_IDX ***\n");


  for (int i = 0; i < 1; i++)
   {
     int len = rand()%100;
     //printf("len = %d\n\n",len);
     int tab[len];
     for (int j=0; j < len; j++)
       {
	 tab[j]=rand()%100;
       }

     printf_tab(tab,len);
     printf("\n");

     struct assos* to_fill = init_assos(tab,len);
     
     sort(tab,0,len-1);
     printf_tab(tab,len);
     printf("\n");
     
     put_idx(tab,to_fill);
     printf_tab(to_fill->sorted_idx,len);

     for (int j = 0; j < to_fill->len ; j++)
       {
	 if (to_fill->init_tab[j] != tab[to_fill->sorted_idx[j]] )
	 {
	   printf("error : mauvais indice");
	 }
       }
   }

  return 1;
  
}



int main(int argc, char** argv)
{
  srand(45);
  //  test_myrand();
  //  test_swap();
  //  test_printf_tab();
  //  test_pivot_choice();
  //  test_partition();
  //  test_sort();
  //test_init_assos();
  test_put_idx();
  return 0;
}
