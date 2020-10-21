import com.fasterxml.jackson.module.kotlin.KotlinModule
import com.zaxxer.hikari.HikariDataSource
import mu.KotlinLogging
import io.dropwizard.Application
import io.dropwizard.Configuration
import io.dropwizard.jackson.Jackson
import io.dropwizard.jackson.JsonSnakeCase
import io.dropwizard.setup.Bootstrap
import io.dropwizard.setup.Environment
import org.jooq.*
import org.jooq.impl.DefaultConfiguration
import javax.ws.rs.core.MediaType;
import org.jooq.impl.DSL

import javax.validation.Valid
import javax.ws.rs.*

val baseMapper = Jackson.newObjectMapper().registerModule(KotlinModule())

private val logger = KotlinLogging.logger {}

data class FirstResponse(val name: String)
data class ResultResponse(val text: String)

data class UserTable(val id: Int, val username: String) {
    companion object {
        val tableName = DSL.table("users")
        val f_id = DSL.field("id")
        val f_username = DSL.field("username")

        val fields = setOf(
            "id",
            "username"
        ).map { DSL.field(it) }

        val recordMapper: RecordMapper<Record, UserTable> = RecordMapper<Record, UserTable> { UserTable(it) }
    }

    constructor(record: Record) : this(
        id = record.get(f_id, Int::class.java),
        username = record.get(f_username, String::class.java),
    )
}

class UserDatabaseQuery(private val dbctx: DSLContext) {
    fun where(ids: List<Int>? = null): List<UserTable> {
        return dbctx.select()
            .from(UserTable.tableName)
            .apply {
                ids?.let {
                    if (it.isNotEmpty()) {
                        where(UserTable.f_id.`in`(ids.toTypedArray()))
                    }
                }
            }
            .fetch(UserTable.recordMapper)
    }

    fun create(id: Int, username: String): UserTable {
        return dbctx.insertInto(UserTable.tableName)
            .set(UserTable.f_id, id)
            .set(UserTable.f_username, username)
            .returning(UserTable.fields)
            .fetchOne()
            .map(UserTable.recordMapper)
    }

    fun first(): UserTable? {
        return dbctx
            .select()
            .from(UserTable.tableName)
            .limit(1)
            .fetchOptional(UserTable.recordMapper)
            .orElse(null)
    }
}

@Path("/hello")
@Produces(MediaType.APPLICATION_JSON)
class SampleResource(private val dbCtx: DSLContext, private val hi: String) {
    val USER_TABLE_NAME = DSL.table("users")

    @GET
    @Path("/hello")
    fun index(@QueryParam("hello") hello: String?): FirstResponse {
        val users = UserDatabaseQuery(dbCtx).first()
        return FirstResponse(users?.username ?: "hi")
    }

    @GET
    @Path("set")
    fun create(@QueryParam("value") value: String): ResultResponse {
        val r = UserDatabaseQuery(dbCtx).create(
            id = 1,
            username = value
        )

        return ResultResponse(r.username)
    }
}

@JsonSnakeCase
data class DatabaseConfig(
    val url: String,
    val maxPoolSize: Int,
    val minPoolSize: Int,
) {
    fun build(): DSLContext {
        val dataSource = HikariDataSource().apply {
            jdbcUrl = url
            password = "postgres"
            username = "postgres"
        }
        val conf = DefaultConfiguration().set(dataSource).set(SQLDialect.POSTGRES)
        return DSL.using(conf)
    }
}

@JsonSnakeCase
data class MyConfig(
    @field:Valid val database: DatabaseConfig,
    val template: String,
) : Configuration()

class Api : Application<MyConfig>() {
    override fun initialize(bootstrap: Bootstrap<MyConfig>) {
        // Enable serde of data class of kotlin
        bootstrap.objectMapper = baseMapper
    }

    override fun run(config: MyConfig, environment: Environment) {
        val dbContext = config.database.build()
        environment.jersey().register(SampleResource(dbContext, "hi"))
    }
}

fun main(args: Array<String>) {
    Api().run(*args)
}
