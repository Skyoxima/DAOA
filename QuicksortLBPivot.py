def partitioner(arr, lb, ub):
    start = lb; end = ub; pivot = arr[lb]
    while start < end:
        while (start < len(arr) - 1) and (arr[start] <= pivot):
            start += 1
        while arr[end] > pivot:
            end -= 1
        if(start < end):
            arr[start], arr[end] = arr[end], arr[start]
    
    arr[lb], arr[end] = arr[end], arr[lb]
    return end

def quicksort(arr, lb, ub):
    if(lb < ub):
        prev_pivot = partitioner(arr, lb, ub)
        quicksort(arr, lb, prev_pivot - 1)
        quicksort(arr, prev_pivot + 1, ub)

array = [int(i) for i in input("Enter the sequence of integers: ").split()]
quicksort(array, 0, len(array) - 1)
print("Quicksorted array: ", end = "")
print(*array, sep = ', ')