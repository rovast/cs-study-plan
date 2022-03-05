import org.junit.Test;

import static org.junit.Assert.*;

public class TestOffByOne {
    // You must use this CharacterComparator and not instantiate
    // new ones, or the autograder might be upset.
    static CharacterComparator offByOne = new OffByOne();

    // Your tests go here.
    @Test
    public void testEqualCharts() {
        assertTrue(offByOne.equalChars('a', 'b'));  // true
        assertTrue(offByOne.equalChars('r', 'q'));  // true
        assertTrue(offByOne.equalChars('%', '&'));  // true
        assertTrue(offByOne.equalChars('&', '%'));  // true
        assertFalse(offByOne.equalChars('a', 'e'));  // false
        assertFalse(offByOne.equalChars('a', 'B'));  // false
        assertFalse(offByOne.equalChars('z', 'a'));  // falseB
        assertFalse(offByOne.equalChars('a', 'a'));  // false
    }
}
