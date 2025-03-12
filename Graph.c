#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex{
	int dersKodu;
	int *adjVertexs;
}Vertex;

void swap(int *a,int *b){
	int tmp;
	tmp=*a;
	*a=*b;
	*b=tmp;
}


void createMat(int **mat,int N){
	int i,j;
	printf("Adjacency Matrisi giriniz:\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("Matrix[%d][%d]= ",i+1,j+1);
			scanf("%d",&mat[i][j]);
		}
	}
}

void matToList(Vertex ***vertexs,int **mat,int N){
	int i,j;
	int size;
	for(i=0;i<N;i++){      									 //array of pointers to structure
		(*vertexs)[i]=(Vertex*)malloc(sizeof(Vertex));
		(*vertexs)[i]->dersKodu=i+1;
		(*vertexs)[i]->adjVertexs=(int*)malloc(sizeof(int));
		(*vertexs)[i]->adjVertexs[0]=-1;		
		size=1;
		for(j=0;j<N;j++){									//to define adjacency Vertexs
			if(mat[i][j]==1){
				size++;
				if(size>2){
					(*vertexs)[i]->adjVertexs=(int*)realloc((*vertexs)[i]->adjVertexs,size*sizeof(int));
				}
				(*vertexs)[i]->adjVertexs[size-2]=j;
				(*vertexs)[i]->adjVertexs[size-1]=-1;
			}
		}
	}
}

int indegree(Vertex **vertexs,int N,int i){       //complexity = V + E
	int count=0;
	int j,k;
	for(j=0;j<N;j++){
		k=0;
		while(vertexs[j]->adjVertexs[k]!=-1){
			if(vertexs[j]->adjVertexs[k]==i){
				count++;
			}
			k++;
		}
	}
	return count;
}

void printIndegree(Vertex **vertexs,int N){
	int i;
	printf("Derslerin on sart sayilari:\n");
	for(i=0;i<N;i++){
		printf("Course-%d : %d\n",vertexs[i]->dersKodu,indegree(vertexs,N,i));
	}
}

void min_Heapify(int *arr,int *nodes,int size,int i){
	int min=i;
	if(2*i+1<size && arr[2*i+1]<arr[min]){
		min=2*i+1;
	}
	if(2*i+2<size && arr[2*i+2]<arr[min]){
		min=2*i+2;
	}
	if(i!=min){
		swap(&nodes[min],&nodes[i]);
		swap(&arr[min],&arr[i]);
		min_Heapify(arr,nodes,size,min);
	}
}

int removeRoot(int *arr,int *nodes,int *size){
	int indis=nodes[0];
	if(*size==1){
		arr[0]=-1;	
	}else{
		arr[0]=arr[*size-1];
		nodes[0]=nodes[*size-1];
		(*size)--;		
	}
	return indis;
}


void countTerms(Vertex **vertexs,int N){
	int i,j,k,t;
	int count,size=0,term=0;
	int found,token=0;
	int *deleted=(int*)malloc(sizeof(int));
	int *heap=(int*)malloc(N*sizeof(int));
	int *nodeIndis=(int*)malloc(N*sizeof(int));
	char str;
	for(i=0;i<N;i++){       //complexity = N
		size++;
		heap[i]=indegree(vertexs,N,i);  //complexity = N + E
		nodeIndis[i]=i;
	}                        //complexity = N*(N+E) = N^2
	for(i=N/2-1;i>=0;i--){             //complexity = N
		min_Heapify(heap,nodeIndis,size,i);
	}
	
	while(token<N){     //Worst case complexity = N
		term++;
		count=0;
		printf("Ogrenci %d. donemde alabilecegi dersler:\n",term);
		while(heap[0]==0){      //Worst case complexity = N
			printf(">>> Course-%d\n",vertexs[nodeIndis[0]]->dersKodu);
			token++;
			count++;
			deleted=(int*)realloc(deleted,count*sizeof(int));
			deleted[count-1]=removeRoot(heap,nodeIndis,&size);      //O(1)
			min_Heapify(heap,nodeIndis,size,0);                //logN
		}  				//Worst case complexity = N * logN
		i=0;
		while(i<count){           
			j=0;
			while(vertexs[deleted[i]]->adjVertexs[j]!=-1){      //silinen node'un komsulari bulmak için
				k=vertexs[deleted[i]]->adjVertexs[j];
				t=0;
				found=0;
				while(t<size && found==0){
					if(k==nodeIndis[t]){
						heap[t]--;
						found=1;
					}
					t++;
				}
				j++;
			}
			i++;
		}
		for(i=size/2-1;i>=0;i--){
			min_Heapify(heap,nodeIndis,size,i);
		}
	}
	printf("Ogrenci bolumu %d donemde bitirebilir.",term);
	
	free(heap);
	free(deleted);
	free(nodeIndis);
}


void printMat(int **mat,int N){
	int i,j;
	printf("Adjacency Matrix:\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("| %d |",mat[i][j]);
		}
		printf("\n");
	}
}

void printList(Vertex **vertexs,int N){
	int i,j;
	printf("Adjacency List:\n");
	for(i=0;i<N;i++){
		printf("Course-%d:",vertexs[i]->dersKodu);
		j=0;
		while(vertexs[i]->adjVertexs[j]!=-1){
			printf(" >>> Course-%d ",vertexs[vertexs[i]->adjVertexs[j]]->dersKodu);
			j++;
		}
		printf("\n");
	}
}

void freeList(Vertex **vertexs,int N){
	int i;
	for(i=0;i<N;i++){
		free(vertexs[i]->adjVertexs);
		free(vertexs[i]);
	}
	free(vertexs);
}

int main(){
	Vertex **vertexs;
	int N;
	int **mat;
	int i;
	
	printf("Ders sayisi giriniz: ");
	scanf("%d",&N);
	
	mat=(int**)malloc(N*sizeof(int*));
	for(i=0;i<N;i++){
		mat[i]=(int*)malloc(N*sizeof(int));
	}
	
	createMat(mat,N);
	printMat(mat,N);
	
	vertexs=(Vertex**)malloc(N*sizeof(Vertex*));
	matToList(&vertexs,mat,N);
	printList(vertexs,N);
	
	printIndegree(vertexs,N);
	
	countTerms(vertexs,N);
	
	for(i=0;i<N;i++){
		free(mat[i]);
	}
	free(mat);
	freeList(vertexs,N);
	
	return 0;
}
