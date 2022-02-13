public class QuickFindDS implements DisjointSets {
    private int[] id;

    /**
     * Θ(N)
     *
     * @param N 元素的数量
     */
    public QuickFindDS(int N) {
        id = new int[N];
        for (int i = 0; i < N; i++) {
            id[i] = i;
        }
    }

    @Override
    public void connect(int p, int q) {
        int pid = id[p];
        int qid = id[q];
        for (int i = 0; i < id.length; i++) {
            if (id[i] == pid) {
                id[i] = qid;
            }
        }
    }

    @Override
    public boolean isConnected(int p, int q) {
        return id[p] == id[q];
    }
}
