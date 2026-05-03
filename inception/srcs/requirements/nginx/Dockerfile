FROM debian:bookworm

RUN apt-get update && apt-get install -y \
    nginx \
    openssl \
    && rm -rf /var/lib/apt/lists/*

COPY tools/generate_ssl.sh /generate_ssl.sh
RUN chmod +x /generate_ssl.sh && /generate_ssl.sh

COPY conf/nginx.conf /etc/nginx/sites-available/default

EXPOSE 443

CMD ["nginx", "-g", "daemon off;"]
