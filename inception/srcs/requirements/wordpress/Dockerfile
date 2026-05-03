FROM debian:bookworm

RUN apt-get update && apt-get install -y \
    php8.2-fpm \
    php8.2-mysql \
    php8.2-curl \
    php8.2-gd \
    php8.2-mbstring \
    php8.2-xml \
    php8.2-zip \
    curl \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    && chmod +x wp-cli.phar \
    && mv wp-cli.phar /usr/local/bin/wp

RUN curl -O https://wordpress.org/latest.tar.gz \
    && tar -xzf latest.tar.gz \
    && mkdir -p /var/www/html \
    && mv wordpress/* /var/www/html \
    && rm -rf latest.tar.gz wordpress

COPY conf/www.conf /etc/php/8.2/fpm/pool.d/www.conf

COPY tools/wp_setup.sh /wp_setup.sh
RUN chmod +x /wp_setup.sh

RUN mkdir -p /run/php \
    && chown -R www-data:www-data /var/www/html

EXPOSE 9000

ENTRYPOINT ["/wp_setup.sh"]
