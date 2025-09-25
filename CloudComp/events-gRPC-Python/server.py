import grpc
from concurrent import futures
import time

import events_pb2
import events_pb2_grpc

# Sample events data (in a real scenario, this could be from a database)
events_data = [
    {"title": "voetballen", "description": "voetbalmatch 20:00", "date": "2025-02-01"},
    {"title": "vollybal", "description": "vollybalen training", "date": "2025-02-01"},
    {"title": "toestelturnen", "description": "proberen niet ons nek te breken", "date": "2025-01-31"}
]

class EventService(events_pb2_grpc.EventServiceServicer):
    def GetEventsFromDay(self, request, context):
        date = request.date
        events = [event for event in events_data if event["date"] == date]
        
        response = events_pb2.GetEventsResponse()
        for event in events:
            response.events.add(title=event["title"], description=event["description"], date=event["date"])
        return response

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    events_pb2_grpc.add_EventServiceServicer_to_server(EventService(), server)
    server.add_insecure_port('[::]:50051')
    print("Server is running on port 50051...")
    server.start()
    try:
        while True:
            time.sleep(86400)  # Keep the server running
    except KeyboardInterrupt:
        server.stop(0)

if __name__ == "__main__":
    serve()
