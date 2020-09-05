FROM gcc:4.9

RUN mkdir app/
RUN mkdir app/hangman/

COPY ./*.c app/hangman/

WORKDIR /app/hangman

RUN gcc main.c -o hangman

CMD ./hangman
