#include<stdio.h>
#include<stdlib.h>
void swap(int* a, int* b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

int partition(int* array,int low,int high){
  int pivot=high;
  int left=low;
  int right=high-1;
  while(1){
    while(array[left]<array[pivot] && left<=right)
      left++;
    while(array[right]>array[pivot] && left<=right)
      right--;
    if(left>right)
      break;
    swap(&array[left],&array[right]);
    left++;
    right--;
  }
  swap(&array[pivot],&array[left]);
  return left;
}

void quickSort(int* array,int low,int high){
  if(low<high){
    int pivot=partition(array,low,high);
    quickSort(array,low,pivot-1);
    quickSort(array,pivot+1,high);
  }
}
int main()
{
  int array[]={3,5,7,8,0,9,6,4,1,2};
  quickSort(array,0,9);
  int i;
  for(i=0;i<10;i++)
    printf("%-5d",array[i]);
  printf("\n");
  return 0;
}
