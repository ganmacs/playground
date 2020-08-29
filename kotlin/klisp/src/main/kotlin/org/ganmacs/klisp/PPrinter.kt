package org.ganmacs.klisp

class PPrinter {
    fun pp(nodes: List<Node>) {
        innerPrettyPrint(nodes[0])
        val rest = nodes.subList(1, nodes.size)
        rest.forEach {
            innerPrettyPrint(it)
        }
        println("")
    }

    private fun innerPrettyPrint(node: Node) {
        when(node) {
            is Atom -> printAtom(node)
            is ListCell -> {
                print("(")
                val rest = node.inner.subList(1, node.inner.size)
                innerPrettyPrint(node.inner[0])
                rest.forEach {
                    print(" ")
                    innerPrettyPrint(it)
                }
                print(")")
            }
            is Nil -> {

            }
        }
    }

    private fun printAtom(node: Atom) {
        when (val t = node.token) {
            is TPlus -> print("+")
            is TMinus -> print("-")
            is TMul -> print("*")
            is TDiv -> print("/")
            is TInt -> print(t.value)
        }
    }
}