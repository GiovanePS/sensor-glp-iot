package main

import (
	"fmt"
	"log"
	"time"

	"github.com/gofiber/contrib/websocket"
	"github.com/gofiber/fiber/v2"
)

func RunWebsocket() {
    app := fiber.New()

    app.Get("/", websocket.New(func(c *websocket.Conn) {
        defer func() {
            if r := recover(); r != nil {
                log.Printf("Recovered from panic: %v", r)
            }
        }()

        // var message []byte
        var record Record
        var startTime time.Time
        var endTime time.Time
        var duration time.Duration

        started, finished := false, false

        for {
            _, message, err := c.ReadMessage()
            if err != nil {
                log.Println("read:", err)
                break // Exit the loop if there is an error
            }

            fmt.Printf("%s", message)
            value := message[0] // Assuming message is a byte array containing '0' or '1'

            if value == '0' && !started {
                started = true
                startTime = time.Now()
            }

            if started && value == '1' {
                finished = true
            }

            if finished {
                endTime = time.Now()
                duration = endTime.Sub(startTime)

                seconds := duration.Seconds()

                record = Record{
                    start_time: startTime,
                    end_time:   endTime,
                    duration:   seconds,
                }
                fmt.Println(record)
				// InsertRecord(record)

                // Reset flags
                started, finished = false, false
            }
        }
    }))

    log.Fatal(app.Listen(":3000"))
}
