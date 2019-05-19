from RCB import RCB


class Resource:
    def __init__(self):
        r1 = RCB("R1", 1)
        r2 = RCB("R2", 2)
        r3 = RCB("R3", 3)
        r4 = RCB("R4", 4)
        self._resource_list = list()
        self._resource_list.append(r1)
        self._resource_list.append(r2)
        self._resource_list.append(r3)
        self._resource_list.append(r4)

    def get_rl(self):
        return [{"rid": x.get_rid(), "max": x.get_max(), "status": x.get_status(), "waiting_list": x.get_waiting_list(),
                 "_allocated_list": x.get_all_allocated_list()}
                for x in self._resource_list]

    def request(self, process, rid, request_status):
        if len([x for x in self._resource_list if x.get_rid() == rid]) != 0:
            resource = [x for x in self._resource_list if x.get_rid() == rid][0]
            # 如果剩余资源大于等于请求资源，则请求资源成功
            if resource.get_status() >= request_status:
                # 维护剩余资源状态
                resource.set_status(status=resource.get_status() - request_status)
                # 维护已分配资源状态
                allocated_status = resource.get_allocated_status(pid=process.get_pid())
                resource.set_allocated_list(process={
                    "pid": process.get_pid(),
                    "priority": process.get_priority(),
                    "status": allocated_status + request_status
                })
                return 0
            # 否则阻塞
            else:
                resource.set_waiting_list(process={
                    "pid": process.get_pid(),
                    "priority": process.get_priority(),
                    "status": request_status
                })
                return 1
        else:
            print("Resource", rid, "not exist!")
            return -1

    def release(self, process, rid, release_status):
        if len([x for x in self._resource_list if x.get_rid() == rid]) != 0:
            resource = [x for x in self._resource_list if x.get_rid() == rid][0]
            allocated_status = resource.get_allocated_status(pid=process.get_pid())
            # 如果释放资源大于该进程已分配资源
            if release_status > allocated_status:
                print("request failed, the release number exceeds the number of the resource this process requested!")
                return -1
            # 如果该进程已分配资源大于等于释放资源，则释放资源成功
            else:
                # 维护资源状态
                resource.set_status(status=resource.get_status() + release_status)
                # 维护已分配资源的状态
                resource.set_allocated_list(process={
                    "pid": process.get_pid(),
                    "priority": process.get_priority(),
                    "status": allocated_status - release_status
                })
                return 0
        else:
            print("Resource", rid, "not exist!")
            return -1

    def get_rcb(self, rid):
        if len([x for x in self._resource_list if x.get_rid() == rid]) != 0:
            return [x for x in self._resource_list if x.get_rid() == rid][0]
        else:
            return []
