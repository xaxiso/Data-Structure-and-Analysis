#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define q 262139
#define d 27
// #define d 10
#define ll long long int

char s[10000000];

ll backhash[10000000];
ll hash1[10000000];
ll power[30000000];

char ans[30000000];
ll ansindex[10000000];

ll left[10000000];
ll right[10000000];

ll idx1, idx2, slen, startlen, anshash, anslen, ansi;

void powerCalc(ll tlen){
	for(ll i=1;i<=tlen;i++){
		if(i==1) power[i] = d;
		else power[i] = (power[i-1]*d)%q;
	}
}

ll find(ll len, ll prevlen, ll firstl, ll firstr, ll secondl, ll secondr){
	// printf("%lld %lld %lld %lld\n", left[idx1]-1, right[idx1], hash1[left[idx1]-1], hash1[right[idx1]-1]);	
	ll firsthash = (hash1[firstr] - (hash1[firstl-1] * power[len])%q )%q;
	if(firsthash < 0) firsthash += q;


	ll secondhash = (backhash[secondr] - (backhash[secondl-1] * power[len])%q )%q;
	if(secondhash<0) secondhash += q;

	// printf("firsthash: %lld, secondhash: %lld\n\n", firsthash, secondhash);

	if(firsthash == secondhash){
		// printf("\ntrue\n");
		if(len==1) return 1;
		if(len==startlen) return len;
		// printf("prevl: %lld, prevr: %lld\n", secondl, secondr);

		firstr = firstl-1;
		secondr = secondl-1;
		firstl -= prevlen;
		secondl -= prevlen;

		ll newlen = firstr-firstl+1;
		// printf("newlen: %lld\n", newlen);
		// printf("len: %lld, firstl: %lld, firstr: %lld, secondl: %lld, secondr: %lld\n", newlen, firstl, firstr, secondl, secondr);

		ll L = find(newlen, len, firstl, firstr, secondl, secondr);
		return L+len;
	}
	else{
		if(len==1 || len==0) return 0;
		len /= 2;
		firstl += len;
		secondl += len;
		ll newlen = firstr-firstl+1;
		// printf("\nfalse\nlen: %lld, firstl: %lld, firstr: %lld, secondl: %lld, secondr: %lld\n", newlen, firstl, firstr, secondl, secondr);

		ll R = find(newlen, len, firstl, firstr, secondl, secondr);
		return R;
	}
}

ll last = 1;

int main(){
	ll i, j, k, m, result;

	scanf("%s", s);
	slen = strlen(s);

	powerCalc(slen);

	scanf("%lld", &m);

	for(i=0;i<m;i++)
		scanf("%lld %lld", &left[i], &right[i]);

	for(i=1;i<=slen;i++){
		if(i==1) backhash[i] = (s[slen-i] - '`')%q;
		else
			backhash[i] = ((d*backhash[i-1])%q + (s[slen-i] - '`'))%q;
		// printf("%c, %lld: %lld      (%d*%lld + %d)\n", s[slen-i], i, backhash[i], 27, backhash[i-1], s[slen-i]-'`');
	}

	for(i=0;i<m-1;i++){
		ll len1, len2;
		if(i==0)
			len1 = right[i]-left[i]+1;
		else
			len1 = last-1;
		len2 = right[i+1]-left[i+1]+1;
		// printf("len1: %lld, len2: %lld\n", len1, len2);


		ll len, firstdiff = 0, seconddiff = 0;
		if(len1 <= len2){
			len = len1;
			seconddiff = len2 - len1;
			// printf("seconddiff: %lld\n", seconddiff);
		}
		else{
			len = len2;
			firstdiff = len1 - len2;
			// printf("firstdiff: %lld\n", firstdiff);
		}

		startlen = len;

		if(i==0){
			for(j=left[i];j<=right[i];j++){
				if(j==left[i]) hash1[last++] = (s[j-1] - '`')%q;
				else{
					hash1[last] = ((d*hash1[last-1])%q + (s[j-1] - '`'))%q;
					last++;
				}
				// printf("%c: %lld, %lld\n", s[j-1], hash1[last-1], last-1);
			}
		}

		idx1 = i;
		idx2 = i+1;

		// printf("%lld %lld\n", left[idx2], right[idx2]);
		ll newl = slen - right[idx2] + 1 + seconddiff;
		ll newr = slen - left[idx2] + 1;

		// printf("ansleft: %lld, ansright: %lld, secondl: %lld, secondr: %lld\n", firstdiff+1, last-1, newl, newr);
		ll resultlen = find(len, 0, firstdiff+1, last-1, newl, newr);
		// printf("resultlen: %lld\n", resultlen);

		// printf("%lld\n", hash1[last-1]);
		for(j=left[idx2]+resultlen;j<=right[idx2];j++){
			hash1[last] = ((d*hash1[last-1])%q + (s[j-1] - '`'))%q;
			last++;
			// printf("%c: %lld\n", s[j-1], hash1[last-1]);
		}

		// if(i==0)
		// 	strncat(ans, s+left[i]-1, right[i]-left[i]+1);

		// strncat(ans, s+left[idx2]+resultlen-1, len2-resultlen);

		if(i==0){
			ansindex[ansi++] = left[i];
			ansindex[ansi++] = right[i];
		}
		
		ansindex[ansi++] = left[idx2] + resultlen;
		ansindex[ansi++] = right[idx2];

		// printf("%s\n\n", ans);
		// printf("==================================================\n");
	}

	// printf("%s\n", ans);

	// ansi++;
	for(i=0;i<ansi;i+=2){
		// printf("%lld: %lld\n", i, ansindex[i]);
		for(j=ansindex[i];j<=ansindex[i+1];j++){
			printf("%c", s[j-1]);
		}
	}

	return 0;
}

/*
abcdiiikjbadc
4
3 6
5 9
9 11
13 13



ank
2
2 2
3 4



kkkkkkjjtttttt
2
1 7
8 14


abcdbfghiihktlaibttbihi
3
1 9
10 18
19 23






abcdcbkk
2
1 3
5 7

abcdefghhgfedcka
2
1 8
9 16


abcdbfghiihktlaibt
2
1 9
10 18


abcdbfggfbaltk
2
1 7
8 14

abcdbfggfbdltk
2
1 7
8 14

abcabcddcbalta
2
1 7
8 14


abcdefdcklai
2
2 4
7 10


abcdefdcklai
2
1 4
7 9


abcdefcbakij
2
1 3
7 12



abcdefgedcbak
2
1 5
8 12
*/