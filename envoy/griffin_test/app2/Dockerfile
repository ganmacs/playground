FROM golang:1.11 as build

RUN mkdir /app
WORKDIR /app
COPY go.mod go.sum /app/
RUN go mod download

COPY app.go /app/
RUN go mod verify && go build app.go

FROM ubuntu:18.04

RUN apt-get update && \
      apt-get install -y ca-certificates && \
      apt-get clean && \
      rm -rf /var/lib/apt/lists/*

COPY --from=build /app/app /usr/local/bin/

EXPOSE 8080

CMD ["app"]
