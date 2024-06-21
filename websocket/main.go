// File: main.go
package main

import (
	"log"
	"github.com/gofiber/fiber/v2"
	"github.com/gofiber/websocket/v2"
	"sync"
)

var clients = sync.Map{}

func main() {
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

		for {
			messageType, msg, err := c.ReadMessage()
			if err != nil {
				log.Println("Error reading message:", err)
				break
			}
			log.Printf("R: %s, T: %v", msg, messageType)

			// Echo the message back to all clients
			clients.Range(func(key, value interface{}) bool {
				client := key.(*websocket.Conn)
				if err := client.WriteMessage(messageType, msg); err != nil {
					log.Println("Error writing message:", err)
				}
				return true
			})
		}
	}))

	log.Println("Server started at :3000")
	log.Fatal(app.Listen(":3000"))
}
