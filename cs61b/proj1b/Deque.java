public interface Deque<T> {
    public void addFirst(T item);

    public void addLast(T item);

    // 接口方法的默认实现
    default boolean isEmpty(){
        return size() == 0;
    }

    public int size();

    public void printDeque();

    public T removeFirst();

    public T removeLast();

    public T get(int index);
}
