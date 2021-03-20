#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
 


struct assos{
  char codee[52];
  char decodee[52];
  int niv;
};

int add(char new, char mean, struct assos* info)
{
  for(int i= 0; i < info->niv ; i++) //eviter redondances
    {
      if (new == info->codee[i])
	return 0;
    }
  info->codee[info->niv]=new;
  info->codee[info->niv+1]=new-32;
  info->decodee[info->niv]=mean;
  info->decodee[info->niv+1]=mean-32;
  info->niv=info->niv+2;
  info->codee[info->niv]=0;
  info->decodee[info->niv]=0;
  //printf("codee = %s\n decodee = %s\n",info->codee,info->decodee);
  return 0;
}

char decrypt_letter(char letter,struct assos* info)
{
  for (int i= 0; i< info->niv ; i++)
    {
      if (letter == info->codee[i])
	{
	  //printf("%c devient %c\n",letter,info->decodee[i]);
	  return info->decodee[i];
	}
    }
  return letter;
}

int decrypt_text(char* message, char* text, int len,struct assos* info)
{
  for (int i = 0; i<len; i++)
    {
      message[i] = decrypt_letter(text[i],info);
    }
  return 0;
}

int main(int argc, char** argv)
{
  struct assos* info = malloc(sizeof(struct assos));
  add('l','e',info);
  add('s','l',info);
  add('z','s',info);
  add('a','t',info);
  add('u','n',info);
  add('h','a',info);
  add('w','p',info);
  add('y','r',info);
  add('p','i',info);
  add('i','b',info);
  add('n','g',info);
  add('m','f',info);
  add('b','u',info);
  add('c','v',info);
  add('v','o',info);
  add('g','z',info);
  add('t','m',info);
  add('j','c',info);
  add('k','d',info);
  add('x','q',info);
  add('q','j',info);
  add('o','h',info);
  add('f','y',info);
  add('e','x',info);
  
  //printf("%c\n",100-32);
struct stat* data = malloc(sizeof(struct stat));
 stat("enonce/txt/code",data);
 //printf("Taille : %zu \n",data->st_size);
 off_t size = data->st_size;

 char message[size];
 
 int code_f = open("enonce/txt/code",O_RDONLY);
 char code_txt[size];
 read(code_f,code_txt,size);

 decrypt_text(message,code_txt,size,info);
 printf("%s\n",message);
 
 int decode_f = open("enonce/txt/decode",O_CREAT | O_WRONLY,S_IRWXU);
 write(decode_f,message,size);

 free(data);
 close(code_f);
 close(decode_f);
 return 0;
}
