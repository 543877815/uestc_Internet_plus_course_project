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
            new_pcb.set_parent(self._running_list[0])
            self._running_list[0].set_children(new_pcb)
        # 创建成功后打印进程pid
        print(pid)

    def delete_process(self, pid):
        # 从所有队列中找到该pid的状态，从该状态的队列中删除
        print(pid)
        processes = self.get_process_list()
        process = [x for x in processes if x.get_pid() == pid]
        if len(process) == 0:
            return
        # 删除父母节点
        process_parent = process[0].get_parent()
        process_parent.delete_children(pid)
        # 级联删除
        process_children = process[0].get_children()
        [self.delete_process(x.get_pid()) for x in process_children]
        # 根据状态查找对应的队列进行删除
        process_status = process[0].get_status()
        if process_status == 'running':
            self._running_list.pop([x.get_pid() for x in self._running_list].index(pid))
        elif process_status == 'blocked':
            self._block_list.pop([x.get_pid() for x in self._block_list].index(pid))
        elif process_status == 'ready':
            self._ready_list.pop([x.get_pid() for x in self._ready_list].index(pid))

        # 进行调度
        self.schedule()

    def get_process_info(self, pid):
        processes = self.get_process_list()
        info = [x.get_info() for x in processes if x.get_pid() == pid]
        if len(info) == 0:
            print("process: " + pid + " not exist!")
            return
        print(info[0])

    def get_process_list(self):
        return self._ready_list + self._block_list + self._running_list

    def get_ready_list(self):
        return [x.get_pid() for x in self._ready_list]

    def get_block_list(self):
        return [x.get_pid() for x in self._block_list]

    def get_running_list(self):
        return [x.get_pid() for x in self._running_list]

    def schedule(self):
        # 选取优先级最高而且到达时间最早的进程
        system = [x for x in self._ready_list if int(x.get_priority()) == 2]
        user = [x for x in self._ready_list if int(x.get_priority()) == 1]
        if len(system) != 0:
            tasks = system
        elif len(user) != 0:
            tasks = user
        else:
            tasks = [x for x in self._ready_list if int(x.get_priority()) == 0]

        # 调度
        self._ready_list.append(self._running_list[0])
        # 如果为0则证明删除了正在运行的进程
        if len(self._running_list) == 0:
            self._running_list.append(tasks[0])
        else:
            self._running_list[0] = tasks[0]
        self._ready_list.pop(self._ready_list.index(tasks[0]))

        # 状态设置
        self._running_list[0].set_status("ready")
        tasks[0].set_status("running")

        # 调度成功后打印进程pid
        print(self._running_list[0].get_pid())
