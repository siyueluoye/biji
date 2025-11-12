#include<stdio.h>
void swap(int* a,int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int partition(int arr[],int low,int high)
{
    int pivot = arr[high];
    int i = (low-1);
    int j;
    for(j=low;j<high;j++)
    {
        if(arr[j]<pivot)
        {
            i++;
            swap(&arr[i+1],&arr[j]);
        }
    }
    swap(&arr[i+1],&arr[high]);
    return (i+1);
}
void quick_sort(int arr[],int low,int high)
{
    if(low>high)
    {
        int pi=partition(arr,low,high);
        quick_sort(arr,low,pi-1);
        quick_sort(arr,pi+1,high);
    }
}
void printarray(int arr[],int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}
int main(){
    int arr[]={64,34,25,12,22,11,90};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("原始数组:");
    printarray(arr,n);
    quick_sort(arr,0,n-1);
    printf("排序完后的数组：");
    printarray(arr,n);
    return 0;
}










        

