#include<stdio.h>
#include<stdlib.h>
void insertionSort(int* array,int sizeofArray)
{
  int i,j,temp;
  i=1;
  while(i<sizeofArray){
    j=i-1;
    temp=array[i];
    while(j>=0 && array[j]>temp){
      array[j+1]=array[j];
      j--;
    }
    array[j+1]=temp;
    i++;
  }
}
int main()
{
  int array[]={3,4,7,2,1,8,9,0,5,6};
  insertionSort(array,10);
  int i;
  for(i=0;i<10;i++)
    printf("%-5d",array[i]);
  printf("\n");
  return 0;
}
