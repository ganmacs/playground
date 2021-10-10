import java.io.File
import java.io.RandomAccessFile
import java.nio.ByteBuffer
import kotlin.system.exitProcess

class Page(val num: Int) {
    var data: ByteBuffer? = null
        private set
    private val pageOffSet: Long = num.toLong() * PAGE_SIZE

    fun copyData(src: Page) {
        if (data == null) {
            data = ByteBuffer.wrap(ByteArray(PAGE_SIZE))
        }

        data!!.position(0)
        src.data!!.position(0)
        data!!.put(src.data)
    }

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
            data = null
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

    fun sync(pageNum: Int) {
        pages[pageNum].write(file)
    }

    fun createNewPage(): Result<Int> {
        pageNum += 1
        if (pageNum > TABLE_MAX_PAGES) {
            return Result.failure(Error("size is too big. $pageNum > ${this.pageNum}"))
        }

        return Result.success(pageNum)
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

    fun copyPage(dst: Int, src: Int) {
        pages[dst].copyData(pages[src])
    }
}

fun printPage1(page: ByteBuffer) {
    val node = Node(page)
    println("isRoot = ${node.isRoot()}")
    println("parentPointer = ${node.parent()}")
    when (val t = node.asNodeBody()) {
        is Leaf -> {
            println("NodeType = Leaf")
            println("numCell = ${t.numCell()}")
            for (i in 0 until t.numCell()) {
                println("key = ${t.getKey(i)}")
            }
        }
        is Internal -> {
            println("NodeType = Internal")
            println("numCell = ${t.numCell()}")
            println("rightMostChild = ${t.getRightChild()}")
            for (i in 0 until t.numCell()) {
                println("child = ${t.getChild(i)}, key = ${t.getKey(i)}")
            }
        }

    }
}

fun printPage(pageId: Int, pager: Pager, desc: String = "") {
    val page = pager.fetchPage(pageId)
    println("=============== $desc =============== start")
    println("pageId = $pageId")
    printPage1(page)
    println("=============== $desc =============== end")
}