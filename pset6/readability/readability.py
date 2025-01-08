from cs50 import get_string


text = get_string('TEXTO: ')

def indice(t):

    # Deixando somente as letras.
    e = ''.join(c for c in t if c.isalpha())
    l = len(e)
    s = 0
    p = 1

    for f in t:
        # Contanto as sentenças.
        if f in '.!?':
            s += 1
        # Contanto as palavras.
        if f in ' ':
            p += 1
    # Medias por 100.
    ml = (l / p) * 100
    ms = (s / p) * 100

    # Retorno arredondado da fórmula Coleman-Liau
    return round(0.0588 * ml - 0.296 * ms - 15.8)


if indice(text) < 1:
    print('Before Grade 1')

if indice(text) >= 16:
    print("Grade 16+")

if indice(text) >= 1 and indice(text) < 16:
    print(f'Grade {indice(text)}')
