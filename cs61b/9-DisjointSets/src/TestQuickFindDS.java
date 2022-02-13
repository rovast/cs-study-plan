import org.junit.Test;

import static org.junit.Assert.*;

public class TestQuickFindDS {

    @Test
    public void testConected() {
        DisjointSets DS = new QuickFindDS(5);
        DS.connect(1, 3);
        assertTrue(DS.isConnected(1, 3));
        assertFalse(DS.isConnected(1, 4));
    }
}
