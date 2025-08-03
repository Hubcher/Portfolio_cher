#!/bin/bash

docker stop temp
docker rm temp
docker rmi -f nginx