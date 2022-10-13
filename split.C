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
    printf("\nWord: <%s> Node inserted\n", WordArray->word);  
    }  
}

char* getSubString1(char str[], int s, int e){
    int d = e - s;
    char* newOne = (char*)malloc(d * sizeof(char));

    int t = 0;
    for(t = 0; t <= d; t++){
        newOne[t] = str[s + t];
    }
    newOne[t] = '\0';
    
    return newOne;
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
                insertWord(getSubString1(str, sWord, eWord - 1));
                isWordStarted = false;
            }
        }
    }
    if(isWordStarted)
        insertWord(getSubString1(str, sWord, len));
}

void printWords(){
    struct Word *temp; 
    struct Word *temp1;  
    printf("\nprinting values...\n");  
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
        printf("~%s~\t",temp->word);
        temp=temp->nextWord;  
    }  
}

int main(){
    char s[] = "this is my sentense";
    split(s);
    printWords();
    return 0;
}
