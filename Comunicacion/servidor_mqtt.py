#!/usr/bin/env python3
import paho.mqtt.client as mqtt
import json, csv
from datetime import datetime

CSV_FILE = "readings.csv"

def on_connect(client, userdata, flags, rc):
    print("[INFO] Conectado al broker MQTT.")
    client.subscribe("agro/+/telemetry")

def on_message(client, userdata, msg):
    s = msg.payload.decode("utf-8", "ignore")
    try:
        data = json.loads(s)
    except:
        data = {"_raw": s}
    data["topic"] = msg.topic
    data["received"] = datetime.utcnow().isoformat() + "Z"

    with open(CSV_FILE, "a", newline="", encoding="utf-8") as f:
        writer = csv.writer(f)
        writer.writerow([data.get("topic"), s, data.get("received")])
    print(f"[SUB] {msg.topic}: {s}")

client = mqtt.Client("logger")
client.on_connect = on_connect
client.on_message = on_message
client.connect("127.0.0.1", 1883, 60)
client.loop_forever()
