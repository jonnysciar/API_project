#include <stdio.h>
#include <stdlib.h>

void initVet(unsigned long int[], int);
void printVet(unsigned long int[], int);
unsigned long int sumVet(unsigned long int[], int);


int main (int argc, char* argv[]){
	unsigned long int mat[] = {	
		
63147,0,520,29721,
37677,0,0,0,
0,21293,13632,41156,
0,0,0,0

};
	
	int sum = 0;
	int n = 4;
	int i, j;
	unsigned long int vet[n];
	initVet(vet, n);
	//printf("%d", mat[1]);
	for (j=1; j<n; j++){
		vet[j]=mat[j];	
	}
	for (i=1; i<n; i++){
		if (vet[i]!=0){
			for (j=1; j<n; j++){
				if (j!=i && mat[i*n+j]!=0) {
					sum = mat[i*n+j] + vet[i];
					if (sum<vet[j] || vet[j]==0){
						vet[j]=sum;
					}				
				}		
			}
		}
	}
	printVet(vet, n);
	printf("\n%lu", sumVet(vet, n));
	return 0;
}

void initVet(unsigned long int v[], int len){
	int i;
	for (i=0; i<len; i++){
		v[i]=0;
	}
}

void printVet(unsigned long int v[], int len){
	int i;
	printf("\n");
	for (i=0; i<len; i++){
		printf(" %lu -", v[i]);
	}
}

unsigned long int sumVet(unsigned long int v[], int len){
	int i;
	unsigned long int sum = 0;
	for (i=0; i<len; i++){
		sum = sum + v[i];
	}
	return sum;
}

