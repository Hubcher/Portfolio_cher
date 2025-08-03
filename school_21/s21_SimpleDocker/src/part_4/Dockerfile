FROM nginx

COPY start.sh /
COPY mini_server.c /

RUN apt-get update &&  \
    apt-get install -y gcc spawn-fcgi libfcgi-dev && \ 
    rm -rf /var/lib/apt/lists && \
    gcc server.c -lpthread -lfcgi -o webserver && \
    chmod +x /start.sh

USER nginx
HEALTHCHECK --interval=5m --timeout=3s CMD curl -f http://localhost/ || exit 1
ENTRYPOINT ["./start.sh"]


