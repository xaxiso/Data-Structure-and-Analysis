#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <unistd.h>

int RNG[1000003];
int STH[1000003];
int lefttrack[1000003];
int righttrack[1000003];
int left[1000003];
int right[1000003];

typedef struct stack{
	int top;
	int n;
	int *arr;
}Stack;

Stack* createStack(int n){
	Stack* stack = malloc(sizeof(Stack));
	if(!stack) return NULL;
	stack->n = n;
	stack->top = -1;
	stack->arr = (int*)malloc(stack->n*sizeof(int));
	if(!stack->arr) return NULL;
	return stack;
}

int isEmpty(Stack* stack){
	return (stack->top==-1);
}

int isFull(Stack* stack){
	return (stack->top==stack->n-1);
}

void push(Stack* stack, int item){
	if(isFull(stack))
		return;
	else
		stack->arr[++stack->top] = item;
}

int pop(Stack* stack){
	if(isEmpty(stack))
		return 0;
	else
		return (stack->arr[stack->top--]);
}

int peek(Stack* stack){
	if(isEmpty(stack))
		return -1;
	return stack->arr[stack->top];
}

int main(){
	int n, i, j, temp;
	scanf("%d", &n);
	Stack* stack = createStack(n);

	for(i=0;i<n;i++)
		scanf("%d", &STH[i]);
	for(i=0;i<n;i++)
		scanf("%d", &RNG[i]);
	
	int count = 0;
	for(i=0;i<n;i++){
		if(i==0){
			push(stack, i);
			lefttrack[i] = 0;
		}
		else if(!isEmpty(stack) && STH[peek(stack)]<STH[i]){
			count = 0;
			while(!isEmpty(stack) && STH[peek(stack)]<STH[i]){
				// printf("peek: %d, STH[%d]: %d, count: %d\n", peek(stack), i, STH[i], count);
				lefttrack[i]+=(lefttrack[peek(stack)]+1);
				// else count++;
				pop(stack);
				
				// printf("after: %d, STH[%d]: %d, count: %d\n", peek(stack), i, STH[i], count);
			}
			// lefttrack[i] = count;
			push(stack, i);
			// printf("STH[%d]: %d, count: %d\n", i, STH[i], count);
		}
		else{
			push(stack, i);
			// printf("STH[%d]: %d, count: %d\n", i, STH[i], count);
		}
	}

	// for(i=0;i<n;i++){
	// 	printf("%d ", lefttrack[i]);
	// }

	for(i=0;i<n;i++){
		if(RNG[i]>=lefttrack[i])
			left[i] = i-lefttrack[i];
		else{
			left[i] = i-RNG[i];
		}
	}

	while(!isEmpty(stack)){
		pop(stack);
		// printf("here\n");
	}

	for(i=n-1;i>=0;i--){
		if(i==(n-1)){
			push(stack, i);
			righttrack[i] = 0;
		}
		else if(!isEmpty(stack) && STH[peek(stack)]<STH[i]){
			while(!isEmpty(stack) && STH[peek(stack)]<STH[i]){
				// printf("peek: %d, STH[%d]: %d, count: %d\n", peek(stack), i, STH[i], count);
				righttrack[i]+=(righttrack[peek(stack)]+1);
				// else count++;
				pop(stack);
				
				// printf("after: %d, STH[%d]: %d, count: %d\n", peek(stack), i, STH[i], count);
			}
			// righttrack[i] = count;
			push(stack, i);
			// printf("STH[%d]: %d, count: %d\n", i, STH[i], count);
		}
		else{
			push(stack, i);
			// printf("STH[%d]: %d, count: %d\n", i, STH[i], count);
		}
	}

	// for(i=0;i<n;i++){
	// 	printf("%d ", righttrack[i]);
	// }

	for(i=n-1;i>=0;i--){
		if(RNG[i]>=righttrack[i])
			right[i] = i+righttrack[i];
		else{
			right[i] = i+RNG[i];
		}
	}


	for(i=0;i<n;i++){
		printf("%d %d\n", left[i], right[i]);
	}

	return 0;
}

// int STH[1000003];
// int RNG[1000003];
// int left[1000003];
// int right[1000003];
// int resLeft[1000003];
// int resRight[1000003];
// int leftskip[1000003];
// int rightskip[1000003];
// /*
// 10
// 2 3 5 2 3 5 7 6 2 5
// 2 2 4 2 2 4 7 2 5 1

// 10
// 2 3 1 4 8 1 1 1 9 2
// 2 3 4 1 4 1 3 2 9 0
// */


// int main(){
// 	int i, j, n;
// 	scanf("%d", &n);

// 	for(i=0;i<n;i++)
// 		scanf("%d", &STH[i]);
// 		// scanf("%d", &STH[i]);

// 	for(i=0;i<n;i++)
// 		scanf("%d", &RNG[i]);
// 		// scanf("%d", &RNG[i]);

// 	for(i=0;i<n;i++){
// 		if(i==0) left[i]=0;
// 		else if(STH[i-1]<STH[i] && RNG[i]>=1)
// 			left[i]=1;
// 		else
// 			left[i]=0;

// 		if(i==(n-1)) right[i]=0;
// 		else if(STH[i+1]<STH[i] && RNG[i]>=1)
// 			right[i]=1;
// 		else
// 			right[i]=0;
// 	}

// 	for(i=0;i<n;i++){
// 		if(i==0)
// 			leftskip[i]=0;
// 		else if(STH[i]>STH[i-1])
// 			leftskip[i]=leftskip[i-1];
// 		else
// 			leftskip[i]=i;
// 	}

// 	for(i=(n-1);i>=0;i--){
// 		if(i==(n-1))
// 			rightskip[i]=i;
// 		else if(STH[i]>STH[i+1])
// 			rightskip[i]=rightskip[i+1];
// 		else
// 			rightskip[i]=i;
// 	}

// 	// printf("\n");
// 	// for(i=0;i<n;i++)
// 	// 	printf("%d ", leftskip[i]);
// 	// printf("\n");
// 	// for(i=0;i<n;i++)
// 	// 	printf("%d ", rightskip[i]);
// 	// printf("\n\n");

// 	for(i=0;i<n;i++){
// 		if(left[i]==0){
// 			resLeft[i]=i;
// 			// printf("if - i: %d, k: %d\n", i, k);
// 			continue;
// 		}
// 	}

// 	for(i=(n-1);i>=0;i--){
// 		if(right[i]==0){
// 			resRight[i]=i;
// 			continue;
// 		}
// 	}

// 	for(i=0;i<n;i++){ //going right, recording left most index
// 		int k = i-1;		
// 		// printf("i: %d, k: %d\n", i, k);

// 		// if(left[i]==0){
// 		// 	resLeft[i]=i;
// 		// 	printf("if - i: %d, k: %d\n", i, k);
// 		// 	continue;
// 		// }

// 		while(k>=0){
// 			if(STH[k]<STH[i] && (i-k)<=RNG[i]){
// 				if(resLeft[k]!=k){ //DP
// 					//printf("DP i: %d, k: %d\n", i, k);
// 					if(i-resLeft[k]<=RNG[i]){
// 						k=resLeft[k];
// 						//printf("DD i: %d, k: %d\n", i, k);
// 						if(k==0){
// 							resLeft[i]=k;
// 							break;
// 						}
// 						//printf("DA i: %d, k: %d\n", i, k);
// 					}
// 					else{
// 						//printf("DG i: %d, k: %d\n", i, k);
// 						k=(i-RNG[i]);
// 						resLeft[i]=k;
// 						k--;
// 					}
// 				}
// 				// else if(STH[i]>STH[leftskip[k]]){
// 				// 	if(i-leftskip[k]<=RNG[i]){
// 				// 		k=leftskip[k];
// 				// 		resLeft[i]=leftskip[k];
// 				// 		k--;
// 				// 	}
// 				// 	else{
// 				// 		k=(i-RNG[i]);
// 				// 		resLeft[i]=k;
// 				// 		k--;
// 				// 	}
// 				// }
// 				else{
// 					//printf("RG i: %d, k: %d\n", i, k);
// 					resLeft[i]=k;
// 					// if(k==0) break;
// 					k--;
// 				}
// 			}
// 			else break;
// 		}
// 	}

// 	//printf("\n\n");

// 	for(i=n-1;i>=0;i--){ //going left, recording right most index
// 		int k = i+1;
// 		//printf("i: %d, k: %d\n", i, k);

// 		// if(right[i]==0){
// 		// 	resRight[i]=i;
// 		// 	continue;
// 		// }

// 		while(k<=n-1){
// 			if(STH[k]<STH[i] && (k-i)<=RNG[i]){
// 				if(resRight[k]!=k){
// 					//printf("DP i: %d, k: %d\n", i, k);
// 					if(resRight[k]-i<=RNG[i]){
// 						k=resRight[k];
// 						//printf("DD i: %d, k: %d\n", i, k);
// 						if(k==n-1){
// 							resRight[i]=k;
// 							break;
// 						}
// 						//printf("DA i: %d, k: %d\n", i, k);
// 					}
// 					else{
// 						//printf("DG i: %d, k: %d\n", i, k);
// 						k=(i+RNG[i]);
// 						resRight[i]=k;
// 						k++;
// 					}
// 				}
// 				// else if(STH[i]>STH[rightskip[k]]){
// 				// 	if(rightskip[k]-i<=RNG[i]){
// 				// 		k=rightskip[k];
// 				// 		resRight[i]=rightskip[k];
// 				// 		k++;
// 				// 	}
// 				// 	else{
// 				// 		k=(i+RNG[i]);
// 				// 		resRight[i]=k;
// 				// 		k++;
// 				// 	}
// 				// 	// //printf("else if: i: %d, k: %d\n", i, k);
// 				// 	// sleep(1);
// 				// }
// 				else{
// 					//printf("RG i: %d, k: %d\n", i, k);
// 					resRight[i]=k;
// 					// if(k==n-1) break;
// 					++k;
// 				}
// 			}
// 			else break;
// 		}
// 	}

// 	for(i=0;i<n;i++){
// 		printf("%d %d\n", resLeft[i], resRight[i]);
// 	}

// 	return 0;
// }



// #include <stdio.h>
// #include <stdlib.h>
// #include <limits.h>
// #include <ctype.h>

// int STH[1000003];
// int RNG[1000003];
// int left[1000003];
// int right[1000003];
// int resLeft[1000003];
// int resRight[1000003];
// int leftcnt[1000003];
// int rightcnt[1000003];

// /*
// 10
// 2 3 5 2 3 5 7 6 2 5
// 2 2 4 2 2 4 7 2 5 1
// */

// int main(){
// 	int i, j, n;
// 	scanf("%d", &n);

// 	for(i=0;i<n;i++)
// 		scanf("%d", &STH[i]);
// 		// scanf("%d", &STH[i]);

// 	for(i=0;i<n;i++)
// 		scanf("%d", &RNG[i]);
// 		// scanf("%d", &RNG[i]);

// 	for(i=0;i<n;i++){
// 		if(i==0) left[i]=0;
// 		else if(STH[i-1]<STH[i] && RNG[i]>=1)
// 			left[i]=1;
// 		else
// 			left[i]=0;

// 		if(i==(n-1)) right[i]=0;
// 		else if(STH[i+1]<STH[i] && RNG[i]>=1)
// 			right[i]=1;
// 		else
// 			right[i]=0;
// 	}

// 	int count = 0;
// 	for(i=0;i<n;i++){
// 		if(left[i]==0 && STH[i]>STH[i-1]){
// 			++count;
// 			leftcnt[i]=count;
// 		}
// 		else
// 			count = 0;
// 	}

// 	count = 0;
// 	for(i=n-1;i>=0;i--){
// 		if(right[i]==0 && STH[i]>STH[i+1]){
// 			++count;
// 			rightcnt[i]=count;
// 		}
// 		else
// 			count = 0;
// 	}

// 	// for(i=0;i<n;i++)
// 	// 	printf("leftcnt: %d, rightcnt: %d, %d %d\n", leftcnt[i], rightcnt[i], left[i], right[i]);

// 	for(i=0;i<n;i++){ //going right, recording left most index
// 		// if(left[i]==0){
// 		// 	resLeft[i]=i;
// 		// 	continue;
// 		// }

// 		int k = i-1;
// 		while(k>=0){
// 			if(STH[k]<STH[i] && (i-k)<=RNG[i]){
// 				if(leftcnt[k]>0 && leftcnt[k]<=RNG[i] && (k-leftcnt[k])>=0){
// 					k-=leftcnt[k];
// 					resLeft[i]=k;
// 					k--;
// 					printf("hi\n");
// 				}
// 				else if(resLeft[k]!=k){ //DP
// 					// printf("DP i: %d, k: %d\n", i, k);
// 					if(i-resLeft[k]<=RNG[i]){
// 						k=resLeft[k];
// 						if(k==0){
// 							resLeft[i]=k;
// 							break;
// 						}
// 						// resLeft[i]=k;
// 						// k--;
// 						printf("here\n");
// 					}
// 					else{
// 						// printf("DG i: %d, k: %d\n", i, k);
// 						resLeft[i]=k;
// 						k--;
// 						printf("else\n");
// 					}
// 				}
// 				else{
// 					// printf("RG i: %d, k: %d\n", i, k);
// 					resLeft[i]=k;
// 					// if(k==0) break;
// 					k--;
// 					printf("last else\n");
// 				}
// 				// printf("i: %d, k: %d\n", i, k);
// 			}
// 			else break;
// 		}
// 	}

// 	// printf("\n\n");

// 	for(i=n-1;i>=0;i--){ //going right, recording left most index
// 		// if(right[i]==0){
// 		// 	resRight[i]=i;
// 		// 	continue;
// 		// }

// 		int k = i+1;
// 		while(k<=n-1){
// 			if(STH[k]<STH[i] && (k-i)<=RNG[i]){
// 				if(rightcnt[k]>0 && rightcnt[k]<=RNG[i] && (rightcnt[k]+k)<=(n-1)){
// 					k+=rightcnt[k];
// 					resRight[i]=k;
// 					k++;
// 					printf("hi\n");
// 				}
// 				else if(resRight[k]!=k){
// 					// printf("DP i: %d, k: %d\n", i, k);
// 					if(resRight[k]-i<=RNG[i]){
// 						k=resRight[k];
// 						if(k==n-1){
// 							resRight[i]=k;
// 							break;
// 						}
// 						resRight[k]=k;
// 						k++;
// 						printf("here right, i: %d, k: %d\n", i, k);
// 					}
// 					else{
// 						// printf("DG i: %d, k: %d\n", i, k);
// 						resRight[i]=k;
// 						k++;
// 					}
// 				}
// 				else{
// 					// printf("RG i: %d, k: %d\n", i, k);
// 					resRight[i]=k;
// 					// if(k==n-1) break;
// 					++k;
// 				}
// 				// printf("i: %d, k: %d\n", i, k);
// 			}
// 			else break;
// 		}
// 	}

// 	for(i=0;i<n;i++){
// 		printf("%d %d\n", resLeft[i], resRight[i]);
// 	}

// 	return 0;
// }


// // if(left[k-4]==0 && left[k-3]==0 && left[k-2]==0 && left[k-1]==0 && left[k]==0){
// 			// 	k-=5;
// 			// 	resLeft[i]=k;
// 			// }
// 			// else if(left[k-3]==0 && left[k-2]==0 && left[k-1]==0 && left[k]==0){
// 			// 	k-=4;
// 			// 	resLeft[i]=k;
// 			// }
// 			// else if(left[k-2]==0 && left[k-1]==0 && left[k]==0){
// 			// 	k-=3;
// 			// 	resLeft[i]=k;
// 			// }
// 			// else if(left[k-1]==0 && left[k]==0){
// 			// 	k-=2;
// 			// 	resLeft[i]=k;
// 			// }
// 			// else if(left[k]==0){
// 			// 	k--;
// 			// 	resLeft[i]=k;
// 			// }

// // if(right[k+4]==0 && right[k+3]==0 && right[k+2]==0 && right[k+1]==0 && right[k]==0){
// 			// 	k+=5;
// 			// 	resRight[i]=k;
// 			// }
// 			// else if(right[k+3]==0 && right[k+2]==0 && right[k+1]==0 && right[k]==0){
// 			// 	k+=4;
// 			// 	resRight[i]=k;
// 			// }
// 			// else if(right[k+2]==0 && right[k+1]==0 && right[k]==0){
// 			// 	k+=3;
// 			// 	resRight[i]=k;
// 			// }
// 			// else if(right[k+1]==0 && right[k]==0){
// 			// 	k+=2;
// 			// 	resRight[i]=k;
// 			// }
// 			// else if(right[k]==0){
// 			// 	k++;
// 			// 	resRight[i]=k;
// 			// }