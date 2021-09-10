import java.nio.ByteBuffer
import java.nio.charset.Charset

const val INT_SIZE = 4 // putInt is 4?
const val ID_SIZE = 4 // putInt is 4?
const val USERNAME_SIZE = 32
const val EMAIL_SIZE = 255

const val ID_OFFSET = 0
const val USERNAME_OFFSET = ID_OFFSET + ID_SIZE
const val EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE
const val ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE

class Row(val id: Int, val userName: ByteArray, val email: ByteArray) {
    companion object {
        fun deserialize(buf: ByteBuffer): Row {
            val idx = buf.position() // FIXME

            val id = buf.int
            buf.position(USERNAME_OFFSET + idx)
            val userNameSize = buf.int
            val userName = ByteArray(userNameSize).also {
                buf.get(it, 0, userNameSize)
            }

            buf.position(EMAIL_OFFSET + idx)
            val emailSize = buf.int
            val email = ByteArray(emailSize).also {
                buf.get(it, 0, emailSize)
            }
            return Row(id, userName, email)
        }
    }

    override fun toString(): String {
        return "Row(id = $id, userName = ${userName.toString(Charset.defaultCharset())}, email = ${email.toString(
            Charset.defaultCharset())})"
    }

    fun serialize(dst: ByteBuffer){
        dst.putInt(id)
        if (userName.size > (USERNAME_SIZE - INT_SIZE)) {
            throw Error("invalid size for userName. username should be less than $USERNAME_SIZE")
        }
        ByteBuffer.allocate(USERNAME_SIZE - INT_SIZE).also {
            dst.putInt(userName.size)
            it.put(userName)
            dst.put(it.array())
        }

        if (email.size > (EMAIL_SIZE - INT_SIZE)) {
            throw Error("invalid size for userName. email should be less than $EMAIL_SIZE")
        }
        ByteBuffer.allocate(EMAIL_SIZE - INT_SIZE).also {
            dst.putInt(email.size)
            it.put(email)
            dst.put(it.array())
        }
    }
}