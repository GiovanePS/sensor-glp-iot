package main

import "time"

type Record struct {
	id         uint32
	start_time time.Time
	end_time   time.Time
	duration   float64
}
