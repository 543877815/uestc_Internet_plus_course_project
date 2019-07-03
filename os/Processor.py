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
        new_pcb = PCB(pid, int(priority))
        self._ready_list.append(new_pcb)
        # 如果创建的不是init进程
        
        if len(self._running_list) != 0:
            new_pcb.set_parent(self._running_list[0])
            self._running_list[0].set_children(new_pcb)
        self.schedule()

    def delete_process(self, resource, pid, time):
        # 从所有队列中找到该pid的状态，从该状态的队列中删除
        processes = [x for x in self.get_process_list() if x.get_pid() == pid]
        if len(processes) == 0:
            return
        else:
            process = processes[0]
        # 删除父母节点
        process_parent = process.get_parent()
        process_parent.delete_children(pid=pid)
        # 级联删除
        process_children = process.get_children()
        [self.delete_process(resource=resource, pid=x.get_pid(), time=time+1) for x in process_children]

        # 将自己拥有的资源进行释放
        resources = process.get_all_resource()
        if len(resources)!=0:
            for i in range(len(resources)):
                self.release_resource(process=process, resource=resource, rid=resources[0]['rid'], release_status=resources[0]['status'])

        # 将资源等待队列记录清除
        for x in resource._resource_list:
            x.set_waiting_list(process={
                    "pid": process.get_pid(),
                    "priority": process.get_priority(),
                    "status": 0
                })

        # 根据状态查找对应的队列进行删除
        process_status = process.get_status()
        # 如果删除的进程是当前正在运行的进程则立即进行调度
        if process_status == 'running':
            self._running_list.pop([x.get_pid() for x in self._running_list].index(pid))
        elif process_status == 'blocked':
            self._block_list.pop([x.get_pid() for x in self._block_list].index(pid))
        elif process_status == 'ready':
            self._ready_list.pop([x.get_pid() for x in self._ready_list].index(pid))
        if time == 0:
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

        # 如果运行队列为空
        if len(self._running_list) == 0:
            self._running_list.append(tasks[0])
            tasks[0].set_status("running")
            self._ready_list.pop(self._ready_list.index(tasks[0]))
            return

        # 如果优先级大于正在运行的进程则进行抢占
        if tasks[0].get_priority() > self._running_list[0].get_priority():
            # 取出正在运行的队列
            self._running_list[0].set_status("ready")
            self._ready_list.append(self._running_list[0])
            self._running_list.pop()

            # 运行被选中的进程
            tasks[0].set_status("running")
            self._ready_list.pop(self._ready_list.index(tasks[0]))
            self._running_list.append(tasks[0])
        else:
            return

    def time_out(self):
        self._running_list[0].set_status("ready")
        self._ready_list.append(self._running_list[0])
        self._running_list.pop()
        self.schedule()

    def request_resource(self, resource, rid, request_status, process=None):
        if process is None:
            process = self._running_list[0]
        # if self._running_list[0].get_pid() == 'init':
        #     print("the process init can not request resource!")
        #     return
        request_status = int(request_status)
        code = resource.request(process=process, rid=rid, request_status=request_status)
        # 若资源请求成功，修改进程状态
        if code == 0:
            process_resource = process.get_resource(rid=rid)
            # 若资源不存在则分配
            if len(process_resource) == 0:
                process.set_resources(resource={
                    "rid": rid,
                    "status": request_status
                })
            # 若资源存在则进行叠加
            else:
                process_resource['status'] += request_status
        # 若资源不足，则修改当前进程为阻塞态, 添加到阻塞队列，移除运行队列，进行调度
        elif code == 1:
            for x in self._running_list:
                self._block_list.append(process)
                x.set_status("blocked")
                self._running_list.pop(self._running_list.index(x))
            self.schedule()

    def release_resource(self, resource, rid, release_status, process=None):
        release_status = int(release_status)
        # 获取当前已分配的资源
        if process is None:
            process = self._running_list[0]
        if len(process.get_resource(rid)) == 0:
            return
        status_allocated = int(process.get_resource(rid)['status'])
        pid = process.get_pid()
        # 如果已分配资源大于等于要求释放资源，则释放资源，并修改进程状态
        if status_allocated >= release_status:
            code = resource.release(process=process, rid=rid, release_status=release_status)
            if code == 0:
                process.set_resources(resource={
                    "rid": rid,
                    "status": status_allocated - release_status
                })
                # 遍历进程的阻塞队列
                # for priority in [2, 1]:
                #     # 根据优先级
                #     block_list = [x for x in self._block_list if x.get_priority() == priority]
                block_list = [x for x in self._block_list]
                flag = False
                for x in block_list:
                    # 查看资源的等待队列
                    rcb = resource.get_rcb(rid=rid)
                    waiting_list = rcb.get_waiting_list()
                    # 标志位用于判断是否遇见阻塞队列
                    for y in waiting_list:
                        # 查看是否能唤醒并分配资源
                        if y["pid"] == x.get_pid():
                            # 标志位为真则证明有先到的进程被阻塞，且不满足唤醒条件，故而后续的队列不进行唤醒询问
                            if flag: return
                            if rcb.get_status() >= y['status']:
                                x.set_status('ready')
                                x.set_resources(resource={
                                    "rid": rid,
                                    "status": y['status']
                                })
                                self._ready_list.append(x)
                                self._block_list.pop(self._block_list.index(x))
                                rcb.get_waiting_list().pop(rcb.get_waiting_list().index(y))
                                resource.request(process=x, rid=rid, request_status=y['status'])
                                self.schedule()
                            else:
                                flag = True
        else:
            print("error, the process '" + process.get_pid() + "' only request", resource.get_status(),
                  "resource(s), your input has exceeded it")
