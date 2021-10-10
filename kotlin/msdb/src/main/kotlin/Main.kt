import kotlin.system.exitProcess
import mu.KotlinLogging
import java.io.File

const val TABLE_MAX_PAGES = 100
const val PAGE_SIZE = 1024 * 4
val logger = KotlinLogging.logger {}

sealed class Statement {
    class InsertStatement(val row: Row): Statement()
    object SelectStatement : Statement()
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
            printTree(table.pager, 0)
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
        "select" -> Result.success(Statement.SelectStatement)
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
      println("Constants:")
      println("ROW_SIZE: $ROW_SIZE")
      println("COMMON_NODE_HEADER_SIZE: $COMMON_NODE_HEADER_SIZE")
      println("LEAF_NODE_HEADER_SIZE: $LEAF_NODE_HEADER_SIZE")
      println("LEAF_NODE_CELL_SIZE: $LEAF_NODE_CELL_SIZE")
      println("LEAF_NODE_SPACE_FOR_CELLS: $LEAF_NODE_SPACE_FOR_CELLS")
      println("LEAF_NODE_MAX_CELLS: $LEAF_NODE_MAX_CELLS")
}

fun printIndent(level: Int) {
    for (i in 0.until(level)) {
        print("  ")
    }
}

fun printTree(pager: Pager, pageNum: Int) {
    println("Tree:")
    printTreeInner(pager, pageNum, 0)
}

fun printTreeInner(pager: Pager, pageNum: Int, level: Int) {
    val page = pager.fetchPage(pageNum)
    when (val node = Node(page).asNodeBody()) {
        is Leaf -> printLeafNode(node, level)
        is Internal -> printInternalNode(pager, node, level)
    }

}

fun printLeafNode(leaf: Leaf, level: Int) {
    val numCells = leaf.numCell()
    printIndent(level)
    println("- leaf (size $numCells)")
    for (i in 0 until numCells) {
        printIndent(level + 1)
        println("- ${leaf.getKey(i)}")
    }
}

fun printInternalNode(pager: Pager, internal: Internal, level: Int) {
    val numCells = internal.numCell()
    printIndent(level)
    println("- internal (size $numCells)")
    for (i in 0 until numCells) {
        val num = internal.getChild(i)
        printTreeInner(pager, num, level + 1)

        printIndent(level + 1)
        println("- key ${internal.getKey(i)}")
    }

    val righChild = internal.getRightChild()
    printTreeInner(pager, righChild, level+1)
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
        val page = pager.fetchPage(0) // always 0
        Node(page).initializeAsLeaf(root = true)
    }
    return Table(pager, 0)
}

fun closeDB(table: Table) {
    table.close()
}

fun main(args: Array<String>) {
    if (args.isEmpty()) {
        println("Must supply a database filename.")
        exitProcess(1)
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
            if (it.message == null || it.message == "") {
                println(it)
                it.stackTrace.forEach { i -> println("${i.fileName}:${i.lineNumber}") }
            } else {
                println(it.message)
            }
        }.onSuccess {
            println("Executed.")
        }
    }
}