import java.nio.ByteBuffer
import kotlin.system.exitProcess
import mu.KotlinLogging
import java.io.File

const val TABLE_MAX_PAGES = 100
const val PAGE_SIZE = 1024 * 4
const val ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE
const val TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES

val logger = KotlinLogging.logger {}

class Table(private val pager: Pager, var rowNum: Int = 0): Iterable<Row> {
     fun rowSlot(rowNum: Int): ByteBuffer {
        val pageId = rowNum / ROWS_PER_PAGE
        val page = pager.fetchPage(pageId)
        val rowOffset = rowNum % ROWS_PER_PAGE
        val byteOffset = rowOffset * ROW_SIZE
        //logger.info { "ReadPage: pageId = $pageId, rowOffset = $rowOffset byteOffset = $byteOffset"}
        return ByteBuffer.wrap(page, byteOffset, ROW_SIZE)
    }

    fun close() {
        pager.close()
    }

    override fun iterator(): Iterator<Row> {
        return Cursor.fromStart(this)
    }
}

sealed class Statement {
    class InsertStatement(val row: Row): Statement()
    class SelectStatement(): Statement()
}

fun handleMetaCommand(buf: String, table: Table): Result<Unit> {
    if (buf == ".exit") {
        closeDB(table)
        exitProcess(0)
    } else {
        return Result.failure(Error("unrecognized command $buf"))
    }
}

fun parseInput(input :String): Result<Statement> {
    val exprs = input.split(" ").map { it.trim() }.filter { it !== "" }
    logger.debug { exprs }
    return when (exprs.firstOrNull()) {
        "insert" -> {
            if (exprs.size != 4) {
                return Result.failure(Error("Syntax error: insert [ID] [USERNAME] [EMAIL]"))
            }
            val r = Row(exprs[1].toInt(), exprs[2].toByteArray(), exprs[3].toByteArray())
            Result.success(Statement.InsertStatement(r))
        }
        "select" -> Result.success(Statement.SelectStatement())
        else -> Result.failure(Error("invalid statement: ${exprs.joinToString { it }}"))
    }
}

fun printByte(b: ByteArray) {
    for (element in b) {
        print(element)
        print(" ")
    }
    println()
}

fun executeInsertStatement(insertStmnt: Statement.InsertStatement, table: Table): Result<Unit> {
    if (table.rowNum > TABLE_MAX_PAGES) {
        return Result.failure(Error("Error: Table full."))
    }

    val cur = Cursor.fromEnd(table)
    return insertStmnt.row.serialize(cur.value()).onSuccess {
        table.rowNum += 1
        return Result.success(Unit)
    }.onFailure {
        return Result.failure(it)
    }
}

fun executeSelectStatement(selectStmnt: Statement.SelectStatement, table: Table): Result<Unit> {
    val iter = table.iterator()
    while (iter.hasNext()) {
        println(iter.next())
    }
    return Result.success(Unit)
}

fun executeStatement(stmnt: Statement, table: Table): Result<Unit> {
     return when (stmnt){
      is Statement.InsertStatement -> executeInsertStatement(stmnt, table)
      is Statement.SelectStatement -> executeSelectStatement(stmnt, table)
    }
}

fun openDB(fileName: String): Table {
    val file = File(fileName)
    val pager = Pager(file)
    return Table(pager, pager.fileLength / PAGE_SIZE)
}

fun closeDB(table: Table) {
    table.close()
}

fun main(args: Array<String>) {
    if (args.isEmpty()) {
        println("Must supply a database filename.");
        exitProcess(1);
    }

    val table = openDB(args[0])
    while (true) {
        print("db > ")
        val input = readLine()
        if (input.isNullOrEmpty()) continue
        if (input[0] == '.') {
            handleMetaCommand(input, table).onFailure {
                println(it.message)
            }
            continue
        }
        Result.runCatching {
            val stmnt = parseInput(input).getOrThrow()
            executeStatement(stmnt, table).getOrThrow()
        }.onFailure {
            println(it.message)
        }.onSuccess {
            println("Executed.")
        }
    }
}