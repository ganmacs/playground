import org.junit.jupiter.api.AfterEach
import org.junit.jupiter.api.Assertions.*
import org.junit.jupiter.api.BeforeEach
import org.junit.jupiter.api.Test
import java.io.File
import java.nio.file.Files
import kotlin.test.assertFails

internal class PagerTest {
    var file: File? = null

    @BeforeEach
    fun setup() {
        val t = Files.createTempFile("pager_test", "t")
        file = t.toFile()
    }

    @AfterEach
    fun teardown() {
        file?.delete()
    }

    @Test
    fun pagerinit() {
        val pager = Pager(file!!)
        assertEquals(0, pager.fileLength)
        file!!.writeText("a")

        val throwable = assertFails { Pager(file!!) }
        kotlin.test.assertEquals("Db file is not a whole number of pages. Corrupt file.", throwable.message)
    }
}