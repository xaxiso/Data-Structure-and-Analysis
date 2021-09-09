#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

char str[1000003];
char min[] = "S";
char max[] = "E";

struct Node { 
	char data;
	int flag;
	struct Node* next; 
	struct Node* prev; 
};

void append(struct Node** head_ref, char new_data){
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node)); 

	struct Node* last = *head_ref;

	new_node->data = new_data; 

	new_node->flag = 0;

	new_node->next = NULL; 

	if (*head_ref == NULL) { 
		new_node->prev = NULL; 
		*head_ref = new_node; 
		return; 
	} 

	while (last->next != NULL) 
		last = last->next; 

	last->next = new_node; 

	new_node->prev = last; 

	return; 
}

void insertBefore(struct Node** head_ref, struct Node* next_node, char new_data){  
    if (next_node == NULL){  
        // printf("the given next node cannot be NULL");  
        return;  
    }

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));  
  
    new_node->data = new_data;  

    new_node->flag = 0;
  
    new_node->prev = next_node->prev;  
  
    next_node->prev = new_node;  
  
    new_node->next = next_node;  
  
    if (new_node->prev != NULL)  
        new_node->prev->next = new_node;  

    else{
    	// printf("new head\n");
        (*head_ref) = new_node;
        (*head_ref)->prev = NULL;
    }
      
}

void printList(struct Node* node){ 
	while (node != NULL) { 
		if(strcmp(&(node->data), min)==0 || strcmp(&(node->data), max)==0){
			node = node->next;
			continue;
		}
		printf("%c", node->data);  
		node = node->next; 
	}
	printf("\n");
}

int main(){
	int t, i, k;

	scanf("%d", &t);

	for(i=0;i<t;i++){
		int sel = 0, track = INT_MIN, rev = 0;
		struct Node* head = NULL;
		struct Node* current = NULL;
		struct Node* last = NULL;
		struct Node* start = NULL;

		scanf("%s", str);

		for(k=0;k<strlen(str);k++){
			// if(k!=0) printf("current: %c, str[%d]: %c\n", current->data, k, str[k]);
			// if(k!=0){
			// 	printf("current: %c, str[%d]: %c\n", current->data, k, str[k]);
			// 	printList(head);
			// }
			if(str[k]>='a' && str[k]<='z'){
				// if(k!=0) printf("current: %c, str[%d]: %c\n", current->data, k, str[k]);
				if(k==0){
					append(&head, *min);
					append(&head, str[k]);
					current = head->next;
					append(&head, *max);
					last = head->next->next;
				}

				else{
					// printf("current: %c, str[%d]: %c\n", current->data, k, str[k]);
					if(sel){
						if(track==0){
							if(current->next == NULL){
								// printf("append: %c, str[%d]: %c\n", current->data, k, str[k]);
								append(&current, str[k]);
								current = current->next;
							}
							else{
								// printf("before: %c, str[%d]: %c\n", current->data, k, str[k]);
								insertBefore(&head, current->next, str[k]);
								current = current->next;
							}
						}
						else if(track>0){
							// printf("%c\n", current->data);
							start->next = current->next;
							current->next->prev = start;

							current = start;

							insertBefore(&head, current->next, str[k]);
							current = current->next;
							track = INT_MIN;
							sel = 0;
						}
						else if(track<0){
							current->next = start->next;
							start->prev = current;

							if(current->next!=NULL) current = current->next;

							if(current->next == NULL){
								append(&current, str[k]);
								current = current->next;
							}
							else{
								insertBefore(&head, current->next, str[k]);
								current = current->next;
							}
							track = INT_MIN;
							sel = 0;
						}
					}
					else if(current->next == NULL){
						// printf("append: %c, str[%d]: %c\n", current->data, k, str[k]);
						append(&current, str[k]);
						current = current->next;
					}
					else{
						// printf("before: %c, str[%d]: %c\n", current->data, k, str[k]);
						insertBefore(&head, current->next, str[k]);
						current = current->next;
					}
				}
			}
			else if(str[k]=='H'){
				// printf("else H\n");
				if(current->prev == NULL){
					continue;
				}
				else{
					current = current->prev;
					if(sel) track -= 1;
				}
			}
			else if(str[k]=='L'){
				// printf("else L\n");
				if(current->next->data == 'E'){
					continue;
				}
				else{
					current = current->next;
					if(sel) track += 1;
				}
			}
			else if(str[k]=='I'){
				// printf("else I\n");
				current = head;
			}
			else if(str[k]=='A'){
				// printf("else A\n");
				current = last->prev;
			}
			else if(str[k]=='V'){
				// printf("else V\n");
				if(!sel){
					start = current;
					// printf("start: %c, %c\n", start->data, start->prev->data);
					sel = 1;
					track = 0;
				}
				else{
					sel = 0;
					track = INT_MIN;
				}
			}
			else if(str[k]=='D'){
				// printf("hi\n");
				if(sel){
					if(track==0) continue;
					else if(track>0){
						// printf("%c\n", current->data);
						start->next = current->next;
						current->next->prev = start;

						current = start;

						track = INT_MIN;
						sel = 0;
					}
					else if(track<0){
						// printf("%c %c\n", current->data, start->data);
						current->next = start->next;
						start->next->prev = current;
						// current = current;

						track = INT_MIN;
						sel = 0;
					}
				}
				else{
					// printf("hi\n");
					continue;
				}
			}
			else if(str[k]=='R'){
				if(sel){
					if(track==0) continue;
					else if(track>0){
						printf("start: %c, current: %c\n\n", start->data, current->data);
						start->flag = 1;
						current->flag = 1;
						rev = 1;

						struct Node* curtemp = (struct Node*)malloc(sizeof(struct Node));
						struct Node* curprev = (struct Node*)malloc(sizeof(struct Node));
						struct Node* curnext = (struct Node*)malloc(sizeof(struct Node));
						struct Node* starttemp = (struct Node*)malloc(sizeof(struct Node));
						struct Node* startprev = (struct Node*)malloc(sizeof(struct Node));
						struct Node* startnext = (struct Node*)malloc(sizeof(struct Node));
						curtemp = current;
						curprev = current->prev;
						curnext = current->next;
						starttemp = start;
						startprev = start->prev;
						startnext = start->next;

						printf("start: %c\n", start->data);
						start->prev = current->next;
						printf("%c->prev: %c\n\n", start->data, start->prev->data);

						start = startprev;
						printf("start: %c\n", start->data);
						start->next = current;
						printf("%c->next: %c\n\n", start->data, start->next->data);

						printf("current: %c\n", current->data);
						current->next = startprev;
						printf("%c->next: %c\n\n", current->data, current->next->data);

						printf("starttemp->prev: %c\n", starttemp->prev->data);
						starttemp->prev->prev = starttemp;
						printf("%c->prev->prev: %c\n\n", starttemp->data, starttemp->prev->prev->data);
						
						start = curtemp;
						current = starttemp;
						printf("start: %c, current: %c\n", start->data, current->data);

						sleep(10);
					}
					// else if(track<0){
					// 	printf("start: %c, current: %c\n\n", start->data, current->data);
					// 	start->flag = 1;
					// 	current->flag = 1;
					// 	rev = 1;

					// 	struct Node* curtemp = (struct Node*)malloc(sizeof(struct Node));
					// 	struct Node* curprev = (struct Node*)malloc(sizeof(struct Node));
					// 	struct Node* curnext = (struct Node*)malloc(sizeof(struct Node));
					// 	struct Node* starttemp = (struct Node*)malloc(sizeof(struct Node));
					// 	struct Node* startprev = (struct Node*)malloc(sizeof(struct Node));
					// 	struct Node* startnext = (struct Node*)malloc(sizeof(struct Node));
					// 	curtemp = current;
					// 	curprev = current->prev;
					// 	curnext = current->next;
					// 	starttemp = start;
					// 	startprev = start->prev;
					// 	startnext = start->next;

					// 	printf("start: %c\n", start->data);
					// 	start->prev = current->next;
					// 	printf("%c->prev: %c\n\n", start->data, start->prev->data);

					// 	start = startprev;
					// 	printf("start: %c\n", start->data);
					// 	start->next = current;
					// 	printf("%c->next: %c\n\n", start->data, start->next->data);

					// 	printf("current: %c\n", current->data);
					// 	current->next = startprev;
					// 	printf("%c->next: %c\n\n", current->data, current->next->data);

					// 	printf("starttemp->prev: %c\n", starttemp->prev->data);
					// 	starttemp->prev->prev = starttemp;
					// 	printf("%c->prev->prev: %c\n\n", starttemp->data, starttemp->prev->prev->data);
						
					// 	start = starttemp;
					// 	printf("start: %c, current: %c\n", start->data, current->data);

					// 	sleep(10);
					// }
				}
				else
					continue;
			}
			else continue;
		}

		printList(head);
	}

	return 0; 
}

/*
1
abcdefHHHVLLR
*/
