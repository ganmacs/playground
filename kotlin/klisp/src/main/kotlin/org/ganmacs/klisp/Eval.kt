package org.ganmacs.klisp

sealed class Value
object NilValue: Value()
data class IntValue(val vi: Int): Value()

class Evaluator {
    fun eval(nodes: List<Node>) {
        nodes.forEach {
            println(evalNode(it))
        }
    }

    private fun evalNode(node: Node): Value {
        return when(node) {
            is Atom -> when(val t = node.token) {
                is TInt -> IntValue(t.value)
                else -> NilValue
            }
            is ListCell -> {
                when (val car = node.car()) {
                    is Atom -> when (car.token) {
                        is TPlus -> {
                           IntValue(evalArgsAsInt(node.cdr()).reduce { acc, unit -> acc + unit })
                        }
                        is TMinus -> {
                            IntValue(evalArgsAsInt(node.cdr()).reduce { acc, unit -> acc - unit })
                        }
                        else -> {
                            throw IllegalStateException("not implemented yet ${car.token}")
                        }
                    }
                    else -> {
                        throw IllegalStateException("not implemented yet")
                    }
                }
            }
            else -> {
                throw IllegalStateException("unexpected token while evaulation: $node")
            }
        }
    }

    private fun evalArgsAsInt(node: Node): List<Int> {
        return evalArgs(node).map {
            when (it) {
                is IntValue -> it.vi
                else -> {
                    throw IllegalStateException("int value is expected: $it")
                }
            }
        }
    }

    private fun evalArgs(node: Node): List<Value> {
        return when (node) {
            is ListCell -> {
                val car = node.car()
                val cdr = node.cdr()
                when (cdr) {
                    Nil -> return listOf(evalNode(car))
                    else -> {
                        listOf(evalNode(car)) + evalArgs(cdr)
                    }
                }

            }
            is Atom -> listOf(evalNode(node))
            Nil -> listOf()
        }
    }
}