class RCB:
    def __init__(self, rid, status):
        self._rid = rid
        self._max = status
        self._status = status
        self._waiting_list = []
        self._allocated_list = []

    def get_rid(self):
        return self._rid

    def get_max(self):
        return self._max

    def get_status(self):
        return self._status

    def set_status(self, status):
        self._status = status

    def get_all_allocated_list(self):
        return self._allocated_list

    def get_allocated_status(self, pid):
        allocated = [x for x in self._allocated_list if pid == x['pid']]
        return allocated[0]['status'] if len(allocated) != 0 else 0

    def set_allocated_list(self, process):
        allocated_exist = [x for x in self._allocated_list if process['pid'] == x['pid']]
        if len(allocated_exist) == 0:
            self._allocated_list.append(process)
        else:
            for x in allocated_exist:
                if process['status'] == 0:
                    self._allocated_list.pop([y['pid'] for y in self._allocated_list].index(x['pid']))
                else:
                    x['status'] = process['status']

    def get_waiting_list(self):
        return self._waiting_list

    def set_waiting_list(self, process):
        waiting_exist = [x for x in self._waiting_list if process['pid'] == x['pid']]
        if len(waiting_exist) == 0 and process['status'] != 0:
            self._waiting_list.append(process)
        else:
            for x in waiting_exist:
                if process['status'] == 0:
                    self._waiting_list.pop([y['pid'] for y in self._waiting_list].index(x['pid']))
                else:
                    x['status'] = process['status']

    def getinfo(self):
        return self._rid, self._status, self._waiting_list
