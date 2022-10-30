#include<stdio.h>
#include<gmp.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

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
    while((opt = getopt(argc, argv,":o:p:g:a:b:h")) != -1) 
    { 
        switch(opt) 
        { 
            case 'p': 
                mpz_set_str(p, optarg,10);
                break;
            case 'g': 
                mpz_set_str(g, optarg,10);
                break;
            case 'a':  
                 mpz_set_str(a, optarg,10);
                break;
            case 'b': 
                mpz_set_str(b, optarg,10);
                break;
            case 'o': 
                filename = (char *)malloc((strlen(optarg)+1)*sizeof(char));
                if (filename == NULL){
                  puts("Memory allocation error.");
                  return 1;
                }
                strcpy(filename,optarg);
                break; 
            case 'h': 
                printf("The argument -p will include the will be the public prime number.\nThe argument -g will be the public primitive root of the previous prime number.\nThe argument -a will be the private key of user A.\nThe argument -b will be the private key of user B.\nThe command line tool will return the public key of user A, the public key of user B, andthe shared secret. The output file must be in the following format:<public key A>, <public key B>, <shared secret>");
                return 1;
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


//Calculating the values for alice and bob  that will be exchanged and then the shared message.
 mpz_powm(A,g,a,p);
 mpz_powm(B,g,b,p);
 mpz_powm(A_s,B,a,p);
 mpz_powm(B_s,A,b,p);


//Checking if both the messages alice and bob received are the same.
 if(mpz_cmp(A_s,B_s) == 0){
   FILE *fp;
   fp = fopen(filename, "w");
    if(fp == NULL)
   {
      printf("Error!");   
      exit(1);             
   }
   //Write values to output file.
   gmp_fprintf(fp,"<%Zd>, <%Zd>, <%Zd>",A, B, A_s);
   fclose(fp);
   
   //Free the space occupied.
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
