#include<stdio.h>
#include<stdlib.h>
void selectionSort(int* array,int sizeofArray)
{
  int i,j,temp;
  int min_index;
  i=0;
  while(i<sizeofArray-1){
    j=i;
    min_index=i;
    while(j<sizeofArray){
      if(array[min_index]>array[j])
	min_index=j;
      j++;
    }
    temp=array[min_index];
    array[min_index]=array[i];
    array[i]=temp;
    i++;
  }
  
}
int main()
{
  int array[]={2,3,5,1,4};
  selectionSort(array,5);
  int i;
  for(i=0;i<5;i++)
    printf("%-5d",array[i]);
  printf("\n");
  return 0;
}
