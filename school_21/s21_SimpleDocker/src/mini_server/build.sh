#!/bin/bash
sudo docker pull nginx
sudo docker run -d -p 81:81 --name temp nginx
sudo docker cp ./mini_server.c temp:etc/nginx/
sudo docker cp ./nginx.conf temp:/etc/nginx/
sudo docker exec temp apt-get update
sudo docker exec temp apt-get install -y gcc spawn-fcgi libfcgi-dev
sudo docker exec temp gcc /etc/nginx/mini_server.c -o /etc/nginx/webserver -l fcgi
sudo docker exec temp spawn-fcgi -p 8080 /etc/nginx/webserver
sudo docker exec temp nginx -s reload
sudo curl http://localhost:81/
