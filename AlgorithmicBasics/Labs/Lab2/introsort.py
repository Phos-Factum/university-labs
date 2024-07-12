import math

try:
    with open("numbers.txt", 'r') as f:
        data = [list(map(int, line.split())) for line in f]      # List with arrays (splitted)
        
        for a in data:                                           # List with numbers 
            print("\nStarting position:\n", a)
            s = []                                               # Output list (heapsort)
            k = len(a)                                           # Length of original list

            if (k > 16):                                         # Heapsort
                for i in range(len(a)):
                    if len(s) == 0:
                        s.append(a[0])
                    else:
                        n = s.index(a[0])
                        if a[i] in s:
                            t = s.index(a[i])
                            s.insert(t, a[i])
                        elif a[i] > a[0]:
                            while (n < len(s)) and (a[i] > s[n]):
                                if a[i] in s:
                                    s.remove(a[i])
                                s.insert(n, a[i])
                                n += 1
                        else:
                            while (n > -1) and (a[i] < s[n]):
                                if a[i] in s:
                                    s.remove(a[i])
                                s.insert(n, a[i])
                                n -= 1
                print("\nUsing 'Heapsort':\n", s)
            else:                                                   # Insertion sort
                for i in range(1, len(a)):
                    key = a[i]                                      # Intermediate var for insertsort
                    j = i - 1
                    while j >= 0 and a[j] > key:
                        a[j + 1] = a[j]
                        j -= 1
                        a[j + 1] = key
                print("\nUsing 'Insertion Sort':\n", a)


except FileNotFoundError:
    print("File doesn't exist!")
except ValueError:
    print("File has incorrect values!")

