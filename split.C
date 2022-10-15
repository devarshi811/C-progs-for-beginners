#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct Word
{
    int wordIndex;
    char* word;
    int wordLen;
    struct Word *previousWord;
    struct Word *nextWord;
};

struct Word *head;

struct List
{
    struct Word *head;
    struct Word *poll;
};

void insertWord(List* list,char* c){
    struct Word *WordArray;
    WordArray = (struct Word*)malloc(sizeof(struct Word));
    
    if(WordArray == NULL){  
        printf("\nOVERFLOW");  
    }  
    else  {  
    
    if(list->poll==NULL)  {  
        WordArray->nextWord = NULL;  
        WordArray->previousWord=NULL;  
        WordArray->word=c;
        WordArray->wordLen=strlen(c);
        WordArray->wordIndex=0;
        list->head=WordArray;
        list->poll=WordArray;
    }  
    else   {  
        WordArray->word=c;  
        WordArray->previousWord=list->head;  
        WordArray->nextWord = NULL;
        WordArray->wordLen=strlen(c);
        WordArray->wordIndex=list->head->wordIndex + 1;
        list->head->nextWord=WordArray;  
        list->head=WordArray;  
    } 

      
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

List* split(char str[]){
    struct List *list = (List*)malloc(sizeof(List));
    list->poll=NULL;
    list->head=NULL;
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
                insertWord(list, getSubString1(str, sWord, eWord - 1));
                isWordStarted = false;
            }
        }
    }
    if(isWordStarted)
        insertWord(list, getSubString1(str, sWord, len));
    
    return list;
}

void printWords(List* list){
    
    struct Word *temp;  
    printf("\nhere is your words...\n");   
    temp=list->poll;
    
    while(temp != NULL){
        printf("\n%d: %s", temp->wordIndex,temp->word);
        temp=temp->nextWord;
    }
    printf("\n");

}

char* getWordAt(List* list, int ind){

    int minIndex = list->poll->wordIndex;
    
    int maxIndex = list->head->wordIndex;

    int indCpy = ind;
    Word* word;

    if(ind < 0)
        ind = maxIndex + ind + 1;
    
    if(ind < 0 || ind > maxIndex){
        printf("\nIndexOutOfBound: index is more then it's item %d", indCpy);
        return NULL;
    };
    
    // binary search

    if(ind == minIndex)
        return list->poll->word;

    else if(ind == maxIndex)
        return list->head->word;

    else{
        // for desiding where should I starting iteration; 
        if(ind - minIndex < maxIndex - ind){
            word = list->poll->nextWord;
            
            while (word->wordIndex != ind)
                word = word->nextWord;
        }
        else{
            word = list->head->previousWord;
            
            while (word->wordIndex != ind)
                word = word->previousWord;
        }
            
        return word->word;
    };
  
}

char* strip(char* str){

    // for left part

    int temp, len = strlen(str);
    int firstCutUntil = 0;
    int lastCutUntil = len;
    char* newStr;

    temp = firstCutUntil;
    while( temp < len && isspace(str[temp++]) != 0);

    if(temp == len && isspace(str[temp - 1]) != 0){
        newStr = (char *)malloc(sizeof(char));
        newStr[0] = '\0';
        return newStr;
    }
    
    firstCutUntil = temp - 1;

    temp = lastCutUntil - 1;

    while( temp > firstCutUntil && isspace(str[temp--]) != 0);

    lastCutUntil = temp + 1;

    newStr = (char*)calloc(lastCutUntil - firstCutUntil + 2, sizeof(char));
    len = 0;

    for(temp = firstCutUntil; temp <= lastCutUntil; temp++){
        newStr[len++] = str[temp];
    }

    newStr[len] = '\0';
    return newStr;
}

int main(){
    char s[] = "this is my sentense    ";
    char s1[] = "     hello this will          be my new list,      !             ";
    char s2[] = "Dolore sint quis mollit esse. Dolore occaecat anim excepteur tempor reprehenderit enim qui proident sint ea duis. Aute consequat laborum labore cillum elit velit culpa labore elit labore quis enim aliquip irure. Pariatur voluptate laboris aute mollit qui proident id. Occaecat minim Lorem eiusmod ex Lorem sint cupidatat esse ea duis ex labore sunt. Magna ut occaecat ipsum ullamco reprehenderit nisi labore aliqua. Velit in aliqua labore magna esse do amet qui amet sit incididunt ea anim.";
    int myInd[] = {-15, -3, 0, 3, 15, 30, -16, -32, 28, -100, 100};

    struct List* list = split(s);
    printWords(list);

    struct List* list1 = split(strip(s1));
    printWords(list1);

    struct List* list2 = split(s2);
    printWords(list2);


    for(int i = 0; i < 11; i++)
        printf("\n%d: %d %s\n", i + 1, myInd[i] ,getWordAt(list2, myInd[i]));
    
    return 0;
}
