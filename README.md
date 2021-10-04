# Hangman in C
Hangman's game with scoring system developed in C.

I have included a Dockerfile that generates an image to run this app.

To build the image first dowload the whole repo and navigate to its directory. Then run:

- **docker build -t image_name .**

You can also pull this image from my Docker Hub repository, instead of building it through the Dockerfile:

- **docker pull jaimemartinagui/jaime_docker_repo:hangman_in_C**

Both options will create an image with the specified name. You can find information about it with:

- **docker images**

To run the container:

- **docker run -it image_name_or_id**

This way you will run your Hangman game!
