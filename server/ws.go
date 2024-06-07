package main

import (
	"log"
	"time"

	"github.com/gofiber/contrib/websocket"
	"github.com/gofiber/fiber/v2"
)

func WebsocketInit() {
	app := fiber.New()

	app.Get("/", websocket.New(func(c *websocket.Conn) {
		var messageType int
		var message []byte
		var err error

		var record Record
		started, finished := false, false
		for {
			if messageType, message, err = c.ReadMessage(); err != nil {
				log.Println("read:", err)
				break
			}

			/*
				TODO: FUNCTION THAT RECEIVES THE MESSAGE AND TESTS TO SET `started` TO `true`
			*/

			// Start of counting the duration time of sensor capture gas
			if started {
				record = Record{
					start_time: time.Now(),
				}
			}

			// End of the duration
			if finished {
				end_time := time.Now()
				record.end_time = end_time
				record.duration = record.end_time.Sub(record.start_time)
				InsertRecord(record)
				started, finished = false, false
			}

			log.Printf("recv: %s", message)

			if err = c.WriteMessage(messageType, message); err != nil {
				log.Println("write: ", err)
				break
			}
		}
	}))

	log.Fatal(app.Listen(":3000"))
}
