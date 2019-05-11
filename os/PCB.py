class PCB:
    def __init__(self, pid, priority, status='ready', parent=None, children=[], resources=[]):
        self._pid = pid
        # 0: init, 1: user, 2: system
        self._priority = priority
        # -1: none, 0: ready, 1:running, 2: blocked
        self._status = status
        self._parent = parent
        self._children = children
        self._resources = resources

    def get_priority(self):
        return self._priority

    def set_parent(self, parent):
        self._parent = parent

    def get_parent(self):
        return self._parent

    def set_children(self, children):
        self._children.append(children)

    def get_children(self):
        return [x for x in self._children]

    def get_pid(self):
        return self._pid

    def get_status(self):
        return self._status

    def set_status(self, status):
        self._status = status
        pass
