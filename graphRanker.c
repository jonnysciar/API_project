#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {	
	long sumPath;
	int position;
} topKstruct;

long dijkstraSum(int);

void min_heapify(topKstruct[], int, int);
void max_heapify(topKstruct[], int, int);

void swapTopK(topKstruct[], int, int);
void inserimentoTopK(topKstruct[], int);

void printInt(int);

int main (int argc, char* argv[]){
	int n = 0;
	int k = 0;
	int i;
	int counter = -1;
	
	char carattere = ' ';

	if (scanf("%d %d\n", &n, &k)){}
	
	topKstruct curr;
	topKstruct topKvet[k];
	
	for (i=0; i<k; i++){
		topKvet[i].sumPath = -1;
		topKvet[i].position = -1;
	}
	
	carattere = getchar_unlocked();
	
	while(!(feof(stdin))){

		if (carattere == 'A'){	
			
			for (i=0; i<13; i++){
				getchar_unlocked();
			}
			
			counter++;
			curr.position = counter;
			curr.sumPath = dijkstraSum(n);
			//printf("\n%d - %lu\n", curr.position, curr.sumPath);
			if (counter<k){
				topKvet[k-counter-1] = curr;
			}
			
			if (counter>=k){
				if (counter==k){	
					for (i=k/2; i>=0; i--){
						max_heapify(topKvet, i, k);
					}
				}
				if (curr.sumPath<topKvet[0].sumPath){
					topKvet[0] = curr;
					max_heapify(topKvet, 0, k);
				}
			}
			
		}
		
		if (carattere == 'T'){
			
			for (i=0; i<4; i++){
				getchar_unlocked();
			}
			
			for (i=0; i<k; i++){
				if (topKvet[i].sumPath!=-1){
					printInt(topKvet[i].position);
					if (i<k-1 && topKvet[i+1].position!=-1){
						putchar_unlocked(' ');
					}
				}
				
			}
			printf("\n");
		}
		
		carattere = getchar_unlocked();
	}
	
	return 0;
}


long dijkstraSum(int numNodi){
	
	long mat[numNodi*numNodi];
	int n = numNodi-1;

	char c;
	
	long sum, currSum;
	int i, j;
	int pos;
	unsigned int val;
	
	topKstruct vettore[n];

	for (i=0; i<numNodi; i++){
		for (j=0; j<numNodi; j++){
			
			val = 0;
			c = getchar_unlocked();
			while (c!=',' && c!='\n') {
				val = (val*10) + (c - '0');
				c = getchar_unlocked();
			} 
			
			if (val == 0) {
				mat[i*numNodi+j] = LONG_MAX;
			} else {
				mat[i*numNodi+j] = val;
			}
			
			if (i == 0 && j>0){
				vettore[j-1].sumPath = mat[i*numNodi+j];
				vettore[j-1].position = j;
			}
			//printf("%lu - ", mat[i*numNodi+j]);	
		}
		//printf("\n");
	}

	for (i=n/2; i>=0; i--){
		min_heapify(vettore, i, n);
	}
	
	pos = vettore[0].position;
	currSum = vettore[0].sumPath;
	sum = 0;
	while (n>0 && currSum<LONG_MAX){

		sum = sum + currSum;
		
		for (i=1; i<n; i++){
			if (mat[pos*numNodi+vettore[i].position]<LONG_MAX){
				if((currSum + mat[pos*numNodi+vettore[i].position])<(vettore[i].sumPath)){
					vettore[i].sumPath = currSum + mat[pos*numNodi+vettore[i].position];
					inserimentoTopK(vettore, i);
				}
			}
		}
		
		vettore[0] = vettore[n-1];
		n--;
		min_heapify(vettore, 0, n);
		
		pos = vettore[0].position;
		currSum = vettore[0].sumPath;
	}	
	
	return sum;
}


void min_heapify(topKstruct vettore[], int n, int len){
	int l = 2*n+1;
	int r = 2*n+2;
	int posmin = n;
	if (l<len && vettore[l].sumPath<vettore[posmin].sumPath){
		posmin = l;
	}
	if (r<len && vettore[r].sumPath<vettore[posmin].sumPath){
		posmin = r;
	}
	if (posmin!=n){
		swapTopK(vettore, n, posmin);
		min_heapify(vettore, posmin, len);
	}
}

void swapTopK(topKstruct vettore[], int pos1, int pos2){
	topKstruct tmp;
	tmp = vettore[pos1];
	vettore[pos1] = vettore[pos2];
	vettore[pos2] = tmp;
}

void max_heapify(topKstruct vettore[], int n, int len){
	int l = 2*n+1;
	int r = 2*n+2;
	int posmax = n;
	if (l<len && vettore[l].sumPath>vettore[posmax].sumPath){
		posmax = l;
	}
	if (r<len && vettore[r].sumPath>vettore[posmax].sumPath){
		posmax = r;
	}
	if (posmax!=n){
		swapTopK(vettore, n, posmax);
		max_heapify(vettore, posmax, len);
	}
}

void inserimentoTopK(topKstruct vettore[], int f){
	int p;
	if (f>2){
		if (f%2!=0){
			p = (f-1)/2;
		} else {
			p = (f-2)/2;
		}
		if(vettore[f].sumPath<vettore[p].sumPath){
			swapTopK(vettore, f, p);
			inserimentoTopK(vettore, p);
		}
	}
}

void printInt(int num){
	char c;
	if (num>9){
		printInt(num/10);
	}
	c = num%10 + '0';
	putchar_unlocked(c);
}
