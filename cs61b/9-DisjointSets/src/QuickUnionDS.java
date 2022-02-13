import java.util.Arrays;

public class QuickUnionDS implements DisjointSets {
    private int[] parent;

    public QuickUnionDS(int N) {
        parent = new int[N];
        Arrays.fill(parent, -1);
    }

    private int find(int p) {
        while (parent[p] >= 0) {
            p = parent[p];
        }

        return p;
    }

    @Override
    public void connect(int p, int q) {
        int i = find(p);
        int j = find(q);

        parent[i] = j;
    }

    @Override
    public boolean isConnected(int p, int q) {
        return find(p) == find(q);
    }
}
