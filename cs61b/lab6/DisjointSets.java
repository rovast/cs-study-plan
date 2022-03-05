public interface DisjointSets {
    void union(int p, int q);

    boolean connected(int p, int q);
}
