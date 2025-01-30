<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Km Teller Service</title>
</head>
<body>

    <h1>Km Teller Service</h1>

    <!-- Form to Get Total Kilometers -->
    <div class="form-section">
        <h2>Total Kilometers</h2>
        <form action="{{ route('kmTeller.getTotal') }}" method="GET">
            <button type="submit">Get Total Kilometers</button>
        </form>
        <p>Total: <span id="totalKilometers">{{ session('total_km', 'N/A') }}</span></p>
    </div>

    <!-- Form to Add Kilometers -->
    <div class="form-section">
        <h2>Add Kilometers</h2>
        <form action="{{ route('kmTeller.add') }}" method="POST">
            @csrf
            <input type="number" name="kilometers" placeholder="Enter Kilometers" required>
            <button type="submit">Add Kilometers</button>
        </form>
    </div>

</body>
</html>
