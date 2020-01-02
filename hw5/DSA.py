import sys
import math
import random


def main():
    if(len(sys.argv) == 3):
        # ./DSA.py -keygen {key length}
        if(sys.argv[1] == '-keygen'):
            generate_key(sys.argv[2])
        # ./DSA.py -sign {message}
        elif(sys.argv[1] == '-sign'):
            sign(sys.argv[2])
        # ./DSA.py -verify {message}
        elif(sys.argv[1] == '-verify'):
            verify(sys.argv[2])
           
    # end main()


def generate_key(key_length):

# end generate_key()

def sign(message):

# end sign()

def verify(message):

# end verify(message)

def generateLargePrime(key_length):
    while True:
        # generate random bits
        number = random.getrandbits(int(key_length))
        # apply a mask to set MSB and LSB to 1
        number |= (1 << int(key_length) - 1) | 1
        if is_prime(number):
            return number

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

def square_and_multiply(x, h, n):   # Output x**h % n
    y = x
    bitH = [int(x) for x in bin(h)[2:]]
    for i in range(1, len(bitH)):
        y = y**2 % n
        if bitH[i] == 1:
            y = y * x % n
    return y
# end square_and_multiply