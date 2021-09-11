import java.nio.ByteBuffer

class Cursor(val table: Table, var rowNum: Int, var endOfTable: Boolean): Iterator<Row> {
    companion object {
        fun fromStart(table: Table): Cursor {
            return Cursor(
                table,
                rowNum = 0,
                endOfTable = (table.rowNum == 0)
            )
        }

        fun fromEnd(table: Table): Cursor {
            return Cursor(
                table,
                rowNum = table.rowNum,
                endOfTable = true,
            )
        }
    }

    fun value(): ByteBuffer {
        return table.rowSlot(rowNum)
    }

    override fun hasNext(): Boolean {
        return rowNum < table.rowNum
    }

    override fun next(): Row {
        val buf = value()
        rowNum++
        return Row.deserialize(buf)
    }
}