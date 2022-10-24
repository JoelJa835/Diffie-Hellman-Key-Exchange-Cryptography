#include<stdio.h>
#include<gmp.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[] )  {  
   int opt;
   char * filename;
   mpz_t p,g,a,b,A,B, A_s,B_s;
   mpz_init (p);
   mpz_init (g);
   mpz_init (a);
   mpz_init (b);
   mpz_init (A);
   mpz_init (B);
   mpz_init (A_s);
   mpz_init (B_s);
    // put ':' in the starting of the
    // string so that program can 
    //distinguish between '?' and ':' 
    while((opt = getopt(argc, argv,":o:p:g:a:b:h:")) != -1) 
    { 
        switch(opt) 
        { 
            case 'p': 
                printf("option: %s\n", optarg);
                mpz_set_str(p, optarg,10);
                break;
            case 'g': 
                printf("option: %s\n", optarg); 
                mpz_set_str(g, optarg,10);
                break;
            case 'a': 
                printf("option: %s\n", optarg); 
                 mpz_set_str(a, optarg,10);
                break;
            case 'b': 
                printf("option: %s\n", optarg); 
                mpz_set_str(b, optarg,10);
                break;
            case 'h': 
                printf("option: %s\n", optarg); 

                break; 
            case 'o': 
                printf("filename: %s\n", optarg);
                filename = (char *)malloc((strlen(optarg)+1)*sizeof(char));
                if (filename == NULL){
                  puts("Memory allocation error.");
                  return 1;
                }
                strcpy(filename,optarg);
                break; 
            case ':': 
                printf("option needs a value\n"); 
                break; 
            case '?': 
                printf("unknown option: %c\n", optopt);
                break; 
        } 
    } 
    // optind is for the extra arguments
    // which are not parsed
    for(; optind < argc; optind++){     
        printf("extra arguments: %s\n", argv[optind]); 
    }

 mpz_powm(A,g,a,p);
 mpz_powm(B,g,b,p);
 mpz_powm(A_s,B,a,p);
 mpz_powm(B_s,A,b,p);

 if(mpz_cmp(A_s,B_s) == 0){
   FILE *fp;
   fp = fopen(filename, "w");
    if(fp == NULL)
   {
      printf("Error!");   
      exit(1);             
   }
   gmp_fprintf(fp,"<%Zd>, <%Zd>, <%Zd>",A, B, A_s);
   fclose(fp);
   mpz_clear(p);
   mpz_clear(g);
   mpz_clear(a);
   mpz_clear(b);
   mpz_clear(A);
   mpz_clear(B);
   mpz_clear(A_s);
   mpz_clear(B_s);
   free(filename);
}
   else{
      printf("Error something wrong happened, message is not the same!");

   }
}
