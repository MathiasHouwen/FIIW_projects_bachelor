<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Http;

class EventController extends Controller
{
    // Method to fetch events from Flask API
    public function getEvents(Request $request)
    {
        // Get the date parameter from the query string
        $date = $request->query('date');
        
        if (!$date) {
            return response()->json(['error' => 'Missing date parameter'], 400);
        }

        // Send a GET request to Flask API
        $response = Http::get("http://localhost:8080/api/v1/events", [
            'date' => $date
        ]);

        // Check if the response was successful
        if ($response->successful()) {
            $events = $response->json()['events']; // Get the events from the response
            return view('events.index', compact('events'));
        } else {
            return view('events.index', ['error' => 'Failed to fetch events from the API']);
        }
    }
}
