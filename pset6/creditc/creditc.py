from cs50 import get_int


def luhn_algorithm(n):

    n = str(n)
    parity = len(n) % 2
    soma = 0
    soma2 = 0

# Indo na str da direita para esquerda
    for i in range(len(n)-1, -1, -1):
        digito = int(n[i])
        #Encontrando o penúltimo digito indo de 2 em 2
        if i % 2 == parity:
            digito *= 2
            if digito > 9:
                n1 = 0
                for j in str(digito):
                    n1 += int(j)
                digito = n1
            soma += digito

        # dígitos que não foram multiplicados por 2
        else:
            soma2 += digito

    return (soma + soma2) % 10 == 0

while True:

    n = get_int("Digite o número do cartão de crédito:  ")
    if n > 0:
        break

if luhn_algorithm(n):

    n = str(n)

    if n[0:2] == '34' or n[0:2] == '37':

        print("AMEX")

    elif n[0:2] == '51' or n[0:2] == '52' or n[0:2] == '53' or n[0:2] == '54' or n[0:2] == '55':

        print('MasterCard')

    elif n[0] == '4':

        print('Visa')

else:

    print('O número do cartão de crédito é inválido.')
