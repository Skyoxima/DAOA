def partitioner(array, lb, ub):
  pivot = array[ub]; i = lb - 1
  for j in range(lb, ub):
    if array[j] <= pivot:
      i += 1
      (array[i], array[j]) = (array[j], array[i])
  
  (array[i + 1], array[ub]) = (array[ub], array[i + 1])
  return i + 1

def quicksort(array, lb, ub):
  if lb < ub:
    pi = partitioner(array, lb, ub)
    quicksort(array, lb, pi - 1)
    quicksort(array, pi + 1, ub)

array = [int(i) for i in input("Enter the sequence of integers: ").split()]
quicksort(array, 0, len(array) - 1)
print("Quicksorted array: ", end = "")
print(*array, sep = ', ')