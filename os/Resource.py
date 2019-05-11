from RCB import RCB


class Resource:
    def __init__(self):
        r1 = RCB("R1", 1)
        r2 = RCB("R2", 2)
        r3 = RCB("R3", 3)
        r4 = RCB("R4", 4)
        self._resourceList = list()
        self._resourceList.append(r1)
        self._resourceList.append(r2)
        self._resourceList.append(r3)
        self._resourceList.append(r4)
        pass

    def get_rl(self):
        [print(str(x._rid) + " " + str(x._status) + " " + str(x._waitingList)) for x in self._resourceList]

    def request(self):
        pass
