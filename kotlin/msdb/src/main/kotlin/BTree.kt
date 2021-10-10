import java.lang.Error
import java.nio.ByteBuffer

/*
 BODY = | type(2 bytes) | is_root(2 bytes) 0 is false | parent_pointer (4 bytes) | (LEAF_NODE or INTERNAL_NODE) |
 LEAF_NODE = | num_cells(4bytes) | LEAF_CELL* |
 LEAF_CELL = | key (4 bytes) | value (ROW_SIZE) |
 INTERNAL_NODE = | num_cells(4 bytes) | right most child(4 bytes) |
 INTERNAL_CELL = | child pointer (4 bytes) | key (4 bytes)
 */

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

/*
 * Internal Node Header Layout
 */
const val INTERNAL_NODE_NUM_KEYS_SIZE = 4
const val INTERNAL_NODE_NUM_KEYS_OFFSET = COMMON_NODE_HEADER_SIZE
const val INTERNAL_NODE_RIGHT_CHILD_SIZE = 4
const val INTERNAL_NODE_RIGHT_CHILD_OFFSET = INTERNAL_NODE_NUM_KEYS_OFFSET + INTERNAL_NODE_NUM_KEYS_SIZE
const val INTERNAL_NODE_HEADER_SIZE = COMMON_NODE_HEADER_SIZE + INTERNAL_NODE_NUM_KEYS_SIZE + INTERNAL_NODE_RIGHT_CHILD_SIZE

/*
 * Internal Node Body Layout
 */

const val INTERNAL_NODE_CELL_OFFSET = INTERNAL_NODE_HEADER_SIZE

const val INTERNAL_NODE_KEY_SIZE = 4
const val INTERNAL_NODE_CHILD_SIZE = 4
const val INTERNAL_NODE_CELL_SIZE = INTERNAL_NODE_CHILD_SIZE + INTERNAL_NODE_KEY_SIZE

enum class NodeType(val idx: Short) {
    LEAF_TYPE(0),
    INTERNAL_TYPE(1),
}

class Node(private val buf: ByteBuffer) {
    fun initializeAsLeaf(root: Boolean = false) {
        nodeHeaderInitialize(NodeType.LEAF_TYPE, root)
        buf.putInt(LEAF_NODE_NUM_CELLS_OFFSET, 0)
    }

    fun initializeAsInternal(root: Boolean = false) {
        nodeHeaderInitialize(NodeType.INTERNAL_TYPE, root)
        buf.putInt(INTERNAL_NODE_NUM_KEYS_OFFSET, 0)
    }

    fun asNodeBody(): NodeBody {
        return NodeBody.new(nodeType(), buf)
    }

    fun nodeType(): NodeType {
        buf.position(NODE_TYPE_OFFSET)
        return when (buf.short.toInt()) {
            0 -> NodeType.LEAF_TYPE
            1 -> NodeType.INTERNAL_TYPE
            else -> throw Error("unknown type")
        }
    }

    fun parent(): Int {
        buf.position(PARENT_POINTER_OFFSET)
        return buf.int
    }

    fun setRoot(root: Boolean) {
        buf.putShort(IS_ROOT_OFFSET, if (root) 1 else 0 )
    }

    fun isRoot(): Boolean {
        buf.position(IS_ROOT_OFFSET)
        return (buf.short.toInt() == 1)
    }

    private fun nodeHeaderInitialize(nodeType: NodeType, root: Boolean) {
        buf.putShort(NODE_TYPE_OFFSET, nodeType.idx)
        setRoot(root)
    }
}

sealed class NodeBody(val buf: ByteBuffer) {
    companion object {
        fun new(nodeType: NodeType, buf: ByteBuffer): NodeBody {
            return when(nodeType) {
                NodeType.LEAF_TYPE -> Leaf(buf)
                NodeType.INTERNAL_TYPE -> Internal(buf)
            }
        }
    }

    fun getMaxKey(): Int {
        return when (this) {
            is Leaf -> {
                this.getKey(this.numCell()-1)
            }
            is Internal -> this.getKey(this.numCell()-1)
        }
    }
        //abstract fun insert(key: Int, row: Row): Result<Unit>
}

class Leaf(buf: ByteBuffer): NodeBody(buf) {
    private var numCell: Int? = null

    fun numCell(): Int {
        this.numCell?.also {
            return it
        }

        buf.position(LEAF_NODE_NUM_CELLS_OFFSET)
        val r = buf.int
        this.numCell = r
        return r
    }

    fun find(key: Int): Int {
        return bsearch(key)
    }

    fun insert(key: Int, row: Row): Result<Unit> {
        buf.position(LEAF_NODE_CELL_OFFSET + (key * LEAF_NODE_CELL_SIZE) + LEAF_NODE_VALUE_OFFSET)

        return row.serialize(buf).onSuccess {
            buf.putInt(LEAF_NODE_CELL_OFFSET + (key * LEAF_NODE_CELL_SIZE), row.id)
            setNumCell(numCell() + 1)
        }
    }

    fun makeSpace(at: Int) {
        val end = numCell()
        val b = ByteArray((end - at) * LEAF_NODE_CELL_SIZE)
        buf.position(LEAF_NODE_CELL_OFFSET + (at * LEAF_NODE_CELL_SIZE))
        buf.get(b) // copy `at` ~ last cell

        buf.position(LEAF_NODE_CELL_OFFSET + ((at + 1) * LEAF_NODE_CELL_SIZE))
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

    private fun bsearch(key: Int): Int {
        var left = 0
        var right = numCell()
        while (right != left) {
            val mid = (left + right) / 2
            val keyAtIdx = nodeKey(mid)
            if (keyAtIdx == key) {
                return mid
            } else if (keyAtIdx > key) {
                right = mid
            } else {
                left = mid + 1
            }
        }
        return left
    }

    fun setNumCell(num: Int) {
        buf.putInt(LEAF_NODE_NUM_CELLS_OFFSET, num)
//        println("set numcell=$num")
        this.numCell = num
    }

    private fun nodeKey(num: Int): Int {
        buf.position(LEAF_NODE_CELL_OFFSET + (num * LEAF_NODE_CELL_SIZE))
        return buf.int
    }
}

class Internal(buf: ByteBuffer): NodeBody(buf) {
    private var numCell: Int? = null

    fun numCell(): Int {
        buf.position(INTERNAL_NODE_NUM_KEYS_OFFSET)
        val r = buf.int
        this.numCell = r
        return r
    }

    fun setNumCell(num: Int) {
        buf.putInt(INTERNAL_NODE_NUM_KEYS_OFFSET, num)
        this.numCell = num
    }

    fun getRightChild(): Int {
        buf.position(INTERNAL_NODE_RIGHT_CHILD_OFFSET)
        return buf.int
    }

    fun setRightChild(i: Int) {
        buf.putInt(INTERNAL_NODE_RIGHT_CHILD_OFFSET, i)
    }

    fun getKey(i: Int): Int {
        buf.position(INTERNAL_NODE_CELL_OFFSET + INTERNAL_NODE_CELL_SIZE * i + INTERNAL_NODE_CHILD_SIZE)
        return buf.int
    }

    fun setKey(i: Int, key: Int) {
        buf.putInt(INTERNAL_NODE_CELL_OFFSET + INTERNAL_NODE_CELL_SIZE * i + INTERNAL_NODE_CHILD_SIZE, key)
    }

    fun getChild(i: Int): Int {
        buf.position(INTERNAL_NODE_CELL_OFFSET + INTERNAL_NODE_CELL_SIZE * i)
        return buf.int
    }


    fun setChild(i: Int, key: Int) {
        buf.putInt(INTERNAL_NODE_CELL_OFFSET + INTERNAL_NODE_CELL_SIZE * i, key)
    }

    /*fun insert(key: Int, row: Row): Result<Unit> {
        TODO("should not pass. it's bug")
    }*/
}