from cs50 import get_int


while True:

    n = get_int('Height: ')

    if n >= 1 and n <= 8:
     break
    
    print('Height ivalid.')

for i  in range(n):
    print(' '*(n-1-i), end='')
    print('#'*(1+i))
