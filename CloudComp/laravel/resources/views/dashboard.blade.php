<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Dashboard</title>
</head>
<body>
    <h1>Welcome to Your Dashboard</h1>

    @if(!empty($weatherData) && isset($weatherData['main']))
        <h2>Current Weather in {{ $weatherData['name'] ?? 'Unknown Location' }}</h2>
        
        <p><strong>Temperature:</strong> {{ round($weatherData['main']['temp'] - 273.15, 1) }} °C</p> 
        <p><strong>Feels Like:</strong> {{ round($weatherData['main']['feels_like'] - 273.15, 1) }} °C</p>
        <p><strong>Weather:</strong> {{ ucfirst($weatherData['weather'][0]['description'] ?? 'N/A') }}</p>
        <p><strong>Humidity:</strong> {{ $weatherData['main']['humidity'] }}%</p>
        <p><strong>Wind Speed:</strong> {{ $weatherData['wind']['speed'] ?? 'N/A' }} m/s</p>
        <p><strong>Cloudiness:</strong> {{ $weatherData['clouds']['all'] ?? 'N/A' }}%</p>
        
    @else
        <p style="color: red;">❌ geen weer data, das sad .</p>
    @endif

    <div class="container mt-4">
        <a href="{{ route('soapOp') }}" class="btn btn-primary">Km Teller</a>
        <a href="/events" class="btn btn-success">Events</a>
        <a href="{{ route('dashboard') }}" class="btn btn-warning">Dashboard</a>
        <a href="{{ route('graphql.form') }}" class="btn btn-info">GraphQL</a>
    </div>
    
    <script>
        @isset($weatherData)
            const weatherData = @json($weatherData);
        @else
            const weatherData = null;
        @endisset

        @isset($response)
            const responseData = @json($response ?? null);
        @else
            const responseData = null;
        @endisset

        if (weatherData) {
            console.log("Weather Data:", weatherData);
        }

        if (responseData) {
            localStorage.setItem('responseData', JSON.stringify(responseData));
            console.log("Response Data:", responseData);
        }
    </script>
</body>
</html>
