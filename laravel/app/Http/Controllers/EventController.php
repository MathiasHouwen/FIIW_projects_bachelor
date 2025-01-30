<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Http;
use Illuminate\Support\Facades\Log;

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

        foreach ($events as &$event) {

            Log::debug('Event: ', $event);
            // Call the rating API for each event (assume it's based on event name)
            $ratingResponse = Http::get('http://localhost:7070/event', [
                'name' => $event['title'],
            ]);

            // If rating API is successful, add the rating to the event
            if ($ratingResponse->successful()) {
                $rating = $ratingResponse->json()['rating'] ?? 'No rating';
                $event['rating'] = $rating;
            } else {
                $event['rating'] = 'Failed to fetch rating';
            }
        }

        return view('events', compact('events', 'date'));
    }
}
