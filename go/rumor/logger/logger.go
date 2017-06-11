package logger

import (
	"fmt"
	"io"
	"log"
)

type LogLevel int

const (
	FATAL LogLevel = iota
	ERROR
	WARN
	INFO
	DEBUG
)

const (
	prefixDebug = "[DEBUG] "
	prefixInfo  = "[INFO] "
	prefixWarn  = "[WARN] "
	prefixError = "[ERROR] "
	prefixFatal = "[FATAL] "
)

type Logger struct {
	backend *log.Logger
	level   LogLevel
}

func NewSimpleLogger(device io.Writer) *Logger {
	return &Logger{
		backend: log.New(device, "", log.LstdFlags),
		level:   INFO,
	}
}

func NewLevelLogger(device io.Writer, level LogLevel) *Logger {
	return &Logger{
		backend: log.New(device, "", log.LstdFlags),
		level:   level,
	}
}

func (l *Logger) Fatal(v ...interface{}) {
	if l.level >= FATAL {
		l.backend.Output(2, prefixFatal+fmt.Sprintln(v...))
	}
}

func (l *Logger) Error(v ...interface{}) {
	if l.level >= ERROR {
		l.backend.Output(2, prefixError+fmt.Sprintln(v...))
	}
}

func (l *Logger) Warn(v ...interface{}) {
	if l.level >= WARN {
		l.backend.Output(2, prefixWarn+fmt.Sprintln(v...))
	}
}

func (l *Logger) Info(v ...interface{}) {
	if l.level >= INFO {
		l.backend.Output(2, prefixInfo+fmt.Sprintln(v...))
	}
}

func (l *Logger) Debug(v ...interface{}) {
	if l.level >= DEBUG {
		l.backend.Output(2, prefixDebug+fmt.Sprintln(v...))
	}
}

func (l *Logger) Fatalf(format string, v ...interface{}) {
	if l.level >= FATAL {
		l.backend.Printf(prefixFatal+format, v...)
	}
}

func (l *Logger) Errorf(format string, v ...interface{}) {
	if l.level >= FATAL {
		l.backend.Printf(prefixError+format, v...)
	}
}

func (l *Logger) Warnf(format string, v ...interface{}) {
	if l.level >= WARN {
		l.backend.Printf(prefixWarn+format, v...)
	}
}

func (l *Logger) Infof(format string, v ...interface{}) {
	if l.level >= INFO {
		l.backend.Printf(prefixInfo+format, v)
	}
}

func (l *Logger) Debugf(format string, v ...interface{}) {
	if l.level >= DEBUG {
		l.backend.Printf(prefixDebug+format, v...)
	}
}
