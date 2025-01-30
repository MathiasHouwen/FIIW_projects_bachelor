<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Events</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet">
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
                        <p class="mb-1">{{ $event['description'] }}</p>
                        <small>{{ $event['date'] }}</small>
                    </div>
                @empty
                    <p>No events found for this date.</p>
                @endforelse
            </div>
        @endif
    </div>
</body>
</html>
