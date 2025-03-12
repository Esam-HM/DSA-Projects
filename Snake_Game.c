#include <stdio.h>
#include <stdlib.h>


int main(){
	int mat[100][100];
	int konum[200];
	int N,M,food_num;
	int hsnake_r,hsnake_c;
	int next=1,length=1,step=0,err=0;
	char direction;
	int i,j,k,r,c,tmp;
	
	srand(time(NULL));
	
	//for(i=0;i<100;i++){             rapor için bu satirlar
	//	konum[i]=-1;
	//}
	
	printf("oyun tahtasinin boyutu giriniz:\nsatir sayisi: ");
	scanf("%d",&N);
	printf("sutun sayisi ");
	scanf("%d",&M);
	
	printf("yemek sayisini giriniz: ");
	i=0;
	do{
		if(i!=0){
			printf("girdiginiz yemek sayisi geçersiz.yemek sayisi tekrar giriniz: ");
		}
		scanf("%d",&food_num);
		i++;
	}while(((N*M)-1)<food_num);
	
	for(i=0;i<N;i++){         //oyun tahtasi bosluk ile doldurma
		for(j=0;j<M;j++){
			mat[i][j]=-1;
		}
	}
	
	hsnake_r=rand()%N;        //yilan konumu rastgele belirleme
	hsnake_c=rand()%M;
	mat[hsnake_r][hsnake_c]=1;
	
	k=1;
	while(k<=food_num){     //yemekler konumu rastgele belirleme
		r=rand()%N;
		c=rand()%M;
		if(mat[r][c]==-1){
			mat[r][c]=0;
			k++;
		}
	}
	
	printf("oyun tahtasinin hali\n");
	for(r=0;r<N;r++){
		printf("| ");
		for(c=0;c<M;c++){
			if(mat[r][c]==-1){
				printf("  | ");
			}else{
				printf("%d | ",mat[r][c]);
			}
		}
		printf("\n");
	}
		
	konum[2]=hsnake_r;
	konum[3]=hsnake_c;
	while(food_num!=0 && next==1){	
		err=0;
		printf("u=yukari , d=down , l=sol , r=sag\n");
		printf("gideceginiz yon seciniz: ");
		scanf(" %c",&direction);
		step++;
		if(direction=='u'){
			hsnake_r--;
			if(hsnake_r<0){
				next=0;
			}else{
				j=mat[hsnake_r][hsnake_c];
				konum[0]=hsnake_r;        			 //bir sonraki hareket için satir ve sutun bilgileri konum 0 ve 1 indislerinde sakli 
				konum[1]=hsnake_c;
			}
		}else{
			if(direction=='d'){
				hsnake_r++;
				if(hsnake_r>N-1){
					next=0;
				}else{
					j=mat[hsnake_r][hsnake_c];
					konum[0]=hsnake_r;
					konum[1]=hsnake_c;
				}
			}else{
				if(direction=='l'){
					hsnake_c--;
					if(hsnake_c<0){
						next=0;
					}else{
						j=mat[hsnake_r][hsnake_c];
						konum[0]=hsnake_r;
						konum[1]=hsnake_c;
					}
				}else{
					if(direction=='r'){
						hsnake_c++;
						if(hsnake_c>M-1){
							next=0;
						}else{
							j=mat[hsnake_r][hsnake_c];
							konum[0]=hsnake_r;
							konum[1]=hsnake_c;
						}
					}else{
						printf("yanlis karakter sectiniz.tekrar deneyin....\n");
						err=1;
						step--;
					}
				}
			}
		}		
		if(err!=1){
			if(next!=0){
				k=1;
				i=2;
				while(k<=length){
					mat[konum[0]][konum[1]]=k;
					tmp=konum[i];
					konum[i]=konum[0];
					konum[0]=tmp;
					tmp=konum[i+1];
					konum[i+1]=konum[1];
					konum[1]=tmp;
					i=i+2;
					k++;
				}
				mat[konum[0]][konum[1]]=-1;
				//printf("yilan kafasi bulundugu goz: satir = %d , sutun= %d\n",hsnake_r,hsnake_c);	     **rapor için bu satirlar.
				//konum[i]=konum[0];       
				//konum[i+1]=konum[1];
				//printf("konum dizisi:{satir,sutun,satir,sutun,....}\n");
		        //i=0;
				//while(konum[i]!=-1){
				//	printf("(%d,%d)\t",konum[i],konum[i+1]);
				//	i=i+2;
				//}
				//printf("\n");			
				printf("oyun tahtasinin hali\n");
				for(r=0;r<N;r++){
					printf("| ");
					for(c=0;c<M;c++){
						if(mat[r][c]==-1){
							printf("  | ");
						}else{
							printf("%d | ",mat[r][c]);
						}
					}
					printf("\n");
				}
				printf("simdiye kadar yapilan hamle sayisi= %d\n",step);
	
				if(j==0){
					food_num--;
					length++;
				}
			}else{
				printf("yilan duvara carpti.kaybettiniz....\n");
				printf("yapilan hamle sayisi= %d\nyilan uzunlugu= %d\nkalan yemek sayisi= %d\n",step,length,food_num);
			}
		}		
	}
	
	
	if(food_num==0){
		printf("oyun bitti.butun yemekleri yediniz...\n");
		printf("yapilan hamle sayisi= %d\nyilan uzunlugu= %d\n",step,length);
	}
	
	return 0;
}
