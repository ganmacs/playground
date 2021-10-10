import org.junit.jupiter.api.AfterEach
import org.junit.jupiter.api.BeforeEach
import java.io.File
import java.io.RandomAccessFile
import java.lang.StringBuilder
import java.nio.file.Files
import kotlin.test.Test
import kotlin.test.assertEquals

internal class PageTest {
    var file: File? = null

    @BeforeEach
    fun setup() {
        val t = Files.createTempFile("test", "t")
        file = t.toFile()
    }

    @AfterEach
    fun teardown() {
        file?.delete()
    }

    @Test
    fun testRead() {
        val file = file!!

        val b = StringBuilder()
        for (i in 0.rangeTo(PAGE_SIZE)) b.append('a')
        for (i in 0.rangeTo(PAGE_SIZE)) b.append('b')

        file.writeBytes(b.toString().toByteArray())
        val p = Page(0)
        p.read(RandomAccessFile(file, "rw"))

        val data = p.data!!
        assertEquals(PAGE_SIZE, data.array().size)
        assertEquals(b.slice(0.until(PAGE_SIZE)).map { it.code.toByte() }, data.array().toList())

        val p2 = Page(1)
        p2.read(RandomAccessFile(file, "rw"))
        val data2 = p2.data!!
        assertEquals(PAGE_SIZE, data2.array().size)
        assertEquals(b.slice(PAGE_SIZE.until(PAGE_SIZE*2)).map { it.code.toByte() }, data2.array().toList())
    }

    @Test
    fun testCopy() {
        val file = file!!
        val b = StringBuilder()
        for (i in 0.rangeTo(PAGE_SIZE)) b.append('a')
        file.writeBytes(b.toString().toByteArray())

        val p = Page(0)
        p.read(RandomAccessFile(file, "rw"))

        val p2 = Page(1)
        p2.copyData(p)
        assertEquals(p.data!!.array().toList(), p2.data!!.array().toList())
    }
}

