import java.nio.ByteBuffer
import kotlin.system.exitProcess
import mu.KotlinLogging

const val TABLE_MAX_PAGES = 100
const val PAGE_SIZE = 1024 * 4
const val ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE
const val TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES

val logger = KotlinLogging.logger {}

class RowTableIter(val table: Table): Iterator<Row> {
    var i = 0
    override fun hasNext(): Boolean {
        return i < table.rowNum
    }

    override fun next(): Row {
        val buf = table.rowSlot(i)
        i++
        return Row.deserialize(buf)
    }
}

class Table(var rowNum: Int = 0): Iterable<Row> {
    var pages = 0.rangeTo(TABLE_MAX_PAGES).map { ByteArray(PAGE_SIZE) }

    fun rowSlot(rowNum: Int): ByteBuffer {
        val pageId = rowNum / ROWS_PER_PAGE
        val page = pages[pageId]
        val rowOffset = rowNum % ROWS_PER_PAGE
        val byteOffset = rowOffset * ROW_SIZE
        //logger.info { "ReadPage: pageId = $pageId, rowOffset = $rowOffset byteOffset = $byteOffset"}
        println("ReadPage: pageId = $pageId, rowOffset = $rowOffset byteOffset = $byteOffset")
        return ByteBuffer.wrap(page, byteOffset, ROW_SIZE)
    }

    override fun iterator(): Iterator<Row> {
        return RowTableIter(this)
    }
}

sealed class Statement {
    class InsertStatement(val row: Row): Statement()
    class SelectStatement(): Statement()
}

fun handleMetaCommand(buf: String): Result<String> {
    if (buf == ".exit") {
        exitProcess(0)
    } else {
        try {
            throw Error("unrecognized command $buf")
        } catch (e: Throwable) {
            return Result.failure(e)
        }
    }
}

fun parseInput(input :String): Statement {
    val exprs = input.split(" ").map { it.trim() }.filter { it !== "" }
    logger.debug { exprs }
    return when (exprs.firstOrNull()) {
        "insert" -> {
            if (exprs.size != 4) {
                throw Error("Syntax error: insert [ID] [USERNAME] [EMAIL]")
            }
            val r = Row(exprs[1].toInt(), exprs[2].toByteArray(), exprs[3].toByteArray())
            Statement.InsertStatement(r)
        }
        "select" -> Statement.SelectStatement()
        else -> throw Error("invalid statement: ${exprs.joinToString { it }}")
    }
}

fun printByte(b: ByteArray) {
    for (element in b) {
        print(element)
        print(" ")
    }
    println()
}

fun executeInsertStatement(insertStmnt: Statement.InsertStatement, table: Table) {
    if (table.rowNum > TABLE_MAX_PAGES) {
        throw Error("table is full")
    }
    insertStmnt.row.serialize(table.rowSlot(table.rowNum))
    table.rowNum += 1

    // TODO: return something
}

fun executeSelectStatement(selectStmnt: Statement.SelectStatement, table: Table) {
    val iter = table.iterator()
    while (iter.hasNext()) {
        println(iter.next())
    }
}

fun executeStatement(stmnt: Statement, table: Table) {
     when (stmnt){
      is Statement.InsertStatement -> {
          executeInsertStatement(stmnt, table)
          println("insert statement here")
      }
      is Statement.SelectStatement -> {
          executeSelectStatement(stmnt, table)
          println("insert statement here")
       }
    }
}

fun main(args: Array<String>) {
    val table = Table()

    while (true) {
        print("db > ")
        val input = readLine()
        if (input.isNullOrEmpty()) continue
        if (input[0] == '.') {
            handleMetaCommand(input).onFailure {
                println(it.message)
            }
            continue
        }

        val stmnt = parseInput(input)
        executeStatement(stmnt, table)
    }
}