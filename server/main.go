package main

import "github.com/gofiber/fiber/v2/log"

func main() {

	err := InitializePostgres()

	if err != nil {
		log.Errorf("Postgres initialization error: %v", err)
		return
	}

	RunWebsocket()
}
