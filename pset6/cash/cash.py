from cs50 import get_float

while True:

    n = get_float('Change owed: ')

    if n > 0:
        break
    print('Change owed: ivalid')

cont = 0
while n > 0:


    if n >= 0.25:
        cont += 1
        n -= 0.25
        n = round(n, 2)

    elif n >= 0.10 and n < 0.25:
        cont += 1
        n -= 0.10
        n = round(n, 2)

    elif n >= 0.05 and n < 0.10:
        cont += 1
        n -= 0.05
        n = round(n, 2)

    elif n >= 0.01 and n < 0.05:
        cont += 1
        n -= 0.01
        n = round(n, 2)

print(cont)
