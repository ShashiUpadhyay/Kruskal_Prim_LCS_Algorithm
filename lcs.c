#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 128
#define ROW 10

char* printCorrectOrder(char* str, char ch);

// Code to print the string
char* printCorrectOrder(char* str, char ch)
{
    int len = strlen(str);
    char* final_str = malloc((len + 1));
    int i;
    
    final_str[0] = ch;
    for(i = 1; i <= len; ++i)
    {
        final_str[i] = str[i - 1];
    }
    return final_str;
}

int main(int argc, char* argv[])
{
	if(argc!=2)
	{
		printf("Please enter just 1 arguments.\n");
		exit(0);
    }else{
        FILE *file = NULL;
        int i, j, max_word;
        char filedata[ROW][BUFFER_SIZE];
        // Assume argv[1] is a filename to open
        file = fopen(argv[1],"r");
        /* fopen returns 0, the NULL pointer, on failure */
        if (file == NULL){
            printf("Couldn't open %s for reading\n",argv[1]);
            return 0;
        }else{
            i=0;
            while(fgets(filedata[i],BUFFER_SIZE,file)){
                filedata[i][strlen(filedata[i])-1] = '\0';
                i++;
            }
            fclose(file);
        }
        
        char* firststring = filedata[0];
        char* secondstring = filedata[1];
        printf("\nImplementation of Longest Common Subsequence algorithm\n");
        printf("First Input string         : %s\n", firststring);
        printf("Second Input string        : %s\n", secondstring);

        int str1 = strlen(firststring);
        int str2 = strlen(secondstring);

        int word_matrix[str1+1][str2+1];
        char* long_str = malloc(sizeof(1));
        long_str[0] = '\0';

        for(i=0;i<=str1;++i){
                for(j=0;j<=str2;++j){
                        word_matrix[i][j] = 0;
                }
        }

//Generating the longest common subsequence from the input strings read from the file.
        for(i=1;i<=str1;++i){
            for(j=1;j<=str2;++j){
                  if(word_matrix[i-1][j]<=word_matrix[i][j-1]){
                    max_word = word_matrix[i][j-1];
			      }else{
				    max_word = word_matrix[i-1][j];
                  }

                if(firststring[i-1] != secondstring[j-1]){
                    word_matrix[i][j] = max_word;
                }else{
                    word_matrix[i][j] = max_word+1;
                }
            }
        }
    
// Backtracking the matrix to check the appearance of characters in same sequence in both inputs
	for(i=str1,j=str2; (i>0 && j>0);)							{
		if(firststring[i-1] == secondstring[j-1]){
			long_str = printCorrectOrder(long_str,firststring[i-1]);
			i--;
			j--;
		}else if(word_matrix[i-1][j] > word_matrix[i][j-1]){
			i--;
		}else{
			j--;
		}
	}
        printf("Longest Common Subsequence : %s %lu \n", long_str, strlen(long_str));
  }
        return 0;
}
