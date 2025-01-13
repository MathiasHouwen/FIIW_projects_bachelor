import grpc
import events_pb2
import events_pb2_grpc

class GRPCClient:
    def __init__(self, host='localhost', port=50051):
        self.channel = grpc.insecure_channel(f'{host}:{port}')
        self.stub = events_pb2_grpc.EventServiceStub(self.channel)

    def get_events_from_day(self, date):
        try:
            request = events_pb2.GetEventsRequest(date=date)
            response = self.stub.GetEventsFromDay(request)
            return response
        except grpc.RpcError as e:
            print(f"gRPC Error: {e}")
            return None
