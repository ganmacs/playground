import org.junit.jupiter.api.Assertions.*
import org.junit.jupiter.api.Test
import java.nio.ByteBuffer

internal class LeafTest {
    @Test
    fun emptyFind() {
        val buf = ByteBuffer.allocate(PAGE_SIZE)
        val l = Leaf(buf)
        assertEquals(0, l.find(0))
        assertEquals(0, l.find(100))
    }

    @Test
    fun insertAndFind() {
        val buf = ByteBuffer.allocate(PAGE_SIZE)
        val l = Leaf(buf)
        l.insert(0, Row(0, "hello1".toByteArray(), "email1".toByteArray()))
        l.insert(5, Row(5, "hello2".toByteArray(), "email2".toByteArray()))
        l.insert(4, Row(4, "hello2".toByteArray(), "email2".toByteArray()))
        l.insert(1, Row(1, "hello2".toByteArray(), "email2".toByteArray()))
        l.insert(3, Row(3, "hello2".toByteArray(), "email2".toByteArray()))
        l.insert(2, Row(2, "hello2".toByteArray(), "email2".toByteArray()))

        assertEquals(6, l.numCell())
        assertEquals(0, l.find(0))
        assertEquals(1, l.find(1))
        assertEquals(2, l.find(2))
        assertEquals(3, l.find(3))
        assertEquals(4, l.find(4))
        assertEquals(5, l.find(5))
        assertEquals(6, l.find(6))
    }
}