import sys
import math
import random


def main():
    # ./RSA.py init {size}
    if(len(sys.argv) == 3):
        if(sys.argv[1] == 'init'):
            generate_key(int(sys.argv[2]))
    elif(len(sys.argv) == 5):
        # .RSA.py -e {plaintext} {n} {e}
        if(sys.argv[1] == '-e'):
            print(encrypt(sys.argv[2], int(sys.argv[3]), int(sys.argv[4])))
    # .RSA.py -d {plaintext} {n} {d}
        elif(sys.argv[1] == '-d'):
            print(decrypt(sys.argv[2], int(sys.argv[3]), int(sys.argv[4])))
    # end main()


def generate_key(size):
    # 產生隨機質數 p 和 q
    p = None
    while(p == None):
        temp = random.randrange(2**(size-1), 2**size)
        if(is_prime(temp)):
            p = temp
    print('p:', p)
    q = None
    while(q == None):
        temp = random.randrange(2**(size-1), 2**size)
        if(is_prime(temp) and temp != p):
            q = temp
    print('q:', q)
    n = p*q
    print('n:', n)
    phiN = (p-1)*(q-1)
    # 從 1 - phiN 中取一個與 phiN 互質的 e
    e = None
    while(e == None):
        temp = random.randrange(2**(size-1), 2**size)
        if(math.gcd(temp, phiN) == 1):
            e = temp
            break
    print('e:', e)
    # 找一個 d 使 d * e ≡ 1 mod phiN
    d = find_mode_inverse(e, phiN)
    print('d:', d)
    return p, q, n, e, d
# end generate_key()


def square_and_multiply(x, h, n):   # Output x**h % n
    y = x
    bitH = [int(x) for x in bin(h)[2:]]
    for i in range(1, len(bitH)):
        y = y**2 % n
        if bitH[i] == 1:
            y = y * x % n
    return y
# end square_and_multiply


def find_mode_inverse(a, m):
    if math.gcd(a, m) != 1:
        return None
    u1, u2, u3 = 1, 0, a
    v1, v2, v3 = 0, 1, m

    while v3 != 0:
        q = u3 // v3
        v1, v2, v3, u1, u2, u3 = (
            u1 - q * v1), (u2 - q * v2), (u3 - q * v3), v1, v2, v3
    return u1 % m


def is_prime(number):   # 判斷質數

    if(number < 2):
        return False
    elif(number == 2):
        return True
    elif(number % 2 == 0):
        return False
    # 測試 2 - sqrt(n) 中有無 n 的因數
    elif(number < 1000):
        temp = math.ceil(math.sqrt(number))
        for i in range(3, temp, 2):
            if(number % i == 0):
                return False
        return True
    else:
        return rabin_miller(number)
# end is_prime()


def rabin_miller(number):
    # 找 u 和 r 使 p' -1 = 2**u * r
    r = number - 1
    u = 0
    while r % 2 == 0:
        r = r // 2
        u += 1
    # 做五次測試
    for test in range(5):
        # 找 a 使 a**r % p' != 1
        a = random.randrange(2, number - 1)
        temp = square_and_multiply(a, r, number)
        if temp != 1:
            # 找 a 使 a**r**2j != (p'-1) % p'
            j = 0
            while temp != (number - 1):
                if j == u - 1:
                    # 找到的話為合數
                    return False
                else:
                    j = j + 1
                    temp = square_and_multiply(temp, 2, number)
    # 找不到就有可能是質數
    return True
# end rabin_miller(num)


def encrypt(plaintext, n, e):
    y = 0
    for i in range(len(plaintext)):
        y += (ord(plaintext[i])-33) * 90**(len(plaintext)-i)
    y = square_and_multiply(y, e, n)
    ciphertext = ''
    for i in range(len(plaintext)):
        char = y % 90
        y //= 90
        char = chr(char+33)
        ciphertext = ciphertext + char
    return ciphertext
    # end encrypt()


def decrypt(ciphertext, n, d):
    x = 0
    for i in range(len(ciphertext)):
        x += (ord(ciphertext[i])-33) * 90**(len(ciphertext)-i)
    x = square_and_multiply(x, d, n)
    plaintext = ''
    for i in range(len(ciphertext)):
        char = x % 90
        x //= 90
        char = chr(char+33)
        plaintext = plaintext + char
    return plaintext
    # end encrypt()


if __name__ == "__main__":
    main()
