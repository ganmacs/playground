import org.jetbrains.kotlin.gradle.tasks.KotlinCompile

plugins {
    kotlin("jvm") version "1.4.10"
    application
    idea

    //id("org.jmailen.kotlinter") version "3.2.0"
}

group = "me.user"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

dependencies {
    testImplementation(kotlin("test-junit"))

    val coroutineVersion = "1.3.9"
    implementation("org.jetbrains.kotlinx:kotlinx-coroutines-core:$coroutineVersion")
    implementation("org.jetbrains.kotlinx:kotlinx-coroutines-slf4j:$coroutineVersion")

    implementation("io.github.microutils:kotlin-logging-jvm:2.0.2")

    val dropwizardVersion = "2.0.13"
    implementation("io.dropwizard:dropwizard-core:$dropwizardVersion")

    implementation("org.postgresql:postgresql:42.2.0")
    implementation("com.zaxxer:HikariCP:3.2.0")
    implementation("org.jooq:jooq:3.13.5")


    implementation("com.fasterxml.jackson.module:jackson-module-kotlin:2.11.3")
}

tasks.withType<KotlinCompile>() {
    kotlinOptions.jvmTarget = "1.8"
}

tasks {
    named<JavaExec>("run") {
        args("server", "./config/application.yml")
    }
}

application {
    mainClassName = "MainKt"
}