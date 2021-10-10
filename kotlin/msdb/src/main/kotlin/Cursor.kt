const val LEAF_NODE_RIGHT_SPLIT_COUNT = LEAF_NODE_MAX_CELLS / 2
const val LEAF_NODE_LEFT_SPLIT_COUNT = LEAF_NODE_MAX_CELLS - LEAF_NODE_RIGHT_SPLIT_COUNT

class Cursor(var cellIdx: Int, val pageIdx: Int, val table: Table): Iterator<Row> {
    companion object {
        fun find(table: Table, key: Int): Cursor {
            return _find(table, table.rootPageNum, key)
        }

        fun _find(table: Table, pageIdx: Int, key: Int): Cursor {
            val page = table.pager.fetchPage(pageIdx)
            val node = Node(page).asNodeBody()
            val child = node.find(key)
            return when (node) {
                is Leaf -> Cursor(cellIdx = child, pageIdx, table)
                is Internal -> _find(table, child, key)
            }
        }

        fun fromStart(table: Table): Cursor {
            return find(table, 0)
        }
    }

    override fun hasNext(): Boolean {
        if (table.pager.pageNum < pageIdx) {
            return false
        }

        val page = table.pager.fetchPage(pageIdx)
        return (Node(page).asNodeBody().numCell() > cellIdx)
        /*return when (val node = Node(page).asNodeBody()) {
            is Leaf -> (node.numCell() > cellIdx)
            is Internal -> {
                TODO("need to implement when node is internal")
            }
        }*/
    }

    override fun next(): Row {
        val page = table.pager.fetchPage(cellIdx)
        return when (val node = Node(page).asNodeBody()) {
            is Leaf -> {
                val buf = node.getCell(cellIdx)
                cellIdx++
                Row.deserialize(buf)
            }
            is Internal -> {
                TODO("need to implement when node is internal2")
            }
        }
    }

    fun insert(row: Row): Result<Unit> {
        val page = table.pager.fetchPage(pageIdx)
        return when (val node = Node(page).asNodeBody()) {
            is Leaf -> {
                val numCell = node.numCell()
                if (numCell >= LEAF_NODE_MAX_CELLS) {
                    return insertAndSplit(row)
                }

                if (numCell > cellIdx) {
                    node.makeSpace(cellIdx) // for insertion point
                }

                node.insert(cellIdx, row)
            }
            is Internal -> {
                TODO("need to implement when node is internal3")
            }
        }
    }

    private fun insertAndSplit(row: Row): Result<Unit> {
        val newPageIdx = table.pager.createNewPage().onFailure { return Result.failure(it) }.getOrThrow()
        val newNode = Node(table.pager.fetchPage(newPageIdx))
        newNode.initializeAsLeaf()
        val newLeaf = newNode.asNodeBody() as Leaf

        val oldPage = table.pager.fetchPage(pageIdx)
        val oldNode = Node(oldPage)
        when (val body = oldNode.asNodeBody()) {
            is Leaf -> {
                val oldLeaf = body // FIXME: just rename
                newLeaf.buf.position(LEAF_NODE_CELL_OFFSET)
                oldLeaf.buf.position(LEAF_NODE_CELL_OFFSET + (LEAF_NODE_LEFT_SPLIT_COUNT*LEAF_NODE_CELL_SIZE))
                newLeaf.buf.put(oldLeaf.buf) // copy right half nodes to new node

                oldLeaf.setNumCell(LEAF_NODE_LEFT_SPLIT_COUNT)
                newLeaf.setNumCell(LEAF_NODE_RIGHT_SPLIT_COUNT)

                // insert
                val destination = if (cellIdx <= LEAF_NODE_LEFT_SPLIT_COUNT) oldLeaf else newLeaf
                if (destination.numCell() > cellIdx) {
                    destination.makeSpace(cellIdx) // for insertion point
                }

                destination.insert(cellIdx % LEAF_NODE_LEFT_SPLIT_COUNT, row).onFailure {
                    return Result.failure(it)
                }

                if (oldNode.isRoot()) {
                    return createNewRoot(newPageIdx)
                } else {
                    TODO("need to implement")
                }
            }
            is Internal -> {
                TODO("need to implement when node is internal")
            }
        }
    }

    private fun createNewRoot(rightPageIdx: Int): Result<Unit> {
        val leftLeafIdx = table.pager.createNewPage().onFailure { return Result.failure(it) }.getOrThrow()
        table.pager.copyPage(dst = leftLeafIdx, src = table.rootPageNum) // old root node will be left node
        val lnode = Node(table.pager.fetchPage(leftLeafIdx))
        lnode.setRoot(false)

        // root node is new internal node
        val rootNode = Node(table.pager.fetchPage(table.rootPageNum))
        rootNode.initializeAsInternal(true)
        val interNode = rootNode.asNodeBody() as Internal
        interNode.setNumCell(1)
        interNode.setChild(0, leftLeafIdx)
        interNode.setKey(0, lnode.asNodeBody().getMaxKey())
        interNode.setRightChild(rightPageIdx)

//        printPage(table.rootPageNum, table.pager, "rootPage")
//        printPage(leftLeafIdx, table.pager, "newLeftPage")
//        printPage(rightPageIdx, table.pager, "newRigthage")

        return Result.success(Unit)
    }
}