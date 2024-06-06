FROM postgres

COPY /database /iot/database

ENV POSTGRES_USER=admin
ENV POSTGRES_PASSWORD=admin
ENV POSTGRES_DB=database
ENV POSTGRES_PORT=5432

WORKDIR /iot

EXPOSE 5432

COPY /docker/init-db.sh /docker-entrypoint-initdb.d/init-db.sh

RUN chmod +x /docker-entrypoint-initdb.d/init-db.sh

ENTRYPOINT [ "docker-entrypoint.sh" ]

CMD [ "postgres" ]
