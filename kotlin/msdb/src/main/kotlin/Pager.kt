import java.io.File
import java.io.RandomAccessFile
import kotlin.system.exitProcess

class Buffer(val inner: ByteArray = ByteArray(PAGE_SIZE), var isDirty: Boolean= false, var isLoad: Boolean = false) {
    fun loadFrom(buf: RandomAccessFile) {
        buf.read(inner)
        isLoad = true
    }

    fun flushTo(buf: RandomAccessFile) {
        buf.write(inner)
        isLoad = false
        isDirty = false
    }
}

class Pager(file: File) {
    private val file = RandomAccessFile(file, "rw")
    var fileLength: Int = file.length().toInt()
    private var pages = 0.rangeTo(TABLE_MAX_PAGES).map { Buffer() }

    fun close() {
        pages.forEachIndexed { id, page ->
            if (page.isLoad) {
                file.seek(id.toLong() * PAGE_SIZE)
                page.flushTo(file)
            }
        }

        file.close()
    }

    fun fetchPage(pageNum: Int): ByteArray {
        if (pageNum > TABLE_MAX_PAGES) {
            println("Tried to fetch page number out of bounds. $pageNum > $TABLE_MAX_PAGES")
            exitProcess(1);
        }
        val page = pages[pageNum]
        if (!page.isLoad) {
            file.seek(pageNum.toLong() * PAGE_SIZE.toLong())
            page.loadFrom(file)
        }

        return page.inner
    }
}