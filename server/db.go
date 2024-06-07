package main

import "github.com/gofiber/fiber/v2/log"

func InsertRecord(r Record) {
	sql := `INSERT INTO glp_history (start_time, end_time, duration)
	VALUES ($1, $2, $3)`

	_, err := dbConn.Exec(
		sql,
		r.start_time,
		r.end_time,
		r.duration,
	)

	if err != nil {
		log.Warnf("Error on inserting records: %v", err)
	}
}
