package org.ganmacs.klisp

import java.io.InputStream
import java.nio.file.Paths

fun process(input: InputStream) {
    val tokenStream = Lexer(input).call()
    println(tokenStream)
    val tree = Parser(tokenStream).parse()
    println(tree)
    PPrinter().pp(tree)
    Evaluator().eval(tree)
}

fun main(args: Array<String>) {
    println("start")
    val inputPath = Paths.get("src", "main", "resources", "test1.lisp")
    val inStream = inputPath.toFile().inputStream()

    process(inStream)
}

