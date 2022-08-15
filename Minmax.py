def minmax(arr, lb, ub):
    if(lb == ub): #strictly one array element in consideration
        return(arr[lb], arr[lb])
    elif(ub - lb == 1): #strictly two array elements in consideration
        if(arr[lb] < arr[ub]):
            return(arr[lb], arr[ub])
        else:
            return(arr[ub], arr[lb])
    else: #more than 2 elements sub-arrays
        mid = (lb + ub) // 2
        [l_sub_min, l_sub_max] = minmax(arr, lb, mid)
        [r_sub_min, r_sub_max] = minmax(arr, mid + 1, ub)

        #For combinations, code reachable only when sub-array(s) at hand as 2 elements at the most
        if(l_sub_min < r_sub_min):
            mini = l_sub_min
        else:
            mini = r_sub_min
        
        if(l_sub_max < r_sub_max):
            maxi = r_sub_max
        else:
            maxi = l_sub_max
        
        return(mini, maxi)
#* if block is the recursion ending statement group

array = [int(array_ele) for array_ele in input("Enter the array elements\n(Delimiter = space): ").split()]
[mini, maxi] = minmax(array, 0, len(array) - 1)
print("\nMaximum: {}\nMinimum: {}".format(maxi, mini))