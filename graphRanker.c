#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {	
	unsigned long sumPath;
	int position;
} topKstruct;

unsigned long sumVet(unsigned long[], int);
unsigned long dijkstraSum(int);
void heapify(topKstruct[], int);
void checkRow(unsigned long[], unsigned long[], int, int);

int main (int argc, char* argv[]){
	int n = 0;
	int k = 0;
	int i;
	int counter = -1;
	char string[14];
	topKstruct curr, tmp;
	
	(void)scanf("%d %d", &n, &k);
	
	topKstruct topKvet[k];
	
	
	for (i=0; i<k; i++){
		topKvet[i].sumPath = -1;
		topKvet[i].position = -1;
	}
	
	(void)scanf("%s", string);
	while(!(feof(stdin))){

		if (strncmp(string, "AggiungiGrafo", 13)==0){
			counter++;
			curr.position = counter;
			curr.sumPath = dijkstraSum(n);
			//printf("\n%d - %lu\n", curr.position, curr.sumPath);
			for (i=0; i<k; i++){
				if (curr.sumPath<topKvet[i].sumPath || topKvet[i].sumPath==-1){
					tmp.sumPath = topKvet[i].sumPath;
					tmp.position = topKvet[i].position;
					topKvet[i].sumPath = curr.sumPath;
					topKvet[i].position = curr.position;
					curr.sumPath = tmp.sumPath;
					curr.position = tmp.position;
				}
			}
		
		}
		
		if (strncmp(string, "TopK", 4)==0){
			//printf("\n%d\n", counter);
			for (i=0; i<k; i++){
				if (topKvet[i].sumPath!=-1){
					printf("%d", topKvet[i].position);
					if (i<k-1 && topKvet[i+1].position!=-1){
						printf(" ");
					}
				}
				
			}
			printf("\n");
		}
		(void)scanf("%s", string);
		
	}
	
	return 0;
}

void heapify(topKstruct A[], int pos){
	
	
}


unsigned long dijkstraSum(int numNodi){
	
	unsigned long mat[numNodi*numNodi];
	unsigned long vet[numNodi];
	
	int i, j;
	vet[0] = 0;
	for (i=0; i<numNodi; i++){
		for(j=0; j<numNodi; j++){
			(void)scanf("%lu,", &mat[i*numNodi+j]);
			if (i==0 && j>0){
				vet[j]=mat[i*numNodi+j];
			}
		}
	}
	
	for (i=1; i<numNodi; i++){
		checkRow(mat, vet, i, numNodi);
	}
	/*for (i=0; i<numNodi; i++){
		printf(" %lu -", vet[i]);
	}*/
	return sumVet(vet, numNodi);
}

void checkRow(unsigned long matrice[], unsigned long vettore[], int r, int len){
	int j;
	unsigned long sum;
	if (vettore[r]!=0){
		for (j=1; j<len; j++){
			sum = 0;
			if (r!=j && matrice[r*len+j]!=0) {
				sum = matrice[r*len+j] + vettore[r];
				if (sum<vettore[j] || vettore[j]==0){
					vettore[j]=sum;
					//printf(" %lu -", vettore[i]);
					if (j<r){
						checkRow(matrice, vettore, j, len);
					}
				}				
			}		
		}
	}
}

unsigned long sumVet(unsigned long v[], int len){
	int i;
	unsigned long int sum = 0;
	for (i=0; i<len; i++){
		sum = sum + v[i];
	}
	return sum;
}
