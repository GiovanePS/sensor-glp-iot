package main

import (
	"log"
	"github.com/gofiber/fiber/v2"
	"github.com/gofiber/websocket/v2"
)

func main() {
	app := fiber.New()

	app.Get("/", websocket.New(func(c *websocket.Conn) {
		defer func() {
            if err := c.Close(); err != nil {
                log.Println("Error closing connection:", err)
            }
        }()

        log.Println("New client connected")

        for {
            // Read message from client
            messageType, msg, err := c.ReadMessage()
            if err != nil {
                log.Println("Error reading message:", err)
                break
            }
            log.Printf("Received: %s", msg)
            // c.WriteMessage(messageType, msg)

            // Write message back to client
            if err = c.WriteMessage(messageType, msg); err != nil {
                log.Println("Error writing message:", err)
                break
            }
        }

		log.Println("Client disconnected")
	}))

	log.Println("Server started at :3000")
	log.Fatal(app.Listen(":3000"))
}