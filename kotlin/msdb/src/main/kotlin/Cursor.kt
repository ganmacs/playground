class Cursor(var cellIdx: Int, val pageIdx: Int, val pager: Pager): Iterator<Row> {
    companion object {
        fun find(table: Table, key: Int): Cursor {
            val page = table.pager.fetchPage(table.rootPageNum)
            return when (val node = Node(page).asNodeBody()) {
                is Leaf -> {
                    return Cursor(
                        cellIdx = node.find(key),
                        pageIdx = table.rootPageNum,
                        pager = table.pager,
                    )
                }
                is Internal -> {
                    TODO("need to implement when node is internal")
                }
            }
        }

        fun fromStart(table: Table): Cursor {
            return find(table, 0)
        }
    }

    override fun hasNext(): Boolean {
        if (pager.pageNum < pageIdx) {
            return false
        }

        val page = pager.fetchPage(pageIdx)
        return when (val node = Node(page).asNodeBody()) {
            is Leaf -> (node.numCell() > cellIdx)
            is Internal -> {
                TODO("need to implement when node is internal")
            }
        }
    }

    override fun next(): Row {
        val page = pager.fetchPage(cellIdx)
        return when (val node = Node(page).asNodeBody()) {
            is Leaf -> {
                val buf = node.getCell(cellIdx)
                cellIdx++
                Row.deserialize(buf)
            }
            is Internal -> {
                TODO("need to implement when node is internal")
            }
        }
    }

    fun insert(row: Row): Result<Unit> {
        val page = pager.fetchPage(pageIdx)
        return when (val node = Node(page).asNodeBody()) {
            is Leaf -> {
                val numCell = node.numCell()
                if (numCell > LEAF_NODE_MAX_CELLS) {
                    return insertAndSplit(row)
                }

                if (numCell > cellIdx) {
                    node.makeSpace(cellIdx) // for insertion point
                }

                node.insert(cellIdx, row)
                Result.success(Unit)
            }
            is Internal -> {
                TODO("need to implement when node is internal")
            }
        }
    }

    private fun insertAndSplit(row: Row): Result<Unit> {
        TODO("insert and split")
    }
}