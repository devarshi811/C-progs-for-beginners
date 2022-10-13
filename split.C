#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Word
{
    int wordIndex;
    char* word;
    int wordLen;
    struct Word *previousWord;
    struct Word *nextWord;
};

struct Word *head;

void insertWord(char* c){
    struct Word *WordArray;
    WordArray = (struct Word*)malloc(sizeof(struct Word));  
    
    if(WordArray == NULL){  
        printf("\nOVERFLOW");  
    }  
    else  {  
    
    if(head==NULL)  {  
        WordArray->nextWord = NULL;  
        WordArray->previousWord=NULL;  
        WordArray->word=c;
        WordArray->wordLen=strlen(c);
        WordArray->wordIndex=0;
        head=WordArray;
    }  
    else   {  
        WordArray->word=c;  
        WordArray->previousWord=head;  
        WordArray->nextWord = NULL;
        WordArray->wordLen=strlen(c);
        WordArray->wordIndex=head->wordIndex + 1;
        head->nextWord=WordArray;  
        head=WordArray;  
    }  
    printf("\nNode inserted\n");  
    }  
}

char* getSubString(char* inputString, char* subString,
    int index, int subStringLength){
    int counter, inputStringLength = strlen(inputString);    
    /* Input validation 
     * range of sub-string must be in [0, strlen(inputString)]
     */
    if(index < 0 || index > inputStringLength || 
          (index + subStringLength) > inputStringLength){
        printf("Invalid Input");
        return NULL;
    }
    subString = (char*)malloc(sizeof(char) * (subStringLength + 1));
    for(counter = 0; counter < subStringLength; counter++){
        subString[counter] = inputString[index++];
    }
    subString[counter] = '\0';
    return subString;
}

void split(char str[]){
    int len = strlen(str);
    int t;
    
    char* buffer;
    int sWord = 0;
    int eWord = 0;
    bool isWordStarted = false;
    for(t = 0; t < len; t++){
        
        if(str[t] != ' '){
            if (!isWordStarted)
            {
                sWord = t;
                isWordStarted = true;
            }
        }
        else{
            if(isWordStarted){
                eWord = t;
                printf("\n%d %d %s", sWord, eWord, getSubString(str, buffer, sWord, eWord - sWord));
                insertWord(getSubString(str, buffer, sWord, eWord - sWord));
                isWordStarted = false;
            }
        }
    }
    if(isWordStarted)
        insertWord(getSubString(str, buffer, sWord, len - sWord));
}

void printWords(){
    struct Word *temp; 
    struct Word *temp1;  
    printf("\n printing values...\n");  
    temp = head;
    temp1 = head;
    while(temp != NULL)  
    {  
        temp1=temp->previousWord;
        if(temp1 == NULL)
            break;
        temp = temp1;  
    } 
    
    while(temp != NULL)  
    {  
        printf("%s\t",temp->word);
        temp=temp->nextWord;  
    }  
}

int main(){
    char s[] = "this is my sentense";
    split(s);
    printWords();
    return 0;
}
