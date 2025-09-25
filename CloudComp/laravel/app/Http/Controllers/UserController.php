<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Http;

class UserController extends Controller
{
    public function registerUser(Request $request)
    {
        // Validate user input
        $validated = $request->validate([
            'username' => 'required|string|max:50',
            'password' => 'required|string|min:6',
            'rank' => 'required|string|in:hp,lp,schacht,lid,comu',
            'email' => 'required|email|max:100',
            'sex' => 'required|string|in:male,female,other',
        ]);

        // Data to send to the Node.js service
        $data = ([
            'username' => $validated['username'],
            'password' => $validated['password'],
            'rank' => strtolower($validated['rank']),
            'email' => $validated['email'],
            'sex' => strtolower($validated['sex']),
        ]);
        
        // Call the Node.js service's /register endpoint
        $response = Http::post('http://localhost:3000/register', $data);

        // Handle the response
        if ($response->successful()) {
            return response()->json([
                'success' => true,
                'message' => 'User registered successfully!',
                'data' => $response->json(),
            ]);
        }


        // Handle errors
        return response()->json([
            'success' => false,
            'error' => 'Registration failed!',
            'details' => $response->json(),
        ], $response->status());
    }

    public function loginUser(Request $request)
    {

        // Validate user input
        $validated = $request->validate([
            'username' => 'required|string',
            'password' => 'required|string|min:6',
        ]);

        // Data to send to the Node.js service
        $data = [
            'username' => $validated['username'],
            'password' => $validated['password'],
        ];

        // Send the POST request to the external login endpoint
        $response = Http::post('http://localhost:3000/login', $data);

        if ($response->successful()) {
            // Assume $response->json() contains an associative array
            return view('dashboard', ['response' => $response->json()]);
        }

        return response()->json([
            'message' => 'Login failed',
            'error' => $response->json()
        ], $response->status());
    }
}
