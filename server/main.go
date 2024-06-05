package main

import (
	"log"

	"github.com/gofiber/contrib/websocket"
	"github.com/gofiber/fiber/v2"
)

func main() {
	app := fiber.New()

	app.Get("/", websocket.New(func(c *websocket.Conn) {
		var mt int
		var msg []byte
		var err error

		for {
			if mt, msg, err = c.ReadMessage(); err != nil {
				log.Println("read:", err)
				break
			}

			log.Printf("recv: %s", msg)

			if err = c.WriteMessage(mt, msg); err != nil {
				log.Println("write: ", err)
				break
			}
		}
	}))

	log.Fatal(app.Listen(":3000"))
}
