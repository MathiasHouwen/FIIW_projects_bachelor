<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Events</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet">
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
</head>
<body>
    <div class="container mt-4">
        <h2 class="mb-3">Events for {{ $date }}</h2>

        <form method="GET" action="{{ url('/events') }}" class="mb-3">
            <label for="date">Select Date:</label>
            <input type="date" id="date" name="date" value="{{ $date }}" class="form-control w-25 d-inline">
            <button type="submit" class="btn btn-primary">Fetch Events</button>
        </form>

        @if(isset($error))
            <div class="alert alert-danger">{{ $error }}</div>
        @else
            <div class="list-group">
                @forelse($events as $event)
                    <div class="list-group-item">
                        <h5 class="mb-1">{{ $event['title'] }}</h5>
                        <p class="mb-1">{{ $event['description'] ?? 'No description available' }}</p>
                        <small>{{ $event['date'] }}</small>
                        <p class="mb-1">Rating: <span id="rating-{{ $loop->index }}">{{ $event['rating'] }}</span></p>

                        <!-- Upvote Button -->
                        <button class="btn btn-success btn-sm" id="upvote-btn-{{ $loop->index }}" onclick="upvoteEvent('{{ $event['title'] }}', {{ $loop->index }})">Upvote</button>
                    </div>
                @empty
                    <p>No events found for this date.</p>
                @endforelse
            </div>
        @endif
    </div>

    <script>
        // Function to handle upvoting
        function upvoteEvent(eventName, index) {
            $('#upvote-btn-' + index).prop('disabled', true);
            // Send a POST request to the Flask API to upvote the event
            $.ajax({
                url: 'http://localhost:7070/upvote',
                type: 'POST',
                contentType: 'application/json',
                data: JSON.stringify({ name: eventName}),
                success: function(response) {
                    // Update the rating on success
                    if (response.rating) {
                        $('#rating-' + index).text(response.rating);
                    } else {
                        alert('Failed to upvote event.');
                    }
                },
                error: function(xhr, status, error) {
                    alert('Error: ' + error);
                }
            });
        }
    </script>
</body>
</html>
