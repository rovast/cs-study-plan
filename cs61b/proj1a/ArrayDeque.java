public class ArrayDeque<T> implements Deque<T> {
    private int size;
    private int nextFirst;
    private int nextLast;
    private T[] items;

    // 初始化一个新的 arrayDeque，默认长度是 8
    public ArrayDeque() {
        // Java does not allow to create new generic array directly. So need cast.
        items = (T[]) new Object[8];
        nextFirst = 0;
        nextLast = 1;
        size = 0;
    }

    // 深拷贝 other
    public ArrayDeque(ArrayDeque other) {
        items = (T[]) new Object[other.size];
        nextFirst = other.nextFirst;
        nextLast = other.nextLast;
        size = other.size;

        System.arraycopy(other.items, 0, items, 0, other.size);
    }

    @Override
    public void addFirst(T item) {
        if (isFull()) upSize();

        items[nextFirst] = item;
        nextFirst = minusOne(nextFirst);
        size++;
    }

    @Override
    public T removeFirst() {
        if (isSpare()) downSize();

        nextFirst = plusOne(nextFirst);
        T toRemove = items[nextFirst];
        size--;

        return toRemove;
    }

    @Override
    public void addLast(T item) {
        if (isFull()) upSize();

        items[nextLast] = item;
        nextLast = plusOne(nextLast);
        size++;
    }

    @Override
    public T removeLast() {
        if (isSpare()) downSize();

        nextLast = minusOne(nextLast);
        T toRemove = items[nextLast];
        size--;

        return toRemove;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public T get(int index) {
        int i = (nextFirst + index + 1 + items.length) % items.length;
        return items[index + nextFirst];
    }

    @Override
    public void printDeque() {
        int start = nextFirst;
        int end = nextLast;
        while (start != end) {
            start = plusOne(start);
            System.out.printf("[%d]: %s\r\n", start, items[start]);
        }
    }

    private int minusOne(int index) {
        return (index - 1 + items.length) % items.length;
    }

    private int plusOne(int index) {
        return (index + 1) % items.length;
    }

    // 看看是不是需要扩容
    private boolean isFull() {
        return size == items.length;
    }

    // 看看是不是要缩容，空余的太多了
    private boolean isSpare() {
        return (items.length > 15) && (items.length > size * 4);
    }

    private void upSize() {
        resize(size * 2);
    }

    private void downSize() {
        resize(items.length / 2);
    }

    private void resize(int capacity) {
        T[] newQueue = (T[]) new Object[capacity];
        int oldIndex = plusOne(nextFirst);

        for (int newIndex = 0; newIndex < size; newIndex++) {
            newQueue[newIndex] = items[oldIndex];
            oldIndex = plusOne(oldIndex);
        }
        items = newQueue;
        nextFirst = capacity - 1;
        nextLast = size;
    }
}
