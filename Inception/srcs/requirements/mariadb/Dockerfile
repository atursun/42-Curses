FROM debian:bullseye

RUN apt update && apt install -y mariadb-server

RUN mkdir -p /run/mysqld && chown -R mysql:mysql /run/mysqld \
    && chown -R mysql:mysql /var/lib/mysql

COPY tools/setup.sh /setup.sh

RUN chmod +x /setup.sh

EXPOSE 3306

CMD ["/setup.sh"]