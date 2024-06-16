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
		var message []byte

		var record Record
		started, finished := false, false
		for {
			_, message, _ = c.ReadMessage()

			value := int(message[0])

			if value == 48 && !started {
				started = true
				fmt.Printf("Started: %v\n", started)
			}

			// Start of counting the duration time of sensor capture gas
			if started {
				record = Record{
					start_time: time.Now(),
				}
			}
			
			if started && value == 49 {
				finished = true
				fmt.Printf("Finished: %v\n", finished)
			}

			// End of the duration
			if finished {
				end_time := time.Now()
				record.end_time = end_time
				record.duration = record.end_time.Sub(record.start_time)
				InsertRecord(record)
				started, finished = false, false
			}

			fmt.Printf("Message: %s\n", message)

		}
	}))

	log.Fatal(app.Listen(":3000"))
}
