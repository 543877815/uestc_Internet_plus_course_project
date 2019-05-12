import re
from Resource import Resource
from Processor import Processor


def systeminit():
    processor = Processor()
    resource = Resource()
    processor.create_process('init', 0)
    return processor, resource


if __name__ == '__main__':
    print("Process init is running")
    processor, resource = systeminit()
    while (True):
        x = input("- ")
        # 去除输入两边空格
        x = x.strip()
        # 去除输入中多个空格
        x = re.sub('[ ]+', ' ', x)

        # 解析用户输入
        Xs = x.split(" ")
        if len(Xs) == 3:
            # create process
            if Xs[0] == 'cr':
                pid = Xs[1]
                priority = Xs[2]
                # 只能创建优先级为1或者2的进程，init进程的优先级为0
                if priority != '1' and priority != '2':
                    print("invalid syntax:" + priority + ", type [1,2]")
                    continue
                processor.create_process(pid, priority)
            # request resource
            elif Xs[0] == 'req':
                rid = Xs[1]
                try:
                    num = float(Xs[2])
                except ValueError:
                    print("error, the request number must be integer!")
                else:
                    if num.is_integer():
                        processor.request_resource(resource, rid, num)
                    else:
                        print("error, the request number must be interger!")
            # release resource
            elif Xs[0] == 'rel':
                rid = Xs[1]
                try:
                    num = float(Xs[2])
                except ValueError:
                    print("error, the release number must be integer!")
                else:
                    if num.is_integer():
                        processor.release_resource(resource, rid, num)
                    else:
                        print("error, the release number must be interger!")
            else:
                print("invalid syntax" + Xs[0])
        elif len(Xs) == 2:
            # show specified process
            if Xs[0] == 'lp':
                pid = Xs[1]
                processor.get_process_info(pid)
            # delete process
            elif Xs[0] == 'de':
                # 不能删除 init 进程
                pid = Xs[1]
                if pid == 'init':
                    print("error, can not delete process init!")
                    continue
                processor.delete_process(pid)
                # 进行调度
                processor.schedule()
            else:
                print("syntax occur")
        else:
            # time out
            if x == 'to':
                processor.schedule()
            # list all process
            elif x == 'lp':
                running, ready, blocked = processor.get_running_list(), \
                                          processor.get_ready_list(), \
                                          processor.get_block_list()
                print("running: " + str(running))
                print("ready: " + str(ready))
                print("blocked: " + str(blocked))
            # list all resources
            elif x == 'lr':
                request_list = resource.get_rl()
                [print(x) for x in request_list]
            elif x == 'exit':
                break
            else:
                print("syntax occur")
