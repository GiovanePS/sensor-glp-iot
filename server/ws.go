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

        var record Record
        var start_time time.Time
        var end_time time.Time
        var duration time.Duration

        started, finished := false, false

		log.Println("New client connected")

        for {
			// Read message from client
            msgType, msg, err := c.ReadMessage()
            if err != nil {
                log.Println("Error reading message:", err)
                break 
            }
            fmt.Printf("Received: %s", msg) // Print message to console
			
			// Write message back to client
            if err = c.WriteMessage(msgType, []byte("Server received: "+string(msg))); err != nil {
                log.Println("Error writing message:", err)
                break
            }

            value := msg[0]

            if value == '0' && !started {
                started = true
                start_time = time.Now()
            }

            if started && value == '1' {
                finished = true
            }

            if finished {
                end_time = time.Now()
                duration = end_time.Sub(start_time)

				duration := duration.Seconds()
				
				record = Record{
					start_time: start_time,
					end_time: end_time,
					duration: duration,
				}
				
				// fmt.Printf("Start Time: %v\n", start_time)
				// fmt.Printf("End Time: %v\n", end_time)
				fmt.Printf("Duration: %s\n", duration)
				
				InsertRecord(record)
				
				started, finished = false, false
			}

		}
		log.Println("Client disconnected")
	}))
		
	log.Println("Server started at :3000")
	log.Fatal(app.Listen(":3000"))
}
