#Python program to implement Mergesorting on a given array
from numpy import floor

def mergesort(arr, lb, ub):
    if(lb < ub): #similar to quicksorting, atleast 2 distinct array elements required
     mid = int(floor((lb + ub) / 2)) 
     mergesort(arr, lb, mid)
     mergesort(arr, mid + 1, ub)
     aux_arr = merge(arr, lb, mid, ub)


def merge(arr, lb, mid, ub):
    aux_arr = [] #auxiliary array to temporarily store sorted sub-arrays
    i = lb ; j = mid + 1
    
    while(i <= mid and j <= ub):
        if(arr[i] < arr[j]):
            aux_arr.append(arr[i])
            i += 1
        else:
            aux_arr.append(arr[j])
            j += 1
       
    while(i <= mid): #emptying sub-array if necessary
        aux_arr.append(arr[i])
        i += 1  
    
    while(j <= ub):
        aux_arr.append(arr[j])
        j += 1  

    i = lb ; j = 0
    while(i <= ub):
        arr[i] = aux_arr[j]  # main array being sorted using auxiliary array's content for each call of merge function
        i += 1
        j += 1


array = []
x = 0
while(x != -1):
    x = int(input("Enter array element, (-1 to stop): "))
    if(x != -1):
        array.append(x)

mergesort(array, 0, len(array) - 1)

print("\nMergesorted array:", end = ' ')
for i in array: 
    print(i, end = ' ')