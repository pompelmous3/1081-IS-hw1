from PIL import Image
import sys
import os
from Crypto.Cipher import AES


def main():
    # 輸入圖檔路徑、 block cipher mode 和 key
    file_path = None
    mode = None
    key = None
    if(len(sys.argv) == 4):
        file_path = sys.argv[1]
        mode = sys.argv[2]
        key = (sys.argv[3]).upper()
    else:
        file_path = input('Enter the path of the image (Ex. color.png): ')
        mode = input(
            'Enter the mode of block cipher (ECB/ CBC/ CTR): ')
        key = (input('Enter the key (16 characters, not case-sensitive): ')).upper()

    # 取出檔案名稱和副檔名
    filename, ext = os.path.splitext(os.path.split(file_path)[1])

    # 把檔案轉存成 ./____.ppm
    Image.open(file_path).save(filename+'_'+mode+'.ppm')

    # 對 .ppm 加密
    if(mode == 'ECB'):
        ECB(filename + '_'+mode + '.ppm', key)
    elif(mode == 'CBC'):
        CBC(filename + '_'+mode + '.ppm', key)
    elif(mode == 'CTR'):
        CTR(filename + '_'+mode + '.ppm', key)

    # 將 .ppm 轉存成 ./____.xxx (jpeg/gif/png/bmp)
    target_format = ext[1:]
    if(target_format.lower() == 'jpg'):
        target_format = 'jpeg'
    Image.open(filename + '_'+mode + '.ppm').save(filename + '_' + mode +
                                                  '_encrypted' + ext, target_format)

    # 刪除 ./____.ppm
    os.remove(filename + '_'+mode + '.ppm')
# // end main()


def ECB(file_path, key):
    result = b''
    with open(file_path, 'rb') as file:
        # 照抄前三行
        enter_amount = 0
        while(enter_amount != 3):
            temp = file.read(1)
            result += temp
            if(temp == b'\n'):
                enter_amount += 1
        # 每個 block 用 AES 加密
        cipher = AES.new(bytes(key.encode('utf-8')), AES.MODE_ECB)
        current_block = file.read(16)
        while(len(current_block) == 16):
            ciphertext = cipher.encrypt(current_block)
            result += ciphertext
            current_block = file.read(16)
        # PKCS padding
        if(len(current_block) != 0):
            padding_amount = 16 - len(current_block)
            padding = (padding_amount*16).to_bytes(1, 'big')
            current_block += padding * padding_amount
            ciphertext = cipher.encrypt(current_block)
            result += ciphertext
    with open(file_path, 'wb') as file:
        file.write(result)
# // end ECB()


def CBC(file_path, key):
    # 產生 IV
    i_v = ''
    i_p = [7, 15, 6, 1, 10, 8, 3, 11, 16, 13, 2, 9, 14, 4, 5, 12]
    i_p = i_p[(int(key[0]) % 16):] + i_p[:(int(key[0]) % 16)]
    for index in i_p:
        i_v += key[index - 1]
    i_v = bytes(i_v.encode('utf-8'))
    result = b''
    with open(file_path, 'rb') as file:
        # 照抄前三行
        enter_amount = 0
        while(enter_amount != 3):
            temp = file.read(1)
            result += temp
            if(temp == b'\n'):
                enter_amount += 1
        # 每個 block 用 AES 加密
        cipher = AES.new(bytes(key.encode('utf-8')), AES.MODE_ECB)
        current_block = file.read(16)
        while(len(current_block) == 16):
            current_block = bytes([current_block[i] ^ i_v[i]
                                   for i in range(16)])
            ciphertext = cipher.encrypt(current_block)
            # 以密文作為下一個 IV
            i_v = ciphertext
            result += ciphertext
            current_block = file.read(16)
        # PKCS padding
        if(len(current_block) != 0):
            padding_amount = 16 - len(current_block)
            padding = (padding_amount*16).to_bytes(1, 'big')
            current_block += padding * padding_amount
            current_block = bytes([current_block[i] ^ i_v[i]
                                   for i in range(16)])
            ciphertext = cipher.encrypt(current_block)
            result += ciphertext
    with open(file_path, 'wb') as file:
        file.write(result)
# // end CBC()


def CTR(file_path, key):
    # 產生 IV
    i_v = ''
    i_p = [7, 15, 6, 1, 10, 8, 3, 11, 16, 13, 2, 9, 14, 4, 5, 12]
    i_p = i_p[(int(key[0]) % 16):] + i_p[:(int(key[0]) % 16)]
    for index in i_p:
        i_v += key[index - 1]
    i_v = bytes(i_v.encode('utf-8'))

    result = b''
    with open(file_path, 'rb') as file:
        # 照抄前三行
        enter_amount = 0
        while(enter_amount != 3):
            temp = file.read(1)
            result += temp
            if(temp == b'\n'):
                enter_amount += 1
        # 每個 block 用 AES 加密
        cipher = AES.new(bytes(key.encode('utf-8')), AES.MODE_ECB)
        current_block = file.read(16)
        while(len(current_block) == 16):
            ciphertext_i_v = cipher.encrypt(i_v)
            ciphertext = bytes(
                [current_block[i] ^ ciphertext_i_v[i] for i in range(16)])
            result += ciphertext
            current_block = file.read(16)
            # IV += 1
            i_v = (int.from_bytes(i_v, 'big') + 1).to_bytes(16, 'big')
        # PKCS padding
        if(len(current_block) != 0):
            padding_amount = 16 - len(current_block)
            padding = (padding_amount*16).to_bytes(1, 'big')
            current_block += padding * padding_amount
            ciphertext_i_v = cipher.encrypt(i_v)
            ciphertext = bytes([current_block[i] ^ ciphertext_i_v[i]
                                for i in range(16)])
        result += ciphertext
    with open(file_path, 'wb') as file:
        file.write(result)
# // end CTR()


if __name__ == '__main__':
    main()
