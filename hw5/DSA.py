import sys
import math
import random
import hashlib

def main():
	if(len(sys.argv) == 3):
		# ./DSA.py -keygen {key length}
		if(sys.argv[1] == '-keygen'):
			generate_key(int(sys.argv[2]))
		# ./DSA.py -sign {message}
		elif(sys.argv[1] == '-sign'):
			sign(sys.argv[2])
		# ./DSA.py -verify {message}
		elif(sys.argv[1] == '-verify'):
			verify(sys.argv[2])
# end main()


def generate_key(key_length):
	q = generate_prime(key_length)
	p = q << (1024-160)
	while (not (is_prime(p + 1)) and (len(bin(p)[2:]) == 1024)):
		p = p + q
	p = p + 1

	while ((len(bin(p)[2:]) != 1024)):
		q = generate_prime(key_length)
		p = q << (1024-160)
		while (not (is_prime(p + 1)) and (len(bin(p)[2:]) == 1024)):
			p = p + q
		p = p + 1
	
	alpha = None
	for h in range(2, p-1):
		# a = h^((p-1)//q) % p
		alpha = square_and_multiply(h, (p - 1) // q, p)
		if(square_and_multiply(alpha,q,p) == 1):
			break;

	d = random.randrange(1, q)
	beta = square_and_multiply(alpha, d, p)

	fp = open("public_key.txt", "w")
	fp.write(str(p) + "\n")
	fp.write(str(q) + "\n")
	fp.write(str(alpha) + "\n")
	fp.write(str(beta) + "\n")
	fp.close()

	fp = open("private_key.txt", "w")
	fp.write(str(d) + "\n")
	fp.close()
# end generate_key()

def sign(message):
	# 讀公鑰
	file = open('public_key.txt','r')
	p = int(file.readline())
	q = int(file.readline())
	a = int(file.readline())
	b = int(file.readline())
	file.close()
	# 讀私鑰
	file = open('private_key.txt','r')
	d = int(file.readline())
	file.close()
	
	# 0 < k < q
	k = random.randrange(1,q)
	# r = (a^k % p) % q 
	r = square_and_multiply(a, k, p) % q
	# s = (SHA(x) + d * r) * k^-1 % q
	sha_x = int(hashlib.sha1(message.encode('utf8')).hexdigest(),16)
	s = (( sha_x + d * r) * find_mode_inverse(k,q)) % q
	# 存簽章
	file = open('signature.txt','w')
	file.write( str(r) + '\n' + str(s))
	file.close()
# end sign()

def verify(message):
	# 讀公鑰
	file = open('public_key.txt','r')
	p = int(file.readline())
	q = int(file.readline())
	a = int(file.readline())
	b = int(file.readline())
	file.close()
	# 讀簽章
	file = open('signature.txt','r')
	r = int(file.readline())
	s = int(file.readline())
	file.close()
	
	# w = s^-1 % q
	w = find_mode_inverse(s,q) % q
	# u1 = w * SHA(x) % q
	sha_x = int(hashlib.sha1(message.encode('utf8')).hexdigest(),16)
	u1 = w * sha_x % q
	# u2 = w * r % q
	u2 = w * r % q
	# v = (a^u1 * b^u2 % p) % q
	v = (square_and_multiply(a,u1,p)*square_and_multiply(b,u2,p)) % q
	if(v == r):
		print('valid')
	else:
		print('invalid')
# end verify(message)

def generate_prime(key_length):
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

def is_prime(number):	# 判斷質數

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

def square_and_multiply(x, h, n):	# Output x**h % n
	y = x
	bitH = [int(x) for x in bin(h)[2:]]
	for i in range(1, len(bitH)):
		y = y**2 % n
		if bitH[i] == 1:
			y = y * x % n
	return y
# end square_and_multiply

if __name__ == '__main__':
	main()
