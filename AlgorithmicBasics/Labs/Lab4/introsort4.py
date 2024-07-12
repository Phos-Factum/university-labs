class Node:
    def __init__(self, data):
        self.data = data
        self.next = None


class CircularQueue:
    def __init__(self):
        self.head = None
        self.tail = None

    def enqueue(self, data):
        new_node = Node(data)
        if not self.head:
            self.head = new_node
        else:
            self.tail.next = new_node
        self.tail = new_node
        self.tail.next = self.head

    def dequeue(self):
        if not self.head:
            return None
        data = self.head.data
        if self.head == self.tail:
            self.head = None
            self.tail = None
        else:
            self.head = self.head.next
            self.tail.next = self.head
        return data

    def is_empty(self):
        return self.head is None


def introsort(arr):
    MAX_DEPTH = 20
    threshold = 2 * int(len(arr) ** 0.5)

    def insertion_sort(arr, left, right):
        for i in range(left + 1, right + 1):
            key = arr[i]
            j = i - 1
            while j >= left and arr[j] > key:
                arr[j + 1] = arr[j]
                j -= 1
            arr[j + 1] = key

    def partition(arr, left, right):
        pivot = arr[right]
        i = left - 1
        for j in range(left, right):
            if arr[j] <= pivot:
                i += 1
                arr[i], arr[j] = arr[j], arr[i]
        arr[i + 1], arr[right] = arr[right], arr[i + 1]
        return i + 1

    def introsort_util(arr, left, right, depth):
        if right - left <= threshold:
            insertion_sort(arr, left, right)
            return

        if depth == 0:
            arr[left:right + 1] = sorted(arr[left:right + 1])
            return

        if left < right:
            partition_index = partition(arr, left, right)
            introsort_util(arr, left, partition_index - 1, depth - 1)
            introsort_util(arr, partition_index + 1, right, depth - 1)

    introsort_util(arr, 0, len(arr) - 1, MAX_DEPTH)


def introspective_sort_from_file(filename):
    queue = CircularQueue()

    # Read numbers from file and enqueue them
    with open(filename, 'r') as file:
        for line in file:
            for num_str in line.split():
                num = int(num_str)
                queue.enqueue(num)

    # Dequeue numbers, sort them using introsort, and enqueue them again
    numbers = []
    while not queue.is_empty():
        numbers.append(queue.dequeue())

    introsort(numbers)

    for num in numbers:
        print(num)


# Example usage: (file you want to work with)
introspective_sort_from_file("numbers.txt")
