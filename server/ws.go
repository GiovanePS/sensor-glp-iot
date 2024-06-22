package main

import (
	"fmt"
	"log"
	"sync"
	"time"

	"github.com/gofiber/contrib/websocket"
	"github.com/gofiber/fiber/v2"
)

var clients = sync.Map{}

func RunWebsocket() {
	app := fiber.New()

	app.Get("/", websocket.New(func(c *websocket.Conn) {
		defer func() {
			if err := c.Close(); err != nil {
				log.Println("Error closing connection:", err)
			}
			clients.Delete(c)
			log.Println("Client disconnected")
		}()

		log.Println("New client connected")
		clients.Store(c, true)

		var record Record
		var start_time time.Time
		var end_time time.Time
		var duration time.Duration

		started, finished := false, false

		for {
			// Read message from client
			msgType, msg, err := c.ReadMessage()
			if err != nil {
				log.Println("Error reading message:", err)
				break
			}
			fmt.Printf("R: %s\n", msg) // Print message to console

			// Echo the message back to all clients
			clients.Range(func(key, value interface{}) bool {
				client := key.(*websocket.Conn)
				if err := client.WriteMessage(msgType, msg); err != nil {
					log.Println("Error writing message:", err)
				}
				return true
			})

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

				record = Record{
					start_time: start_time,
					end_time:   end_time,
					duration:   duration.Seconds(),
				}

				fmt.Printf("Duration: %f seconds\n", record.duration)

				InsertRecord(record)

				started, finished = false, false
			}
		}
	}))

	log.Println("Server started at :3000")
	log.Fatal(app.Listen(":3000"))
}