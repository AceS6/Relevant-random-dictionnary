#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <stdbool.h>

#define scenarios 1024
#define useless_cases 28
#define wordLength 10

void write(FILE* f, char** password, int length){
  for(int i=0;i<length;i++){
    fprintf(f, "%s\n", password[i]);
  }
}

void writeScenario(FILE* f, char* password){
    fprintf(f, "%s", password);
}


void genDictionnary(FILE* f, char*(*dictionnary)[scenarios], int* index, char* number[wordLength], int n) {
    if(n > 0) {
        number[wordLength-n] = "?u";
        genDictionnary(f, dictionnary, index, number, n - 1);
        number[wordLength-n] = "?d";
        genDictionnary(f, dictionnary, index, number, n - 1);
    }
    else {
        char* prev = "";
        int nbOccurences=0;
        bool ok = true;
        int i = 0;

        while(i<wordLength && ok){
          //printf("%s", number[i]);
          if(number[i]==prev || prev==""){
            nbOccurences++;
          }
          else{

            nbOccurences=0;
          }
          if(nbOccurences>2){
            ok=false;
            //printf("false !\n");
          }
          prev = number[i];
          //printf("prev=%s\n", prev);
          i++;
        }
        if(ok){
          for(int i=0;i<wordLength;i++){
            //printf("%s", number[i]);
            writeScenario(f, number[i]);
          }
          writeScenario(f, "\n");
        }
        (*index)++;
    }
}

FILE* openFile(){
  FILE *f = fopen("pass.txt", "w");
  if (f == NULL)
  {
      printf("Error opening file!\n");
      return NULL;
  }
  return f;
}
void closeFile(FILE* f){
    fclose(f);
}

int main(){
  int nbNumber=5;
  int nbLetters=5;  // caps only

  char letters[26]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
  char numbers[10]={'0','1','2','3','4','5','6','7','8','9'};

  FILE* f = openFile();
  char* dictionnary[scenarios] = {""};
  int index = 0;
  char *number[wordLength] = {"?u"};
  printf("%s", dictionnary[0]);
  for(int i=0;i<scenarios;i++){dictionnary[i]="";}
  genDictionnary(f, &dictionnary, &index, number, wordLength);
  printf("dictionnary generated in file pass.txt\n");
}
