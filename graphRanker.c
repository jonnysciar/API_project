#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {	
	long sumPath;
	int position;
} topKstruct;

long dijkstraSum(int);
void swap(int[], int, int);
void min_heapify(long[], int[], int, int);

int main (int argc, char* argv[]){
	int n = 0;
	int k = 0;
	int i;
	int counter = -1;
	char string[14];
	topKstruct curr;// max; 
	int i_max = 0;
	
	
	if (scanf("%d %d", &n, &k)){}
	
	topKstruct topKvet[k];
	
	
	for (i=0; i<k; i++){
		topKvet[i].sumPath = -1;
		topKvet[i].position = -1;
	}
	
	if (scanf("%s", string)){}
	while(!(feof(stdin))){

		if (strncmp(string, "AggiungiGrafo", 13)==0){
			counter++;
			curr.position = counter;
			curr.sumPath = dijkstraSum(n);
			//printf("\n%d - %lu\n", curr.position, curr.sumPath);
			if (counter<k){
				topKvet[counter] = curr;
				if (topKvet[i_max].sumPath<curr.sumPath){
					i_max = counter;
					/*max.sumPath = curr.sumPath;
					max.position = curr.position;*/
				}
			}
			else if (counter>=k){
				if (curr.sumPath<topKvet[i_max].sumPath){
					topKvet[i_max] = curr;
					for (i=0; i<k; i++){
						if (topKvet[i].sumPath>topKvet[i_max].sumPath){
							i_max = i;
						}
					}
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
		if (scanf("%s", string)){}
		
	}
	
	return 0;
}


long dijkstraSum(int numNodi){
	
	long mat[numNodi*numNodi];
	int n = numNodi-1;
	int vet[n];
	
	long sum;
	int i, j;
	
	for (i=0; i<numNodi; i++){
		if (i>0){
			vet[i-1] = i;
		}
		for(j=0; j<numNodi; j++){
			
			if (scanf("%lu,", &mat[i*numNodi+j])>0 && mat[i*numNodi+j]==0){
				mat[i*numNodi+j]=LONG_MAX;
			}
			//printf("%lu - ", mat[i*numNodi+j]);	
		}
		//printf("\n");
	}
	
	for (i=n/2; i>=0; i--){
		min_heapify(mat, vet, i, n);
	}
	
	sum = 0;
	while (n>0 && mat[vet[0]]<LONG_MAX){
		
		sum = sum + mat[vet[0]];
		
		/*printf("\n");
		for (i=0; i<n; i++){
			printf("- %d -", vet[i]);
		}
		printf("\n");*/
		//printf("%d - %lu\n", vet[0], mat[vet[0]]);
		
		for (i=1; i<numNodi; i++){
			if (mat[vet[0]*numNodi+i]<LONG_MAX && vet[0]!=i){
				if (mat[vet[0]]+mat[vet[0]*numNodi+i]<mat[i]){
					mat[i] = mat[vet[0]] + mat[vet[0]*numNodi+i];
					for (i=n/2; i>=0; i--){
						min_heapify(mat, vet, i, n);
					}
				}
			}
		}
		
		//sum = sum + mat[vet[0]];
		//mat[vet[0]] = LONG_MAX;
		vet[0]=vet[n-1];
		n--;
		min_heapify(mat, vet, 0, n);
	}
	
	/*for (i=1; i<numNodi; i++){
		if (mat[i]<LONG_MAX){
			sum = sum + mat[i];
		}
	}*/
	
	return sum;
}


void swap(int vettore[], int pos1, int pos2){
	int tmp;
	tmp = vettore[pos1];
	vettore[pos1] = vettore[pos2];
	vettore[pos2] = tmp;
}


void min_heapify(long matrice[], int vettore[], int n, int len){
	int l = 2*n+1;
	int r = 2*n+2;
	int posmin = n;
	if (l<len && matrice[vettore[l]]<matrice[vettore[posmin]]){
		posmin = l;
	}
	if (r<len && matrice[vettore[r]]<matrice[vettore[posmin]]){
		posmin = r;
	}
	if (posmin!=n){
		swap(vettore, n, posmin);
		min_heapify(matrice, vettore, posmin, len);
	}
}
