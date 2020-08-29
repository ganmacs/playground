package org.ganmacs.klisp

import java.io.InputStream

open class LineInfo(val lineNo: Int, val index: Int)
open class Token(open val info: LineInfo)
data class TRightParen(override val info: LineInfo) : Token(info)
data class TLeftParen(override val info: LineInfo) : Token(info)
data class TPlus(override val info: LineInfo) : Token(info)
data class TMinus(override val info: LineInfo) : Token(info)
data class TMul(override val info: LineInfo) : Token(info)
data class TDiv(override val info: LineInfo) : Token(info)
data class TSpace(override val info: LineInfo) : Token(info)
data class TDot(override val info: LineInfo) : Token(info)
data class TDash(override val info: LineInfo) : Token(info)
data class TInt(val value: Int, override val info: LineInfo) : Token(info)
data class TSymbol(val value: String, override val info: LineInfo) : Token(info)

class PeekableStream(val inner: InputStream) {
    private var aheadChar: Char? = null
    var lineNo = 1
      private set
    var idx = 1
      private set
    var idxInline = 1
       private set

    fun peek(): Char? {
        aheadChar = aheadChar ?: readChar()
        return aheadChar
    }

    fun read(): Char? {
        val c = peek()
        aheadChar = null
        return c
    }

    fun consume(): Char? {
        val c = aheadChar
        aheadChar = null
        return c
    }

    fun toLineInfo(): LineInfo {
        return LineInfo(lineNo, idxInline)
    }

    private fun readChar(): Char? {
        val c = inner.read()
        idx += 1
        idxInline += 1
        // LF 10, CR 13
        if (c == 10 || c == 13) {
            lineNo += 1
            idxInline = 1
        }

        if (c == -1) {
            return null
        }
        return c.toChar()
    }
}

class Lexer(val input: PeekableStream) {
    constructor(ins: InputStream): this(PeekableStream(ins))

    private val SPACE = ' ';
    private val LPAREN = '(';
    private val RPAREN = ')';
    private val ADD_OP = '+';
    private val SUB_OP = '-';
    private val MUL_OP = '*';
    private val DIV_OP = '/';
    private val DOT = '.';
    private val SQUOTE = '\'';
    private val DQUOTE = '"';

    fun call(): List<Token> {
        var ret = mutableListOf<Token>()
        while (true) {
            val c = readToken() ?: break
            ret.add(c)
        }
       return ret.toList()
    }

    private fun readToken(): Token? {
        return when(val c = input.peek()) {
            SPACE -> {
                val li = input.toLineInfo()
                input.consume()
                TSpace(li)
            }
            LPAREN -> {
                val li = input.toLineInfo()
                input.consume()
                TLeftParen(li)
            }
            RPAREN -> {
                val li = input.toLineInfo()
                input.consume()
                TRightParen(li)
            }
            ADD_OP -> {
                val li = input.toLineInfo()
                input.consume()
                TPlus(li)
            }
            SUB_OP -> {
                val li = input.toLineInfo()
                input.consume()
                TMinus(li)
            }
            MUL_OP -> {
                val li = input.toLineInfo()
                input.consume()
                TMul(li)
            }
            DOT -> {
                val li = input.toLineInfo()
                input.consume()
                TDot(li)
            }
            in 'a'..'z' -> {
                val li = input.toLineInfo()
                TSymbol(readSymbol(), li)
            }
            in '0'..'9' -> {
                val li = input.toLineInfo()
                TInt(readInt(), li)
            }
            null -> null // expected EOF
            else -> {
                throw IllegalStateException("unexpected char: $c at line: ${input.lineNo}, at: ${input.idxInline}")
            }
         }
    }

    private fun readInt(): Int {
        val toInt = { v: Char -> v.toInt() - '0'.toInt() }
        var v = toInt(input.consume()!!)
        val nc = input.peek()
        if (v == 0 && nc != null && nc !in '0'..'9') {
            throw IllegalStateException("Invalid Int: 0${nc} a line: ${input.lineNo}, at: ${input.idxInline}")
        }

        while (true) {
            when (val nc = input.peek()) {
                in '0'..'9' -> {
                    v = (v * 10) + toInt(nc!!)
                    println(input.consume())
                }
                SPACE, RPAREN -> {
                    return v
                }
                else -> {
                    throw IllegalStateException("Invalid Int: $v$nc a line: ${input.lineNo}, at: ${input.idxInline}")
                }
            }
        }

        return 0
    }

    private fun readSymbol(): String {
        var s = input.consume()!!.toString()
        while (true) {
            when (val nc = input.peek()) {
                in 'a'..'z' -> {
                    input.consume()
                    s += nc
                }
                in 'A'..'Z' -> {
                    input.consume()
                    s += nc
                }
                '_' -> {
                    input.consume()
                    s += nc
                }
                SPACE, RPAREN -> {
                    return s
                }
                else -> {
                    throw IllegalStateException("Invalid symbol: $s$nc a line: ${input.lineNo}, at: ${input.idxInline}")
                }
            }
        }
    }
}
