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

    <script>
        // Pass PHP data to JavaScript
        const responseData = @json($weatherData);

        console.log(responseData);
    </script>
</body>
</html>
