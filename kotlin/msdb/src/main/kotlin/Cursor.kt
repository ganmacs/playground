class Cursor(
    val node: Node,
    var cellIdx: Int,
): Iterator<Row> {
    companion object {
        fun fromStart(table: Table): Cursor {
            val page = table.pager.fetchPage(table.rootPageNum)
            return Cursor(
                node = Leaf(page),
                cellIdx = 0,
            )
        }

        fun fromEnd(table: Table): Cursor {
            val page = table.pager.fetchPage(table.rootPageNum)
            val l = Leaf(page)
            return Cursor(
                node = l,
                cellIdx = l.numCell(),
            )
        }

        fun find(table: Table, id: Int): Cursor {
            val page = table.pager.fetchPage(table.rootPageNum)
            val node = Leaf(page)

            // TODO: check if node is leaf
            if (true) {
                val t = node.find(id)
          //      println("node $t")
                return Cursor(
                    node,
                    cellIdx = t,
                )
            } else {
                TODO("need to implement when node is internal")
            }
        }
    }

    fun insert(row: Row): Result<Unit> {
        val numCell = node.asLeaf().numCell()
        if (numCell > LEAF_NODE_MAX_CELLS) {
            return Result.failure(TODO("imple split"))
        }

        //println(node.asLeaf().getKey(cellIdx))
        //println(row.id)

        // shift all data to make space
        val leaf = node.asLeaf()
        if (numCell > cellIdx) {
            leaf.makeSpace(cellIdx)
        }

        if (node.asLeaf().getKey(cellIdx) == row.id) {
            return Result.failure(Error("Error: Duplicate key."))
        }

        return node.asLeaf().insertRow(cellIdx, row).onSuccess {
            cellIdx++
        }
    }

    /*
    private fun value(): ByteBuffer {
        node.asLeaf().getCell(cellNum)
    }
    */

    override fun hasNext(): Boolean {
        return cellIdx < node.asLeaf().numCell()
    }

    override fun next(): Row {
        val buf = node.asLeaf().getCell(cellIdx)
        cellIdx++
        return Row.deserialize(buf)
    }
}