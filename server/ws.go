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
		
		var start_time time.Time
		var end_time time.Time
		var duration time.Duration
		
		started, finished := false, false
		
		for {
			_, message, _ = c.ReadMessage()

			value := int(message[0])

			if value == 48 && !started {
				started = true
				fmt.Printf("Started: %v\n", started)
			}

			// Start of counting the duration time of sensor capture gas
			if started && value == 49 {
				finished = true
				fmt.Printf("Finished: %v\n", finished)
			}

			if finished {
				end_time = time.Now()
				duration = end_time.Sub(start_time)

				record = Record{
					start_time: start_time,
					end_time: end_time,
					duration: duration,
				}
				
				InsertRecord(record)
				
				fmt.Printf("Duration: %v\n", record.duration)
				started, finished = false, false
			}

			fmt.Printf("%s", message)
		}
	}))

	log.Fatal(app.Listen(":3000"))
}
