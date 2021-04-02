FROM python:3
WORKDIR /srv/
ADD SubsBot.py /srv/
RUN pip install paho-mqtt requests influxdb sockets
CMD [ "python3", "-u", "/srv/SubsBot.py" ] # -u = print on stdout


