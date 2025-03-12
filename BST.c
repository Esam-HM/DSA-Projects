#include <stdio.h>
#include <stdlib.h>


typedef struct Tree{
	int data;
	struct Tree *left;
	struct Tree *right;
}tree;

void createTree(tree **root,int N,int M){
	int i,j,found;
	int randNum;
	int *arr=(int*)malloc(M*sizeof(int));
	tree *tmp;
	tree *curr,*prev;
	for(i=0;i<M;i++){
		do{               //tekrarli sayiyi önlemek için
			found=0;
			randNum=rand()%(N-1)+1;
			arr[i]=randNum;
			for(j=0;j<i;j++){
				if(arr[j]==randNum){
					found=1;
				}
			}
		}while(found==1);
		tmp=(tree*)malloc(sizeof(tree));
		if(tmp==NULL){
			printf("Allocating Error\n");
			return;
		}
		tmp->data=randNum;
		if(*root==NULL){
			tmp->left=NULL;
			tmp->right=NULL;
			*root=tmp;
		}else{
			curr=*root;
			while(curr!=NULL){
				prev=curr;
				if(curr->data<randNum){
					curr=curr->right;
				}else{
					curr=curr->left;
				}
			}
			tmp->left=NULL;
			tmp->right=NULL;
			if(prev->data<tmp->data){
				prev->right=tmp;
			}else{
				prev->left=tmp;
			}	
		}	
	}
	free(arr);
	printf("Tree created successfully\n");
}


void treeToArray(tree *root,int *arr,int *arr2,int *i){
	tree *tmp=root;
	if(tmp==NULL){
		return;
	}
	arr[*i]=tmp->data;
	arr2[*i]=tmp->data;
	(*i)++;
	treeToArray(tmp->left,arr,arr2,i);
	treeToArray(tmp->right,arr,arr2,i);
}

void print_BST(tree *root){
	tree *tmp=root;
	if(tmp==NULL){
		return;
	}
	printf("%d\t",tmp->data);
	print_BST(tmp->left);
	print_BST(tmp->right);
}

int findMax(tree *root){
	
	if(root->right==NULL){
		return root->data;
	}else{
		findMax(root->right);
	}
}

tree* fix_BST(tree *root,int num){
	tree *tmp;
	if(num<root->data){
		root->left=fix_BST(root->left,num);
	}else{
		if(num>root->data){
			root->right=fix_BST(root->right,num);
		}else{
			if(root->left==NULL && root->right==NULL){
				free(root);           // node >> leaf
				return NULL;
			}else{
				if(root->left==NULL){
					tmp=root->right;
					free(root);
					return tmp;
				}else{
					if(root->right==NULL){
						tmp=root->left;
						free(root);
						return tmp;
					}else{
						root->data=findMax(root->left);         //son case
						root->left=fix_BST(root->left,root->data);
					}
				}
			}
		}
	}	
	return root;
}

void meyve_vur(tree **root,int M){
	int p,k;
	int kova[M],ptr=-1;
	int ek_kova[M],ek_ptr=-1;
	int *meyve=(int*)malloc(M*sizeof(int));
	int *new_val=(int*)malloc(M*sizeof(int));
	int count=0,found;
	int j,i=0;
	treeToArray(*root,meyve,new_val,&i);
	while(count!=M){
		printf("\nvurmak istediginiz meyve degeri giriniz: ");
		scanf("%d",&k);
		printf("atis gucu giriniz: ");
		scanf("%d",&p);
		i=0;
		found=0;
		while(found==0){
			if(k==meyve[i]){
				new_val[i]=new_val[i]-p;
				found=1;
			}else{
				i++;	
			}
		}
		if(new_val[i]<=0){
			count++;
			*root=fix_BST(*root,k);
			//agac yeniden duzenlenecek
			kova[++ptr]=k;
		}
		printf(">> '%d' degerine sahip dugum son degeri %d oldu\n",k,new_val[i]);
		printf("\nAgacin son hali (preorder traverse: Node >> Left >> Right)\n");
		print_BST(*root);
	}
	while(ptr>=0){
		ek_kova[++ek_ptr]=kova[ptr--];
	}
	printf("kova: ");
	while(ek_ptr>=0){
		printf("%d\t",ek_kova[ek_ptr--]);
	}
	free(meyve);
	free(new_val);
}

int main(){
	tree *root=NULL;
	int N,M;
	
	srand(time(NULL));
	
	printf("Meyve adedi giriniz: ");
	scanf("%d",&M);
	printf("Maksimum meyve agirligi: ");
	scanf("%d",&N);
	
	createTree(&root,N,M);
	printf("\nOlusturulan agac (preorder traverse: Node >> Left >> Right):\n");
	print_BST(root);
	meyve_vur(&root,M);	
	return 0;
}
