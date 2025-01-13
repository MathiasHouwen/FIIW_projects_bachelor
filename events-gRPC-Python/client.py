from flask import Flask, request, jsonify
from grpc_client import GRPCClient

app = Flask(__name__)
grpc_client = GRPCClient(host='localhost', port=50051)

@app.route('/api/v1/events', methods=['GET'])
def get_events():
    # Extract 'date' from query parameters
    date = request.args.get('date')
    if not date:
        return jsonify({"error": "Missing 'date' query parameter"}), 400

    # Call the gRPC client
    grpc_response = grpc_client.get_events_from_day(date)
    if grpc_response is None:
        return jsonify({"error": "Failed to fetch events from gRPC server"}), 500

    # Transform the gRPC response to JSON
    events = [{"title": event.title, "description": event.description, "date": event.date} 
              for event in grpc_response.events]
    return jsonify({"events": events})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=7000, debug=True)
