#!/bin/bash

mkdir -p /etc/ssl/certs /etc/ssl/private

openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/ssl/private/inception.key \
    -out    /etc/ssl/certs/inception.crt \
    -subj   "/C=ES/ST=Madrid/L=Madrid/O=42Madrid/OU=alfsanch/CN=alfsanch.42.fr"
