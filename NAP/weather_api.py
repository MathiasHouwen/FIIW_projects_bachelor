import requests
import datetime
import config

API_KEY = config.OPENWEATHER_API_KEY
LOCATION = "Diepenbeek,BE"

def get_weather_for_date(date_str):
    try:
        # Call the current weather endpoint for Diepenbeek
        url = f"https://api.openweathermap.org/data/2.5/weather?q={LOCATION}&units=metric&appid={API_KEY}"
        response = requests.get(url)
        response.raise_for_status()
        data = response.json()

        description = data["weather"][0]["description"].capitalize()
        temperature = round(data["main"]["temp"], 1)
        return f"{description}, {temperature}°C (openweathermap)"
    except Exception as e:
        print(f"[WAARSCHUWING] Weerdata ophalen mislukt: {e}")
        return f"Zonnig op {date_str} (mock info)"
