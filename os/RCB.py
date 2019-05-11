class RCB:
    def __init__(self, rid, status, waitingList=[]):
        self._rid = rid
        self._status = status
        self._waitingList = waitingList

    def getinfo(self):
        return self._rid, self._status, self._waitingList
