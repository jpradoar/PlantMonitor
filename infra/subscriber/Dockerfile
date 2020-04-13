FROM python:3
WORKDIR /srv/
ADD SubsBot.py /srv/
RUN pip install paho-mqtt requests influxdb
CMD [ "python", "/srv/SubsBot.py" ]
