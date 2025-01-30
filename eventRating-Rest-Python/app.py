from flask import Flask, jsonify, request
from flask_cors import CORS

app = Flask(__name__)
CORS(app, origins="http://127.0.0.1:8000")

# Example data: event ratings, now using event name as the key
events = {
    "Event1": {"event_name": "Concert A", "rating": 4.5},
    "Event2": {"event_name": "Conference B", "rating": 3.8},
    "Event3": {"event_name": "Festival C", "rating": 4.9}
}

# Route to get the rating of an event by its name
@app.route('/event', methods=['GET'])
def get_event_rating():
    event_name = request.args.get('name')  # Get event name from the query parameter
    if event_name:
        event = events.get(event_name)
        if event:
            return jsonify({
                "event_name": event["event_name"],
                "rating": event["rating"]
            })
        else:
            return jsonify({"error": "Event not found"}), 404
    else:
        return jsonify({"error": "Event name is required"}), 400

@app.route('/upvote', methods=['POST'])
def upvote_event():
    event_name = request.json.get('name')
    
    if event_name and event_name in events:
        # Increase rating by 1
        events[event_name]["rating"] += 1
        return jsonify({
            "event_name": event_name,
            "rating": events[event_name]["rating"]
        })
    else:
        return jsonify({"error": "Event not found"}), 404

if __name__ == '__main__':
    # Set the port to 7070 for Docker
    app.run(debug=True, host='0.0.0.0', port=7070)
