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

func GetRecords() []float64 {
	sql := `SELECT duration FROM glp_history`

	rows, err := dbConn.Query(sql)
	if err != nil {
		log.Warnf("Error on selecting durations: %v", err)
		return nil
	}
	defer rows.Close()

	var durations []float64
	for rows.Next() {
		var duration float64
		err := rows.Scan(&duration)
		if err != nil {
			log.Warnf("Error on scanning durations: %v", err)
			return nil
		}
		durations = append(durations, duration)
	}

	return durations
}