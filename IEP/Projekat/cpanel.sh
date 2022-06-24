#!/bin/bash

if [ "$#" -ne 1 ]
then
    echo "One argument required."
    exit 1
fi

case "$1" in
    db:auth)
        mysql -u root -P 3310 -proot -D auth
        ;;
    db:shop)
        mysql -u root -P 3311 -proot -D shop
        ;;
    db:clean)
        docker stop projekat-authentication-1
        docker stop projekat-daemon-1
        docker stop projekat-customer-1
        docker rm projekat-paradajz-1 -f
        docker rm projekat-krastavac-1 -f
        mysql -u root --protocol tcp -P 3310 -proot -e "DROP DATABASE auth;"
        mysql -u root --protocol tcp -P 3311 -proot -e "DROP DATABASE shop;"
        docker-compose up -d --build paradajz krastavac
        docker-compose up -d
        ;;
    redis)
        redis-cli
        ;;
    test)
        cd tests
        pip install -r requirements.txt
        python main.py \
            --authentication-address http://127.0.0.1:5001 \
            --jwt-secret "zaki@etf.bg.ac.rs" \
            --roles-field roles \
            --customer-role user \
            --warehouse-role warehouse \
            --administrator-role admin \
            --with-authentication \
            --warehouse-address http://127.0.0.1:5002 \
            --customer-address http://127.0.0.1:5003 \
            --administrator-address http://127.0.0.1:5004 \
            --type all
        ;;
    purge)
        docker-compose down --volumes
        docker swarm leave --force
        docker kill $(docker ps -q)
        docker rm $(docker ps --filter=status=exited --filter=status=created -q)
        docker rm -f $(docker ps -a -q)
        docker rmi $(docker images -a -q)
        docker volume rm $(docker volume ls -q)
        docker network rm $(docker network ls -q)
        docker system prune -a
        docker builder prune
        ;;
    deploy)
        docker swarm init
        docker-compose build
        docker stack deploy --compose-file docker-compose.yml projekat
        ;;
    status)
        docker stack services projekat
        ;;
    *)
        echo "Invalid command."
        exit 1
        ;;
esac
