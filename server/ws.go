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
				start_time = time.Now()
			}

			// Start of counting the duration time of sensor capture gas
			if started && value == 49 {
				finished = true
				fmt.Printf("Finished: %v\n", finished)
			}

			if finished {
				end_time = time.Now()
				duration = end_time.Sub(start_time)

				// d := (time.Millisecond * 1)
				// duration = duration.Round(d)
				seconds := duration.Seconds()
				
				record = Record{
					start_time: start_time,
					end_time: end_time,
					duration: seconds,
				}
				
				fmt.Printf("Start Time: %v\n", start_time)
				fmt.Printf("End Time: %v\n", end_time)
				fmt.Printf("Duration: %s\n", duration)
				
				InsertRecord(record)
				
				started, finished = false, false
			}

			fmt.Printf("%s", message)
		}
	}))

	log.Fatal(app.Listen(":3000"))
}
