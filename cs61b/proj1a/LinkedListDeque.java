public class LinkedListDeque<T> {
    // 泛性的节点
    public class TNode {
        public TNode prev;
        public TNode next;
        public T item;

        public TNode(T val, TNode p, TNode n) {
            item = val;
            prev = p;
            next = n;
        }
    }

    private int size; // 储存当前的链表大小，便于以 O(1) 的复杂度直接访问 size
    private TNode firstSentinel; // 头部哨兵节点，用来避免一些边界条件判断
    private TNode lastSentinel; // 尾部哨兵节点，用来避免一些边界条件判断

    public LinkedListDeque() {
        this.initSentinelAndSize();
    }

    // 深拷贝 other
    public LinkedListDeque(LinkedListDeque other) {
        this.initSentinelAndSize();

        for (int i = 0; i < other.size; i++) {
            addLast((T) other.get(i));
        }
    }

    private void initSentinelAndSize() {
        firstSentinel = new TNode(null, null, null);
        lastSentinel = new TNode(null, null, null);
        firstSentinel.next = lastSentinel;
        lastSentinel.prev = firstSentinel;
        size = 0;
    }

    public void addFirst(T item) {
        firstSentinel.next = new TNode(item, firstSentinel, lastSentinel);
        lastSentinel.prev = firstSentinel.next;
        size++;
    }

    public void addLast(T item) {
        lastSentinel.prev.next = new TNode(item, lastSentinel.prev, lastSentinel);
        lastSentinel.prev = lastSentinel.prev.next;
        size++;
    }

    public boolean isEmpty() {
        return this.size == 0;
    }

    public int size() {
        return this.size;
    }

    public T get(int index) {
        if (index > size || size < 0) return null;

        TNode p = firstSentinel.next;
        for (int i = 0; i < index; i++) {
            p = p.next;
        }

        return p.item;
    }

    private T getRecurize(int index, TNode curr) {
        if (index == 0) return curr.item;

        return getRecurize(index - 1, curr.next);
    }

    public T getRecurize(int index) {
        return this.getRecurize(index, firstSentinel.next);
    }

    public void printDeque() {
    }

    public T removeFirst() {
        T removedItem = firstSentinel.next.item;
        firstSentinel.next.next.prev = firstSentinel;
        firstSentinel.next = firstSentinel.next.next;

        if (!isEmpty()) size--;

        return removedItem;
    }

    public T removeLast() {
        T removedItem = lastSentinel.prev.item;
        lastSentinel.prev.prev.next = lastSentinel;
        lastSentinel.prev = lastSentinel.prev.prev;

        return removedItem;
    }
}
