# How to run
```
cd docker
docker build --rm -t iot-server-image .. --file Dockerfile-go
docker build --rm -t iot-postgres-image .. --file Dockerfile-db
docker-compose up -d
```

# Video of the project working:
https://www.youtube.com/watch?v=j_nqwQE9AEs
