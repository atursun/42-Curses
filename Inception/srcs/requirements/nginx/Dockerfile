FROM debian:bullseye

RUN apt update && apt install -y nginx openssl

RUN mkdir -p /etc/ssl/certs /etc/ssl/private && \
	openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
	-keyout /etc/ssl/private/key.pem \
	-out /etc/ssl/certs/cert.pem \
	-subj "/CN=atursun.42.fr"

COPY conf/nginx.conf /etc/nginx/nginx.conf

EXPOSE 443

CMD ["nginx", "-g", "daemon off;"]