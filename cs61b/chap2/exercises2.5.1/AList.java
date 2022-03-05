/**
 * Array based list.
 *
 * @author Josh Hug
 */

public class AList {
    int size;
    int[] box = new int[100];

    /**
     * Creates an empty list.
     */
    public AList() {
        size = 0;
    }

    /**
     * Inserts X into the back of the list.
     */
    public void addLast(int x) {
        box[size] = x;
        size++;
    }

    /**
     * Returns the item from the back of the list.
     */
    public int getLast() {
        if (size == 0) return 0;

        return box[size - 1];
    }

    /**
     * Gets the ith item in the list (0 is the front).
     */
    public int get(int i) {
        return box[i];
    }

    /**
     * Returns the number of items in the list.
     */
    public int size() {
        return size;
    }

    /**
     * Deletes item from back of the list and
     * returns deleted item.
     */
    public int removeLast() {
        if (size == 0) return 0;

        size--;
        return box[size];
    }
} 
