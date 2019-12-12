import math


def ext_gcd(a, b):
    if a == 0:
        return b, 0, 1
    else:
        g, y, x = ext_gcd(b % a, a)
        return g, x - (b // a) * y, y


def mod_one(a, m):
    g, x, y = ext_gcd(a, m)
    if g != 1:
        print("modular inverse does not exist")
    else:
        return x % m


def main():

    p = 101
    q = 113
    n = p * q

    phi = (p - 1) * (q - 1)

    e = 0
    for i in range(2, phi):
        if math.gcd(i, phi) == 1:
            e = i
            break

    d = mod_one(e, phi)

    print("p: ", p, ", q: ", q, ", n: ", n, ", e: ", e, ", d:", d)

    type = input("Encrypt or Decrypt?")

    plain = ""
    cipher = ""

    if type == "Encrypt":
        plain = input("Enter plaintext")
        for i in range(len(plain)):
            cipher += chr(pow(ord(plain[i]), e, n))
        print("Ciphertext: ", cipher)
    elif type == "Decrypt":
        cipher = input("Enter ciphertext")
        for i in range(len(cipher)):
            plain += chr(pow(ord(cipher[i]), d, n))
        print("Plaintext: ", plain)


if __name__ == '__main__':
    main()