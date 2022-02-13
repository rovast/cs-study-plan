import org.junit.Test;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

public class TestUnionFindDS {

    @Test
    public void testConected() {
        DisjointSets DS = new QuickUnionDS(5);
        DS.connect(1, 3);
        assertTrue(DS.isConnected(1, 3));
        assertFalse(DS.isConnected(1, 4));
    }
}
