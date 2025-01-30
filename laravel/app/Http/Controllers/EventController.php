<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Http;

class EventController extends Controller
{
    public function index(Request $request)
    {
        // Get date from query parameters or use today's date as default
        $date = $request->query('date', now()->toDateString());

        // Call the external API
        $response = Http::get('http://localhost:7000/api/v1/events', [
            'date' => $date,
        ]);

        // Check for errors
        if ($response->failed()) {
            return view('events', ['error' => 'Failed to fetch events', 'date' => $date]);
        }

        // Decode response
        $events = $response->json()['events'] ?? [];

        return view('events', compact('events', 'date'));
    }
    // Method to fetch events from Flask API
    // public function getEvents(Request $request)
    // {
    //     // Get the date parameter from the query string
    //     $date = $request->query('date');
    //     
    //     if (!$date) {
    //         return response()->json(['error' => 'Missing date parameter'], 400);
    //     }
// 
    //     // Send a GET request to Flask API
    //     $response = Http::get("http://localhost:8080/api/v1/events", [
    //         'date' => $date
    //     ]);
// 
    //     // Check if the response was successful
    //     if ($response->successful()) {
    //         $events = $response->json()['events']; // Get the events from the response
    //         return view('events.index', compact('events'));
    //     } else {
    //         return view('events.index', ['error' => 'Failed to fetch events from the API']);
    //     }
    // }
}
