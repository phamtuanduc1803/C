#include<stdio.h>
#include<stdlib.h>
void swap(int *a,int *b){
  int temp=*a;
  *a=*b;
  *b=temp;
}

void heapify(int* array,int n,int i){
  int largest=i;
  int l=2*i+1;
  int r=2*i+2;

  if(l<n && array[l]>array[largest])
    largest=l;
  if(r<n && array[r]>array[largest])
    largest=r;
  if(largest!=i){
    swap(&array[i],&array[largest]);
    heapify(array,n,largest);
  }
}

void heapSort(int* array,int n){
  int i;
  for(i=n/2-1;i>=0;i--){
    heapify(array,n,i);
  }
  for(i=n-1;i>=0;i--){
    swap(&array[0],&array[i]);
    heapify(array,i,0);
  }
}

int main(){
  int array[]={3,4,7,8,0,1,2,5,6,9};
  heapSort(array,10);
  int i;
  for(i=0;i<10;i++)
    printf("%-5d",array[i]);
  printf("\n");
  return 0;
}
