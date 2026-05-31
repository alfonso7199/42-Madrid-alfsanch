FROM debian:bookworm

RUN apt-get update && apt-get install -y \
    php8.2-cli \
    php8.2-mysql \
    curl \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /var/www && curl -Lo /var/www/adminer.php https://www.adminer.org/latest.php

EXPOSE 8080

CMD ["php", "-S", "0.0.0.0:8080", "-t", "/var/www"]
