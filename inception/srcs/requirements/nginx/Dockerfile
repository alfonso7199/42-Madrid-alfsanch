FROM debian:bookworm

RUN apt-get update && apt-get install -y \
    nginx \
    openssl \
    && rm -rf /var/lib/apt/lists/*

# Generamos el certificado autofirmado en tiempo de build
COPY tools/generate_ssl.sh /generate_ssl.sh
RUN chmod +x /generate_ssl.sh && /generate_ssl.sh

# Copiamos la configuración de nginx
COPY conf/nginx.conf /etc/nginx/sites-available/default

# Solo escuchamos en 443 (HTTPS), nunca en 80
EXPOSE 443

CMD ["nginx", "-g", "daemon off;"]
