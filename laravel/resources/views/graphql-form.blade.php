<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>GraphQL User Data</title>
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css">
</head>
<body>
    <div class="container mt-5">
        <h1 class="mb-4">Fetch User Data</h1>

        <!-- Show any general error message -->
        @if(session('errorMessage'))
            <div class="alert alert-danger">
                {{ session('errorMessage') }}
            </div>
        @endif

        <!-- Form for submitting user ID -->
        <form action="{{ route('graphql.fetch') }}" method="POST">
            @csrf
            <div class="mb-3">
                <label for="user_id" class="form-label">User ID:</label>
                <input type="number" id="user_id" name="user_id" class="form-control" value="{{ old('user_id') }}" required>
            </div>
            <button type="submit" class="btn btn-primary">Fetch Data</button>
        </form>

        <!-- Display user data if available -->
        @isset($userData)
            <h2 class="mt-5">User Data</h2>
            <table class="table table-bordered mt-3">
                <tr>
                    <th>ID</th>
                    <td>{{ $userData['id'] }}</td>
                </tr>
                <tr>
                    <th>Name</th>
                    <td>{{ $userData['name'] }}</td>
                </tr>
                <tr>
                    <th>Email</th>
                    <td>{{ $userData['email'] }}</td>
                </tr>
            </table>
        @endisset
    </div>
</body>
</html>
