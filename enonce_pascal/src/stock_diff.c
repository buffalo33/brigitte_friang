#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

struct diff
{
  char* data;
  int size;
};

void free_diff(struct diff* to_free)
{
  free(to_free->data);
  free(to_free);
}

struct diff* compare(char* file1, char* file2,int size1,int size2)
{
  char* content;
  struct diff* res;
  int max = 0;
  char* origi;
  char* inter;
  if (size1 > size2)
    {
      content = malloc(size1);
      max = size1;
      origi = file2;
      inter = file1;
    }
  else
    {
      content = malloc(size2);
      max = size2;
      origi = file1;
      inter = file2;
    }
  res = malloc(sizeof(struct diff));
  res->data = content;
  res->size = 0;
  int pos = 0;
  for (int i = 0; i< max ; i++)
    {
      if (origi[pos] != inter[i])
	{
	  res->data[res->size]=inter[i];
	  res->size++;
	}
      else
	{
	  pos++;
	}
    }
  return res;  
}


int main(int argc, char** argv)
{

  
  struct stat* data_origi = malloc(sizeof(struct stat));
  stat("enonce_pascal/txt/original.txt",data_origi);
  int size_origi = (int)data_origi->st_size;
  int origi_f = open("enonce_pascal/txt/original.txt",O_RDONLY);
  char* origi_r = malloc(size_origi);
  read(origi_f,origi_r,size_origi);
  //printf("%s\n",origi_r);
  
  struct stat* data_inter = malloc(sizeof(struct stat));
  stat("enonce_pascal/txt/intercepte.txt",data_inter);
  int size_inter = (int)data_inter->st_size;
  int inter_f = open("enonce_pascal/txt/intercepte.txt",O_RDONLY);
  char* inter_r = malloc(size_inter);
  read(inter_f,inter_r,size_inter);
  //printf("%s\n",inter_r);
  
  struct diff* res = malloc(sizeof(struct diff));
  res=compare(origi_r,inter_r,size_origi,size_inter);
  //printf("%s\n",res->data);
  //printf("%s\n",res->data);

  int diff_f = open("diff_f.txt",O_CREAT | O_RDWR, S_IRWXU);
  write(diff_f,res->data,res->size);
  //system("cat diff_f.txt");
  //printf("%zu\n",size_inter);

  close(origi_f);
  close(inter_f);
  close(diff_f);
  free(data_origi);
  free(origi_r);
  free(data_inter);
  free(inter_r);
  free_diff(res);
  return 0;
}
