# How to run
```
cd docker
docker build -t iot-server-image .. --file Dockerfile-go
docker build -t iot-postgres-image .. --file Dockerfile-db
docker-compose up -d
```