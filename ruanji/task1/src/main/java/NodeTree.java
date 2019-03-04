public class NodeTree {
    Goods data; //根节点数据
    NodeTree left; //左子树
    NodeTree right; //右子树

    public NodeTree() {
        super();
    }

    public NodeTree(Goods data) { //实例化二叉树
        super();
        this.data = data;
        left = null;
        right = null;
    }

    public void insert(NodeTree root, Goods data) {
        if (data.ID > root.data.ID) { //如果插入的节点大于跟节点
            if (root.right == null) {          //如果右子树为空，就插入，如果不为空就再创建一个节点
                root.right = new NodeTree(data); //就把插入的节点放在右边
            } else {
                this.insert(root.right, data);
            }
        } else {  //如果插入的节点小于根节点
            if (root.left == null) { //如果左子树为空，就插入，如果不为空就再创建一个节点
                root.left = new NodeTree(data); //就把插入的节点放在左边边
            } else {
                this.insert(root.left, data);
            }
        }
    }

    public static void preOrder(NodeTree root) { // 先根遍历
        if (root != null) {
            System.out.println(root.data + "-");
            System.out.println();
            preOrder(root.left);
            preOrder(root.right);
        }
    }

    public static void inOrder(NodeTree root) { // 中根遍历

        if (root != null) {
            inOrder(root.left);
            System.out.print(root.data + "--");
            inOrder(root.right);
        }
    }

    public static void postOrder(NodeTree root) { // 后根遍历

        if (root != null) {
            postOrder(root.left);
            postOrder(root.right);
            System.out.print(root.data + "---");
        }
    }
}
