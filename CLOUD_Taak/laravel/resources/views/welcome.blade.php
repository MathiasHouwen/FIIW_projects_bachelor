<!DOCTYPE html>
<html lang="{{ str_replace('_', '-', app()->getLocale()) }}">
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">

        <title>Laravel</title>

        <!-- Fonts -->
        <link rel="preconnect" href="https://fonts.bunny.net">
        <link href="https://fonts.bunny.net/css?family=figtree:400,500,600&display=swap" rel="stylesheet" />

        <style>
        /* General Styling */
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            background-color: #fff;
            color: #333;
            display: flex;
            justify-content: center;
            align-items: center;
            min-height: 100vh;
        }

        .container {
            width: 100%;
            max-width: 400px;
            padding: 20px;
            box-shadow: 0px 4px 8px rgba(0, 0, 0, 0.1);
            border-radius: 10px;
            background-color: #fff;
        }

        h1 {
            font-size: 1.8rem;
            color: #ff4d4d;
            text-align: center;
            margin-bottom: 20px;
        }

        form {
            display: flex;
            flex-direction: column;
            gap: 15px;
        }

        input {
            padding: 10px;
            border: 1px solid #ff4d4d;
            border-radius: 5px;
            font-size: 1rem;
        }

        input:focus {
            outline: none;
            border-color: #ff3333;
            box-shadow: 0 0 5px rgba(255, 51, 51, 0.5);
        }

        button {
            padding: 10px;
            background-color: #ff4d4d;
            color: #fff;
            border: none;
            border-radius: 5px;
            font-size: 1rem;
            cursor: pointer;
            transition: background-color 0.3s ease;
        }

        button:hover {
            background-color: #ff3333;
        }

        /* Additional Styling */
        .form-section {
            margin-bottom: 30px;
        }

        .form-section:last-child {
            margin-bottom: 0;
        }

        select {
            padding: 10px;
            border: 1px solid #ff4d4d;
            border-radius: 5px;
            font-size: 1rem;
            color: #333;
            background-color: #fff;
        }

        select:focus {
            outline: none;
            border-color: #ff3333;
            box-shadow: 0 0 5px rgba(255, 51, 51, 0.5);
        }
    </style>
</head>
<body>
    <div class="container">
        <!-- Registration Section -->
        <div class="form-section">
            <h1>User Register</h1>
            <form action="/register-user" method="POST">
                @csrf
                <input type="text" name="username" placeholder="Username" required>
                <input type="password" name="password" placeholder="Password (min 6 characters)" required minlength="6">
                <input type="email" name="email" placeholder="Email Address" required>
                
                <select name="rank" required>
                    <option value="" disabled selected>Select Rank</option>
                    <option value="hp">hp</option>
                    <option value="lp">lp</option>
                    <option value="schacht">schacht</option>
                    <option value="lid">lid</option>
                    <option value="comu">comu</option>
                </select>
                
                <select name="sex" required>
                    <option value="" disabled selected>Select Gender</option>
                    <option value="male">Male</option>
                    <option value="female">Female</option>
                    <option value="other">Other</option>
                </select>
                
                <button type="submit">Register</button>
            </form>
        </div>

        <!-- Login Section -->
        <div class="form-section">
            <h1>User Login</h1>
            <form action="/login-user" method="POST">
                @csrf
                <input type="text" name="username" placeholder="Username" required>
                <input type="password" name="password" placeholder="Password" required>
                <button type="submit">Login</button>
            </form>
        </div>
    </div>
</body>
</html>
