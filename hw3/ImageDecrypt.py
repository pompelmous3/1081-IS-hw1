from PIL import Image
import sys
import os
from Crypto.Cipher import AES


def main():
    # 輸入圖檔路徑、 block cyphor mode 和 key
    file_path = None
    mode = None
    key = None
    if len(sys.argv) == 4:
        file_path = sys.argv[1]
        mode = sys.argv[2]
        key = sys.argv[3]
    else:
        file_path = input('The path of the image (Ex. penguin.png): ')
        mode = input('The mode of block cypher (ECB/ CBC/ CTR): ')
        key = input('The key (not case-sensitive): ')

    # 取出檔案名稱和副檔名
    filename, ext = os.path.splitext(os.path.split(file_path)[1])

    # 把檔案轉存成 ./____.ppm
    Image.open(file_path).save(filename+'.ppm')

    # 對 .ppm 解密
    if mode == 'ECB':
        ECB(filename + '.ppm', key)
    elif mode == 'CBC':
        CBC(filename + '.ppm', key)
    elif mode == 'CTR':
        CTR(filename + '.ppm', key)

    # 將 .ppm 轉存成 ./____.xxx

    target_format = ext[1:]
    if target_format.lower() == 'jpg':
        target_format = 'jpeg'
    Image.open(filename + '_' + mode + '.ppm').save(filename + '_' + mode +
                                                    '_encrypted' + ext, target_format)

    # 刪除 ./____.ppm
    os.remove(filename + '.ppm')
# // end main()

# 加解密用套件的AES
# 除了第三個0A（換行符號）前的東西不變　其他的東西用16byte為單位丟進去做就對了
# padding 的方式用 PKCS ？ (有N個 就寫N0補到滿)


def ECB(file_path, key):
    result = b''
    with open(file_path, 'rb') as file:
        line = 1
        while line <= 3:
            one_byte = file.read(1)
            result += one_byte
            if one_byte == b'\n':
                line += 1
        cryptor = AES.new(bytes(key.encode('utf-8')), AES.MODE_ECB)
        current_block = file.read(16)
        while len(current_block) == 16:     # 16bytes
            plain_text = cryptor.decrypt(current_block)
            result += plain_text
            current_block = file.read(16)
        if len(current_block) != 0:         # 不夠16bytes
            padding_amount = 16 - len(current_block)
            padding = padding_amount.to_bytes(1, 'little')
            current_block += padding * padding_amount
            plain_text = cryptor.decrypt(current_block)
            result += plain_text
    with open(file_path, 'wb') as file:
        file.write(result)
    return
# // end ECB()


def CBC(file_path, key):
    i_v = ''
    i_p = [7, 15, 6, 1, 10, 8, 3, 11, 16, 13, 2, 9, 14, 4, 5, 12]
    i_p = i_p[(int(key[0]) % 16):] + i_p[:(int(key[0]) % 16)]
    for index in i_p:
        i_v += key[index - 1]
    i_v = bytes(i_v.encode('utf-8'))
    result = b''
    with open(file_path, 'rb') as file:
        line = 1
        while line <= 3:
            one_byte = file.read(1)
            result += one_byte
            if one_byte == b'\n':
                line += 1
        cryptor = AES.new(bytes(key.encode('utf-8')), AES.MODE_CBC)

        cipher_block = file.read(16)
        # 16 bytes
        while len(cipher_block) == 16:
            plain_text = cryptor.decrypt(cipher_block)
            plain_text = bytes([plain_text[i] ^ i_v[i] for i in range(16)])

            # 以密文作為下一個 IV
            i_v = cipher_block
            result += plain_text
            cipher_block = file.read(16)
        # 不夠 16 bytes, PKCS padding
        if len(cipher_block) != 0:
            padding_amount = 16 - len(cipher_block)
            padding = padding_amount.to_bytes(1, 'little')
            cipher_block += padding * padding_amount
            plain_text = cryptor.decrypt(cipher_block)
            plain_text = bytes([plain_text[i] ^ i_v[i] for i in range(16)])
            result += plain_text
    with open(file_path, 'wb') as file:
        file.write(result)
    return
# // end CBC()


def CTR(file_path, key):
    i_v = ''
    i_p = [7, 15, 6, 1, 10, 8, 3, 11, 16, 13, 2, 9, 14, 4, 5, 12]
    i_p = i_p[(int(key[0]) % 16):] + i_p[:(int(key[0]) % 16)]
    for index in i_p:
        i_v += key[index - 1]
    i_v = bytes(i_v.encode('utf-8'))

    result = b''
    with open(file_path, 'rb') as file:
        line = 1
        while line <= 3:
            one_byte = file.read(1)
            result += one_byte
            if one_byte == b'\n':
                line += 1
        cryptor = AES.new(bytes(key.encode('utf-8')), AES.MODE_CTR)

        cipher_block = file.read(16)
        while len(cipher_block) == 16:
            cipher_i_v = cryptor.encrypt(i_v)
            plain_text = bytes([cipher_block[i] ^ cipher_i_v[i] for i in range(16)])
            result += plain_text
            i_v = (int.from_bytes(i_v, 'big') + 1).to_bytes(16, 'big')
            cipher_block = file.read(16)
        # 不夠 16 bytes, PKCS padding
        if len(cipher_block) != 0:
            padding_amount = 16 - len(cipher_block)
            padding = padding_amount.to_bytes(1, 'little')
            cipher_block += padding * padding_amount
            cipher_i_v = cryptor.encrypt(i_v)
            plain_text = bytes([cipher_block[i] ^ cipher_i_v[i] for i in range(16)])
        result += plain_text
    with open(file_path, 'wb') as file:
        file.write(result)
    return
# // end selfMade()

main()

