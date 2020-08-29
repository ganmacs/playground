package org.ganmacs.klisp

sealed class Node
object Nil: Node()
data class Atom(val token: Token): Node()

data class ListCell(val inner: List<Node>): Node() {
    fun car(): Node {
        return inner[0]
    }

    fun cdr(): Node {
        val v = inner.subList(1, inner.size)
        return if (v.isEmpty()) {
            Nil
        } else {
            ListCell(inner.subList(1, inner.size))
        }
    }
}

class Parser(val tokenStream: List<Token>) {
    private var index = 0

    fun parse(): List<Node> {
        val r = mutableListOf<Node>()
        return listOf(buildTree())
    }

    fun buildTree(): Node {
        while (index < tokenStream.size) {
            when (val t = tokenStream[index]) {
                is TLeftParen -> {
                    index += 1
                    return ListCell(buildList())
                }
                is TSpace -> {
                    index += 1
                }
                else -> {
                    throw IllegalStateException("unexpected token: $t at line: ${t.info.lineNo}, point in line:${t.info.index}")
                }
            }
        }

        return Nil
    }

    private fun buildList(): List<Node> {
        var r = mutableListOf<Node>()

        while (index < tokenStream.size) {
            val t = tokenStream[index]
            index += 1
            when (t) {
                is TRightParen -> {
                    index += 1 // consume Right paren
                    break
                }
                is TLeftParen -> {
                    index -= 1
                    r.add(buildTree())
                }
                is TSpace -> {
                    // nothing
                }
                is TSymbol, is TInt, is TPlus, is TMul, is TDiv, is TMinus -> {
                    r.add(Atom(t))
                }
                else -> {
                    throw IllegalStateException("unpexected token: $t at line: ${t.info.lineNo}, idex in line:${t.info.index}")
                }
            }
        }
        return r.toList()
    }
}

