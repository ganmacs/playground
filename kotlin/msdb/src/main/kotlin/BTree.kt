import java.nio.ByteBuffer
import kotlin.math.absoluteValue
import kotlin.system.exitProcess

// BODY = | type(2 bytes) | is_root(2 bytes) | parent_pointer (4 bytes) | LEFF_NODE* |
// LEAF_NODE = | nums_cells(4bytes) | LEAF_CELL* |
// LEAF_CELL = | key (4 bytes) | value (ROW_SIZE) |

/*
 * Common header offset
 */
const val NODE_TYPE_SIZE = 2 // short size is 2 bytes
const val NODE_TYPE_OFFSET = 0
const val IS_ROOT_SIZE = 2 // short
const val IS_ROOT_OFFSET = NODE_TYPE_OFFSET + NODE_TYPE_SIZE;
const val PARENT_POINTER_SIZE = 4 // int
const val PARENT_POINTER_OFFSET = IS_ROOT_OFFSET + IS_ROOT_SIZE
const val COMMON_NODE_HEADER_SIZE = NODE_TYPE_SIZE + IS_ROOT_SIZE + PARENT_POINTER_SIZE

/*
 * Leaf node Layout
 */
const val LEAF_NODE_NUM_CELLS_SIZE = 4 // int
const val LEAF_NODE_NUM_CELLS_OFFSET = COMMON_NODE_HEADER_SIZE
const val LEAF_NODE_HEADER_SIZE = COMMON_NODE_HEADER_SIZE + LEAF_NODE_NUM_CELLS_SIZE

/*
 * Leaf Node Body Layout
 */
const val LEAF_NODE_CELL_OFFSET = LEAF_NODE_HEADER_SIZE

const val LEAF_NODE_KEY_SIZE = 4 // byte. int
const val LEAF_NODE_KEY_OFFSET = 0 // Should be 0?
const val LEAF_NODE_VALUE_SIZE = ROW_SIZE
const val LEAF_NODE_VALUE_OFFSET = LEAF_NODE_KEY_OFFSET + LEAF_NODE_KEY_SIZE
const val LEAF_NODE_CELL_SIZE = LEAF_NODE_KEY_SIZE + LEAF_NODE_VALUE_SIZE
const val LEAF_NODE_SPACE_FOR_CELLS = PAGE_SIZE - LEAF_NODE_HEADER_SIZE
const val LEAF_NODE_MAX_CELLS = LEAF_NODE_SPACE_FOR_CELLS / LEAF_NODE_CELL_SIZE;

// enum?
const val LEAF_TYPE: Short = 0
const val INTERNAL_TYPE: Short = 1

sealed class Node(protected val buf: ByteBuffer) {
    fun asLeaf(): Leaf {
        return (this as Leaf) // TODO: fix
    }

    fun setAsLeaf() {
        buf.position(0)
        buf.putShort(LEAF_TYPE)
    }
}

class Leaf(buf: ByteBuffer): Node(buf) {
    private var numCell: Int? = null

    constructor(buf: ByteArray): this(ByteBuffer.wrap(buf)) {
        setAsLeaf()
    }

    fun numCell(): Int {
        if (this.numCell == null) {
            buf.position(LEAF_NODE_NUM_CELLS_OFFSET)
            this.numCell = buf.int
        }
        return this.numCell!!
    }

      fun setNumCell(num: Int) {
          buf.position(LEAF_NODE_NUM_CELLS_OFFSET)
          buf.putInt(num)
          this.numCell = num
    }

    fun find(key: Int): Int {
        var ok: Int = 0
        var ng: Int = numCell()*3
        var lim = 100
        while ((ng - ok).absoluteValue > 1) {
            lim--
            if (lim <= 0) {
                exitProcess(1)
            }
//          println("ok = $ok, ng = $ng")
            val mid = (ok + ng)/2
            if (mid > numCell()) {
                ng = mid
                continue
            }
            // FIXME
            if (mid == numCell()) {
                val keyAt = getKey(mid-1)
                //println("last mid = $mid key = $key keyAt = $keyAt")
                if (keyAt == key) {
                    return mid-1
                } else if (keyAt < key) {
                    return mid
                } else {
                    ng = mid-1
                    if (ng < ok) ok = ng
                }
                continue
            }

            val keyAt = getKey(mid)
            //println("mid = $mid key = $key keyAt = $keyAt")
            if (keyAt == key) return mid

            if (keyAt > key) {
                ng = mid
            } else {
                ok = mid
            }
        }

        if (key > getKey(ok)) {
            return if(ok+1 > numCell()) numCell() else ok+1
        }

        return ok
    }

    // shift all following key by a cell size
    fun makeSpace(at: Int) {
        val num = numCell()
        buf.position(LEAF_NODE_CELL_OFFSET + (at * LEAF_NODE_CELL_SIZE))
        val b = ByteArray((num-at) * LEAF_NODE_CELL_SIZE)
        buf.get(b) // copy `at` ~ last cell

        buf.position(LEAF_NODE_CELL_OFFSET + ((at+1) * LEAF_NODE_CELL_SIZE))
        buf.put(b) // copy `at + 1` ~ last cell to be able to insert new value at `at`
    }

    fun getCell(id: Int): ByteBuffer {
        buf.position(LEAF_NODE_CELL_OFFSET + (id * LEAF_NODE_CELL_SIZE) + LEAF_NODE_VALUE_OFFSET)
        return buf // TODO: restrict
    }

    fun getKey(id: Int): Int {
        buf.position(LEAF_NODE_CELL_OFFSET + (id * LEAF_NODE_CELL_SIZE))
        return buf.int // TODO: restrict
    }

    fun insertRow(key: Int, row: Row): Result<Unit> {
        if (LEAF_NODE_MAX_CELLS < key) {
            return Result.failure(TODO("Need to implement splitting a leaf node."))
        }

        buf.position(LEAF_NODE_CELL_OFFSET + (key * LEAF_NODE_CELL_SIZE) + LEAF_NODE_VALUE_OFFSET)
        return row.serialize(buf).onSuccess {
            buf.position(LEAF_NODE_CELL_OFFSET + (key * LEAF_NODE_CELL_SIZE))
            buf.putInt(row.id)
            setNumCell(numCell() + 1)
        }
    }
}

class Internal(buf: ByteBuffer): Node(buf) {
}


/*
sealed class Node(private val type: Short, val isRoot: Short, val pointerSize: Int) {
    val isLoad = false

    companion object {
        fun build(buf: ByteBuffer): Node {
            buf.rewind()
            val type = buf.short
            val isRoot = buf.short
            val pointerSize = buf.int

            return if (type == LEAF_TYPE) {
                Leaf(buf, isRoot, pointerSize)
            } else {
                Internal(buf, isRoot, pointerSize)
            }
        }
    }

    fun isLeaf(): Boolean {
        return type == LEAF_TYPE
    }

    fun isInternal(): Boolean {
        return type == INTERNAL_TYPE
    }

    abstract fun numCell(): Int
    abstract fun insert(key: Int, row: Row)
}

class Leaf(val buf: ByteBuffer, isRoot: Short = 0, pointerSize: Int = 0): Node(LEAF_TYPE, isRoot, pointerSize) {
    var numCell = 0
    var keys: MutableList<ByteArray> = mutableListOf()
    var values: MutableList<ByteArray> = mutableListOf()

    constructor(buf: ByteArray, isRoot: Short = 0, pointerSize: Int = 0): this(ByteBuffer.wrap(buf), isRoot, pointerSize)

    override fun numCell(): Int {
        return numCell
    }

    override fun insert(key: Int, row: Row) {
        ByteArray(ROW_SIZE).also {
            row.serialize(ByteBuffer.wrap(it))
            values.add(it)
        }
        ByteArray(4).also { // key size is int(4)
            ByteBuffer.wrap(it).putInt(key)
            keys.add(it)
        }
        numCell++;
    }

    private fun loadKeys(): MutableList<ByteArray> {
        return 0.rangeTo(numCell).map { i ->
            buf.position(LEAF_NODE_HEADER_SIZE + (i * LEAF_NODE_CELL_SIZE))
            ByteArray(ROW_SIZE).also { buf.get(it) }
        }.toMutableList()
    }

    private fun loadValues(): MutableList<ByteArray> {
        return 0.rangeTo(numCell).map { i ->
            buf.position(LEAF_NODE_HEADER_SIZE + (i * LEAF_NODE_CELL_SIZE) + LEAF_NODE_VALUE_SIZE)
            ByteArray(ROW_SIZE).also { buf.get(it) }
        }.toMutableList()
    }

    private fun loadNumCell(): Int {
        buf.position(LEAF_NODE_NUM_CELLS_OFFSET)
        return buf.int
    }
}

class Internal(buf: ByteBuffer, isRoot: Short, pointerSize: Int): Node(INTERNAL_TYPE, isRoot, pointerSize) {
    override fun numCell(): Int {
        TODO("implement")
    }

    override fun insert(key: Int, row: Row) {
        TODO("implement")
    }
}
*/
class BTree {
}