import java.util.Arrays;

public class UnionFind implements DisjointSets {
    // TODO - Add instance variables?
    private final int[] intSets;

    /* Creates a UnionFind data structure holding n vertices. Initially, all
       vertices are in disjoint sets. */
    public UnionFind(int n) {
        intSets = new int[n];
        Arrays.fill(intSets, -1);
    }

    /* Throws an exception if v1 is not a valid index. */
    private void validate(int vertex) {
        // TODO
        if (vertex < -1 || vertex >= intSets.length) {
            throw new IllegalArgumentException("Invalid index");
        }
    }

    /* Returns the size of the set v1 belongs to. */
    public int sizeOf(int v1) {
        // TODO
        validate(v1);

        return -parent(find(v1)); // find 找到的是 root， paret(root) 返回的是具体的值
    }

    /* Returns the parent of v1. If v1 is the root of a tree, returns the
       negative size of the tree for which v1 is the root. */
    public int parent(int v1) {
        // TODO
        validate(v1);

        return intSets[v1];
    }

    /* Returns true if nodes v1 and v2 are connected. */
    public boolean connected(int v1, int v2) {
        // TODO
        validate(v1);
        validate(v1);

        return find(v1) == find(v2);
    }

    /* Connects two elements v1 and v2 together. v1 and v2 can be any valid 
       elements, and a union-by-size heuristic is used. If the sizes of the sets
       are equal, tie break by connecting v1's root to v2's root. Unioning a 
       vertex with itself or vertices that are already connected should not 
       change the sets but may alter the internal structure of the data. */
    public void union(int v1, int v2) {
        // TODO
        validate(v1);
        validate(v2);

        if (!connected(v1, v2)) {
            if (sizeOf(v1) > sizeOf(v2)) {
                connect(v2, v1);
            } else {
                connect(v1, v2);
            }
        }
    }

    // connect v1 --> v2
    // v1 对应的 set 总数量需要加上 v2 sets 数量。由于是负值，直接减去即可
    private void connect(int v1, int v2) {
        intSets[find(v2)] -= sizeOf(v1);
        intSets[find(v1)] = find(v2);
    }

    /* Returns the root of the set V belongs to. Path-compression is employed
       allowing for fast search-time. */
    public int find(int vertex) {
        // TODO
        validate(vertex);

        int root = vertex;
        while (parent(root) > -1) {
            root = parent(root);
        }

        // 路径压缩。当我们发现查找的父节点不是根节点时，进行压缩处理
        int currParent;
        while (vertex != root) {
            currParent = parent(vertex);
            intSets[vertex] = root;
            vertex = currParent;
        }

        return root;
    }

}
