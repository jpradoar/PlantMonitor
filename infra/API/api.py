from flask import Flask, jsonify, request, Response
from functools import wraps
from influxdb import InfluxDBClient # FOR write data in influxDB


app = Flask(__name__)

# Vars
host='influxdb'
port=8086
user='admin'
password='admin'
dbname='IoT'
showhelp="Example:\ncurl -s -u admin:admin http://127.0.0.1:8080/api/{resource}"




# Replace this function. use remote database
def check_auth(username, password):
    # Check if username and password are admin:admin. 
    # Here you can use a function to check this data on remote database
    return username == 'admin' and password == 'admin'

def not_authenticate():
    # If user or pass are wrong, send an error message
    return Response('401 Unauthorized. Login fail: User and/or Password are wrong!\n', 401,  {'WWW-Authenticate': 'Basic realm="Login Required"'})

def requires_auth(f):
    @wraps(f)
    def decorated(*args, **kwargs):
        auth = request.authorization
        if not auth or not check_auth(auth.username, auth.password):
            return not_authenticate()
        return f(*args, **kwargs)
    return decorated




@app.route('/api/help', methods=['GET'])
def hello():
    return "Sensor Names: Humidity / Temperature / Ldr / Soil\ncurl -s  'http://url:port/api/sensor?fields=Temperature&limit=20'"


@app.route('/api/sensor', methods=['GET'])
@requires_auth
def get_temp():
    fields = str(request.args.get('fields'))
    Qlimit = int(request.args.get('limit'))
    if(Qlimit > 20):
        return "Sorry: limit must be less than 20"
    else:
        dbClient = InfluxDBClient(host, port, user, password, dbname)
        DBquery = dbClient.query('SELECT '+fields+' FROM '+fields+' ORDER BY time DESC LIMIT '+str(Qlimit))
        Qoutput = DBquery.raw
        print(Qoutput)
        return Qoutput



if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080, debug=True) # Open a webserver on port 8090
