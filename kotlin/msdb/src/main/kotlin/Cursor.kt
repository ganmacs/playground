import java.nio.ByteBuffer

class Cursor(val node: Node, var cellNum: Int): Iterator<Row> {
    companion object {
        fun fromStart(table: Table): Cursor {
            val page = table.pager.fetchPage(table.rootPageNum)
            return Cursor(
                node = Leaf(page),
                cellNum = 0,
            )
        }

        fun fromEnd(table: Table): Cursor {
            val page = table.pager.fetchPage(table.rootPageNum)
            val l = Leaf(page)
            return Cursor(
                node = l,
                cellNum = l.numCell(),
            )
        }
    }

    fun insert(row: Row): Result<Unit> {
        if (node.asLeaf().numCell() > LEAF_NODE_MAX_CELLS) {
            return Result.failure(TODO("imple split"))
        }

        //if (node.numCell() != cellNum) {
        //    return Result.failure(Error("Invalid cell_num ${node.numCell()} != ${cellNum}"))
        //}
        return node.asLeaf().insertRow(cellNum, row).onSuccess {
            cellNum++
        }
    }

    /*
    private fun value(): ByteBuffer {
        node.asLeaf().getCell(cellNum)
    }
    */

    override fun hasNext(): Boolean {
        return cellNum < node.asLeaf().numCell()
    }

    override fun next(): Row {
        val buf = node.asLeaf().getCell(cellNum)
        cellNum++
        return Row.deserialize(buf)
    }
}