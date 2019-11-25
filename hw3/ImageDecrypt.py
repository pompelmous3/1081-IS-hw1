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
        filePath = input('The path of the image (Ex. penguin.png): ')
        mode = input(
            'The mode of block cypher (ECB:0 CBC:1 Self-made:2): ')
        key = input('The key (not case-sensitive): ')

    # 取出檔案名稱和副檔名
    filename, ext = os.path.splitext(os.path.split(filePath)[1])

    # 把檔案轉存成 ./____.ppm
    Image.open(filePath).save(filename+'.ppm')

    # 對 .ppm 解密
    if(mode == '0'):
        ECB(filename + '.ppm', key)
    elif(mode == '1'):
        CBC(filename + '.ppm', key)
    elif(mode == '2'):
        selfMade(filename + '.ppm', key)

    # 將 .ppm 轉存成 ./____.xxx
    Image.open(filename + '.ppm').save(filename + '_decrypted' + ext, ext[1:])

    # 刪除 ./____.ppm
    os.remove(filename + '.ppm')
# // end main()

# 加解密用套件的AES
# 除了第三個0A（換行符號）前的東西不變　其他的東西用16byte為單位丟進去做就對了
# padding 的方式用 PKCS ？ (有N個 就寫N0補到滿)


def ECB(filePath, key):
    return
# // end ECB()


def CBC(filePath, key):
    return
# // end CBC()


def selfMade(filePath, key):
    return
# // end selfMade()


main()
