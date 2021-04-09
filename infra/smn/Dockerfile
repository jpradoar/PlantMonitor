FROM alpine:3.13.4

RUN apk update; apk add python3 py-pip py3-paho-mqtt
ADD smn.py /

CMD ["python3", "-u", "/smn.py"]
