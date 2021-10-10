class Table(val pager: Pager, val rootPageNum: Int) {
    fun close() {
        pager.close()
    }

    fun insert(row: Row): Result<Unit> {
        val cur = Cursor.find(this, row.id)
        return cur.insert(row)
    }

    fun select(): Result<Unit> {
        val iter = Cursor.fromStart(this)
        while (iter.hasNext()) {
            println(iter.next())
        }
        return Result.success(Unit)
    }
}
