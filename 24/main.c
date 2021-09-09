#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

char str[5000000];
int lps[5000000];

void computeLPSArray(int M){ 
	int len = 0, i;

	lps[0] = 0;
	i = 1; 

	while (i < M){ 
		if (str[i] == str[len]){ 
			len++; 
			lps[i] = len; 
			i++; 
		} 
		else{ 
			if (len != 0){
				len = lps[len-1]; 
			} 
			else{ 
				lps[i] = 0; 
				i++; 
			} 
		}
	} 
}

int main(){
	int n, i, len, m, flag=0, min=INT_MAX, temp=0, index=-1;
	scanf("%d", &n);
	scanf("%s", str);

	computeLPSArray(n);

	for(i=0;i<n;i++){
		// printf("lps[%d]: %d\n", i, lps[i]);
		len = lps[i];
		m = i+1;
		int pre = m/(m-len);
		// printf("\n%d\n", pre);

		if(len > 0 && m%(m-len) == 0){
			// printf("True\n");
			if(flag==1){
				// printf("here: index: %d\n", index);
				if((i+1)%index != 0){
					// printf("here\n");
					flag = 0;
				}
			}
			if(flag==0){
				// printf("if\n");
				if(i==1){
					temp = 1;
					printf("%d: %d\n", m, 1);
				}
				else if(i>1 && str[i]==str[i-1] && temp==1 && str[i]==str[0]){
					// printf("hi\n");
					printf("%d: %d\n", m, 1);
				}
				else if(pre<min){
					
					// temp = 0;
					min = m/pre;
					index = (i+1)/2;
					// printf("else: %d\n", index);
					flag = 1;
					printf("%d: %d\n", m, min);
				}
				else{
					// temp = 0;
					// printf("pre: %d, min: %d\n", pre, min);
					printf("%d: %d\n", m, m);
				}
			}
			else{
				// temp = 0;
				printf("%d: %d\n", m, min);
			}

		}
		else{
			// printf("False\n");
			// flag = 0;
			printf("%d: %d\n", m, m);
		}
	}

}

// bool isRepeat(char str[]){
// 	int n = strlen(str); 
// 	int lps[n]; 

// 	computeLPSArray(str, n, lps);

// 	int len = lps[n-1];  

// 	// for(int i=0;i<n;i++){
// 	// 	printf("lps[%d]: %d\n", i, lps[i]);
// 	// }

// 	printf("n: %d, len: %d\n", n, len);
// 	printf("%d\n", n/(n-len));
// 	return (len > 0 && n%(n-len) == 0)? true: false; 
// }

// int main(){ 
//    char txt[][100] = {"a", "ab", "aba", "abab", 
//                       "ababa", "ababab", "abababa", "abababab"}; 
//    int n = sizeof(txt)/sizeof(txt[0]); 
//    for (int i=0; i<n; i++) 
//       isRepeat(txt[i])? printf("True\n\n") : printf("False\n\n"); 
//    return 0; 
// } 

// void computeLPSArray(char str[], int M, int lps[]){
// 	int k=0, q;
// 	for(q=2;q<M;q++){
// 		while(k>0 && str[k+1]!=str[q])
// 			k=lps[k];
// 		if(str[k+1]==str[q])
// 			k++;
// 		lps[q]=k;
// 	}
// }