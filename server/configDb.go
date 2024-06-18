package main

import (
	"database/sql"
	"fmt"
	"os"
	"log"

	_ "github.com/lib/pq"
	"github.com/joho/godotenv"
)

var (
	dbConn *sql.DB
)


func InitializePostgres() error {
	err := godotenv.Load("../.env")
	 if err != nil {
	   log.Fatal("Error loading .env file")
	 }
	
	fmt.Println("Connecting to Postgres...")


	dsn := fmt.Sprintf("host=%v user=%v password=%v dbname=%v port=%v sslmode=disable",
		os.Getenv("POSTGRES_HOST"),
		os.Getenv("POSTGRES_USER"),
		os.Getenv("POSTGRES_PASSWORD"),
		os.Getenv("POSTGRES_DBNAME"),
		os.Getenv("POSTGRES_PORT"),
	)

	database, err := sql.Open("postgres", dsn)

	if err != nil {
		panic(err)
	}

	dbConn = database

	return err
}
