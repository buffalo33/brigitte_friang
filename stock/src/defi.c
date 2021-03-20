#include "optimization.h"
#include "defi.h"


int fichier(char letter)
{
  struct problem pb = problems[letter - 'a'];
  
  int obj = pb.obj;
  int len = pb.len;
  int* tab = pb.tab;

  struct response* res = optimize(tab,len,obj);
  
  printf("record : %d\n taille: %d\n",res->record,res->len_record);
  
  printf_tab(res->tab_record,res->len_record);
  printf("\n");
  int tab_val[res->len_record];
  for (int i = 0; i < res->len_record; i++)
    {
      tab_val[i] = tab[res->tab_record[i]];
    }
  printf_tab(tab_val,res->len_record);
  return 1;
}


int awnser(char letter)
{
  struct problem pb = problems[letter - 'a'];

  int obj = pb.obj;
  int len = pb.len;
  int* tab = pb.tab;
  
  //printf_tab(tab,len);
  
  
  struct assos* association = init_assos(tab,len);

  sort(tab,0,len-1);

  /*printf("\n");
  printf_tab(tab,len);
  printf("\n");*/
    
  put_idx(tab,association);

  struct response* res = optimize(tab,len,obj);

  printf("record : %d\n taille: %d\n",res->record,res->len_record);
  printf("\n");

  int tab_real_idx[res->len_record];
  for (int i = 0; i < res->len_record ; i++)
    {
      tab_real_idx[i] = in_tab(association->sorted_idx,association->len,res->tab_record[i]);
      printf(" %d ",tab[res->tab_record[i]]);
    }
  printf("\n\n");  
  printf_tab(tab_real_idx,res->len_record);

  return 1;
 
}

int main(int argc, char** argv)
{

  //  fichier(argv[1][0]);
  awnser(argv[1][0]);
  return 0;
}
  
