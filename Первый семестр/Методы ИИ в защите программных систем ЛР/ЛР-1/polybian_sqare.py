import string
def text_decryption(text: str, polybian_square) -> str:
    new_text = ""
    for symbol in text:
        for i in range(len(polybian_square)):
            for j in range(len(polybian_square[0])):
                if symbol == polybian_square[i][j]:
                    new_text += polybian_square[(i-1)%len(polybian_square)][j]
    return new_text

def text_encryption(text: str, polybian_square) -> str:
    new_text = ""
    for symbol in text:
        for i in range(len(polybian_square)):
            for j in range(len(polybian_square[0])):
                if symbol == polybian_square[i][j]:
                    new_text += polybian_square[(i+1)%len(polybian_square)][j]
    return new_text

if __name__ == "__main__":
    text = "asdf world!"
    polybian_square = [['q', 'w', 'e', 'r', 't'],
                      ['a', 's', 'd', 'f', 'm'],
                      ['z', 'x', 'c', 'v', 'b'],
                      ['y', 'u', 'i', 'o', 'p'],
                      ['h', 'j', 'k', 'l', 'n'],
                      ['g', ' ', ',', '.', '!']]

    # Первичная обработка текста
    simbols = string.ascii_letters + " "+ "," + "." + "!"
    text = "".join(x for x in text if x in (simbols)).lower().strip()
    print("Исходный текст: " + text)
    text = text_encryption(text, polybian_square)
    print("Зашифрованный текст: " + text)
    text = text_decryption(text, polybian_square)
    print("Расшифрованный текст: " + text)
    
