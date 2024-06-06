#!/bin/bash

set -e

psql 'postgresql://admin:admin@localhost:5432/database' -f /iot/database/db.sql