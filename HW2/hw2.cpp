#include <iostream>

int almostBinarySearch(int arr[],int min,int max,int val ){
    if(max >= 1){
        int mid = min + ((max-min)/4);
        std::cout << mid << std::endl;
        if(val == arr[mid]){
            return mid;
        }else if(val > arr[mid]){
            return almostBinarySearch(arr,mid+1,max,val);
        }else if(val < arr[mid]){
            return almostBinarySearch(arr,min,mid-1,val);
        }
    }
    return -1;
}

int binarySearch(int arr[],int min,int max,int val){
    if(max >= 1){
        int mid = min + ((max-min)/2);
        std::cout << mid << std::endl;
        if(val == arr[mid]){
            return mid;
        }else if(val > arr[mid]){
            return almostBinarySearch(arr,mid+1,max,val);
        }else if(val < arr[mid]){
            return almostBinarySearch(arr,min,mid-1,val);
        }
    }
    return -1;
}



int main(){
    int arr[] = {1,2,3,4,5,6,7,8,9,12};
    int result = almostBinarySearch(arr,0,9,12);
    //int resultTwo = binarySearch(arr,0,9,12);
    if(result == -1){
        std::cout << "Value not found." << std::endl;
    }else{
        std::cout << "Value found at index: " << result << std::endl;
    }
}