from PIL import Image
import sys
import os
from Crypto.Cipher import AES


def main():
    # 輸入圖檔路徑、 block cyphor mode 和 key
    filePath = None
    mode = None
    key = None
    if(len(sys.argv) == 4):
        filePath = sys.argv[1]
        mode = sys.argv[2]
        key = sys.argv[3]
    else:
        filePath = input('Enter the path of the image (Ex. penguin.png): ')
        mode = input(
            'Choose the mode of block cypher (ECB:0 CBC:1 Self-made:2): ')
        key = input('Enter the key (not case-sensitive): ')

    # 取出檔案名稱和副檔名
    filename, ext = os.path.splitext(os.path.split(filePath)[1])

    # 把檔案轉存成 ./____.ppm
    Image.open(filePath).save(filename+'.ppm')

    # 對 .ppm 加密
    if(mode == '0'):
        ECB(filename + '.ppm', key)
    elif(mode == '1'):
        CBC(filename + '.ppm', key)
    elif(mode == '2'):
        selfMade(filename + '.ppm', key)

    # 將 .ppm 轉存成 ./____.xxx (jpeg/gif/png/bmp)
    targetFormat = ext[1:]
    if(targetFormat.lower() == 'jpg'):
        targetFormat = 'jpeg'
    Image.open(filename + '.ppm').save(filename +
                                       '_encrypted' + ext, targetFormat)

    # 刪除 ./____.ppm
    # os.remove(filename + '.ppm')
# // end main()

# 加解密用套件的AES
# 除了第三個0A（換行符號）前的東西不變　其他的東西用16byte為單位丟進去做就對了
# padding 的方式用 PKCS ？ (有N個 就寫N0補到滿)


def ECB(filePath, key):
    result = b''
    with open(filePath, 'rb') as file:
        # 照抄前三行
        enterAmount = 0
        while(enterAmount != 3):
            temp = file.read(1)
            result += temp
            if(temp == b'\n'):
                enterAmount += 1
        # 每個block加密
        cipher = AES.new(bytes(key.encode('utf-8')), AES.MODE_ECB)
        currentBlock = file.read(16)
        while(len(currentBlock) == 16):
            ciphertext = cipher.encrypt(currentBlock)
            # print(ciphertext)0
            result += ciphertext
            currentBlock = file.read(16)
        paddingAmount = 16 - len(currentBlock)
        padding = (paddingAmount*16).to_bytes(1,'big')
        currentBlock += padding * paddingAmount
        ciphertext = cipher.encrypt(currentBlock)
        result += ciphertext
    with open(filePath, 'wb') as file:
        file.write(result)
# // end ECB()


def CBC(filePath, key):
    return
# // end CBC()


def selfMade(filePath, key):
    return
# // end selfMade()


main()
