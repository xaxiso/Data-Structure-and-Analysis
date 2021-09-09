#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXL 10000

typedef struct node{
    struct node *next[26];
}Node;

Node *makeNode(){
    Node *newNode = (Node *)malloc(sizeof(Node));
    for(int i = 0; i < 26; i ++)
        newNode->next[i] = NULL;
    return newNode;
}

void addtrie(char *s, Node *currentNode){
    char c = s[0];
    if(c != '\0'){
        if(currentNode->next[c - 'a'] == NULL)
            currentNode->next[c - 'a'] = makeNode();
        addtrie(s + 1, currentNode->next[c - 'a']);
    }
    return;
}

void search(char *s, Node* current){
    char c = s[0];
    if(c!='\0'){
        if(current->next[c-'a'] == NULL)
            if()
            search(s+1, current->next[c-'a']);

    }
    else{
        printf("%s\n", );
    }
}

int main() {
    int n, m;
    char s[MAXL];
    scanf("%d%d", &n, &m);
    Node *head = makeNode();
    for(int i = 0; i < n; i ++){
        scanf("%s", s);
        int l = strlen(s);
        for(int j = 0; j < l; j ++){
            addtrie(s + j, head);
        }
    }

    for(int i=0;i<m;i++){
        scanf("%s", s);
        search(s, head);
    }

    return 0;
}