import paho.mqtt.client as mqtt
import json

# MQTT instellingen
broker = "mqtt.eclipse.org"
port = 1883
topic = "events/rating"

# Definieer de MQTT client
client = mqtt.Client()

# Definieer de on_connect event handler
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Verbonden met broker")
        client.subscribe(topic)
    else:
        print("Verbinding mislukt")

# Definieer de on_message event handler
def on_message(client, userdata, msg):
    try:
        payload = json.loads(msg.payload.decode())
        event_id = payload.get("event_id")
        rating = payload.get("rating")
        print(f"Ontvangen beoordeling voor evenement {event_id}: {rating}")
    except Exception as e:
        print(f"Fout bij verwerken bericht: {e}")

# Stel de event handlers in
client.on_connect = on_connect
client.on_message = on_message

# Verbind met de broker
client.connect(broker, port)

# Start de MQTT client loop
client.loop_forever()