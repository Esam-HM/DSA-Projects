#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Carklar{
	int sayi;
	struct Carklar *next;
	struct Carklar *prev;
}cark;

void NodeBagla(cark **head,cark **tail,cark **tmp,int i,int M){
	if(*head==NULL){
		(*tmp)->next=NULL;
		(*tmp)->prev=NULL;
		*tail=*tmp;
	}else{
		(*tmp)->next=*head;
		(*tmp)->prev=NULL;
		(*head)->prev=*tmp;
		if(i==M-1){
			(*tail)->next=*tmp;
			(*tmp)->prev=*tail;
		}
	}
	*head=*tmp;
}

void printCark(cark *head){
	cark *tmp=head;
	do{
		printf("%d\t",tmp->sayi);
		tmp=tmp->next;
	}while(tmp!=head);
}

int Cmp(cark *head,int x){
	int hata=0,run=1;
	cark *tmp=head;
	
	while(tmp!=NULL && run==1 && hata==0){
		if(tmp->sayi==x){
			hata=1;
		}else{
			tmp=tmp->next;
			if(tmp==head){
				run=0;
			}
		}
	}
	return hata;
}


void CarkOlustur(cark **head1,cark **head2,cark **head3,int N,int M){
	int i,j,run,valid;
	int ortkSayi=rand()%(N-1)+1;
	int *arr=(int*)calloc(N+1,sizeof(int));
	if(arr==NULL){
		printf("Allocating Error!...\n");
	}
	int konum[3];
	cark *cark1;
	cark *cark2;
	cark *cark3;
	cark *tail1;
	cark *tail2;
	cark *tail3;
	i=0;
	while(i<3){
		valid=1;
		konum[i]=rand()%M;
		for(j=i-1;j>=0;j--){
			if(konum[i]==konum[j]){
				valid=0;
			}
		}
		if(valid==1){
			i++;
		}
	}
	arr[ortkSayi]=3;
	for(i=0;i<M;i++){
		cark1=(cark*)malloc(sizeof(cark));
		if(i!=konum[0]){
			run=1;
			while(run==1){
				cark1->sayi=rand()%(N-1)+1;
				arr[cark1->sayi]++;
				if(Cmp(*head1,cark1->sayi)==0){
					if(arr[cark1->sayi]<3){
						run=0;
					}
				}
			}		
		}else{
			cark1->sayi=ortkSayi;
		}
		NodeBagla(head1,&tail1,&cark1,i,M);
		cark2=(cark*)malloc(sizeof(cark));
		//------------------------------------------
		if(i!=konum[1]){
			run=1;
			while(run==1){
				cark2->sayi=rand()%(N-1)+1;
				arr[cark2->sayi]++;
				if(Cmp(*head2,cark2->sayi)==0){
					if(arr[cark2->sayi]<3){
						run=0;
					}
				}
			}		
		}else{
			cark2->sayi=ortkSayi;
		}
		NodeBagla(head2,&tail2,&cark2,i,M);
		cark3=(cark*)malloc(sizeof(cark));
		//--------------------------------------------
		if(i!=konum[2]){
			run=1;
			while(run==1){
				cark3->sayi=rand()%(N-1)+1;
				arr[cark3->sayi]++;
				if(Cmp(*head3,cark3->sayi)==0){
					if(arr[cark3->sayi]<3){
						run=0;
					}
				}
			}	
		}else{
			cark3->sayi=ortkSayi;
		}
		NodeBagla(head3,&tail3,&cark3,i,M);
		//printf(">>> %d. pass: %d , %d , %d\n",i,cark1->sayi,cark2->sayi,cark3->sayi);
	}
	
	free(arr);
}

void freeList(cark **head){
	cark *tmp1=*head;
	cark *curr;
	while(*head!=tmp1){
		curr=*head;
		(*head)=(*head)->next;
		free(curr);
	}
	free(*head);
}

int findOrtkSayi(cark *head1,cark *head2,cark *head3,int *konum){
	int ortkSayi,found=0;
	int i=1,j,k;
	cark *cark1=head1;
	cark *cark2=head2;
	cark *cark3=head3;
	printf("Hareketler:\n");
	do{
		konum[0]=i;
		j=1;
		do{
			konum[1]=j;
			if(cark1->sayi==cark2->sayi){
				k=1;
				do{
					konum[2]=k;
					if(cark1->sayi==cark3->sayi){
						found=1;
						ortkSayi=cark3->sayi;
					}
					k++;
					cark3=cark3->next;
				}while(cark3!=head3 && found==0);
			}
			j++;
			cark2=cark2->next;
		}while(cark2!=head2 && found==0);
		i++;
		cark1=cark1->next;
	}while(cark1!=head1 && found==0);
	printf("Ortak sayi: %d\n",ortkSayi);
	for(i=0;i<3;i++){
		printf("%d. carktaki konumu: %d\n",i+1,konum[i]);
	}
	return ortkSayi;
}

void dondur(cark **head,int yon,int M){
	int run=1;
	int tmp,index=1;
	cark *crk=*head;
	if(yon>0){
		while(run==1){
			tmp=index+yon;
			while(tmp>M){
				tmp=tmp-M;
			}
			if(tmp==1){
				run=0;
			}else{
				crk=crk->next;
				index++;			
			}
		}
	}else{
		while(run==1){
			tmp=index+yon;
			while(tmp<=0){
				tmp=index+M;
			}
			if(tmp==1){
				run=0;
			}else{
				crk=crk->next;
				index++;
			}
		}	
	}
	*head=crk;
}

void hareketSayma(cark **head,int *konum,int M,int i){
	int xx,yy;
	int yon;
			
	if(konum[i]>konum[0]){
		xx=konum[i]-konum[0];
		yy=M-xx;
	}else{
		yy=konum[0]-konum[i];
		xx=M-yy;
	}
	if(xx<yy){
		printf("%d. cark saat yonunun tersinde %d adim cevrilmeli.\n",i+1,xx);
		yon=-1*xx;
	}else{
		printf("%d. cark saat yonunde %d adim cevrilmeli.\n",i+1,yy);
		yon=yy;
	}
	
	dondur(head,yon,M);
	
}


int main(){
	int N,M;
	int hata,i;
	int ortkSayi;
	int *konum=(int*)malloc(3*sizeof(int));
	cark *head1=NULL;
	cark *head2=NULL;
	cark *head3=NULL;
	
	srand(time(NULL));
	
	do{
		hata=0;
		printf("Sayi adedi (M sayisi) giriniz: ");
		scanf("%d",&M);
		printf("Kullanilacak sayi araligi [1,N] ise N sayisi giriniz: ");
		scanf("%d",&N);
		if(3*(M-1)>2*(N-1) && M>N){
			hata=1;
			printf("Girdiginiz degerler uygun degil.\nTekrar giriniz...\n");
		}
	}while(hata==1);
	
	CarkOlustur(&head1,&head2,&head3,N,M);
	printf("1.cark: ");
	printCark(head1);
	printf("\n2.cark: ");
	printCark(head2);
	printf("\n3.cark: ");
	printCark(head3);
	printf("\n");
	ortkSayi=findOrtkSayi(head1,head2,head3,konum);
	printf("\nHareket yonleri:\n");
	hareketSayma(&head2,konum,M,1);
	hareketSayma(&head3,konum,M,2);
	printf("Cevrildikten sonraki carklarin hali:\n");
	printf("1.cark: ");
	printCark(head1);
	printf("\n2.cark: ");
	printCark(head2);
	printf("\n3.cark: ");
	printCark(head3);	
	freeList(&head1);
	freeList(&head2);
	freeList(&head3);
	free(konum);
	return 0;
}
