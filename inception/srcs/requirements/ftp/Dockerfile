FROM debian:bookworm

RUN apt-get update && apt-get install -y \
    vsftpd \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

COPY tools/vsftpd.conf /etc/vsftpd.conf
COPY tools/ftp_setup.sh /ftp_setup.sh
RUN chmod +x /ftp_setup.sh

EXPOSE 21 21100-21110

ENTRYPOINT ["/ftp_setup.sh"]
