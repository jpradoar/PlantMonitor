FROM python:3
WORKDIR /srv/
ADD api.py /srv/
RUN pip install requests influxdb flask
EXPOSE 8080
CMD [ "python", "api.py" ]