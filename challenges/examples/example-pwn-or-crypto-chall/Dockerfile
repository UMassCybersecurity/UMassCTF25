FROM ubuntu
RUN apt update && apt install -y g++ 

RUN echo "root:root07896789340275098236489127" | chpasswd

WORKDIR /home/ctf

RUN useradd -d /home/ctf/ ctf
RUN echo "ctf:ctf4353254387438958902" | chpasswd

COPY ./static/main.cpp .
RUN g++ -o main main.cpp -static -std=c++17
COPY ynetd .

RUN chmod 755 main
RUN chmod 755 ynetd

RUN chown -R root:root /home/ctf

USER ctf

EXPOSE 4444
CMD ./ynetd -p 4444 "./main"
