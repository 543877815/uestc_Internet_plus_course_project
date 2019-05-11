import re

if __name__ == '__main__':
    while (True):
        x = input("- ")
        # 去除输入两边空格
        x = x.strip()
        # 去除输入中多个空格
        x = re.sub('[  ]+', ' ', x)
        if x == 'init':
            pass
        else if x == 'exit':
            return
        Xs = x.split(" ")
        [print(x) for x in Xs]
