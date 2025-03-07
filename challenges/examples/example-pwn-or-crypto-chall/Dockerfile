FROM ubuntu:19.10

RUN echo "root:root07896789340275098236489127" | chpasswd

WORKDIR /home/ctf

RUN useradd -d /home/ctf/ ctf
RUN echo "ctf:ctf4353254387438958902" | chpasswd

COPY ./main .
COPY ynetd .
COPY flag.txt .

RUN chmod 755 main
RUN chmod 755 ynetd

RUN chown -R root:root /home/ctf

USER ctf

EXPOSE 4444
CMD ./ynetd -p 4444 "./main"