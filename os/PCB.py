class PCB:
    def __init__(self, pid, priority):
        self._pid = pid
        # 0: init, 1: user, 2: system
        self._priority = int(priority)
        # -1: none, 0: ready, 1:running, 2: blocked
        self._status = 'ready'
        self._parent = None
        self._children = []
        self._resources = []

    def get_info(self):
        return {
            "pid": self._pid,
            "priority": self._priority,
            "status": self._status,
            "parent": self._parent.get_pid() if self._parent is not None else None,
            "children": [x.get_pid() for x in self._children],
            "resources": self._resources
        }

    def get_priority(self):
        return self._priority

    def set_parent(self, parent):
        self._parent = parent

    def get_parent(self):
        return self._parent

    def delete_children(self, pid):
        children = [x for x in self._children if x.get_pid() == pid]
        child_delete = children[0]
        self._children.pop(self._children.index(child_delete))

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

    def set_resources(self, resource):
        resource_exist = [x for x in self._resources if resource['rid'] == x['rid']]
        if len(resource_exist) == 0:
            self._resources.append(resource)
        else:
            for x in resource_exist:
                if resource['status'] == 0:
                    self._resources.pop([y['rid'] for y in self._resources].index(x['rid']))
                else:
                    x['status'] = resource['status']

    def get_resource(self, rid):
        for x in self._resources:
            if x['rid'] == rid:
                return x
        return []

    def get_all_resource(self):
        return self._resources
