#include<stdio.h>
#include<stdlib.h>

void merge(int* array,int l,int m,int r){
  int i,j,k;
  int a1=m-l+1;
  int a2=r-m;
  int L[a1],R[a2];
  for(i=0;i<a1;i++)
    L[i]=array[l+i];
  for(j=0;j<a2;j++)
    R[j]=array[m+j+1];

  i=0;
  j=0;
  k=l;
  while(i<a1 && j<a2){
    if(L[i]<=R[j]){
      array[k]=L[i];
      i++;
    }
    else{
      array[k]=R[j];
      j++;
    }
    k++;
  }
  while(i<a1){
    array[k++]=L[i++];
  }
  while(j<a2){
    array[k++]=R[j++];
  }
}

void mergeSort(int* array,int l,int r){
  if(l<r){
    int m=(l+r)/2;
    mergeSort(array,l,m);
    mergeSort(array,m+1,r);
    merge(array,l,m,r);
  }
}
int main(){
  int array[]={7,4,5,6,8,1,2,3,0,9};
  mergeSort(array,0,9);
  int i;
  for(i=0;i<10;i++)
    printf("%-5d",array[i]);
  printf("\n");
  return 0;
}
