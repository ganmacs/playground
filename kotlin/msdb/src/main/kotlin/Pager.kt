import java.io.File
import java.io.RandomAccessFile
import java.nio.ByteBuffer
import kotlin.system.exitProcess

class Page(val num: Int) {
    var data: ByteBuffer? = null
        private set
    private val pageOffSet: Long = num.toLong() * PAGE_SIZE

    fun read(raf: RandomAccessFile) {
        if (data == null) {
            val buf = ByteArray(PAGE_SIZE)
            raf.seek(pageOffSet)
            raf.read(buf)
            this.data = ByteBuffer.wrap(buf)
        }
    }

    fun write(buf: RandomAccessFile) {
        if (data != null) {
            buf.seek(pageOffSet)
            buf.write(data!!.array())
        }
    }
}

class Pager(file: File) {
    private val file = RandomAccessFile(file, "rw")
    var fileLength: Int = file.length().toInt().also {
        if (it % PAGE_SIZE != 0) {
            throw Error("Db file is not a whole number of pages. Corrupt file.")
        }
    }

    var pageNum = fileLength / PAGE_SIZE
    private var pages = 0.rangeTo(TABLE_MAX_PAGES).map { i -> Page(i) } // TODO: cache invalidate

    fun close() {
        pages.forEach { page -> page.write(file) }
        file.close()
    }

    fun createNewPage(): ByteBuffer {
        pageNum += 1
        if (pageNum > TABLE_MAX_PAGES) {
            println("size is too big. $pageNum > ${this.pageNum}")
        }

        return fetchPage(pageNum)
    }

    fun fetchPage(pageNum: Int): ByteBuffer {
        if (pageNum > this.pageNum) {
            println("Tried to fetch page number out of bounds. $pageNum > ${this.pageNum}")
            exitProcess(1);
        }
        val page = pages[pageNum]
        page.read(file)
        return page.data!!
    }
}