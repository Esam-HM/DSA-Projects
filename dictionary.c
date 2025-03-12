#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 10
#define fileName "20011908_dictionary.txt"

typedef struct Trie{
	int Key;
	char *word;
	struct Trie *firstChild;
	struct Trie *nextSibling;
}tree;

char* reverseString(char *str){
	char *stack=(char*)malloc(size*sizeof(char));
	int top=-1,i=0;
	for(i=0;str[i];i++){
		stack[++top]=str[i];
	}
	i=0;
	while(top!=-1){
		str[i++]=stack[top--];
	}
	free(stack);
	return str;
}

int findKey(char harf){
	int key;
	if(harf=='y' || harf=='z'){
		key=9;
	}else{
		if(harf=='v'){
			key=8;
		}else{
			if(harf=='s'){
				key=7;
			}else{
				if(harf=='#'){
					key=0;
				}else{
					key=((harf-'a')/3)+2;
				}
			}
		}
	}
	return key;
}

tree* findNode(tree *Node,int Num){        //recursive function
	tree *tmp;
	if(Node==NULL){
		return NULL;            //node not found
	}else{
		if(Node->Key==Num){
			return Node;      //node found
		}else{
			tmp = findNode(Node->nextSibling,Num);       //if not equal check sibling nodes
			return tmp;
		}
	}
}

tree* findLastSibling(tree *Node){
	tree *tmp=Node;
	while(tmp->nextSibling!=NULL){
		tmp=tmp->nextSibling;
	}
	return tmp;        //return last sibling node in the n. level
}

tree* skipNode(tree *Node){        //skip nodes which have # key value (words that have same number)
	tree *tmp=Node->firstChild;
	tree *prev=Node;
	int next=1;
	while(tmp!=NULL && next==1){
		if(tmp->Key=='#'){
			prev=tmp;
			tmp=tmp->firstChild;
		}else{
			next=0;
		}
	}
	return prev;
}

tree* initNode(int key){             //to create new node
	tree *node=(tree*)malloc(sizeof(tree));
	node->firstChild=NULL;
	node->nextSibling=NULL;
	node->word=NULL;
	node->Key=key;
	return node;
}

int createTrie(tree **root){             //create Tree
	FILE *fp=fopen(fileName,"r");
	if(fp==NULL){
		printf("Dosya acarken hata olustu...\n");
		return -1;
	}
	tree *node,*currNode,*prevNode,*tmpNode;
	char *token=(char*)malloc(size*sizeof(char));
	int key,i;
	
	
	*root=initNode(-1);				//bos root olusturma
	
	while(fgets(token,size,fp)!=NULL){
		token=strtok(token,"\n");
		//printf("%s\n",token);
		currNode=*root;
		for(i=0;token[i];i++){
			key=findKey(token[i]);
			tmpNode=findNode(currNode->firstChild,key);
			if(tmpNode==NULL){
				node=initNode(key);
				if(currNode->firstChild==NULL){
					currNode->firstChild=node;
				}else{
					prevNode=findLastSibling(currNode->firstChild);
					prevNode->nextSibling=node;
				}
				currNode=node;
			}else{
				currNode=tmpNode;
				currNode=skipNode(currNode);            //if node value == #
			}
		}
		if(currNode->word==NULL){
			currNode->word=(char*)malloc((strlen(token)+1)*sizeof(char));
			strcpy(currNode->word,token);
		}else{
			node=initNode('#');
			node->word=(char*)malloc((strlen(token)+1)*sizeof(char));
			strcpy(node->word,token);
			if(currNode->firstChild==NULL){
				currNode->firstChild=node;
			}else{
				prevNode=currNode->firstChild;
				currNode->firstChild=node;
				node->firstChild=prevNode;
			}
		}
	}
	
	free(token);
	fclose(fp);
	return 0;
}

void findWord(tree *root,char *str){
	tree *currNode=root;
	tree *tmpNode;
	int num,temp;
	int found,i=0,bitir=0;
	str=reverseString(str);       		//if word size is m then >>>> O(m)
	num=atoi(str);
	while(bitir==0 && i<strlen(str)){
		temp=num%10;
		num=(num-temp)/10;
		tmpNode=findNode(currNode->firstChild,temp);      //if level has 10 nodes then worst case to reach last node is O(10)
		if(tmpNode==NULL){
			bitir=1;
		}else{
			i++;
			if(i!=strlen(str)){
				tmpNode=skipNode(tmpNode);    //ihmal edilebilir
			}
			currNode=tmpNode;
		}
	}
	if(bitir==1){
		printf("Sozlukte bu sayinin karsiligi bir kelime yoktur.\n");
	}else{
		if(currNode->word==NULL){
			printf("Sozlukte bu sayinin karsiligi bir kelime yoktur.\n");
		}else{
			printf(">> %s\n",currNode->word);
			found=1;
			currNode=currNode->firstChild;
			while(currNode!=NULL && found==1){     //ihmal edilebilr.
				if(currNode->Key=='#'){
					printf(">> %s\n",currNode->word);
					currNode=currNode->firstChild;
				}else{
					found=0;
				}
			}
		}
	}
}

void freeTree(tree *node) {
    if (node == NULL) {
        return;
    }
    freeTree(node->firstChild);
    freeTree(node->nextSibling);
    free(node->word);
    free(node);
}

void traverseTree(tree *node){
	static int i=0;
	if(node==NULL){
		return;
	}
	if(node->word!=NULL){
		if(node->Key=='#'){
			printf("%d)>> key= %c ",++i,node->Key);
		}else{
			printf("%d)>> key= %d ",++i,node->Key);
		}
		printf(", word= %s\n",node->word);
	}else{
		printf("%d)>> key= %d , word= NULL\n",++i,node->Key);
	}
	traverseTree(node->firstChild);
	traverseTree(node->nextSibling);
}

int main(){
	tree *root=NULL;
	char *inStr=(char*)malloc(size*sizeof(char));
	int kontrol,run=1;
	kontrol=createTrie(&root);
	if(kontrol==-1){            //dosya acarken hata olustuysa
		return 0;
	}
	if(root->firstChild==NULL){
		printf("Sozluk bos oldugu icin islem sonlandirildi.\nDosyayi kontrol ediniz!!\n");
		freeTree(root);
		return 0;
	}
	while(run==1){
		printf("Enter number or q to Exit: ");
		scanf("%s",inStr);
		if(strcmp(inStr,"q")!=0){
			findWord(root,inStr);
		}else{
			run=0;
			printf("Program finished...\n");
		}		
		
	}
	//printf("Agac bu sekilde:(first child >> next sibling)\n");
	//traverseTree(root->firstChild);
	freeTree(root);
	free(inStr);
	return 0;
}
