FROM debian:bookworm

RUN apt-get update && apt-get install -y \
    nginx \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

COPY index.html /var/www/html/index.html
RUN chmod 644 /var/www/html/index.html

RUN echo 'server { listen 80; root /var/www/html; index index.html; }' \
    > /etc/nginx/sites-available/default

EXPOSE 80

CMD ["nginx", "-g", "daemon off;"]
