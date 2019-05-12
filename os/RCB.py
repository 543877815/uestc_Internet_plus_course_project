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

    def get_allocated_list(self):
        return self._allocated_list

    def set_allocated_list(self, rid, status):
        self._allocated_list.append({
            "rid": rid,
            "status": status
        })

    def get_waiting_list(self):
        return self._waiting_list

    def set_waiting_list(self, rid, status):
        self._waiting_list.append({
            "rid": rid,
            "status": status
        })

    def getinfo(self):
        return self._rid, self._status, self._waiting_list

