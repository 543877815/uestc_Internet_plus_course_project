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
        return [{"rid": x.get_rid(), "max": x.get_max(), "status": x.get_status(), "waiting_list": x.get_waiting_list(), "_allocated_list": x.get_allocated_list()}
                for x in self._resource_list]

    def request(self, process, rid, status):
        resources = [x for x in self._resource_list if x.get_rid() == rid]
        resource = resources[0]
        # 如果同一进程请求超过资源拥有的最大数量
        if resource.get_max() < status:
            print("request failed, the request number exceeds the max number of the resource!")
            return -1
        # 如果请求资源小于等于剩余资源，则请求资源成功
        if resource.get_status() >= status:
            resource.set_status(int(resource.get_status()) - int(status))
            resource.set_allocated_list(process.get_pid(), status)
            return 0
        # 否则阻塞
        else:
            resource.set_waiting_list(process.get_pid(), status)
            return 1

    def release(self, process, rid, status):
        resources = [x for x in self._resource_list if x.get_rid() == rid]
        resource = resources[0]
        if int(resource.get_max()) - int(resource.get_status()) >= int(status):
            resource.set_status(int(resource.get_status()) + int(status))
            return 0
        else:
            # print("error, the process '" + pid + "' only request", resource.get_status(),
            #       "resource(s), your input has exceeded it")
            return -1
