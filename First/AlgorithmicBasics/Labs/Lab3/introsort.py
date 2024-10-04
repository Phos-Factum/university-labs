# Insertion sorting function
def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

# Stackelement (contains data and link to next element)
class StackNode:
    def __init__(self, data):
        self.data = data
        self.next = None

# Checking if stack is empty
def is_empty(root):
    return not root

# Adding new element in root 
def push(root, data):
    stack_node = StackNode(data)
    stack_node.next = root
    root = stack_node
    return root

# Removing element from root and changing on another one
def pop(root):
    if is_empty(root):
        return None, -1
    temp = root
    root = root.next
    popped = temp.data
    return root, popped

# Quicksort partition
def partition(arr, low, high):
    pivot = arr[high]
    i = low - 1
    for j in range(low, high):
        if arr[j] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1

# Introsort (partition)
def introsort(arr, low, high, max_depth):
    if low < high:
        if high - low + 1 <= 10:                       
            insertion_sort(arr[low:high+1])
        elif max_depth == 0:
            arr = heapsort(arr, low, high)              
            return arr
        else:
            pivot_index = partition(arr, low, high)
            introsort(arr, low, pivot_index - 1, max_depth - 1)
            introsort(arr, pivot_index + 1, high, max_depth - 1)

# Pyramidal sorting function (heapsort)
def heapsort(arr, low, high):
    def heapify(arr, n, i):
        largest = i
        left = 2 * i + 1
        right = 2 * i + 2
        if left < n and arr[left] > arr[largest]:
            largest = left
        if right < n and arr[right] > arr[largest]:
            largest = right
        if largest != i:
            arr[i], arr[largest] = arr[largest], arr[i]
            heapify(arr, n, largest)

    n = high - low + 1
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)
    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        heapify(arr, i, 0)
    return arr

# Introsort function
def introspective_sort(stack):
    arr = []
    while not is_empty(stack):
        stack, num = pop(stack)
        arr.append(num)
    
    # Сортируем полученный список
    insertion_sort(arr)  # Можете использовать любой другой метод сортировки

    return arr


if __name__ == "__main__":
    try:
        # Oppening file
        with open("numbers1.txt", "r") as file:
            stack = None
            # Replacing numbers from file to stack
            for line in file:
                num = int(line.strip())
                stack = push(stack, num)
    except FileNotFoundError:
        print("Error while openning file.")
        exit(1)

    # Introsorting
    sorted_numbers = introspective_sort(stack)

    # Output of sorted numbers
    print("Отсортированный список:", sorted_numbers)
