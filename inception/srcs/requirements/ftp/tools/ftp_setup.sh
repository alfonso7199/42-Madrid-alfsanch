#!/bin/bash
set -e

FTP_PASSWORD=$(cat /run/secrets/ftp_password)

useradd -m -d /var/www/html -s /bin/sh ftpuser 2>/dev/null || true
echo "ftpuser:${FTP_PASSWORD}" | chpasswd

exec vsftpd /etc/vsftpd.conf
