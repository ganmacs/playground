import java.nio.ByteBuffer
import kotlin.system.exitProcess
import mu.KotlinLogging
import java.io.File

const val TABLE_MAX_PAGES = 100
const val PAGE_SIZE = 1024 * 4
val logger = KotlinLogging.logger {}

class Table(val pager: Pager, val rootPageNum: Int) {
    fun close() {
        pager.close()
    }

    fun insert(row: Row): Result<Unit> {
        val cur = Cursor.fromEnd(this)
        if (cur.cellNum >= LEAF_NODE_MAX_CELLS) {
            return Result.failure(Error("Error: Table full."))
        }

        return cur.insert(row).onFailure {
            return Result.failure(it)
        }
    }

    fun select(): Result<Unit> {
        val iter = Cursor.fromStart(this)
        while (iter.hasNext()) {
            println(iter.next())
        }
        return Result.success(Unit)
    }
}

sealed class Statement {
    class InsertStatement(val row: Row): Statement()
    class SelectStatement(): Statement()
}

fun handleMetaCommand(buf: String, table: Table): Result<Unit> {
    when (buf) {
        ".exit" -> {
            closeDB(table)
            exitProcess(0)
        }
        ".constants" -> {
            printConstants()
            return Result.success(Unit)
        }
        ".btree" -> {
            printLeafNode(Leaf(table.pager.fetchPage(0)))
            return Result.success(Unit)
        }
        else -> {
            return Result.failure(Error("unrecognized command $buf"))
        }
    }
}

fun parseInput(input :String): Result<Statement> {
    val exprs = input.split(" ").map { it.trim() }.filter { it !== "" }
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

fun printConstants() {
      println("Constants:");
      println("ROW_SIZE: $ROW_SIZE");
      println("COMMON_NODE_HEADER_SIZE: $COMMON_NODE_HEADER_SIZE");
      println("LEAF_NODE_HEADER_SIZE: $LEAF_NODE_HEADER_SIZE");
      println("LEAF_NODE_CELL_SIZE: $LEAF_NODE_CELL_SIZE");
      println("LEAF_NODE_SPACE_FOR_CELLS: $LEAF_NODE_SPACE_FOR_CELLS");
      println("LEAF_NODE_MAX_CELLS: $LEAF_NODE_MAX_CELLS");
}

fun printLeafNode(node: Node) {
    println("Tree:")
    val numCells = node.asLeaf().numCell()
    println("leaf (size $numCells)")
    for (i in 0 until numCells) {
        val key = node.asLeaf().getCell(i).int
        println("  - $i : $key")
    }
}

fun executeInsertStatement(insertStmnt: Statement.InsertStatement, table: Table): Result<Unit> {
    return table.insert(insertStmnt.row)
}

fun executeSelectStatement(selectStmnt: Statement.SelectStatement, table: Table): Result<Unit> {
    return table.select()
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

    if (pager.fileLength == 0) {
        val page = pager.fetchPage(0)
        val l = Leaf(page)
    }
    return Table(pager, 0)
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