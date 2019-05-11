from PCB import PCB


class Processor:
    # 就绪进程的队列, 阻塞进程的队列
    def __init__(self):
        self._ready_list = []
        self._block_list = []
        self._running_list = []
        pass

    def create_process(self, pid, priority):
        # 判断进程是否存在
        if len(self._running_list) != 0 and pid in [x.get_pid() for x in self.get_process_list()]:
            print("create failed, process '" + pid + "' existed!")
            return

        # 新创建的进程插入到RL队列的末尾
        new_pcb = PCB(pid, priority)
        self._ready_list.append(new_pcb)
        if len(self._running_list) == 0:
            self._running_list.append(new_pcb)
            new_pcb.set_status("running")
            self._ready_list.pop()
        else:
            pass
        # 创建成功后打印进程pid
        print(pid)

    def get_process_list(self):
        return self._ready_list + self._block_list + self._running_list

    def get_ready_list(self):
        return [x.get_pid() for x in self._ready_list]

    def get_block_list(self):
        return [x.get_pid() for x in self._block_list]

    def get_running_process(self):
        return [x.get_pid() for x in self._running_list]

    def schedule(self):
        high_priority = [x for x in self._ready_list if x.get_priority() == '2' if self._running_list[0].get_pid != x.get_pid ]
        if len(high_priority) != 0:
            task = high_priority
        else:
            task = [x for x in self._ready_list if x.get_priority() == '1' if self._running_list[0].get_pid != x.get_pid ]
        self._ready_list.append(self._running_list[0])
        self._running_list[0] = task[0]
        self._ready_list.pop(self._ready_list.index(task[0]))
        print(self._running_list[0].get_pid())
