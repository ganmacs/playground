package com.ganmacs

import java.nio.ByteBuffer
import java.nio.ByteOrder

fun Byte.toStringByte(): String = Integer.toBinaryString(this.toUByte().toInt()).padStart(8, '0')

fun printIntArray(buf: ByteArray) = println(buf.map { it.toStringByte() })

private fun ByteBuffer.putU8(b: UByte): ByteBuffer = this.put(b.toByte())
private fun ByteBuffer.putU16(value: UShort): ByteBuffer = this.putShort(value.toShort())
private fun ByteBuffer.putU32(value: UInt): ByteBuffer = this.putInt(value.toInt())

fun main(args: Array<String>) {
    val buf = ByteBuffer.allocate(10)
        .order(ByteOrder.BIG_ENDIAN)

    buf.putU16(12u)
    buf.putU8(8u)
    buf.putU32(1024u)
    printIntArray(buf.array())
}
