
___________________________________________________________________________

                            COMMON COMMANDS
___________________________________________________________________________

EXAMPLE USES PLEX SERVER

1. SEARCH HOST FOR CONTAINERS | VOLUMES | IMAGES
```bash
docker ps -a
docker volume ls
docker images
```

2. CREATE THE FOLDER TO HOLD CONTAINER DATA AND VOLUMES
```bash
mkdir C:\Users\Sumeet\Documents\plex-docker
mkdir C:\plex\config
mkdir C:\plex\tv_shows
mkdir C:\plex\movies
cd C:\Users\Sumeet\Documents\plex-docker
```

3. CREATE docker-compose.yml
```yaml
version: '3.8'

services:
  plex:
    image: linuxserver/plex:latest
    container_name: plex
    environment:
      - PUID=1000 # Default value, can be any number
      - PGID=1000 # Default value, can be any number
      - VERSION=docker
    volumes:
      - C:\plex\config:/config
      - C:\plex\tv_shows:/tv_shows
      - C:\plex\movies:/movies
    ports:
      - 32400:32400
      - 32469:32469
      - 32469:32469/udp
      - 5354:5354/udp
      - 1900:1900/udp
    restart: unless-stopped
```

4. RUN COMMAND
```bash
docker-compose up -d
```

5. ACCESS PLEX via http://localhost:32400/web

6. TO STOP CONTAINER
```bash
docker-compose down
docker volume prune
docker images

PS C:\Users\Sumeet\Documents\plex-docker> docker images
REPOSITORY         TAG       IMAGE ID       CREATED        SIZE
linuxserver/plex   latest    16eea72d766a   19 hours ago   416MB

docker rmi 16eea72d766a # DELETE DOCKER IMAGE

```
