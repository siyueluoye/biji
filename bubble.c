#include<stdio.h>
void bubble_sort(int arr[],int n)
{
    int i,j,temp;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}
void printarray(int arr[],int n)
{
    int i;
    for(i=0;i<=n-1;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}
int main()
{
    int arr[]={64,34,25,12,22,11,90};
    int n= sizeof(arr)/sizeof(arr[0]);
    printf("原始数组：");
    printarray(arr,n);
    bubble_sort(arr,n);
    printf("排序之后的数组：");
    printarray(arr,n);
    return 0;
}
