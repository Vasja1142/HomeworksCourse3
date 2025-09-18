
import string

def text_decryption(text: str, key_word: str, key_num: int) -> str:
    pass

def text_encryption(text: str, key_word: str, key_num: int) -> str:
    symbols = dict()
    letters = string.ascii_letters + " "
    for let in key_word:
        letters.replace(let, '')

    counter = 0
    for i in range(key_num, len(key_word)):
        symbols[i] = key_word[counter]
        counter += 1
    counter = 0
    for i in range(key_num+len(key_word), len(string.ascii_letters)+1):
        symbols[i] = letters[counter]
        counter += 1
    
    for i in range(key_num):
        symbols[i] = letters[counter]
        counter += 1
    
    
    for 

    pass    

if __name__ == "__main__":
    text = "Hello world"
    key_word = "python"
    key_num = "11"

    # Первичная обработка текста
    key_word = "".join(x for x in key_word if x in (string.ascii_letters + " ")).lower().strip()
    text = "".join(x for x in text if x in (string.ascii_letters + " ")).lower().strip()


    print(f"~~~~Сообщение: \"{text}\" ~~~~\nКлючевое слово: {key_word}, ключевое число: {key_num}")
    # encrypted_text = text_encryption(text, key_word, key_num)
    # print(f"Зашифрованное сообщение: \"{encrypted_text}\"")

    # decrypted_text = text_decryption(encrypted_text, key_word, key_num)
    # print(f"Расшифрованное сообщение: \"{decrypted_text}\"")
    
    # if text == decrypted_text:
    #     print("Задача выполнена!")
    # else:
    #     print("Ошибка в алгоритме! Разработчик лошара!")